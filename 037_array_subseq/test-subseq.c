#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void check(int * array, size_t n, size_t answer) {
  if (maxSeq(array, n) == answer) {
    printf("right!\n");
  }
  else {
    printf("wrong\n");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  int a1[1] = {0};
  int a2[1] = {1};

  int a3[3] = {1, 1, 1};
  int a4[3] = {1, 1, 2};
  int a5[3] = {1, 2, 3};
  int a6[3] = {1, 3, 5};
  int a7[3] = {-1, 0, 1};
  int a8[3] = {-5, -3, -1};
  int a9[5] = {1, 1, 2, 3, 5};
  int a10[5] = {1, 2, 3, 6, 1};
  int a11[5] = {1, 2, 1, 2, 3};
  int a12[3] = {3, 2, 1};
  int a13[12] = {1, 2, 3, 1, 2, 3, 4, 5, 1, 2, 3, 4};
  int a14[7] = {-1, -2, -3, 4, 5, 7, 9};
  int a15[8] = {-6, -3, -2, -1, 4, 5, 7, 9};
  int a16[10] = {1, 2, 1, 3, 5, 8, 2, 4, 6, 9};
  int a17[7] = {-4, -3, -2, -1, 0, -5, -6};
  int a18[1] = {2};
  int * a19 = NULL;
  check(a1, 1, 1);
  check(a2, 1, 1);
  check(a3, 3, 1);
  check(a4, 3, 2);
  check(a5, 3, 3);
  check(a6, 3, 3);
  check(a7, 3, 3);
  check(a8, 3, 3);
  check(a9, 5, 4);
  check(a10, 5, 4);
  check(a11, 5, 3);
  check(a12, 3, 1);
  check(a13, 12, 5);
  check(a14, 7, 5);
  check(a15, 8, 8);
  check(a16, 10, 4);
  check(a17, 7, 5);
  check(a18, 1, 1);
  check(a19, 0, 0);
  return EXIT_SUCCESS;
}
