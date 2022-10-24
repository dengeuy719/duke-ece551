#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"
int main(int argc, char ** argv) {
  if (argc != 3) {
    error("should have 3 arguments");
  }
  // parse category
  FILE * f_cat = open_file(argv[1]);
  catarray_t * parsedWords = parseWord(f_cat);
  //parse template
  FILE * f_temp = open_file(argv[2]);
  parsedArrs_t * res = parseTemp(f_temp);

  category_t * memo = create_memo();
  replace_word_2(res, parsedWords, memo);

  free_parsedArrs(res);
  free_parsedWords(parsedWords);
  free_memo(memo);
  file_close(f_cat);
  file_close(f_temp);
  return EXIT_SUCCESS;
}
