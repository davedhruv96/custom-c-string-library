#include "vm.h"
#include "arena.h"
#include "gc.h"
#include "mystring.h"
#include "stringlib.h"
#include "types.h"
#include <complex.h>
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
    return 1;
  }

  g_vm = createVM(memSize);
  return 0;
}

void destroyVM() {
  if (g_vm->arena) {
    Arena *arena = g_vm->arena;

    free(g_vm->roots);

    arenaClear(g_vm->arena);
    arenaDestroy(g_vm->arena);
    // frees the arena buffer, not arena

    free(arena);
  }
}

void sl_shutdown(void) {
  if (g_vm) {
    destroyVM();
    g_vm = NULL;
  }
}

VM *createVM(u64 arenaSize) {
  Arena *arena = arenaCreate(arenaSize);
  if (!arena) {
    exit(-1);
  }
  VM *vm = (VM *)arenaPushWithoutOffset(arena, (u64)sizeof(VM));
  if (!vm) {
    exit(-1);
  }

  vm->arena = arena;

  vm->roots = malloc(sizeof(void *) * 24);

  vm->firstString = NULL;
  vm->rootsCount = 0;
  vm->rootsCapacity = 24;

  return vm;
}

u32 push(String *str) {
  if (!g_vm || !str) {
    return -1;
  }

  if (g_vm->rootsCount >= g_vm->rootsCapacity) {
    if (gc_should_run()) {
      gc();
    } else {
      g_vm->rootsCapacity *= 2;
      g_vm->roots = realloc(g_vm->roots, sizeof(void *) * g_vm->rootsCapacity);
    }
  }

  g_vm->roots[g_vm->rootsCount++] = str;
  return g_vm->rootsCount - 1;
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
  if (!g_vm) {
    exit(-1);
  }

  u64 position = sizeof(VM);
  for (u64 i = 0; i < g_vm->rootsCount; i++) {
    if (g_vm->roots[i] != NULL && position != g_vm->roots[i]->offsetInArena) {
      g_vm->roots[i] = compact(g_vm->arena, g_vm->roots[i], &position);
    } else if (g_vm->roots[i] && position == g_vm->roots[i]->offsetInArena) {
      position += g_vm->roots[i]->capacity + sizeof(String);
    }
  }
  setBottomToPos(g_vm->arena, position);
}

void link_string(String *str) {
  if (!str) {
    return;
  }

  str->next = g_vm->firstString;
  g_vm->firstString = str;
}
