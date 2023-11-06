#include "chunk_type.h"
#ifndef _HELPERH_
#define _HELPERH_

int alphabetic(char c);
int compare_types(ChunkType *a, ChunkType *b);
void uint32_to_uint8(uint32_t input, uint8_t output[4]);
#endif

