#include <cmath>
#include <cstdio>
#include <iostream>

#include "function.h"

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n), f(fn), mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};
int binarySearchForZero(Function<int, int> * f, int low, int high);

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int n;
  if (high > low) {
    n = log2(high - low) + 1;
  }
  else {
    n = 1;
  }
  CountedIntFn * countFunc = new CountedIntFn(n, f, mesg);
  int res = binarySearchForZero(countFunc, low, high);
  if (res != expected_ans) {
    fprintf(stderr, " funtion %s is wrong\n", mesg);
    exit(EXIT_FAILURE);
  }
}

class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class NegConstantFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return -10; }
};

class PosConstantFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10; }
};

class PosXFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10 * arg + 10; }
};
class NegXFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return -arg; }
};
int main() {
  SinFunction sf;
  NegConstantFunction ncf;
  PosConstantFunction pcf;
  PosXFunction pxf;
  NegXFunction nxf;
  check(&sf, 0, 150000, 52359, "sin Function");
  //ncf
  check(&ncf, 1, 10000, 9999, "all positive in ncf");
  check(&ncf, -100, -1, -2, "all negative in ncf");
  check(&ncf, -100, 100, 99, "include 0 in ncf");
  check(&ncf, 0, 0, 0, "only 0 in ncf");

  //pcf
  check(&pcf, 1, 10000, 1, "all positive in pcf");
  check(&pcf, -10000, -1, -10000, "all negative in pcf");
  check(&pcf, -10000, 10000, -10000, "include 0 in ncf");
  check(&pcf, 0, 0, 0, "only 0 in pcf");

  //pxf
  check(&pxf, 1, 10000, 1, "all positive in xf");
  check(&pxf, -10000, -1, -2, "all negative in xf");
  check(&pxf, -10000, 10000, -1, "include 0 in xf");
  check(&pxf, 0, 0, 0, "onlu 0 in pxf");

  //nxf
  check(&nxf, 1, 100, 99, "all positive in nxf");
  check(&nxf, -100, -1, -100, "all negative in nxf");
  check(&nxf, -100, 100, 0, "include 0 in nxf");
  check(&nxf, 0, 0, 0, "only 0 in nxf");
}
