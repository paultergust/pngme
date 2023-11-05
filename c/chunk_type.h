#include <stdint.h>
#ifndef _CHUNKTYPEH_
#define _CHUNKTYPEH_

typedef struct {
  uint8_t ancillary;
  uint8_t priv;
  uint8_t reserved;
  uint8_t safe;
} ChunkType;

uint8_t* to_bytes(ChunkType* type);
uint8_t is_valid(ChunkType* type);
uint8_t is_critical(ChunkType* type);
uint8_t is_reserved_bit_valid(ChunkType* type);
uint8_t is_safe_to_copy(ChunkType* type);
ChunkType from_bytes(uint8_t bytes[]);

#endif
