#include <string.h>
#include <stdlib.h>
#include "helper.h"
#include "chunk_type.h"
#include "chunk.h"
#include "crc_32.h"

Chunk new_chunk(ChunkType type, Vector* data, int length) {
  Chunk chunk = {.length = length, .type = type, .data = data, .crc = crc32(data, length)};
  return chunk;
}

int length(Chunk* chunk) {
  return chunk->length;
}

ChunkType chunk_type(Chunk* chunk) {
  return chunk->type;
}

Vector* data(Chunk* chunk) {
  return chunk->data;
}

uint32_t crc(Chunk* chunk) {
  return chunk->crc;
}

char* data_as_str(Chunk* chunk) {
  return (char*)chunk->data;
}

