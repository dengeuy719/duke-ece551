#include "pandemic.h"

#include <stdio.h>
#include <string.h>

#define IS_SPACE(c) ((c) == ' ')
#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9')
#define IS_ALPHA(c) (((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z'))

country_t parseLine(char * line) {
  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;
  //check line is vaild
  if (line == NULL) {
    printf("Input line is NULL!");
    exit(EXIT_FAILURE);
  }
  if (*line == '\0') {
    printf("Input line is empty!");
    exit(EXIT_FAILURE);
  }
  // find coma
  char * coma_p = strchr(line, ',');
  if (coma_p == NULL) {
    printf("Can not find a comma!");
    exit(EXIT_FAILURE);
  }
  // after finding a coma, we can seperate line into name and population
  // first, parse name string
  size_t i = 0;
  while (*(line + i) != ',') {
    if (!IS_SPACE(*(line + i)) && !IS_ALPHA(*(line + i))) {
      printf("Illegal character on name!");
      exit(EXIT_FAILURE);
    }
    if (i == 63) {
      printf("Name too long!");
      exit(EXIT_FAILURE);
    }
    ans.name[i] = *(line + i);
    i++;
  }
  ans.name[i] = '\0';
  if (i == 0) {
    printf("Can not find a character for country name!");
    exit(EXIT_FAILURE);
  }
  // second, parse population nums
  line += i + 1;
  char * p;
  uint64_t chartonum = strtoul(line, &p, 10);
  ans.population = chartonum;
  return ans;
}
void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
}
