// #include "gc.h"
// #include "mystring.h"
// #include <stdlib.h>
//
// void push(VM *vm, String *str) {
//   if (!vm || !str) {
//     return;
//   }
//
//   // if(vm->numObjects >= vm->maxObjects){
//   //
//   // }
//   // vm->roots[vm->rootsCount++] = str;
// }
//
// String *pop(VM *vm) {
//   if (!vm) {
//     return NULL;
//   }
//
//   if (vm->rootsCount <= 0) {
//     return NULL;
//   }
//   return vm->roots[--vm->rootsCount];
//   // the string will be there in arena,
//   // but next sweep or push will overwrite
//   // it, no need to bother
// }
//
// void mark(String *str) {
//   if (str->marked) {
//     return;
//   }
//   str->marked = 1;
// }
//
// void markAll(VM *vm) {
//   for (u64 i = 0; i < vm->rootsCount; i++) {
//     mark(vm->roots[i]);
//   }
// }
