#include "mystring.h"

struct String {
  char *data;
  u64 length;
  u64 capacity;
};

String *createString(Arena *arena, int initialSize) {
  String *str = arena_push(arena, initialSize);
  if (!str) {
    return NULL;
  }

  return str;
}
