#ifndef _PAGE_HPP_
#define _PAGE_HPP_

#include <exception>
#include <iostream>
#include <vector>

class Choice {
 private:
  size_t num;
  std::string sentence;
  std::pair<std::string, long int> condition;
  bool isPro;

 public:
  Choice(size_t num,
         std::string sentence,
         std::pair<std::string, long int> cond,
         bool isPro) :
      num(num), sentence(sentence), condition(cond), isPro(isPro) {}
  size_t getNum() { return num; }
  std::string getSentence() { return sentence; }
  std::pair<std::string, long int> getCondition() { return condition; }
  void setPro() { isPro = true; }
  bool getPro() { return isPro; }
};

class Page {
 private:
  std::vector<Choice> choices;
  std::string type;
  std::vector<std::pair<std::string, long int> > precondition;
  std::vector<std::string> content;

 public:
  Page(){};
  Page(std::istream & pagePath, std::string & pageType) : type(pageType) {
    parseContent(pagePath);
  }
  void parseContent(std::istream & is);
  std::vector<size_t> printPage(bool proMode,
                                std::vector<std::pair<std::string, long int> > gotItem);
  std::string getType() { return type; }
  std::vector<Choice> getChoices() { return choices; }
  void setChoices(Choice c) { choices.push_back(c); }
  std::vector<std::pair<std::string, long int> > getPrecondition() {
    return precondition;
  }
  void setPrecondition(std::pair<std::string, long int> p);
};
#endif
