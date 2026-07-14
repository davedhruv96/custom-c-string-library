#include "arena.h"
#include "mystring.h"
#include "types.h"
#include "vm.h"

u64 newString(VM *vm, u64 initialSize) {
  if (!vm) {
    return -1;
  }
  String *str = createString(getArena(vm), initialSize);
  return push(vm, str);
}

void getstr(VM *vm, int indexOString) {
  if (!vm || !isValidIndex(vm, indexOString)) {
    return;
  }
  String **temp = getRoots(vm);
  if (temp) {
    getString(temp[indexOString]);
  }
}

void printstr(VM *vm, int indexOString) {
  if (!vm || !isValidIndex(vm, indexOString)) {
    return;
  }
  String **temp = getRoots(vm);
  if (temp) {
    printStringToTerm(temp[indexOString]);
  }
}
