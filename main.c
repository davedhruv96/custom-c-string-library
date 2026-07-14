#include "gc.h"
#include "mystring.h"
#include "strlib.h"
#include "types.h"
#include "vm.h"
#include <stdio.h>

int main() {
  printf("Hello And Welcome to SUPER STRING!\n");

  VM *vm = createVM(MiB(1));

  u64 index = newString(vm, 10);
  printf("Enter the string : ");
  getstr(vm, index);
  printstr(vm, index);

  destroyVM(vm);
  return 0;
}
