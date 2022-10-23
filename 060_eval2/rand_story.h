#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

//any functions you want your main to use
void error(char * msg);

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

parsedArrs_t * parseTemp(FILE * f);
void replace_word(parsedArrs_t * res);
void free_parsedArr(parsedArr_t * arr);
void free_parsedArrs(parsedArrs_t * res);
void file_close(FILE * f);
#endif
