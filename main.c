#include "include/stringlib.h"
#include "src/types.h"
#include "src/vm.h"

int main(void) {
  sl_init(MiB(4));

  StringHandle h1 = sl_create_with_capacity("Hello World", 10);
  StringHandle h2 = sl_create_with_capacity("Hiii", 10);
  StringHandle h3 = sl_create_with_capacity("Heyooo", 10);
  sl_print(h1);
  sl_print(h2);
  sl_print(h3);

  sl_destroy(h1);

  gc();
  sl_print(h1);
  sl_print(h2);
  sl_print(h3);

  sl_destroy(h3);

  gc();
  sl_print(h1);
  sl_print(h2);
  sl_print(h3);

  sl_destroy(h2);
  sl_print(h1);
  sl_print(h2);
  sl_print(h3);

  sl_shutdown();
  return 0;
}
