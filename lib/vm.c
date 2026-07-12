#include "vm.h"
#include "arena.h"
#include "gc.h"
#include <stdlib.h>

struct VM {
  Arena *arena;

  String *firstString;
  String **roots;
  u64 rootsCount;
  u64 rootsCapacity;
};

VM *createVM(u64 arenaSize) {
  Arena *arena = arenaCreate(arenaSize);
  if (!arena) {
    exit(-1);
  }

  VM *vm = (VM *)arenaPush(arena, (u64)sizeof(VM));
  if (!vm) {
    exit(-1);
  }

  vm->arena = arena;
  vm->roots = getPtrToBuffer(arena) + sizeof(VM);
  // strings will allocate after VM is allocated on the arena,
  // so the starting point is Buffer + size(VM)

  vm->firstString = NULL;
  vm->rootsCount = 0;
  vm->rootsCapacity = 24;

  return vm;
}

void destroyVM(VM *vm) {
  if (!vm) {
    return;
  }

  if (vm->arena) {
    Arena *arena = vm->arena;
    arenaClear(vm->arena);
    arenaDestroy(vm->arena);
    // frees the arena buffer, not arena

    free(arena);
  }
}

void push(VM *vm, String *str) {
  if (!vm || !str) {
    return;
  }

  // if(vm->numObjects >= vm->maxObjects){
  //
  // }
  vm->roots[vm->rootsCount++] = str;
}

String *pop(VM *vm) {
  if (!vm) {
    return NULL;
  }

  if (vm->rootsCount <= 0) {
    return NULL;
  }
  return vm->roots[--vm->rootsCount];
  // the string will be there in arena,
  // but next sweep or push will overwrite
  // it, no need to bother
}
