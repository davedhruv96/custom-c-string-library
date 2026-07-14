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
String *ensureCapacity(VM *vm, String *str, u64 size) {
  if (!str) {
    return NULL;
  }

  if (str->capacity >= size) {
    return str;
  }
  String *newstr = createString(getArena(vm), size);
  copystr(vm, str, newstr);
  return newstr;
}

int getString(VM *vm, String *str) {
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
      str = ensureCapacity(vm, str, len + 1);
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
void copystr(VM *vm, String *copyFrom, String *copyTo) {
  if (!vm || !copyFrom || !copyTo) {
    return;
  }

  for (int i = 0; i < copyFrom->length; i++) {
    if (copyTo->capacity < i + 1) {
      copyTo = ensureCapacity(vm, copyTo, copyTo->capacity * 2);
    }
    copyTo->data[i] = copyFrom->data[i];
    copyTo->length++;
  }
}
