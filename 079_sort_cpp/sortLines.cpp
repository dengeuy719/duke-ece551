#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

void sortLines(std::istream & is) {
  std::string line;
  std::vector<std::string> res;
  while (std::getline(is, line)) {
    res.push_back(line);
  }
  std::sort(res.begin(), res.end());
  for (size_t i = 0; i < res.size(); i++) {
    std::cout << res[i] << std::endl;
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    sortLines(std::cin);
  }
  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      std::ifstream ifs(argv[i]);
      if (ifs.is_open()) {
        sortLines(ifs);
        ifs.close();
      }
      else {
        std::cerr << "cannot open file";
        exit(EXIT_FAILURE);
      }
    }
  }
  return EXIT_SUCCESS;
}
