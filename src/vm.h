#ifndef VM_H
#define VM_H

#include "stringlib.h"
#include "types.h"

typedef struct VM VM;
typedef struct String String;
typedef struct Arena Arena;
typedef u32 StringHandle;

VM *createVM(u64 arenaSize);

u32 push(String *str);

Arena *getArena();

b8 isValidIndex(u32 index);

String **getRoots();

void removeFromStack(StringHandle strToRemove);

void markall();

void gc();

void link_string(String *str);

#endif
