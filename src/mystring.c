#include "mystring.h"
#include "arena.h"
#include "vm.h"
#include <stdio.h>
#include <stdlib.h>

String *createString(Arena *arena, u64 initialSize) {
  if (!arena) {
    return NULL;
  }
  u64 offset = 0;
  String *str = arenaPush(arena, sizeof(String), &offset);
  str->data = arenaPushWithoutOffset(arena, initialSize);
  // actual character buffer
  str->offsetInArena = offset;
  if (!str || !str->data) {
    return NULL;
  }

  str->capacity = initialSize;
  str->data[0] = '\0';
  str->length = 1;

  return str;
}

b8 shouldGrow(String *str, u64 neededSize) {
  if (!str) {
    return 0;
  }
  return str->capacity < neededSize;
}

void copyStringAfterGrowing(StringHandle h, String *newString) {
  if (!isValidIndex(h) || !newString) {
    return;
  }
  String **roots = getRoots();
  if (!roots)
    return;
  String *copyFrom = roots[h];
  for (u32 i = 0; i < copyFrom->length; i++) {
    newString->data[i] = copyFrom->data[i];
    newString->length++;
  }
}

void growString(StringHandle h, u64 minCapacity) {
  if (!isValidIndex(h)) {
    return;
  }
  String **roots = getRoots();
  if (!roots)
    return;
  String *newstr = createString(getArena(), minCapacity * 2);
  copyStringAfterGrowing(h, newstr);
  roots[h] = newstr;
  return;
}

int getString(StringHandle h) {
  if (!isValidIndex(h)) {
    return -1;
  }
  String **roots = getRoots();
  if (!roots)
    return -1;
  String *string = roots[h];
  string->length = 0;
  u64 len = 0;
  int ch = getchar();
  while (ch == '\n') {
    ch = getchar();
  }
  while ((ch != (int)'\n') && (ch != EOF)) {
    if (shouldGrow(string,
                   len + 1)) { // note to self: neededSize should be changed
      growString(h, len + 1);
      string = roots[h];
    }
    string->data[len] = (char)ch;
    ch = getchar();
    len++;
  }
  string->length = len;
  string->data[len] = '\0';
  return 0;
}

void printStringToTerm(String *str) { // temporary debugging function
  for (u64 i = 0; i < str->length; i++) {
    printf("%c", str->data[i]);
  }
  printf("\n");
}

// overwrites "copyTo" string
void copyString(StringHandle h1, StringHandle h2) {
  if (!isValidIndex(h1) || !isValidIndex(h2)) {
    return;
  }
  String **roots = getRoots();
  if (!roots)
    return;

  String *copyFrom = roots[h1];
  String *copyTo = roots[h2];

  for (u32 i = 0; i < copyFrom->length; i++) {
    if (shouldGrow(copyTo, copyTo->length)) {
      growString(h2, copyTo->length);
    }
    copyTo->data[i] = copyFrom->data[i];
    copyTo->length++;
  }
}

void copystr_char(const char *copyFrom, StringHandle h) {
  if (!copyFrom || !isValidIndex(h)) {
    return;
  }

  String **roots = getRoots();
  if (!roots) {
    return;
  }

  String *copyTo = roots[h];
  copyTo->length = 0;
  int i = 0;
  for (i = 0; copyFrom[i] != '\0'; i++) {
    if (shouldGrow(copyTo, i + 1)) {
      growString(h, i + 1);
      copyTo = roots[h];
    }
    copyTo->data[i] = copyFrom[i];
    copyTo->length++;
  }
  copyTo->data[i] = '\0';
}

void unmark(String *str) {
  if (!str) {
    return;
  }
  str->marked = 0;
}

void copystr_compact(String *copyFrom, String *copyTo) {
  if (!copyFrom || !copyTo) {
    return;
  }
  u64 i;
  for (i = 0; i < copyFrom->length; i++) {
    copyTo->data[i] = copyFrom->data[i];
    copyTo->length++;
  }
  copyTo->data[i] = '\0';
}
