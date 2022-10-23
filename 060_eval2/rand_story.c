#include "rand_story.h"

void error(char * msg) {
  fprintf(stderr, "%s\n", msg);
  exit(EXIT_FAILURE);
}

// parse the input template and return the result.
parsedArrs_t * parseTemp(FILE * f) {
  char * line = NULL;
  size_t sz;
  parsedArrs_t * res = malloc(sizeof(*res));  //free
  res->n = 0;
  res->arrs = NULL;
  while (getline(&line, &sz, f) >= 0) {
    char * p = line;  //free
    parsedArr_t * arr = malloc(sizeof(*arr));
    arr->n = 0;
    arr->seg = NULL;
    while (*p != '\n') {
      char * left = strchr(p, '_');
      //test: left = NULL
      if (left == NULL) {
        arr->n++;
        arr->seg = realloc(arr->seg, arr->n * sizeof(*arr->seg));
        arr->seg[arr->n - 1] = strdup(p);
        break;
      }
      size_t pre_len = left - p;
      arr->n++;
      arr->seg = realloc(arr->seg, arr->n * sizeof(*arr->seg));  //free
      arr->seg[arr->n - 1] = strndup(p, pre_len);                //free
      char * right = strchr(left + 1, '_');
      //test: right = NULL
      if (right == NULL) {
        error("illegal template formal");
      }
      size_t blank_len = right - left + 1;
      arr->n++;
      arr->seg = realloc(arr->seg, arr->n * sizeof(*arr->seg));
      arr->seg[arr->n - 1] = strndup(left, blank_len);
      p = right + 1;
    }
    res->n++;
    res->arrs = realloc(res->arrs, res->n * sizeof(*res->arrs));  //free
    res->arrs[res->n - 1] = arr;
  }
  free(line);
  return res;
}

void replace_word(parsedArrs_t * res) {
  for (size_t i = 0; i < res->n; i++) {
    for (size_t j = 0; j < res->arrs[i]->n; j++) {
      if (strchr(res->arrs[i]->seg[j], '_') != NULL) {
        free(res->arrs[i]->seg[j]);
        res->arrs[i]->seg[j] = strdup(chooseWord("verb", NULL));  //free
      }
      fprintf(stdout, "%s", res->arrs[i]->seg[j]);
    }
    fprintf(stdout, "\n");
  }
}
void free_parsedArr(parsedArr_t * arr) {
  for (size_t n = 0; n < arr->n; n++) {
    free(arr->seg[n]);
  }
  free(arr->seg);
  free(arr);
}
void free_parsedArrs(parsedArrs_t * res) {
  for (size_t i = 0; i < res->n; i++) {
    free_parsedArr(res->arrs[i]);
  }
  free(res->arrs);
  free(res);
}
void file_close(FILE * f) {
  if (fclose(f) != 0) {
    error("Could not close file");
    exit(EXIT_FAILURE);
  }
}
