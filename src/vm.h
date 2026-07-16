#ifndef VM_H
#define VM_H

#include "stringlib.h"
#include "types.h"

typedef struct VM VM;
typedef struct String String;
typedef struct Arena Arena;
typedef u32 StringHandle;

VM *createVM(u64 arenaSize);

void destroyVM(VM *vm);

u32 push(String *str);

String *pop(VM *vm);

Arena *getArena();

b8 isValidIndex(u32 index);

String **getRoots();

void removeFromStack(StringHandle strToRemove);

#endif
