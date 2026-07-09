#ifndef ARENA_H
#define ARENA_H

#include "def.h"

Arena *arenaCreate(Arena *arena, u64 size);

u64 alignOffset(u64 currentOffset, u64 alignment);

void *arenaPush(Arena *arena, u64 size);

void arenaClear(Arena *arena);

void arenaDestroy(Arena *arena);

void *arenaPushFromEnd(Arena *arena, u64 size);

void arenaPopTemp(Arena *arena, u64 size);

#endif
