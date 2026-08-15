#ifndef STRLIB_H
#define STRLIB_H

#include "../src/types.h"

typedef u32 StringHandle;
typedef struct String String;

b8 sl_init(u64 memSize);

StringHandle sl_create(const char *string);

StringHandle sl_create_with_capacity(const char *string, u64 initial_size);

void sl_destroy(StringHandle to_destroy);

void sl_shutdown(void);

void copyTo(const char *copyFrom, StringHandle copyTo);

const char *sl_cstr(StringHandle h);

#endif
