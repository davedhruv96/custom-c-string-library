#ifndef GC_H
#define GC_H

#include "types.h"

typedef struct String String;
typedef struct VM VM;

b8 gc_should_run();

#endif
