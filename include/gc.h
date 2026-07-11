#ifndef GC_H
#define GC_H

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

void push(VM *vm, String *str);

String *pop(VM *vm);

void mark(String *str);

void markAll(VM *vm);

#endif
