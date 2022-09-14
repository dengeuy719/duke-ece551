#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y) {
  if (y == 0) {
    return 1;
  }
  else if (x == 0) {
    return 0;
  }
  unsigned ans = x * power(x, y - 1);
  return ans;
}
