#include "include/stringlib.h"
#include "src/types.h"
#include "src/vm.h"
#include <stdio.h>

int main(void) {
  sl_init(KiB(2));

  StringHandle h[40];
  for (int i = 0; i < 40; i++) {
    h[i] = sl_create_with_capacity("Hello world", 12);
  }

  for (int i = 0; i < 40; i++) {
    printf("%d: ", i);
    sl_print(h[i]);
  }

  for (int i = 1; i < 40; i += 2) {
    sl_destroy(h[i]);
  }

  for (int i = 0; i < 40; i++) {
    printf("%d: ", i);
    sl_print(h[i]);
  }
  gc();

  for (int i = 1; i < 40; i += 2) {
    h[i] = sl_create_with_capacity("Hello world", 12);
  }

  for (int i = 0; i < 40; i++) {
    printf("%d: ", i);
    sl_print(h[i]);
  }
  sl_shutdown();
  return 0;
}
