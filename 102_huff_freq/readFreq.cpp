#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>
void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  uint64_t * ans = new uint64_t[257]();
  std::ifstream is(fname);
  char c;
  while (is.get(c)) {
    unsigned uc = c;
    ans[uc]++;
  }
  ans[256] = 1;
  is.close();
  return ans;
}
