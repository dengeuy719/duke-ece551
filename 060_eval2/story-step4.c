#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"
int main(int argc, char ** argv) {
  // reuse_on
  if (argc == 3) {
    execute_opt(argv[1], argv[2], REUSE_ON);
  }
  //reuse_off
  else if (argc == 4) {
    if (strcmp("-n", argv[1]) == 0) {
      execute_opt(argv[2], argv[3], REUSE_OFF);
    }
    else {
      error("invalid optional argument, should be -n");
    }
  }
  else {
    error("wrong number of arguments");
  }

  return EXIT_SUCCESS;
}
