#include "vm.h"
#include "arena.h"
#include "gc.h"
#include "mystring.h"
#include "stringlib.h"
#include "types.h"
#include <stdlib.h>
#include <strings.h>

struct VM {
  Arena *arena;

  String *firstString;
  String **roots;
  u32 rootsCount;
  u32 rootsCapacity;
};

static VM *g_vm = NULL;

b8 sl_init(u64 memSize) {
  if (g_vm) {
    return 0;
  }
  g_vm = createVM(memSize);
  return 1;
}

void sl_shutdown(void) {
  if (g_vm) {
    destroyVM(g_vm);
    g_vm = NULL;
  }
}

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

u32 push(String *str) {
  if (!g_vm || !str) {
    return -1;
  }

  // if(vm->numObjects >= vm->maxObjects){
  //
  // }
  g_vm->roots[g_vm->rootsCount++] = str;
  return g_vm->rootsCount - 1;
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

Arena *getArena() {
  if (!g_vm) {
    return NULL;
  }

  return g_vm->arena;
}

b8 isValidIndex(u32 index) {
  if (index < g_vm->rootsCount) {
    return 1;
  }
  return 0;
}

String **getRoots() {
  if (g_vm) {
    return g_vm->roots;
  }
  return NULL;
}

void removeFromStack(StringHandle indexToRm) {
  if (!isValidIndex(indexToRm)) {
    return;
  }

  unmark(g_vm->roots[indexToRm]);
  g_vm->roots[indexToRm] = NULL;
}

void markall() {
  for (u32 i = 0; i < g_vm->rootsCount; i++) {
    if (!g_vm->roots[i]) {
      continue;
    }
    g_vm->roots[i]->marked = 1;
  }
}

void gc() {
  String **string = &g_vm->firstString;
  String *unreached;
  while (*string) {
    if (!(*string)->marked) {
      unreached = *string;
      *string = (*string)->next;
      compact(unreached->capacity, unreached->offsetInArena);
    } else {
      (*string)->marked = 0;
      string = &(*string)->next;
    }
  }
}

void link_string(String *str) {
  if (!str) {
    return;
  }

  str->next = g_vm->firstString;
  g_vm->firstString = str;
}
