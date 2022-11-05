#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "bstset.h"
int main(void) {
  BstSet<int> set;
  set.add(60);
  set.add(19);
  set.add(93);
  set.add(4);
  set.add(25);
  set.add(84);
  set.add(1);
  set.add(11);
  set.add(21);
  set.add(35);
  set.add(70);
  set.add(86);
  bool find1 = set.contains(60);
  std::cout << "find1 should be true and is " << find1 << std::endl;
  bool find2 = set.contains(100);
  std::cout << "find1 should be false and is " << find2 << std::endl;
  set.remove(60);
  bool find3 = set.contains(60);
  std::cout << "find1 should be false and is " << find3 << std::endl;
  return EXIT_SUCCESS;
}
