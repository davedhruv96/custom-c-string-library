#ifndef STRLIB_C
#define STRLIB_C

#include "types.h"

typedef struct VM VM;
typedef struct String String;

u64 newString(VM *vm, u64 initialSize);

void getstr(VM *vm, int indexOString);

void printstr(VM *vm, int indexOString);

#endif
