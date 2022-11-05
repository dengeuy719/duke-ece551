#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low >= high - 1) {
    return low;
  }
  int mid = (high - low) / 2 + low;
  int ans = f->invoke(mid);
  if (ans > 0) {
    return binarySearchForZero(f, low, mid);
  }
  else if (ans < 0) {
    return binarySearchForZero(f, mid, high);
  }
  else {
    return mid;
  }
}
