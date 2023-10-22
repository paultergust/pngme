#include <stdlib.h>
#include "helper.h"
#include "chunk_type.h"
#include "chunk.h"

Chunk new_chunk(ChunkType type, int* data) {
  Chunk chunk = {.length = get_size(data), .type = type, .data = data, .crc = NULL};
  return chunk;
}

int length(Chunk* chunk) {
  return chunk->length;
}

ChunkType chunk_type(Chunk* chunk) {
  return chunk->type;
}

int* data(Chunk* chunk) {
  return chunk->data;
}

int crc(Chunk* chunk) {
  return chunk->crc;
}

char* data_as_str(Chunk* chunk) {
  return (char*)chunk->data;
}

