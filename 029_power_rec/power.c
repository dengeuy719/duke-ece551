#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y) {
  if (x == 0) {
    return 0;
  }
  else if (y == 0) {
    return 1;
  }
  unsigned ans = x * power(x, y - 1);
  return ans;
}
