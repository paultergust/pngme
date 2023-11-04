#include "../chunk_type.c"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define CHUNK_TYPE_SIZE 4

void point() {
  printf(".");
}

// test_chunk_type_from_bytes 
void test_chunk_type_from_bytes() {
  int expected[CHUNK_TYPE_SIZE] = {82, 117, 83, 116};
  ChunkType type = from_bytes(expected);
  int *resulting_bytes = to_bytes(&type);
  for (int i = 0; i < CHUNK_TYPE_SIZE; i++) {
    assert(resulting_bytes[i] == expected[i]);
  }
  point();
}

// test_chunk_type_is_critical 
void is_chunk_type_critical() {
  int type_array[CHUNK_TYPE_SIZE] = {88, 77, 83, 68};
  ChunkType type = from_bytes(type_array);
  assert(is_critical(&type));
  point();
}

// test_chunk_type_is_not_critical 
void is_chunk_type_not_critical() {
  int type_array[CHUNK_TYPE_SIZE] = {112, 77, 83, 68};
  ChunkType type = from_bytes(type_array);
  assert(!is_critical(&type));
  point();
}

// test_chunk_type_is_public 
void is_chunk_public() {
  int type_array[CHUNK_TYPE_SIZE] = {112, 76, 83, 68};
  ChunkType type = from_bytes(type_array);
  assert(is_public(&type));
  point();
}

// test_chunk_type_is_not_public 
void is_chunk_not_public() {
  int type_array[CHUNK_TYPE_SIZE] = {112, 122, 83, 68};
  ChunkType type = from_bytes(type_array);
  assert(!is_public(&type));
  point();
}

// test_chunk_type_is_reserved_bit_valid 
void is_chunk_type_is_reserved_bit_valid() {
  int type_array[CHUNK_TYPE_SIZE] = {112, 122, 83, 68};
  ChunkType type = from_bytes(type_array);
  assert(is_reserved_bit_valid(&type));
  point();
}

// test_chunk_type_is_reserved_bit_invalid 
void is_chunk_type_is_reserved_bit_invalid() {
  int type_array[CHUNK_TYPE_SIZE] = {112, 122, 111, 68};
  ChunkType type = from_bytes(type_array);
  assert(!is_reserved_bit_valid(&type));
  point();
}

// test_chunk_type_is_safe_to_copy 
void is_chunk_type_safe_to_copy() {
  int type_array[CHUNK_TYPE_SIZE] = {77, 98, 74, 110};
  ChunkType type = from_bytes(type_array);
  assert(is_safe_to_copy(&type));
  point();
}

// test_chunk_type_is_unsafe_to_copy 
void is_chunk_type_unsafe_to_copy() {
  int type_array[CHUNK_TYPE_SIZE] = {77, 98, 111, 89};
  ChunkType type = from_bytes(type_array);
  assert(!is_safe_to_copy(&type));
  point();
}
// test_output_to_bytes
void test_chunk_type_to_bytes() {
  int type_array[CHUNK_TYPE_SIZE] = {77, 98, 111, 89};
  ChunkType type = from_bytes(type_array);
  int* output = to_bytes(&type);
  for (int i = 0; i < CHUNK_TYPE_SIZE; i++) {
    assert(type_array[i] == output[i]);
  }
  free(output);
  point();
}

int main() {
  test_chunk_type_from_bytes();
  is_chunk_type_critical();
  is_chunk_type_not_critical();
  is_chunk_public();
  is_chunk_not_public();
  is_chunk_type_is_reserved_bit_valid();
  is_chunk_type_is_reserved_bit_invalid();
  is_chunk_type_safe_to_copy();
  is_chunk_type_unsafe_to_copy();
  printf("\nAll tests passed\n");
}
