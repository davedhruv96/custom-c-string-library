#include <arena.h>
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
    return NULL;
  }
  arena->buffer = (u8 *)malloc(size);
  if (!arena->buffer) {
    return NULL;
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
    return NULL;
  }
  void *ptr = arena->buffer + currentOffset;

  arena->bottom = currentOffset + size;
  return ptr;
}

void *arenaPushObject(Arena *arena, u64 size, u64 *offsetInArena) {
  void *ptr = arenaPush(arena, size);
  if (ptr) {
    *offsetInArena = arena->bottom - size; // bottor or top object ..?
  }
  return ptr;
}

void *arenaPushTemp(Arena *arena, u64 size) {
  u64 currentOffset = alignOffset(arena->top, sizeof(void *));
  if (currentOffset + size + arena->bottom > arena->capacity) {
    return NULL;
  }

  void *ptr = arena->buffer + arena->capacity - currentOffset;

  arena->top = arena->capacity - currentOffset;
  return ptr;
}

// void arenaPopFromEnd(Arena *arena, u64 size) {
//   if (arena->top == arena->capacity) {
//     return;
//   }
//   // popping to savemark will go here
//   arena->top = arena->capacity;
// }

void *getPtrToBuffer(Arena *arena) { return arena->buffer; }

void arenaClear(Arena *arena) { arena->bottom = 0; }

void arenaDestroy(Arena *arena) { free(arena->buffer); }
