#include "mystring.h"
#include "arena.h"
#include "vm.h"
#include <stdio.h>
#include <stdlib.h>

String *createString(Arena *arena, u64 initialSize) {
  if (!arena) {
    return NULL;
  }
  String *str = arenaPush(arena, sizeof(String));
  str->data = arenaPush(arena, initialSize);
  // actual character buffer

  if (!str || !str->data) {
    return NULL;
  }

  str->capacity = initialSize;
  str->data[0] = '\0';
  str->length = 0;

  return str;
}

// will be only used by current file, therefore no need to declare it in header
// file
String *ensureCapacity(String *str, u64 size) {
  if (!str) {
    return NULL;
  }

  if (str->capacity > size) {
    return str;
  }
  String *newstr = createString(getArena(), size * 2);
  copystr(str, newstr);
  unmark(str);
  return newstr;
}

int getString(String *str) {
  if (!str) {
    return -1;
  }
  u64 len = 0;
  int ch = getchar();
  while (ch == '\n') {
    ch = getchar();
  }
  while ((ch != (int)'\n') && (ch != EOF)) {
    if (str->size <= len + 1 + str->length) {
      str = ensureCapacity(str, len + 1);
    }
    str->data[len] = (char)ch;
    ch = getchar();
    len++;
  }
  str->length = len;
  str->data[len] = '\0';
  return 0;
}

void printStringToTerm(String *str) {
  for (u64 i = 0; i < str->length; i++) {
    printf("%c", str->data[i]);
  }
  printf("\n");
}

// overwrites "copyTo" string
void copystr(String *copyFrom, String *copyTo) {
  if (!copyFrom || !copyTo) {
    return;
  }
  copyTo->length = 0;
  for (u32 i = 0; i < copyFrom->length; i++) {
    if (copyTo->capacity < i + 1) {
      copyTo = ensureCapacity(copyTo, copyTo->capacity * 2);
    }
    copyTo->data[i] = copyFrom->data[i];
    copyTo->length++;
  }
}

void copystr_char(const char *copyFrom, String *copyTo) {
  if (!copyFrom || !copyTo) {
    return;
  }
  copyTo->length = 0;
  int i = 0;
  for (i = 0; copyFrom[i] != '\0'; i++) {
    copyTo = ensureCapacity(copyTo, i + 1);
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
