#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"
int main(int argc, char ** argv) {
  // reuse_on
  if (argc == 3) {
    // parse category
    execute_opt(argv[1], argv[2], REUSE_ON);
    //FILE * f_cat = open_file(argv[1]);
    //catarray_t * parsedWords = parseWord(f_cat);
    //parse template
    //FILE * f_temp = open_file(argv[2]);
    //parsedArrs_t * res = parseTemp(f_temp);

    //category_t * memo = create_memo();
    //replace_word_2(res, parsedWords, memo, REUSE_ON);
  }
  //reuse_off
  else if (argc == 4) {
    // parse category
    if (strcmp("-n", argv[1]) == 0) {
      execute_opt(argv[2], argv[3], REUSE_OFF);
      //FILE * f_cat = open_file(argv[2]);
      //catarray_t * parsedWords = parseWord(f_cat);
      //parse template
      //FILE * f_temp = open_file(argv[3]);
      //parsedArrs_t * res = parseTemp(f_temp);

      //category_t * memo = create_memo();
      //replace_word_2(res, parsedWords, memo, REUSE_OFF);
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
