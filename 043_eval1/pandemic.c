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
    ans.name[i] = *(line + i);
    i++;
  }
  ans.name[i] = '\0';
  if (i == 0 || i > 63) {
    printf("number of characters for country name is illegal!");
    exit(EXIT_FAILURE);
  }
  // second, parse population nums
  line += i + 1;
  char * p;
  uint64_t charToNum = strtoul(line, &p, 10);
  ans.population = charToNum;
  return ans;
}
void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  //check data
  if (data == NULL) {
    printf("Input data is NULL!");
    exit(EXIT_FAILURE);
  }
  //check n_days
  if (n_days < 7) {
    printf("days for measuring data are not enough!");
    exit(EXIT_FAILURE);
  }

  //start calc
  for (size_t i = 0; i < (n_days - (7 - 1)); i++) {
    unsigned sum = 0;
    for (size_t j = 0; j < 7; j++) {
      sum += *(data + i + j);
    }
    *(avg + i) = sum / (double)7;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  //check data
  if (data == NULL) {
    printf("Input data is NULL!");
    exit(EXIT_FAILURE);
  }
  //check n_days
  if (n_days < 7) {
    printf("days for measuring data are not enough!");
    exit(EXIT_FAILURE);
  }
  //check pop
  if (pop == 0) {
    printf("populaiton should not be 0!");
    exit(EXIT_FAILURE);
  }
  double sum = 0;
  //start calc
  for (size_t i = 0; i < n_days; i++) {
    sum = sum + *(data + i);
    *(cum + i) = sum * 100000 / pop;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  //check countries
  if (countries == NULL) {
    printf("Input of countries is NULl!");
    exit(EXIT_FAILURE);
  }
  //check data
  if (data == NULL) {
    printf("Data array is null!");
    exit(EXIT_FAILURE);
  }
  char * country_name = NULL;
  unsigned number_cases[n_countries];
  for (size_t i = 0; i < n_countries; i++) {
    number_cases[i] = 0;
  }
  size_t max = 0;
  for (size_t i = 0; i < n_countries; i++) {
    for (size_t j = 0; j < n_days; j++) {
      if (data[i][j] > number_cases[i]) {
        number_cases[i] = data[i][j];
      }
    }
    if (number_cases[i] > number_cases[max]) {
      max = i;
      country_name = countries[max].name;
    }
  }
  printf("%s has the most daily cases with %u\n", country_name, number_cases[max]);
}
