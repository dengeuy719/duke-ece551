#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  //open the file
  FILE * f = fopen(fname, "r");
  //check f
  if (f == NULL) {
    fprintf(stderr, "file is empty!");
    exit(EXIT_FAILURE);
  }
  //spilt them into kv pairs
  kvarray_t * kvarray = malloc(sizeof(*kvarray));
  kvarray->kv_pairs = NULL;
  kvarray->size = 0;

  char * linep = NULL;
  size_t linesz = 0, i = 0;
  char * curr = NULL;
  while (getline(&curr, &linesz, f) >= 0) {
    kvarray->size++;
    kvarray->kv_pairs =
        realloc(kvarray->kv_pairs, kvarray->size * sizeof(kvarray->kv_pairs));

    linep = curr;
    size_t len_k, len_t;
    char *kq, *vq;
    kq = strchr(linep, '=');
    vq = strchr(linep, '\n');
    len_k = kq - linep;
    len_t = vq - kq - 1;
    kvpair_t * kv = malloc(sizeof(*kv));
    kv->key = malloc((len_k + 1) * sizeof(kv->key));
    kv->value = malloc((len_t + 1) * sizeof(kv->value));
    strncpy(kv->key, linep, len_k);
    kv->key[len_k] = '\0';
    strncpy(kv->value, kq + 1, len_t);
    kv->value[len_t] = '\0';
    kvarray->kv_pairs[i] = kv;
    i++;
    curr = NULL;
  }
  if (fclose(f) != 0) {
    fprintf(stderr, "Could not close file");
    exit(EXIT_FAILURE);
  }
  free(curr);
  return kvarray;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->size; i++) {
    free(pairs->kv_pairs[i]->key);
    free(pairs->kv_pairs[i]->value);
    free(pairs->kv_pairs[i]);
  }
  free(pairs->kv_pairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->size; i++) {
    printf(
        "key = '%s' value = '%s'\n", pairs->kv_pairs[i]->key, pairs->kv_pairs[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i < pairs->size; i++) {
    if (strcmp(key, pairs->kv_pairs[i]->key) == 0) {
      return pairs->kv_pairs[i]->value;
    }
  }
  return NULL;
}
