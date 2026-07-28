#include "arena.h"
#include "mystring.h"
#include <stdlib.h>

struct Arena {
  u8 *buffer;
  u64 capacity;
  u64 bottom;
  u64 top;
};

Arena *arenaCreate(u64 size) {
  Arena *arena = (Arena *)malloc(sizeof(Arena));
  if (!arena) {
    exit(-2);
  }
  arena->buffer = (u8 *)malloc(size);
  if (!arena->buffer) {
    exit(-2);
  }

  arena->capacity = size;
  arena->bottom = 0;
  arena->top = arena->capacity;
  return arena;
}

u64 alignOffset(u64 currentOffset, u64 alignment) {
  return (currentOffset + (alignment - 1)) & ~(alignment - 1);
}

void *arenaPush(Arena *arena, u64 size) {
  u64 currentOffset = alignOffset(arena->bottom, sizeof(void *));
  if (currentOffset + arena->bottom + size > arena->capacity) {
    exit(-2);
  }
  void *ptr = arena->buffer + currentOffset;

  arena->bottom = currentOffset + size;
  return ptr;
}

void *arenaPushPersistent(Arena *arena, u64 size, u64 *offsetInArena) {
  void *ptr = arenaPush(arena, size);
  if (ptr) {
    *offsetInArena = arena->bottom - size; // bottor or top object ..?
  }
  return ptr;
}
//
// String *arenaAllocPersistent(Arena *arena, String *str) {
//   if (!arena || !str) {
//     return NULL;
//   }
//
//   String *string = createString(arena, str->capacity * 2);
//   if (!string) {
//     return NULL;
//   }
//
//   return string;
// }

void *arenaPushTemp(Arena *arena, u64 size) {
  u64 currentOffset = alignOffset(arena->top, sizeof(void *));
  if (currentOffset + size + arena->bottom > arena->capacity) {
    return NULL;
  }

  void *ptr = arena->buffer + arena->capacity - currentOffset;

  arena->top = arena->capacity - currentOffset;
  return ptr;
}

void arenaPopTemp(Arena *arena) {
  if (arena->top == arena->capacity) {
    return;
  }
  arena->top = arena->capacity;
}

void *getPtrToBuffer(Arena *arena) {
  return arena->buffer;
} // only for the pointer to the start of string allocation: as of 11th july

void arenaClear(Arena *arena) { arena->bottom = 0; }

void arenaDestroy(Arena *arena) { free(arena->buffer); }

b8 arena_needs_mem(Arena *arena) {
  if (!arena)
    return 0;

  if (arena->top - arena->bottom < arena->capacity / 10) {
    return 1;
  }
  return 0;
}

void setBottomToPos(Arena *arena, u64 position) {
  if (arena) {
    arena->bottom = position;
  }
}

void *compactPush(Arena *arena, u64 *position, u64 size, u64 *offset) {
  u64 currentOffset = alignOffset(*position, sizeof(void *));
  if (currentOffset + size > arena->capacity) {
    return NULL;
  }
  *offset = currentOffset;
  void *ptr = arena->buffer + currentOffset;

  *position = currentOffset + size;
  return ptr;
}

String *compact(Arena *arena, String *str, u64 *position) {
  if (!arena || !str) {
    exit(-2);
  }

  u64 offset;
  String *newstr = compactPush(arena, position, str->length, &offset);

  newstr->offsetInArena = offset;
  newstr->capacity = str->length;
  copystr_compact(str, newstr);

  return newstr;
}
