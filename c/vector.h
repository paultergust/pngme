#include <stdint.h>
#ifndef _VECTORH_
#define _VECTORH_

typedef struct Vector {
  int capacity;
  int total;
  uint8_t * items;
} Vector;

#define UNDEFINE -1
#define SUCCESS 0

int vectorTotal(Vector *v);
int vectorResize(Vector *v, int capacity);
int vectorAppend(Vector *v, uint8_t item);
int vectorSet(Vector *v, int index, uint8_t item);
uint8_t vectorGet(Vector *v, int index);
int vectorDelete(Vector *v, int index);
int vectorFree(Vector *v);
void vector_init(Vector *v, int capacity);

#endif
