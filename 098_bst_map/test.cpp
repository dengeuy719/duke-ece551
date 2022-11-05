#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "bstmap.h"
int main(void) {
  BstMap<int, int> map;
  map.add(60, 1);
  map.add(19, 2);
  map.add(93, 3);
  map.add(4, 4);
  map.add(25, 5);
  map.add(84, 6);
  map.add(1, 7);
  map.add(11, 8);
  map.add(21, 9);
  map.add(35, 10);
  map.add(70, 11);
  map.add(86, 12);
  map.inorder();
  int find1 = map.lookup(60);
  std::cout << "find1 should be 1 and is " << find1 << std::endl;
  int find2 = map.lookup(86);
  std::cout << "find1 should be 12 and is " << find2 << std::endl;
  map.remove(60);
  map.inorder();
  int find3 = map.lookup(70);
  std::cout << "find1 should be 1 and is " << find3 << std::endl;
  return EXIT_SUCCESS;
}
