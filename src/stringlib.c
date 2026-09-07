#include "../include/stringlib.h"
#include "gc.h"
#include "mystring.h"
#include "vm.h"
#include <stdio.h>
#include <stdlib.h>

StringHandle sl_create_with_capacity(const char *s, u64 initial_size) {
  String *str = createString(getArena(), initial_size);
  StringHandle h = push(str);
  link_string(str);
  copyTo(s, h);
  return h;
}

StringHandle sl_create(const char *string) {
  String *str = createString(getArena(), 100);
  StringHandle h = push(str);
  link_string(str);
  copyTo(string, h);
  return h;
}

void copyTo(const char *copy_from, StringHandle copy_to) {
  String **roots = getRoots();
  if (!roots || !isValidIndex(copy_to)) {
    return;
  }
  copystr_char(copy_from, copy_to);
}

void sl_concat(StringHandle concatTo, StringHandle concat) {
  if (!isValidIndex(concat) || !isValidIndex(concatTo)) {
    return;
  }
}

const char *sl_cstr(StringHandle h) {
  String **roots = getRoots();
  if (!roots || !isValidIndex(h) || !roots[h]) {
    return NULL;
  }
  return roots[h]->data;
}

void sl_destroy(StringHandle to_destroy) {
  if (!isValidIndex(to_destroy)) {
    return;
  }

  removeFromStack(to_destroy);
}

void sl_print(StringHandle h) {
  String **roots = getRoots();
  if (!roots || !isValidIndex(h)) {
    printf("Invalid Handle\n");
    return;
  }

  const char *str = sl_cstr(h);
  printf("%s\n", str ? str : "(null)");
}
