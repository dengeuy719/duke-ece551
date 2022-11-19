#ifndef _STORY_HPP_
#define _STORY_HPP_

#include <exception>
#include <iostream>
#include <vector>

#include "page.hpp"

class Story {
 private:
  std::vector<Page> pages;

 public:
  //defalut constructor
  Story(){};
  Story(const std::string & dir) { readStory(dir); };
  void readStory(const std::string & dir);
  void parsePage(const std::string & line, const std::string & dir);
  void parseChoice(const std::string & line, std::pair<std::string, long int> cond);
  void parseChoiceWithCond(const std::string & line);
  void setCondition(const std::string & line);
  void display();
  //step2:
  void verify();
  void play(bool playPro);
  bool haveRefPages();
  bool areRefPages();
  bool haveEndingPages();
  size_t readInput(size_t num, std::vector<size_t> validInput);

  //step3:
  void findWinPath();
  void computeWinPath(size_t curPath);
};
#endif
