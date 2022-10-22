#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"
int main(int argc, char ** argv) {
  if (argc != 2) {
    error("should have 2 arguments");
  }
  FILE * f = fopen(argv[1], "r");
}
