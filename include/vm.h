#ifndef VM_H
#define VM_H

#include "types.h"

typedef struct VM VM;
typedef struct String String;
typedef struct Arena Arena;

VM *createVM(u64 arenaSize);

void destroyVM(VM *vm);

void push(VM *vm, String *str);

String *pop(VM *vm);

#endif
