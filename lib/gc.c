#include "gc.h"
#include "arena.h"
#include "def.h"
#include <stdlib.h>

struct VM {
  Object *firstObject;
  Arena *arena;
  Object **objects;
  u64 numObjects;
  u64 maxObjects;
};

VM *vmCreate() {
  Arena *arena = arenaCreate(arena, MiB(1));
  if (!arena) {
    exit(-1);
  }

  VM *vm = (VM *)arenaPush(arena, (u64)sizeof(VM));
  if (!vm) {
    exit(-1);
  }

  vm->arena = arena;

  vm->objects = (Object **)arenaPush(arena, (u64)sizeof(Object) * 24);
  vm->firstObject = NULL;
  vm->numObjects = 0;
  vm->maxObjects = 24;

  return vm;
}

void vmDestroy(VM *vm) {
  if (!vm) {
    return;
  }

  if (vm->arena) {
    arenaClear(vm->arena);
    arenaDestroy(vm->arena);
  }
}

void newObject(VM *vm, String *str) {
  if (!vm || !str) {
    return;
  }

  if (vm->numObjects >= vm->maxObjects) {
    arenaPush(vm->arena, (u64)sizeof(Object) * vm->numObjects);
    vm->maxObjects = vm->numObjects * 2;
  }
  if (!vm->firstObject) {
    vm->firstObject = object;
  }
}
