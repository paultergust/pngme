#include <stdio.h>
#include <stdlib.h>
#include "helper.c"
#include "chunk_type.h"

#define CASE_BITMASK 0b00100000

int8_t* to_bytes(ChunkType* type) {
  int8_t* bytes_alloc = malloc(sizeof(int8_t) * 4);
  bytes_alloc[0] = type->ancillary;
  bytes_alloc[1] = type->priv;
  bytes_alloc[2] = type->reserved;
  bytes_alloc[3] = type->safe;
  return bytes_alloc;
}

int8_t is_valid(ChunkType* type) {
  int8_t* bytes_array = to_bytes(type);
  for(int8_t i = 0; i < 4; i++) {
    if(!alphabetic(bytes_array[i])) {
      return 0;
    }
  }
  return 1;
}

int8_t is_critical(ChunkType *type) {
  return !((type->ancillary & CASE_BITMASK)>>5);
}

int8_t is_public(ChunkType *type) {
  return !((type->priv & CASE_BITMASK)>>5);
}

int8_t is_reserved_bit_valid(ChunkType *type) {
  return !((type->reserved & CASE_BITMASK)>>5);
}

int8_t is_safe_to_copy(ChunkType *type) {
  return ((type->safe & CASE_BITMASK)>>5);
}

ChunkType from_bytes(int8_t bytes[]) {
  ChunkType type = { .ancillary= bytes[0], .priv = bytes[1], .reserved = bytes[2], .safe = bytes[3]};
  if (!is_valid(&type)) {
    printf("Invalid chunk found! %d - %d - %d - %d\n", type.ancillary, type.priv, type.reserved, type.safe);
    exit(1);
  }
  return type;
}

