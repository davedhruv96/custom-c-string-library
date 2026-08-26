#include "include/stringlib.h"
#include "src/types.h"
#include "src/vm.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  sl_init(MiB(40));

  StringHandle h = sl_create("Hello World");
  StringHandle h1 = sl_create("Hiii");
  sl_destroy(h);

  gc();
  sl_print(h);
  sl_print(h1);
  sl_destroy(h1);

  gc();
  sl_print(h);
  sl_print(h1);

  sl_shutdown();
  return 0;
}
