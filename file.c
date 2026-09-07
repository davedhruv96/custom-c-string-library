#include "src/types.h"
#include "stringlib.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  sl_init(MiB(1));
  FILE *fptr;
  char *fname = malloc(sizeof(char) * 100);
  printf("Enter file name: ");
  scanf("%s", fname);

  fptr = fopen("test_file.txt", "rw+");

  fclose(fptr);
  free(fname);
  sl_shutdown();
  return 0;
}
