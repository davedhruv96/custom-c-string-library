#ifndef GC_H
#define GC_H

// #include "types.h"

typedef struct String String;
typedef struct VM VM;

String *pop(VM *vm);

void mark(String *str);

void markAll(VM *vm);

#endif
