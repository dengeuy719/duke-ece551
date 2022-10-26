#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<T> ** rows;

 public:
  Matrix() : numRows(0), numColumns(0), rows(NULL) {}

  Matrix(int r, int c) : numRows(r), numColumns(c) {
    rows = new std::vector<T> *[numRows];
    for (int i = 0; i < numRows; i++) {
      rows[i] = new std::vector<T>(numColumns);
    }
  }

  Matrix(const Matrix & rhs) :
      numRows(rhs.numRows),
      numColumns(rhs.numColumns),
      rows(new std::vector<T> *[numRows]) {
    for (ssize_t i = 0; i < numRows; i++) {
      rows[i] = new std::vector<T>(rhs[i]);
    }
  }

  ~Matrix() {
    for (ssize_t i = 0; i < numRows; i++)
      delete rows[i];
    delete[] rows;
  }
  Matrix & operator=(const Matrix & rhs) {
    if (this != &rhs) {
      for (ssize_t i = 0; i < numRows; i++) {
        delete rows[i];
      }
      delete[] rows;
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
      rows = new std::vector<T> *[rhs.numRows];
      for (ssize_t i = 0; i < rhs.numRows; i++) {
        rows[i] = new std::vector<T>(rhs[i]);
      }
    }
    return *this;
  }
  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }
  const std::vector<T> & operator[](int index) const {
    assert((numRows > index) && (index >= 0));
    return *rows[index];
  }
  std::vector<T> & operator[](int index) {
    assert((numRows > index) && (index >= 0));
    return *rows[index];
  }

  bool operator==(const Matrix & rhs) const {
    if ((numRows != rhs.numRows) || (numColumns != rhs.numColumns)) {
      return false;
    }
    for (ssize_t i = 0; i < numRows; i++) {
      if ((*this)[i] != rhs[i]) {
        return false;
      }
    }
    return true;
  }

  Matrix operator+(const Matrix & rhs) const {
    assert((numRows == rhs.numRows) && (numColumns == rhs.numColumns));
    Matrix res(numRows, numColumns);
    for (ssize_t i = 0; i < numRows; i++) {
      for (ssize_t j = 0; j < numColumns; j++) {
        res[i][j] = rhs[i][j] + (*this)[i][j];
      }
    }
    return res;
  }
};
template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  s << "[ ";
  for (ssize_t i = 0; i < rhs.getRows(); i++) {
    s << rhs[i];
    if (i != rhs.getRows() - 1) {
      s << ",\n";
    }
  }
  s << " ]";
  return s;
}
template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & vec) {
  s << "{ ";
  for (size_t i = 0; i < vec.size(); i++) {
    s << vec[i];
    if (i != vec.size() - 1) {
      s << ",";
    }
  }
  s << " }";
  return s;
}
#endif
