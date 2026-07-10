#ifndef MYSTRING_H
#define MYSTRING_H

#include "gc.h"

String *createString(Arena *arena, u64 initialSize);

int getString(String *str);

#endif
