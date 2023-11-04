#ifndef _CHUNKTYPEH_
#define _CHUNKTYPEH_

typedef struct {
  int ancillary;
  int priv;
  int reserved;
  int safe;
} ChunkType;

int* to_bytes(ChunkType* type);
int is_valid(ChunkType* type);
int is_critical(ChunkType* type);
int is_reserved_bit_valid(ChunkType* type);
int is_safe_to_copy(ChunkType* type);
ChunkType from_bytes(int bytes[]);

#endif
