#include "include/stringlib.h"
#include "src/types.h"
#include "src/vm.h"
#include <stdio.h>
#include <stdlib.h>

static char ch = 'a';

void strconcat(char *s) {
  int len = 0;
  for (int i = 0; s[i] != '\0'; i++) {
    len++;
  }
  s[len] = ch;
  ch++;
  s[len + 1] = '\0';
}

int main(void) {
  sl_init(MiB(4));
  StringHandle h[100];
  char *s = calloc(sizeof(char), 100);
  for (int i = 0; i < 25; i++) {
    strconcat(s);
    h[i] = sl_create_with_capacity(s, 10);
    printf("%d = %s\n", i, sl_cstr(h[i]));
  }
  for (int i = 1; i < 25; i += 2) {
    sl_destroy(h[i]);
  }
  for (int i = 0; i < 25; i++) {
    char *str = sl_cstr(h[i]);
    if (str) {
      printf("%d: %s\n", i, str);
    }
  }
  gc();
  sl_shutdown();
  return 0;
}
