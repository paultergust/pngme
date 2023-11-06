#include <stdint.h>
#ifndef _VECTORH_
#define _VECTORH_

typedef struct Vector {
  int capacity;
  int total;
  void ** items;
} Vector;

#define UNDEFINE -1
#define SUCCESS 0

int vector_total(Vector *v);
int vector_resize(Vector *v, int capacity);
int vector_append(Vector *v, void* item);
int vector_set(Vector *v, int index, void* item);
void *vector_get(Vector *v, int index);
int vector_delete(Vector *v, int index);
int vector_free(Vector *v);
void vector_init(Vector *v, int capacity);

#endif
