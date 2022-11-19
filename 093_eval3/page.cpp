#include "page.hpp"

void Page::parseContent(std::istream & is) {
  std::string line;
  while (getline(is, line)) {
    content.push_back(line);
  }
}
//*
std::vector<size_t> Page::printPage(
    bool proMode,
    std::vector<std::pair<std::string, long int> > gotItem) {
  std::vector<size_t> validInput;
  for (size_t i = 0; i < content.size(); i++) {
    std::cout << content[i] << std::endl;
  }
  std::cout << std::endl;
  if (type == "W") {
    std::cout << "Congratulations! You have won. Hooray!" << std::endl;
  }
  else if (type == "L") {
    std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
  }
  else {
    std::cout << "What would you like to do?" << std::endl << std::endl;
    if (proMode) {
      for (size_t i = 0; i < choices.size(); i++) {
        if (choices[i].condition.first.size() == 0) {
          validInput.push_back(i + 1);
          std::cout << ' ' << i + 1 << ". " << choices[i].sentence << std::endl;
          continue;
        }
        bool condMet = false;
        bool noPair = true;
        for (size_t j = 0; j < gotItem.size(); j++) {
          if (gotItem[j].first.compare(choices[i].condition.first) == 0) {
            noPair = false;
            if (gotItem[j].second == choices[i].condition.second) {
              condMet = true;
              validInput.push_back(i + 1);
            }
          }
        }
        if (noPair && choices[i].condition.second == 0) {
          validInput.push_back(i + 1);
          std::cout << ' ' << i + 1 << ". " << choices[i].sentence << std::endl;
        }
        else if (condMet) {
          std::cout << ' ' << i + 1 << ". " << choices[i].sentence << std::endl;
        }
        else {
          std::cout << ' ' << i + 1 << ". "
                    << "<UNAVAILABLE>" << std::endl;
        }
      }
    }
    else {
      for (size_t i = 0; i < choices.size(); i++) {
        std::cout << ' ' << i + 1 << ". " << choices[i].sentence << std::endl;
      }
    }
  }
  return validInput;
}
