#ifndef GC_H
#define GC_H

#include "def.h"

typedef struct {
  char *data;
  u64 length;
  u64 capacity;
} String;

typedef struct sObject {
  unsigned char marked;
  String str;
  struct sObject *next;
} Object;

typedef struct VM VM;

VM *vmCreate();

void vmDestroy(VM *vm);

#endif
