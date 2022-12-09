#include "story.hpp"

#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

void error(const char * msg) {
  std::cerr << msg << std::endl;
  exit(EXIT_FAILURE);
}

//*
size_t convertToValidNum(const std::string numStr) {
  try {
    std::size_t pos;
    size_t pageNum = std::stoul(numStr.c_str(), &pos, 10);
    std::string rest = numStr.substr(pos);
    if (rest.size() > 0) {
      error("Invalid format of number: exist other characters after number");
    }
    return pageNum;
  }
  catch (const std::invalid_argument & e) {
    std::cerr << "stoul: cannot convert invaild character (exist other characters before "
                 "number)"
              << std::endl;
    exit(EXIT_FAILURE);
  }
}

//* using !
std::string readPagePath(const std::string & dir, const std::string & pageName) {
  std::string pagePath;
  std::stringstream ss;
  ss << dir << "/" << pageName;
  pagePath = ss.str();
  return pagePath;
}

//*
std::string readStoryPath(const std::string & dir) {
  std::string storyPath;
  std::stringstream ss;
  ss << dir << "/story.txt";
  storyPath = ss.str();
  return storyPath;
}
//**
bool Story::haveRefPages() {
  for (size_t i = 0; i < pages.size(); i++) {
    for (size_t j = 0; j < pages[i].getChoices().size(); j++) {
      if (pages[i].getChoices()[j].getNum() > pages.size() - 1) {
        return false;
      }
    }
  }
  return true;
}
//**
bool Story::areRefPages() {
  std::set<size_t> setPages;
  for (size_t i = 1; i < pages.size(); i++) {
    setPages.insert(i);
  }
  for (size_t i = 0; i < pages.size(); i++) {
    for (size_t j = 0; j < pages[i].getChoices().size(); j++) {
      size_t temp = setPages.erase(pages[i].getChoices()[j].getNum());
    }
  }
  if (!setPages.empty()) {
    return false;
  }
  else {
    return true;
  }
}
//**
bool Story::haveEndingPages() {
  bool hasWin = false;
  bool hasLose = false;
  for (size_t i = 0; i < pages.size(); i++) {
    if (pages[i].getType() == "W") {
      hasWin = true;
    }
    if (pages[i].getType() == "L") {
      hasLose = true;
    }
    if (hasWin && hasLose) {
      break;
    }
  }
  bool hasEnding = hasWin && hasLose;
  return hasEnding;
}
//* try
void Story::parsePage(const std::string & line, const std::string & dir) {
  size_t posAt = line.find("@");
  size_t posColon = line.find(":");
  //check whether ":" exists
  if (posColon == std::string::npos) {
    throw std::runtime_error("No : in create page line");
  }
  //between "@"" and ":", we only allow 1 character
  if (posColon - posAt != 2) {
    throw std::runtime_error("Wrong format of page type: between first '@' and first "
                             "':', we only allow 1 character");
  }
  //get the page num : 0@N:page0.txt
  //                   ^
  const std::string pageNumString = line.substr(0, posAt);
  size_t pageNum = convertToValidNum(pageNumString);
  //check whether the order of creating the page is legal
  if (pageNum != pages.size()) {
    throw std::runtime_error("Page declarations must appear in order");
  }
  //get the page type : 0@N:page0.txt
  //                      ^
  std::string pageType = line.substr(posAt + 1, posColon - posAt - 1);
  //this one character must only be 'N', 'W' or 'L'
  if (pageType != "N" && pageType != "W" && pageType != "L") {
    throw std::runtime_error(
        "Wrong format of page type: this one character must only be 'N', 'W' or 'L'");
  }
  //get the page path : 0@N:page0.txt
  //                        ^^^^^^^^^
  const std::string pageNameStr = line.substr(posColon + 1);
  //check whether pagePath's number is valid -- (invalid : 0@N:)
  if (pageNameStr.empty()) {
    error("Page file path is empty");
  }
  //convert pagepath string to pagepath
  const std::string pagePathString = readPagePath(dir, pageNameStr);
  const char * pagePathp = pagePathString.c_str();
  std::ifstream pagePath(pagePathp);
  //check whether pagePath exists
  if (!pagePath.is_open()) {
    error("Page file does not exist");
  }
  //create page and store information to this page
  Page p(pagePath, pageType);
  //this page belongs to this story
  pages.push_back(p);
}
//* <try>  : []
void Story::parseChoice(const std::string & line,
                        std::pair<std::string, long int> cond,
                        bool isPro) {
  if (pages.size() == 0) {
    return;
  }
  // choice without condition
  //find the first ":" -- 0:1:I am ready for this story!
  //                       ^
  size_t posColon1 = line.find(":");
  //find the second ":" -- 0:1:I am ready for this story!
  //                          ^
  size_t posColon2 = line.find(":", posColon1 + 1);
  if (posColon2 == std::string::npos) {
    error("No second ':' in choice line");
  }
  //get the page num : 0:1:I am ready for this story!
  //                   ^
  std::string pageNumString = line.substr(0, posColon1);
  size_t pageNum = convertToValidNum(pageNumString);
  //check whether this page has created
  if (pageNum > pages.size() - 1) {
    throw std::runtime_error(
        "Creating chioce or condition when this page declaration has not appeared yet");
  }
  //check whether this page is N page
  if (pages[pageNum].getType() != "N") {
    throw std::runtime_error("Win and Lose pages MUST NOT have any choices");
  }
  //get the choice num : 0:1:I am ready for this story!
  //                       ^
  std::string pageChoiceNumStr = line.substr(posColon1 + 1, posColon2 - posColon1 - 1);
  size_t pageChoiceNum = convertToValidNum(pageChoiceNumStr);
  //----std::cout << pageChoiceNum<< std::endl;
  //get the choice sentence : 0:1:I am ready for this story!
  //                              ^^^^^^^^^^^^^^^^^^^^^^^^^^
  std::string pageChoiceSentence = line.substr(posColon2 + 1);
  //create the choice for the page
  Choice choice(pageChoiceNum, pageChoiceSentence, cond, isPro);
  //store the page's choice to this page
  pages[pageNum].setChoices(choice);
}
std::pair<std::string, long int> parseCondStr(std::string condStr) {
  // condstr "broke=0"
  std::pair<std::string, long int> ans;
  if (condStr.find('=') == std::string::npos) {
    error("Wrong format of choice line : cannot find '=' inside condtion string");
  }
  size_t posEq = condStr.find('=');
  std::string condWord = condStr.substr(0, posEq);
  std::string condValStr = condStr.substr(posEq + 1);
  long int condVal = convertToValidNum(condValStr);
  ans.first = condWord;
  ans.second = condVal;
  return ans;
}
void Story::parseChoiceWithCond(const std::string & line) {
  if (pages.size() == 0) {
    return;
  }
  //find the "[" -- 8[broke=0]:10:Offer the dragon your last coins.
  //                 ^
  size_t posBracketL = line.find("[");
  //find the "]" -- 8[broke=0]:10:Offer the dragon your last coins.
  //                         ^
  size_t posBracketR = line.find("]", posBracketL + 1);
  if (posBracketR == std::string::npos) {
    error("Wrong format of choice line : cannot find ] after [");
  }
  std::string condStr = line.substr(posBracketL + 1, posBracketR - posBracketL - 1);
  std::pair<std::string, long int> cond = parseCondStr(condStr);
  std::string copyLine = line;
  copyLine.replace(posBracketL, posBracketR - posBracketL + 1, "");
  parseChoice(copyLine, cond, true);
}

void Story::setCondition(const std::string & line) {
  //7$sword=1
  size_t posDol = line.find('$');
  std::string pageNumStr = line.substr(0, posDol);
  std::string condStr = line.substr(posDol + 1);
  size_t pageNum = convertToValidNum(pageNumStr);
  if (pageNum > pages.size() - 1) {
    error("page num is invalid when setting condition");
  }
  std::pair<std::string, long int> cond = parseCondStr(condStr);
  pages[pageNum].setPrecondition(cond);
}

//*  read story.txt
void Story::readStory(const std::string & dir) {
  // storyPath : story1/story.txt
  std::string storyPath = readStoryPath(dir);
  const char * storyPathp = storyPath.c_str();
  std::ifstream ifs(storyPathp);
  if (!ifs.is_open()) {
    error("story.txt file does not exist");
  }
  std::string line;
  while (!ifs.eof()) {
    std::getline(ifs, line);
    //ignore empty line
    if (line.size() == 0) {
      continue;
    }
    char const * symbol = "@:$[";  //////////
    // @ -creating page,
    // [ -set the page's choice line with condition,
    // : -set the page's choice line without condition
    // $ -set the page's condition
    std::size_t const firstSymPos = line.find_first_of(symbol);
    if (firstSymPos == std::string::npos) {
      error("Wrong format of line");
    }
    std::string firstSym = line.substr(firstSymPos, 1);
    try {
      //if @, then it is creating page line
      if (firstSym == "@") {
        parsePage(line, dir);
        //if :$[, it should be seting condition
      }
      else if (firstSym == "$") {
        setCondition(line);
        // if : or [, it should be choice line or empty
      }
      else if (firstSym == "[") {
        parseChoiceWithCond(line);
      }
      else {
        std::pair<std::string, long int> nullPair;
        nullPair.first = "";
        nullPair.second = 0;
        parseChoice(line, nullPair, false);
      }
    }
    catch (const std::runtime_error & e) {
      std::cerr << e.what() << std::endl;
      exit(EXIT_FAILURE);
    }
  }
}
//** try
void Story::verify() {
  try {
    if (!haveRefPages()) {
      throw std::runtime_error(
          "false: exists page num in choices that is not valid in story");
    }
    if (!areRefPages()) {
      throw std::runtime_error("false: exists page num in story that is not referenced");
    };
    if (!haveEndingPages()) {
      throw std::runtime_error(
          "false: At least 1 Win page and 1 Lose page are needed in story");
    };
  }
  catch (std::runtime_error & e) {
    std::cerr << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }
}

//**
size_t Story::readInput(size_t numPage, std::vector<size_t> validInput) {
  std::string input;
  size_t inputChoiceNum;
  while (1) {
    bool isValid = false;
    std::cin >> input;
    //check if inputs in inputfile are enough
    if (std::cin.eof()) {
      error("inputs are not enough to go to the end of the story");
    }
    std::size_t pos;
    inputChoiceNum = std::stoul(input.c_str(), &pos, 10);
    std::string rest = input.substr(pos);
    // std::cout << rest << std::endl;
    if (rest.size() > 0) {
      std::cout << "That is not a valid choice, please try again" << std::endl;
      continue;
    }
    //const char * inputp = input.c_str();
    //inputChoiceNum = strtoll(inputp, NULL, 10);
    if (validInput.size() != 0) {
      std::vector<size_t>::iterator it = validInput.begin();
      while (it != validInput.end()) {
        if (inputChoiceNum == *it) {
          isValid = true;
          break;
        }
        ++it;
      }
      if (isValid) {
        break;
      }
      if (inputChoiceNum > 0 && inputChoiceNum <= pages[numPage].getChoices().size()) {
        std::cout << "That choice is not available at this time, please try again"
                  << std::endl;
      }
      else {
        std::cout << "That is not a valid choice, please try again" << std::endl;
      }
    }
    else {
      if (inputChoiceNum > 0 && inputChoiceNum <= pages[numPage].getChoices().size()) {
        break;
      }
      std::cout << "That is not a valid choice, please try again" << std::endl;
    }
  }
  size_t inputChoicePage = pages[numPage].getChoices()[inputChoiceNum - 1].getNum();
  return inputChoicePage;
}
//*
void Story::display() {
  size_t numPage = 0;
  bool proMode = false;
  std::vector<std::pair<std::string, long int> > gotItem;
  while (numPage < pages.size()) {
    std::cout << "Page " << numPage << std::endl;
    std::cout << "==========" << std::endl;
    std::vector<size_t> num = pages[numPage].printPage(proMode, gotItem);
    numPage++;
  }
}

//**
void Story::play(bool playPro) {
  size_t numPage = 0;
  std::vector<std::pair<std::string, long int> > gotItem;
  while (1) {
    std::vector<size_t> validInput = pages[numPage].printPage(playPro, gotItem);
    for (size_t i = 0; i < pages[numPage].getPrecondition().size(); i++) {
      bool findItem = false;
      for (size_t j = 0; j < gotItem.size(); j++) {
        if (gotItem[j].first == pages[numPage].getPrecondition()[i].first) {
          findItem = true;
          gotItem[j].second = pages[numPage].getPrecondition()[i].second;
        }
      }
      if (!findItem) {
        gotItem.push_back(pages[numPage].getPrecondition()[i]);
      }
    }
    if (pages[numPage].getType() == "L" || pages[numPage].getType() == "W") {
      break;
    }
    numPage = readInput(numPage, validInput);
  }
}

std::vector<size_t> visited;
std::vector<size_t> path;
std::vector<size_t> choice;
std::vector<std::vector<size_t> > pathsToWin;
std::vector<std::vector<size_t> > choicesToWin;
void Story::findWinPath() {
  computeWinPath(0);
  if (pathsToWin.empty()) {
    std::cout << "This story is unwinnable!" << std::endl;
  }
  for (size_t i = 0; i < pathsToWin.size(); i++) {
    for (size_t j = 0; j < pathsToWin[i].size(); j++) {
      std::cout << pathsToWin[i][j] << "(" << choicesToWin[i][j] << ")"
                << ",";
    }
    std::string ending = "(win)";
    size_t numToEndPage = pathsToWin[i][pathsToWin[i].size() - 1];
    size_t ChoiceToEndPage = choicesToWin[i][choicesToWin[i].size() - 1] - 1;
    size_t endingPage = pages[numToEndPage].getChoices()[ChoiceToEndPage].getNum();
    std::cout << endingPage << ending << std::endl;
  }
}

void Story::computeWinPath(size_t curPath) {
  for (size_t i = 0; i < visited.size(); i++) {
    if (curPath == visited[i]) {
      return;
    }
  }
  visited.push_back(curPath);
  if (pages[curPath].getType() == "L") {
    return;
  }
  if (pages[curPath].getType() == "W") {
    pathsToWin.push_back(path);
    choicesToWin.push_back(choice);
    return;
  }
  for (size_t i = 0; i < pages[curPath].getChoices().size(); i++) {
    path.push_back(curPath);
    choice.push_back(i + 1);
    computeWinPath(pages[curPath].getChoices()[i].getNum());
    path.pop_back();
    choice.pop_back();
  }
}
