#ifndef _PAGE_HPP_
#define _PAGE_HPP_

#include <exception>
#include <iostream>
#include <vector>

class Choice {
 public:
  size_t num;
  std::string sentence;
  std::pair<std::string, long int> condition;

 public:
  //Choice(size_t num, std::string sentence):num(num),sentence(sentence){createWithoutCond(num, sentence);}
  Choice(size_t num, std::string sentence, std::pair<std::string, long int> cond) :
      num(num), sentence(sentence), condition(cond) {}
  //void createWithoutCond(size_t n, std::string s);
  //void createWithCond(size_t n, std::string s, std::pair<std::string, long int> c);
};

class Page {
 public:
  std::string type;
  std::vector<Choice> choices;
  std::vector<std::pair<std::string, long int> > precondition;

 private:
  std::vector<std::string> content;

 public:
  Page(){};
  Page(std::istream & pagePath, std::string & pageType) : type(pageType) {
    parseContent(pagePath);
  }
  void parseContent(std::istream & is);
  std::vector<size_t> printPage(bool proMode,
                                std::vector<std::pair<std::string, long int> > gotItem);
};

#endif
