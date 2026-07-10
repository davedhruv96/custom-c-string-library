#include "def.h"
#include "gc.h"
#include "mystring.h"
#include <stdio.h>

int main() {
  printf("Hello And Welcome to SUPER STRING!\n");

  VM *vm = createVM(MiB(1));
  Object *ob1 = newObject(vm);
  printf("Enter string: ");
  getString(ob1->str);
  push(vm, ob1);
  destroyVM(vm);

  return 0;
}
