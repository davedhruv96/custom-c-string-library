#ifndef MYSTRING_H
#define MYSTRING_H

#include "stringlib.h"
#include "types.h"
#include "vm.h"

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

int getString(StringHandle h);

void printStringToTerm(String *str);

void copyString(StringHandle h1, StringHandle h2);

void copystr_char(const char *copyFrom, String *copyTo);

void unmark(String *str);

#endif
