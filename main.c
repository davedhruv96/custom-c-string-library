#include "include/stringlib.h"
#include "src/types.h"
#include "src/vm.h"
#include <stdio.h>

int main(void) {
  sl_init(MiB(2));
  StringHandle h[100];
  int n;
  printf("Enter number (max: 100) of strings: ");
  scanf("%d", &n);
  char s[100];
  for (int i = 0; i < (n < 101 ? n : 100); i++) {
    printf("Enter string: ");
    scanf("%s", s);
    h[i] = sl_create_with_capacity(s, 10);
  }
  for (int i = 0; i < (n < 101 ? n : 100); i++) {
    printf("%s\n", sl_cstr(h[i]));
  }
  gc();
  for (int i = 0; i < (n < 101 ? n : 100); i++) {
    printf("%s\n", sl_cstr(h[i]));
  }
  sl_shutdown();
  return 0;
}
