#include "include/stringlib.h"
#include "src/types.h"
#include <stdio.h>

int main(void) {
  sl_init(MiB(1));
  StringHandle h = sl_create_with_capacity("Hello is This Working or not!", 5);
  printf("%s\n", sl_cstr(h));
  sl_shutdown();
  return 0;
}
