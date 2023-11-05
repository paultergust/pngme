#include "chunk_type.h"
#include <stdint.h>
#include "crc_32.h"
#include "vector.h"

#ifndef _CHUNKH_
#define _CHUNKH_

typedef struct {
  int length;
  ChunkType type;
  Vector* data;
  uint32_t crc;
} Chunk;

Chunk new_chunk(ChunkType type, Vector* data, int length);

int length(Chunk* chunk);

ChunkType chunk_type(Chunk* chunk);

Vector* data(Chunk* chunk);

uint32_t crc(Chunk* chunk);

char* data_as_str(Chunk* chunk);

#endif
