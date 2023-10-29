#include "chunk_type.h"
#include <stdint.h>
#include "crc_32.h"

#ifndef _CHUNKTH_
#define _CHUNKTH_

typedef struct {
  int length;
  ChunkType type;
  int* data;
  uint32_t crc;
} Chunk;

Chunk new_chunk(ChunkType type, int* data);

int length(Chunk* chunk);

ChunkType chunk_type(Chunk* chunk);

int* data(Chunk* chunk);

uint32_t crc(Chunk* chunk);

char* data_as_str(Chunk* chunk);

#endif
