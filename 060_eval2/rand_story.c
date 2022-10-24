#include "rand_story.h"

void error(char * msg) {
  fprintf(stderr, "%s\n", msg);
  exit(EXIT_FAILURE);
}

FILE * open_file(char * n) {
  FILE * f = fopen(n, "r");
  if (f == NULL) {
    error("cannot open file");
  }
  return f;
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

const char * replace_opt(char * seg, catarray_t * cArr, category_t * memo) {
  const char * ans = NULL;
  char * left = strchr(seg, '_');
  char * right = strchr(left + 1, '_');
  seg = left + 1;
  *right = '\0';
  // if seg is a category name
  if (atoi(seg) == 0) {
    for (size_t i = 0; i < cArr->n; i++) {
      if (strcmp(seg, cArr->arr[i].name) == 0) {
        ans = chooseWord(seg, cArr);
        memo->n_words++;
        memo->words = realloc(memo->words, memo->n_words * sizeof(*memo->words));
        memo->words[memo->n_words - 1] = strdup(ans);  //free
      }
    }
  }
  // if seg is a valid number
  else if (atoi(seg) > 0) {
    if (memo->n_words == 0) {
      error("A previously used word do not exsits.");
    }
    if ((size_t)atoi(seg) > memo->n_words) {
      error("don't have so many previously used word");
    }

    ans = memo->words[memo->n_words - (size_t)atoi(seg)];
    memo->n_words++;
    memo->words = realloc(memo->words, memo->n_words * sizeof(*memo->words));
    memo->words[memo->n_words - 1] = strdup(ans);  //free
  }
  else {
    error("the category name is neither a valid integer nor a valid category name");
  }
  return ans;
}

category_t * create_memo() {
  category_t * memo = malloc(sizeof(*memo));  // free
  memo->n_words = 0;
  memo->name = "memo";
  memo->words = NULL;
  return memo;
}

void replace_word_2(parsedArrs_t * res, catarray_t * parsedWords, category_t * memo) {
  for (size_t i = 0; i < res->n; i++) {
    for (size_t j = 0; j < res->arrs[i]->n; j++) {
      if (strchr(res->arrs[i]->seg[j], '_') != NULL) {
        char * temp = strdup(res->arrs[i]->seg[j]);  //free
        free(res->arrs[i]->seg[j]);
        //res->arrs[i]->seg[j] = strdup(chooseWord("verb", NULL));  //free
        res->arrs[i]->seg[j] = strdup(replace_opt(temp, parsedWords, memo));
        free(temp);
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

catarray_t * parseWord(FILE * f) {
  char * line = NULL;
  size_t sz;
  catarray_t * res = malloc(sizeof(*res));  //free
  res->n = 0;
  res->arr = NULL;
  while (getline(&line, &sz, f) >= 0) {
    char * p = line;  //free
    char * colon = strchr(p, ':');
    if (colon == NULL) {
      error("illegal cateoory formal");
    }
    char * newLine = strchr(p, '\n');
    if (newLine == NULL || newLine - colon <= 1 || colon - p <= 1) {
      error("illegal category formal");
    }
    size_t cat_len = colon - p;
    size_t word_len = newLine - colon - 1;
    char * cat = strndup(p, cat_len);            //free
    char * word = strndup(colon + 1, word_len);  //free
    int flag = 0;
    for (size_t i = 0; i < res->n; i++) {
      if (strcmp(res->arr[i].name, cat) == 0) {
        flag = 1;
        free(cat);
        res->arr[i].n_words++;
        //free
        res->arr[i].words =
            realloc(res->arr[i].words, res->arr[i].n_words * sizeof(*res->arr[i].words));
        res->arr[i].words[res->arr[i].n_words - 1] = word;
      }
    }
    if (flag == 0) {
      res->n++;
      res->arr = realloc(res->arr, res->n * sizeof(*res->arr));  //free
      category_t new_name;
      new_name.n_words = 1;
      new_name.name = cat;
      new_name.words = malloc(sizeof(*new_name.words));
      new_name.words[0] = word;
      res->arr[res->n - 1] = new_name;
    }
  }
  free(line);
  return res;
}

void free_memo(category_t * memo) {
  if (memo == NULL) {
    return;
  }
  for (size_t i = 0; i < memo->n_words; i++) {
    free(memo->words[i]);
  }
  //free(cate->name);
  free(memo->words);
  free(memo);
}

void free_parsedWord(category_t * cate) {
  if (cate == NULL) {
    return;
  }
  for (size_t i = 0; i < cate->n_words; i++) {
    free(cate->words[i]);
  }
  free(cate->name);
  free(cate->words);
}
void free_parsedWords(catarray_t * res) {
  if (res == NULL) {
    return;
  }
  for (size_t i = 0; i < res->n; i++) {
    free_parsedWord(&res->arr[i]);
  }
  free(res->arr);
  free(res);
}
