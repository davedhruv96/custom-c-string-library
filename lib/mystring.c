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
  if (!str) {
    return NULL;
  }

  str->capacity = initialSize;
  str->data[0] = '\0';
  str->length = 0;

  return str;
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
  while ((ch != (int)'\n' || ch != EOF) && str->capacity > len - 1) {
    str->data[len] = (char)ch;
    ch = getchar();
    len++;
  }
  str->length = len;
  return 0;
}
