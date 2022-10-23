#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {
}
IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c) {
  rows = new IntArray *[numRows];
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(numColumns);
  }
}

IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.numRows), numColumns(rhs.numColumns), rows(new IntArray *[numRows]) {
  for (ssize_t i = 0; i < numRows; i++) {
    rows[i] = new IntArray(rhs[i]);
  }
}
IntMatrix::~IntMatrix() {
  for (ssize_t i = 0; i < numRows; i++)
    delete rows[i];
  delete[] rows;
}
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    for (ssize_t i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = new IntArray *[rhs.numRows];
    for (ssize_t i = 0; i < rhs.numRows; i++) {
      rows[i] = new IntArray(rhs[i]);
    }
  }
  return *this;
}
int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert((numRows > index) && (index >= 0));
  return *rows[index];
}
IntArray & IntMatrix::operator[](int index) {
  assert((numRows > index) && (index >= 0));
  return *rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
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

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert((numRows == rhs.numRows) && (numColumns == rhs.numColumns));
  IntMatrix res(numRows, numColumns);
  for (ssize_t i = 0; i < numRows; i++) {
    for (ssize_t j = 0; j < numColumns; j++) {
      res[i][j] = rhs[i][j] + (*this)[i][j];
    }
  }
  return res;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
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
