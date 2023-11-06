#include <stdio.h>
#include <assert.h>
#include "../chunk.c"
#include "../crc_32.c"
#include "../vector.c"
#include "point.c"

// testing_chunk
Chunk test_new_chunk() {
  Vector data;
  vector_init(&data, 26);
  for (int i = 0; i < 26; i++) {
    vectorAppend(&data, &i);
  }
  ChunkType type = {.ancillary='a', .priv='a', .reserved='b', .safe='b'};
  Chunk chunk = new_chunk(type, &data);
  printf("%d\n", chunk.crc);
  point();
  return chunk;
}

// test_chunk_length 
void test_chunk_length() {
  Chunk c = test_new_chunk();
  assert(c.length == 26);
  point();
}

// test_chunk_crc 
void test_chunk_crc() {
  Chunk c = test_new_chunk();
  assert(904521224 == c.crc);
  point();
}

int main() {
  test_chunk_length();
  printf("\n All tests passed\n");
}
