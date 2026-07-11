#include "mystring.h"
#include "arena.h"
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

int ensureCapacity(Arena *arena, String *str, u64 size) {
  if (!arena || !str) {
    return -1;
  }

  if (str->capacity >= size) {
    return 1;
  }
  return 1;
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
    str->data[len] = (char)ch;
    ch = getchar();
    len++;
  }
  str->length = len;
  return 0;
}

void printStringToTerm(String *str) {
  for (u64 i = 0; i < str->length; i++) {
    printf("%c", str->data[i]);
  }
  printf("\n");
}
