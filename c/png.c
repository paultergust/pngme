#include "png.h"
#include "vector.h"
#include "helper.h"

#define STANDARD_HEADER {137, 80, 78, 71, 13, 10, 26, 10}

Png from_chunks(Vector chunks) {
  Png png = {.header = STANDARD_HEADER, .chunks = chunks};
  return png;
}

void append_chunk(Png* png, Chunk chunk) {
  vector_append(&png->chunks, &chunk);
}

int remove_chunk(Png* png, ChunkType *chunk_type) {
  int index = chunk_by_type(png, chunk_type);
  if (index >= 0) {
    return vector_delete(&png->chunks, index);
  }
  return 0;
}

uint8_t *header(Png *png) {
  return png->header;
}

Vector* chunks(Png* png) {
  return &png->chunks;
}

int chunk_by_type(Png* png, ChunkType *chunk_type) {
  int total = png->chunks.total;
  for (int i = 0; i < total; i++) {
    if (compare_types(chunk_type, png->chunks.items[i])) {
      return i;
    }
  }
  return -1;
}

Vector as_bytes(Png* png) {
  Vector vbytes;
  vector_init(&vbytes, 100);
  for (int i = 0; i < png->chunks.total; i++) {
    Chunk *c = png->chunks.items[i];
    uint8_t len[4];
    uint32_to_uint8(c->length, len);
    vector_append(&vbytes, len);
    for (int j = 0; j < c->data->total; j++) {
      vector_append(&vbytes, c->data->items[j]);
    }
    uint8_t checksum[4];
    uint32_to_uint8(c->crc, checksum);
    vector_append(&vbytes, checksum);
  }
  return vbytes;
}

