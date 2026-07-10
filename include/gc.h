#ifndef GC_H
#define GC_H

#include "def.h"

typedef struct {
  char *data;
  u64 length;
  u64 capacity;
} String;

typedef struct sObject {
  b8 marked;
  String *str;
  u64 offsetInArena;
  struct sObject *next;
} Object;

typedef struct VM VM;

VM *createVM(u64 arenaSize);

void destroyVM(VM *vm);

Object *newObject(VM *vm);

void push(VM *vm, Object *object);

Object *pop(VM *vm);

void mark(Object *object);

void markAll(VM *vm);

#endif
