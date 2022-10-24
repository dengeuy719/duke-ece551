
#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

//any functions you want your main to use
void error(char * msg);
FILE * open_file(char * n);
struct parsedArr_tag {
  char ** seg;
  size_t n;
};
typedef struct parsedArr_tag parsedArr_t;

struct parsedArrs_tag {
  parsedArr_t ** arrs;
  size_t n;
};
typedef struct parsedArrs_tag parsedArrs_t;

typedef enum opt_tag { NUM, CAT } opt_t;

parsedArrs_t * parseTemp(FILE * f);
void replace_word(parsedArrs_t * res);
void free_parsedArr(parsedArr_t * arr);
void free_parsedArrs(parsedArrs_t * res);
void file_close(FILE * f);

catarray_t * parseWord(FILE * f);
void free_parsedWord(category_t * cate);
void free_parsedWords(catarray_t * res);

//step3
void replace_word_2(parsedArrs_t * res, catarray_t * parsedWords, category_t * memo);
category_t * create_memo();
const char * replace_opt(char * seg, catarray_t * cArr, category_t * memo);
void free_memo(category_t * memo);
#endif
