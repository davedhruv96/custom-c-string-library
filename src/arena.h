#ifndef ARENA_H
#define ARENA_H

#include "types.h"

typedef struct Arena Arena;

typedef struct String String;

Arena *arenaCreate(u64 size);

u64 alignOffset(u64 currentOffset, u64 alignment);

void *arenaPush(Arena *arena, u64 size, u64 *offset);

void *arenaPushWithoutOffset(Arena *arena, u64 size);

void arenaClear(Arena *arena);

void arenaDestroy(Arena *arena);

void *arenaPushTemp(Arena *arena, u64 size); // for temporary string

void arenaPopTemp(Arena *arena);

void *getPtrToBuffer(Arena *arena);

b8 arena_needs_mem(Arena *arena);

void setBottomToPos(Arena *arena, u64 position);

String *compact(Arena *arena, String *str, u64 *position);

#endif
