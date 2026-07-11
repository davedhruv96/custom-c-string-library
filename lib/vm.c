#include "vm.h"
#include "arena.h"
#include "gc.h"
#include "mystring.h"
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
