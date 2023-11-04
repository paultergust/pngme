#ifndef _VECTORH_
#define _VECTORH_

typedef struct sVectorList {
  void ** items;
  int capacity;
  int total;
} sVectorList;

typedef struct sVector vector;

struct sVector {
  sVectorList vectorList;
  int (*pfVectorTotal)(vector *);
  int (*pfVectorResize)(vector *, int);
  int (*pfVectorAdd)(vector *, void *);
  int (*pfVectorSet)(vector *, int, void *);
  void *(*pfVectorGet)(vector *, int);
  int (*pfVectorDelete)(vector *, int);
  int (*pfVectorFree)(vector *);
};

#define VECTOR_INIT_CAPACITY 6
#define UNDEFINE -1
#define SUCCESS 0

#define VECTOR_INIT(vec) vector vec;\
  vector_init(&vec)

int vectorTotal(vector *v);
int vectorResize(vector *v, int capacity);
int vectorPushBack(vector *v, void *item);
int vectorSet(vector *v, int index, void *item);
void *vectorGet(vector *v, int index);
int vectorDelete(vector *v, int index);
int vectorFree(vector *v);
void vector_init(vector *v);

#endif
