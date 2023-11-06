#include "helper.h"
int alphabetic(char c) {
  if(c < 65 || (c > 90 && c < 97) || (c > 122)) {
    return 0;
  } 
  return 1;
}

int compare_types(ChunkType *a, ChunkType *b) {
  if (a->ancillary != b->ancillary) {
    return 0;
  }
  if (a->priv != b->priv) {
    return 0;
  }
  if (a->reserved != b->reserved) {
    return 0;
  }
  if (a->safe != b->safe) {
    return 0;
  }
  return 1;

}

void uint32_to_uint8(uint32_t input, uint8_t output[4]) {
    output[0] = (input >> 24) & 0xFF;
    output[1] = (input >> 16) & 0xFF;
    output[2] = (input >> 8) & 0xFF;
    output[3] = input & 0xFF;
}

uint32_t uint8_to_uint32(uint8_t input[4]) {
  uint32_t output = 0;
    output |= (uint32_t)input[0] << 24;
    output |= (uint32_t)input[1] << 16;
    output |= (uint32_t)input[2] << 8;
    output |= (uint32_t)input[3];
    return output;
}
