#ifndef MYSTRING_H
#define MYSTRING_H

#include "gc.h"

String *createString(Arena *arena, u64 initialSize);

String *reallocString(Arena *arena, String *str);

int getString(String *str);

void printStringToTerm(String *str);

#endif
