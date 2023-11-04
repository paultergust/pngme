#include "helper.h"
int alphabetic(char c) {
  if(c < 65 || (c > 90 && c < 97) || (c > 122)) {
    return 0;
  } 
  return 1;
}

int get_size(int* data) {
  int* i = data;
  int counter;
  while(*i != '\0') {
    counter++;
  }
  return counter;
}

