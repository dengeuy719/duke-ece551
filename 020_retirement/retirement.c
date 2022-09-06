#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

void count(int startAge, double * initial, retire_info info) {
  int age = startAge / 12;
  int month = startAge % 12;
  for (int i = 1; i <= info.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", age, month, *initial);
    age = (startAge + i) / 12;
    month = (startAge + i) % 12;
    *initial = *initial * (1 + info.rate_of_return / 12) + info.contribution;
  }
}

void retirement(int startAge,           //in months
                double initial,         //initial savings in dollars
                retire_info working,    //info about working
                retire_info retired) {  //info about being retired

  count(startAge, &initial, working);

  count(startAge + working.months, &initial, retired);
}

void main() {
  retire_info working = {489, 1000, 0.045};
  retire_info retired = {384, -4000, 0.01};
  retirement(327, 21345, working, retired);
}
