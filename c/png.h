#include "chunk.h"

typedef struct {
  Chunk* chunks;
} Png;

Png from_chunks(Chunk* chunks);
void append_chunk(Png* self, Chunk chunk);
int remove_chunk(Png* self, char* chunk_type);
int* header(Png* self);
Chunk* chunks(Png* self);
Chunk* chunk_by_type(Png* self, char* chunk_type);
int* as_bytes(Png* self);

