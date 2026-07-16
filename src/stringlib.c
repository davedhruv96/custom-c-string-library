#include "../include/stringlib.h"
#include "mystring.h"
#include "vm.h"
#include <stdlib.h>

StringHandle sl_create_with_capacity(const char *s, u32 initial_size) {
  String *str = createString(getArena(), initial_size);
  StringHandle h = push(str);
  copyTo(s, h);
  return h;
}

StringHandle sl_create(const char *string) {
  String *str = createString(getArena(), 100);
  StringHandle h = push(str);
  copyTo(string, h);
  return h;
}

void copyTo(const char *copy_from, StringHandle copy_to) {
  String **roots = getRoots();
  if (!roots || !isValidIndex(copy_to)) {
    return;
  }
  copystr_char(copy_from, roots[copy_to]);
}

const char *sl_cstr(StringHandle h) {
  String **roots = getRoots();
  if (!roots || !isValidIndex(h)) {
    return NULL;
  }
  return roots[h]->data;
}

void sl_destroy(StringHandle *to_destroy) {
  if (!isValidIndex(*to_destroy)) {
    return;
  }

  removeFromStack(*to_destroy);
  *to_destroy = -1;
}
