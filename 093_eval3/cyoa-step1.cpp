#include <cstdlib>
#include <fstream>

#include "story.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Need 2 arguments to run" << std::endl;
    exit(EXIT_FAILURE);
  }
  // ifstream f(argv[1], ifstream::in);
  // if (!f) {
  //   error("Cannot open the file");
  // }
  Story s(argv[1]);
  s.display();
  return EXIT_SUCCESS;
}
