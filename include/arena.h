#ifndef ARENA_H
#define ARENA_H

#include "types.h"

typedef struct Arena Arena;

Arena *arenaCreate(u64 size);

u64 alignOffset(u64 currentOffset, u64 alignment);

void *arenaPush(Arena *arena, u64 size);

void arenaClear(Arena *arena);

void arenaDestroy(Arena *arena);

void *arenaPushTemp(Arena *arena, u64 size);

void *arenaPushObject(Arena *arena, u64 size, u64 *offsetInArena);

void *getPtrToBuffer(Arena *arena);

#endif
