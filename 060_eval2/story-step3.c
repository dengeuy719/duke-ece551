#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"
int main(int argc, char ** argv) {
  if (argc != 3) {
    error("should have 3 arguments");
  }
  execute_opt(argv[1], argv[2], REUSE_ON);
  return EXIT_SUCCESS;
}
