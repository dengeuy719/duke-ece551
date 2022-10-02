#include <stdio.h>
#include <stdlib.h>

void rotate(FILE * f) {
  int c, col = 0, row = 0;
  char m[10][10] = {0};
  while ((c = fgetc(f)) != EOF) {
    if (c == '\n') {
      if (col != 10) {
        fprintf(stderr, "number of columns is illegal");
        exit(EXIT_FAILURE);
      }
      else {
        col = 0;
        row++;
      }
    }

    else {
      m[row][col] = c;
      col++;
    }
  }
  if (row != 10 || col != 0) {
    fprintf(stderr, "maxtrix is illegal");
    exit(EXIT_FAILURE);
  }

  for (int col = 0; col <= 9; col++) {
    for (int row = 9; row >= 0; row--) {
      fprintf(stdout, "%c", m[row][col]);
    }
    fprintf(stdout, "\n");
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: rotateMatrix inputname\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Could not read the roateMatrix information\n");
    return EXIT_FAILURE;
  }
  rotate(f);
  if (fclose(f) != 0) {
    fprintf(stderr, "fail to close file");
    return (EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
