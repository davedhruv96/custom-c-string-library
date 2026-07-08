#include "gc.h"
#include <stdio.h>
#include <stdlib.h>

struct VM {
  Object *firstObject;
  Object *stack[STACK_MAX];
  int stackSize;
  int numObjects;
  int GCThreshold;
};

void assert(int condition, char *message) {

  if (!condition) {
    printf("%s\n", message);
    exit(1);
  }
}

VM *newVM() {
  VM *vm = malloc(sizeof(VM));
  vm->stackSize = 0;
  vm->firstObject = NULL;
  vm->numObjects = 0;
  vm->GCThreshold = INITIAL_GC_THRESHOLD;

  return vm;
}

void push(VM *vm, Object *object) {
  assert(vm->stackSize < STACK_MAX,
         "Stack Overflow"); // temporary error handling through assert.h
  vm->stack[vm->stackSize++] = object;
}

Object *pop(VM *vm) {
  assert(vm->stackSize > 0,
         "Stack Underflow"); // temporary error handling through assert.h
  return vm->stack[--vm->stackSize];
}

Object *newObject(VM *vm, ObjectType type) {
  if (vm->numObjects >= vm->GCThreshold) {
    gc(vm);
  }

  Object *object = malloc(sizeof(Object));
  object->type = type;
  object->marked = 0;

  object->next = vm->firstObject;
  vm->firstObject = object;
  vm->numObjects++;

  return object;
}

void pushInt(VM *vm, int valToPush) {
  Object *object = newObject(vm, OBG_INT);
  object->value = valToPush;
  push(vm, object);
}

Object *pushPair(VM *vm) {
  Object *object = newObject(vm, OBG_PAIR);
  object->tail = pop(vm);
  object->head = pop(vm);

  push(vm, object);
  return object;
}

void mark(Object *object) {
  if (object->marked)
    return;
  object->marked = 1;
  if (object->type == OBG_PAIR) {
    mark(object->head);
    mark(object->tail);
  }
}

void markAll(VM *vm) {
  for (int i = 0; i < vm->stackSize; i++) {
    mark(vm->stack[i]);
  }
}

void sweep(VM *vm) {
  Object **object = &vm->firstObject;
  Object *unreached;
  while (*object) {
    if (!(*object)->marked) {
      unreached = *object;
      *object = (*object)->next;

      vm->numObjects++;
      free(unreached);
    } else {
      (*object)->marked = 0;
      object = &((*object)->next);
    }
  }
}

void gc(VM *vm) {
  markAll(vm);
  sweep(vm);

  vm->GCThreshold = vm->numObjects * 2;
}

void freeVM(VM *vm) {
  gc(vm);

  for (int i = 0; i < vm->stackSize; i++) {
    if (vm->stack[i]->type == OBG_INT) {
      free(vm->stack[i]);
    } else {
      free(vm->stack[i]->head);
      free(vm->stack[i]->tail);
    }
  }
  free(vm);
}

void test1() {
  printf("Test 1: Objects on stack are preserved.\n");
  VM *vm = newVM();
  pushInt(vm, 1);
  pushInt(vm, 2);

  gc(vm);
  assert(vm->numObjects == 2, "Should have preserved objects.");
  freeVM(vm);
}

void test2() {
  printf("Test 2: Unreached objects are collected.\n");
  VM *vm = newVM();
  pushInt(vm, 1);
  pushInt(vm, 2);
  pop(vm);
  pop(vm);

  gc(vm);
  assert(vm->numObjects == 0, "Should have collected objects.");
  freeVM(vm);
}

void test3() {
  printf("Test 3: Reach nested objects.\n");
  VM *vm = newVM();
  pushInt(vm, 1);
  pushInt(vm, 2);
  pushPair(vm);
  pushInt(vm, 3);
  pushInt(vm, 4);
  pushPair(vm);
  pushPair(vm);

  gc(vm);
  assert(vm->numObjects == 7, "Should have reached objects.");
  freeVM(vm);
}

void test4() {
  printf("Test 4: Handle cycles.\n");
  VM *vm = newVM();
  pushInt(vm, 1);
  pushInt(vm, 2);
  Object *a = pushPair(vm);
  pushInt(vm, 3);
  pushInt(vm, 4);
  Object *b = pushPair(vm);

  /* Set up a cycle, and also make 2 and 4 unreachable and collectible. */
  a->tail = b;
  b->tail = a;

  gc(vm);
  assert(vm->numObjects == 4, "Should have collected objects.");
  freeVM(vm);
}

void perftest() {
  printf("Performance Test.\n");
  VM *vm = newVM();

  for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < 20; j++) {
      pushInt(vm, i);
    }

    for (int k = 0; k < 20; k++) {
      pop(vm);
    }
  }
  freeVM(vm);
}
