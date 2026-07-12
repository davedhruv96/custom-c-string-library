#ifndef MYSTRING_H
#define MYSTRING_H

#include "types.h"

typedef struct String {
  u64 size;
  b8 marked;
  u64 offsetInArena;
  struct String *next;
  u64 length;
  u64 capacity;
  char *data;
} String;

typedef struct VM VM;
typedef struct Arena Arena;

String *createString(Arena *arena, u64 initialSize);

String *reallocString(Arena *arena, String *str);

int getString(String *str);

void printStringToTerm(String *str);

#endif
