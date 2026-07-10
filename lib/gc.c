#include "gc.h"
#include "arena.h"
#include "def.h"
#include "mystring.h"
#include <stdlib.h>

struct VM {
  Object *firstObject;
  Arena *arena;
  Object **objects;
  u64 numObjects;
  u64 maxObjects;
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
  vm->objects = getPtrToBuffer(arena) + sizeof(VM);
  vm->firstObject = NULL;
  vm->numObjects = 0;
  vm->maxObjects = 24;

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
    free(arena);
  }
}

Object *newObject(VM *vm) {
  if (!vm) {
    return NULL;
  }

  // if (vm->numObjects >= vm->maxObjects) {
  //   arenaPush(vm->arena, (u64)sizeof(Object) * vm->numObjects);
  //   vm->maxObjects = vm->numObjects * 2;
  // }
  u64 offsetInArena;
  Object *object = arenaPushObject(vm->arena, sizeof(Object), &offsetInArena);
  object->offsetInArena = offsetInArena;
  object->marked = 0;
  object->next = NULL;
  object->str = createString(vm->arena, 10);
  vm->objects[vm->numObjects] = object;
  object->next = vm->firstObject;
  vm->firstObject = object;

  return object;
}

void push(VM *vm, Object *object) {
  if (!vm || !object) {
    return;
  }

  // if(vm->numObjects >= vm->maxObjects){
  //
  // }
  vm->objects[vm->numObjects++] = object;
}

Object *pop(VM *vm) {
  if (!vm) {
    return NULL;
  }

  if (vm->numObjects <= 0) {
    return NULL;
  }
  return vm->objects[--vm->numObjects]; // the object will be there in arena,
                                        // but next sweep or push will overwrite
                                        // it no need to bother
}

void mark(Object *object) {
  if (object->marked) {
    return;
  }
  object->marked = 1;
}

void markAll(VM *vm) {
  for (u64 i = 0; i < vm->numObjects; i++) {
    mark(vm->objects[i]);
  }
}
