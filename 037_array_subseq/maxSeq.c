#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  size_t res = 0;
  size_t temp = 1;
  if (n > 0) {
    for (size_t i = 1; i < n; i++) {
      if (array[i] > array[i - 1]) {
        temp++;
      }
      else {
        if (res < temp) {
          res = temp;
        }
        temp = 1;
      }
    }
    if (res < temp) {
      res = temp;
    }
  }
  return res;
}
