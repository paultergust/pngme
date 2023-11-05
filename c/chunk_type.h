#include <stdint.h>
#ifndef _CHUNKTYPEH_
#define _CHUNKTYPEH_

typedef struct {
  int8_t ancillary;
  int8_t priv;
  int8_t reserved;
  int8_t safe;
} ChunkType;

int8_t* to_bytes(ChunkType* type);
int8_t is_valid(ChunkType* type);
int8_t is_critical(ChunkType* type);
int8_t is_reserved_bit_valid(ChunkType* type);
int8_t is_safe_to_copy(ChunkType* type);
ChunkType from_bytes(int8_t bytes[]);

#endif
