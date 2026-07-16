#include "gc.h"
#include "mystring.h"

void mark(String *str) {
  if (str->marked) {
    return;
  }
  str->marked = 1;
}

// void markAll(VM *vm) {
//   for (u64 i = 0; i < vm->rootsCount; i++) {
//     mark(vm->roots[i]);
//   }
// }
