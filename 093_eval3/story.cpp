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
    // std::cout << rest << std::endl;
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
    for (size_t j = 0; j < pages[i].choices.size(); j++) {
      if (pages[i].choices[j].num > pages.size() - 1) {
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
    for (size_t j = 0; j < pages[i].choices.size(); j++) {
      size_t temp = setPages.erase(pages[i].choices[j].num);
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
    if (pages[i].type == "W") {
      hasWin = true;
    }
    if (pages[i].type == "L") {
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
  //check whether pagePath's number is valid -- (invalid : 0@N:page1.txt)
  // char const* digits = "0123456789";
  // std::size_t const firstDigit = pageNameStr.find_first_of(digits);
  // std::size_t const lastDigit = pageNameStr.find_last_of(digits);
  // std::string pageNameNumStr = pageNameStr.substr(firstDigit, lastDigit-firstDigit+1);

  // size_t pageNameNum = convertToValidNum(pageNameNumStr);
  // if(pageNameNum != pageNum){
  //     throw std::runtime_error("number in pagepath must correspond to the creating page number");
  // }

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
void Story::parseChoice(const std::string & line, std::pair<std::string, long int> cond) {
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
  //get the page num : 0:1:I am ready for this story!
  //                   ^
  std::string pageNumString = line.substr(0, posColon1);
  size_t pageNum = convertToValidNum(pageNumString);
  //check whether this page has created
  if (pageNum > pages.size() - 1) {
    throw std::runtime_error("This page declaration has not appeared yet");
  }
  //check whether this page is N page
  if (pages[pageNum].type != "N") {
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
  Choice choice(pageChoiceNum, pageChoiceSentence, cond);
  //std::cout <<"choice condition:"<<pageNum << "---"<<choice.num << ":" <<choice.condition.first<< ","<<choice.condition.second<< std::endl;
  //store the page's choice to this page
  pages[pageNum].choices.push_back(choice);
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
  parseChoice(copyLine, cond);
}

void Story::setCondition(const std::string & line) {
  //7$sword=1
  size_t posDol = line.find('$');
  std::string pageNumStr = line.substr(0, posDol);
  std::string condStr = line.substr(posDol + 1);
  size_t pageNum = convertToValidNum(pageNumStr);
  std::pair<std::string, long int> cond = parseCondStr(condStr);
  //std::cout<<"page condition: " << "pagenum"<< pageNum<<cond.first <<"," <<cond.second<< std::endl;
  pages[pageNum].precondition.push_back(cond);
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
        parseChoice(line, nullPair);
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
      throw std::runtime_error("false: does no exist any ending page in story");
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
    std::getline(std::cin, input);
    const char * inputp = input.c_str();
    inputChoiceNum = strtoll(inputp, NULL, 10);
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
      if (inputChoiceNum > 0 && inputChoiceNum <= pages[numPage].choices.size()) {
        std::cout << "That choice is not available at this time, please try again"
                  << std::endl;
      }
      else {
        std::cout << "That is not a valid choice, please try again" << std::endl;
      }
    }
    else {
      if (inputChoiceNum > 0 && inputChoiceNum <= pages[numPage].choices.size()) {
        break;
      }
      std::cout << "That is not a valid choice, please try again" << std::endl;
    }
  }
  size_t inputChoicePage = pages[numPage].choices[inputChoiceNum - 1].num;
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
    for (size_t i = 0; i < pages[numPage].precondition.size(); i++)
      gotItem.push_back(pages[numPage].precondition[i]);
    if (pages[numPage].type == "L" || pages[numPage].type == "W") {
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
  for (size_t i = 0; i < pathsToWin.size(); i++) {
    for (size_t j = 0; j < pathsToWin[i].size(); j++) {
      std::cout << pathsToWin[i][j] << "(" << choicesToWin[i][j] << ")"
                << ",";
    }
    std::string ending = "(win)";
    size_t numToEndPage = pathsToWin[i][pathsToWin[i].size() - 1];
    size_t ChoiceToEndPage = choicesToWin[i][choicesToWin[i].size() - 1] - 1;
    size_t endingPage = pages[numToEndPage].choices[ChoiceToEndPage].num;
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
  if (pages[curPath].type == "L") {
    return;
  }
  if (pages[curPath].type == "W") {
    pathsToWin.push_back(path);
    choicesToWin.push_back(choice);
    return;
  }
  for (size_t i = 0; i < pages[curPath].choices.size(); i++) {
    path.push_back(curPath);
    choice.push_back(i + 1);
    computeWinPath(pages[curPath].choices[i].num);
    path.pop_back();
    choice.pop_back();
  }
}
