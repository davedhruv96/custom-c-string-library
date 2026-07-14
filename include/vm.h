#ifndef VM_H
#define VM_H

#include "types.h"

typedef struct VM VM;
typedef struct String String;
typedef struct Arena Arena;

VM *createVM(u64 arenaSize);

void destroyVM(VM *vm);

u64 push(VM *vm, String *str);

String *pop(VM *vm);

Arena *getArena(VM *vm);

b8 isValidIndex(VM *vm, u64 index);

String **getRoots(VM *vm);

#endif
