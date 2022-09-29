#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int maxLetter(size_t * array, size_t len) {
  int maxIndex = -1;
  size_t maxValue = 0;
  for (size_t i = 0; i < len; i++) {
    if (array[i] > maxValue) {
      maxIndex = i;
      maxValue = array[i];
    }
  }
  if (maxIndex >= 4) {
    return maxIndex - 4;
  }
  else {
    return maxIndex + 22;
  }
}

void convert(FILE * f, size_t * count) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      count[c]++;
    }
  }
}

void breaker(FILE * f) {
  size_t len = 26;
  size_t count[26] = {0};
  convert(f, count);
  int key = maxLetter(count, len);
  fprintf(stdout, "%d\n", key);
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  breaker(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
