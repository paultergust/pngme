#include "chunk_type.h"
#ifndef _CHUNKTH_
#define _CHUNKTH_

typedef struct {
  int length;
  ChunkType type;
  int* data;
  int crc;
} Chunk;


Chunk new_chunk(ChunkType type, int* data);

int length(Chunk* chunk);

ChunkType chunk_type(Chunk* chunk);

int* data(Chunk* chunk);

int crc(Chunk* chunk);

char* data_as_str(Chunk* chunk);

#endif
