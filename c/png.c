#include <stdio.h>
#include "png.h"
#include "vector.h"
#include "helper.h"

#define STANDARD_HEADER {137, 80, 78, 71, 13, 10, 26, 10}
#define FOUR_BYTES 4
#define EIGHT_BYTES 8

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
    uint8_t len[FOUR_BYTES];
    uint32_to_uint8(c->length, len);
    vector_append(&vbytes, len);
    for (int j = 0; j < c->data->total; j++) {
      vector_append(&vbytes, c->data->items[j]);
    }
    uint8_t checksum[FOUR_BYTES];
    uint32_to_uint8(c->crc, checksum);
    vector_append(&vbytes, checksum);
  }
  return vbytes;
}

Png png_from_bytes(Vector *bytes) {
  uint8_t header[EIGHT_BYTES] = STANDARD_HEADER;
  for (int a = 0; a < EIGHT_BYTES; a++) {
    if(bytes->items[a] != header[a]) {
      printf("Error in PNG file standard header!\n");
      exit(1);
    }
  }
  //now I just have to check the first 4 bytes after the header, and Ill know the offset of each chunk by length
  Vector chunks;
  vector_init(&chunks, 100);

  //first offset if of 8 bytes and then they are 4(length) + 4(type) + length(data) + 4(crc);
  int index = EIGHT_BYTES; //index to keep track of where we are through the buffer
  int going = 1; //to control the while loop
  ChunkType iend = {.ancillary='I', .priv='E', .reserved='N', .safe='D'};
  while (going) {
    Chunk chunk = try_from_bytes(bytes, index);
    vector_append(&chunks, &chunk);
    index += chunk.length + EIGHT_BYTES + FOUR_BYTES;
    if (compare_types(&chunk.type, &iend)) {
      if (index < bytes->total) {
        printf("IEND chunk not at the end of PNG file!\n");
        exit(1);
      }
      going = 0;
    }
  }
  Png png = {.header=STANDARD_HEADER, .chunks=chunks};
  return png;
}

