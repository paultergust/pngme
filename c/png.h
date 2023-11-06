#include "chunk.h"

typedef struct {
  uint8_t header[8];
  Vector chunks;
} Png;

Png from_chunks(Vector chunks);
void append_chunk(Png* self, Chunk chunk);
int remove_chunk(Png* self, ChunkType *chunk_type);
uint8_t* header(Png* self);
Vector* chunks(Png* self);
int chunk_by_type(Png* self, ChunkType *chunk_type);
Vector as_bytes(Png* self);

