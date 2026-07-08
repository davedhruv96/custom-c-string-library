#ifndef MYSTRING_H
#define MYSTRING_H

#include "arena.h"

typedef struct String String;

String *createString(Arena *arena, int initialSize);

#endif
