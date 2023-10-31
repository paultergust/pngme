#include <stdlib.h>
#include "helper.c"
#include "chunk_type.h"

#define CASE_BITMASK 0b00100000

int* bytes(ChunkType* type) {
  int* bytes_alloc = malloc(sizeof(int) * 4);
  bytes_alloc[0] = type->ancillary;
  bytes_alloc[1] = type->priv;
  bytes_alloc[2] = type->reserved;
  bytes_alloc[3] = type->safe;
  return bytes_alloc;
}

int is_valid(ChunkType* type) {
  int* bytes_array = bytes(type);
  for(int i = 0; i < 4; i++) {
    if(!alphabetic(bytes_array[i])) {
      return 0;
    }
  }
  return 1;
}

int is_critical(ChunkType *type) {
  return !((type->ancillary & CASE_BITMASK)>>5);
}

int is_public(ChunkType *type) {
  return !((type->priv & CASE_BITMASK)>>5);
}

int is_reserved_bit_valid(ChunkType *type) {
  return !((type->reserved & CASE_BITMASK)>>5);
}

int is_safe_to_copy(ChunkType *type) {
  return ((type->ancillary & CASE_BITMASK)>>5);
}

ChunkType try_from(int* bytes) {
  ChunkType type = { .ancillary= bytes[0], .priv = bytes[1], .reserved = bytes[2], .safe = bytes[3]};
  return type;
}

ChunkType from_str(char* str) {
  return try_from((int*)str);
}

