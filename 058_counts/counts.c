#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * c = malloc(sizeof(*c));
  c->counts = NULL;
  c->counts_len = 0;
  c->counts_unk = 0;
  return c;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->counts_unk++;
    return;
  }

  for (size_t i = 0; i < c->counts_len; i++) {
    if (strcmp(c->counts[i].str, name) == 0) {
      c->counts[i].count++;
      return;
    }
  }
  c->counts_len++;
  c->counts = realloc(c->counts, c->counts_len * sizeof(*c->counts));
  c->counts[c->counts_len - 1].count = 1;
  c->counts[c->counts_len - 1].str =
      malloc((strlen(name) + 1) * sizeof(*c->counts[c->counts_len - 1].str));
  strcpy(c->counts[c->counts_len - 1].str, name);
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (size_t i = 0; i < c->counts_len; i++) {
    fprintf(outFile, "%s: %zd\n", c->counts[i].str, c->counts[i].count);
  }
  if (c->counts_unk != 0) {
    fprintf(outFile, "<unknown> : %zd\n", c->counts_unk);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (size_t i = 0; i < c->counts_len; i++) {
    free(c->counts[i].str);
  }
  free(c->counts);
  free(c);
}
