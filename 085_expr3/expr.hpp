#ifndef __EXPR_HPP__
#define __EXPR_HPP__

#include <string.h>

#include <sstream>

class Expression {
 public:
  Expression() {}
  virtual std::string toString() const = 0;
  virtual long evaluate() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
 private:
  long number;

 public:
  NumExpression(long n) : number(n) {}
  std::string toString() const {
    std::stringstream ans;
    ans << number;
    return ans.str();
  }
  long evaluate() const { return number; }
  virtual ~NumExpression() {}
};

class PlusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string toString() const {
    std::stringstream ans;
    ans << "(" << lhs->toString() << " + " << rhs->toString() << ")";
    return ans.str();
  }
  long evaluate() const { return lhs->evaluate() + rhs->evaluate(); }
  virtual ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};

class MinusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  MinusExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string toString() const {
    std::stringstream ans;
    ans << "(" << lhs->toString() << " - " << rhs->toString() << ")";
    return ans.str();
  }
  long evaluate() const { return lhs->evaluate() - rhs->evaluate(); }
  virtual ~MinusExpression() {
    delete lhs;
    delete rhs;
  }
};

class TimesExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  TimesExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string toString() const {
    std::stringstream ans;
    ans << "(" << lhs->toString() << " * " << rhs->toString() << ")";
    return ans.str();
  }
  long evaluate() const { return lhs->evaluate() * rhs->evaluate(); }
  virtual ~TimesExpression() {
    delete lhs;
    delete rhs;
  }
};

class DivExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  DivExpression(Expression * lhs, Expression * rhs) : lhs(lhs), rhs(rhs) {}
  virtual std::string toString() const {
    std::stringstream ans;
    ans << "(" << lhs->toString() << " / " << rhs->toString() << ")";
    return ans.str();
  }
  long evaluate() const { return lhs->evaluate() / rhs->evaluate(); }
  virtual ~DivExpression() {
    delete lhs;
    delete rhs;
  }
};

#endif
