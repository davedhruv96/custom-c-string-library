#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>
#include <stdint.h>

typedef struct Arena Arena;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef i8 b8;
typedef i32 b32;

#define KiB(n) ((u64)(n) << 10)
#define MiB(n) ((u64)(n) << 20)
#define GiB(n) ((u64)(n) << 30)

Arena *arenaCreate(Arena *arena, u64 capacity);

u64 alignOffset(u64 currentOffset, u64 alignment);

void *arenaPush(Arena *arena, u64 size);

void arenaClear(Arena *arena);

void arenaDestroy(Arena *arena);

void *arenaPushFromEnd(Arena *arena, u64 size);

#endif
