#include <cstdlib>
#include <fstream>

#include "story.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Need 2 arguments to run" << std::endl;
    exit(EXIT_FAILURE);
  }
  Story s(argv[1]);
  s.verify();
  bool playPro = false;
  s.play(playPro);
  return EXIT_SUCCESS;
}
