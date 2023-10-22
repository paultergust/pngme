#ifndef _CHUNKTYPETH_
#define _CHUNKTYPETH_

typedef struct {
  int ancillary;
  int priv;
  int reserved;
  int safe;
} ChunkType;

int* bytes(ChunkType* type);
int is_valid(ChunkType* type);
int is_critical(ChunkType* type);
int is_reserved_bit_valid(ChunkType* type);
int is_safe_to_copy(ChunkType* type);
ChunkType try_from(int* bytes);
ChunkType from_str(char* str);

#endif
