#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helper.h"
#include "chunk_type.h"
#include "chunk.h"
#include "crc_32.h"
#include "vector.h"

Chunk new_chunk(ChunkType type, Vector* data) {
  int length = data->total;
  Chunk chunk = {.length = length, .type = type, .data = data, .crc = crc32(data->items, length)};
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

Chunk try_from_bytes(Vector *vec) {

  //first 4 are the length
  uint8_t len_bytes[4];
  for (int a = 0; a < 4; a++) {
    len_bytes[a] = (uint8_t)vec->items[a];
  }
  int length = uint8_to_uint32(len_bytes);

  //now for the type
  uint8_t type_bytes[4];
  for (int b = 4; b < 8; b++) {
    type_bytes[b] = (uint8_t)vec->items[b];
  }
  ChunkType type = from_bytes(type_bytes);

  //then, the next (length) are the data
  Vector data;
  vector_init(&data, length);
  for (int c = 4; c < length; c++) {
    vector_append(&data, vec->items[c]);
  }

  //and then 4 for crc (which should match data)
  uint8_t crc_bytes[4];
  for (int d = 0; d < (length + 4); d++) {
    crc_bytes[d] = (uint8_t)vec->items[d];
  }
  uint32_t crc = uint8_to_uint32(crc_bytes);
  Chunk chunk = new_chunk(type, &data);
  if (crc != chunk.crc) {
    printf("Invalid crc for chunk: ");
    for (int e = 0; e < 4; e++) {
      printf("%d ", type_bytes[e]);
    }
    exit(1);
  }
  //if anything fails, throw an error
  return chunk;
}
