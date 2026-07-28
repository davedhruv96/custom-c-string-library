#include "gc.h"
#include "arena.h"
#include "mystring.h"
#include "vm.h"

b8 gc_should_run() {
  Arena *arena = getArena();
  if (!arena)
    return 0;

  if (arena_needs_mem(arena)) {
    return 1;
  }
  return 0;
}
//
// void gc() {
//   markall();
//   compact();
// }
