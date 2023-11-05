#include <stdlib.h>
#include "vector.h"

int vectorTotal(Vector *v){
  int count = UNDEFINE;
  if (v){
    count = v->total;
  }
  return count;
}

int vectorResize(Vector *v, int capacity) {
  int status = UNDEFINE;
  if (v) {
    void *items = realloc(v->items, sizeof(void *) * capacity);
    if (items) {
      v->items = items;
      v->capacity = capacity;
      status = SUCCESS;
    }
  }
  return status;
}

int vectorAppend(Vector *v, int item) {
  int status = UNDEFINE;
  if (v) {
    if (v->capacity == v->total) {
      status = vectorResize(v, v->capacity * 2);
      if (status != UNDEFINE) {
        v->items[v->total++] = item;
      }
    } else {
      v->items[v->total++] = item;
      status = SUCCESS;
    }
  }
  return status;
}

int vectorSet(Vector *v, int index, int item) {
  int status = UNDEFINE;
  if (v) {
    if ((index >= 0) && (index < v->total)) {
      v->items[index] = item;
      status = SUCCESS;
    }
  }
  return status;
}

int vectorGet(Vector *v, int index) {
  int readData;
  if (v) {
    if ((index >= 0) && (index < v->total)) {
      readData = v->items[index];
    }
  }
  return readData;
}

int vectorDelete(Vector *v, int index) {
  int status = UNDEFINE;
  int i = 0;
  if (v) {
    if ((index < 0) && index >= v->total) {
      return status;
    }
    v->items[index] = -1;
    for (i = index; (i < v->total - 1); i++) {
      v->items[i] = v->items[i + 1];
      v->items[i + 1] = -1;
    }
    v->total--;
    if ((v->total > 0) && ((v->total) == (v->capacity / 4))) {
      vectorResize(v, v->capacity / 2);
    }
    status = SUCCESS;
  }
  return status;
}

int vectorFree(Vector *v) {
  int status = UNDEFINE;
  if (v) {
    free(v->items);
    v->items = NULL;
    status = SUCCESS;
  }
  return status;
}

void vector_init(Vector *v, int capacity) {
  v->capacity = capacity;
  v->total = 0;
  v->items = malloc(sizeof(void *) * v->capacity);
}

