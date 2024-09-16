#ifndef CPP4_MATRIX_H
#define CPP4_MATRIX_H

#include <cmath>
#include <cstring>
#include <iostream>

namespace s21 {
template <typename T>
class Matrix {
  typedef T value_type;

 public:
  Matrix() : rows_(0), cols_(0) { matrix_ = nullptr; }

  Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    matrix_ = new value_type *[rows_];
    for (int i = 0; i < rows; i++) {
      matrix_[i] = new value_type[cols_]{};
    }
  }

  Matrix(const Matrix &other) : rows_(other.rows_), cols_(other.cols_) {
    matrix_ = new value_type *[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new value_type[cols_];
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }

  ~Matrix() { clear(); }

  void clear() {
    if (matrix_ != nullptr) {
      for (int i = 0; i < rows_; i++) {
        if (matrix_[i] != nullptr) {
          delete[] matrix_[i];
        }
      }
      if (matrix_ != nullptr) {
        delete[] matrix_;
      }
    }
    rows_ = 0;
    cols_ = 0;
  }
  Matrix setrowcol(int rows, int cols) {
    Matrix<value_type> new_matrix(rows, cols);
    if (cols_ > 0) {
      for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
          new_matrix.matrix_[i][j] = matrix_[i][j];
        }
      }
    }
    *this = new_matrix;
    return *this;
  }

  void insert(int row, int col, value_type value) {
    if (row < rows_ && col < cols_) {
      matrix_[row][col] = value;
    } else if (col < cols_) {
      setrowcol(row + 1, cols_);
      matrix_[row][col] = value;
    } else if (row < rows_) {
      setrowcol(rows_, col + 1);
      matrix_[row][col] = value;
    } else {
      setrowcol(row + 1, col + 1);
      matrix_[row][col] = value;
    }
  }

  void scale(int vertices_count, double x) {
    if (x) {
      for (int i = 0; i < vertices_count; i++) {
        for (int j = 0; j < 3; j++) {
          matrix_[i][j] *= x;
        }
      }
    }
  }

  void translate(int vertices_count, double x, double y, double z) {
    for (int i = 0; i < vertices_count; i++) {
      matrix_[i][0] += x;
      matrix_[i][1] += y;
      matrix_[i][2] += z;
    }
  }

  void ox_rotate(int vertices_count, double angle) {
    if (angle) {
      for (int i = 0; i < vertices_count; i++) {
        double y = matrix_[i][1];
        double z = matrix_[i][2];
        matrix_[i][1] = y * cos(angle) - z * sin(angle);
        matrix_[i][2] = y * sin(angle) + z * cos(angle);
      }
    }
  }

  void oy_rotate(int vertices_count, double angle) {
    if (angle) {
      for (int i = 0; i < vertices_count; i++) {
        double x = matrix_[i][0];
        double z = matrix_[i][2];
        matrix_[i][0] = x * cos(angle) + z * sin(angle);
        matrix_[i][2] = -x * sin(angle) + z * cos(angle);
      }
    }
  }

  void oz_rotate(int vertices_count, double angle) {
    if (angle) {
      for (int i = 0; i < vertices_count; i++) {
        double x = matrix_[i][0];
        double y = matrix_[i][1];
        matrix_[i][0] = x * cos(angle) - y * sin(angle);
        matrix_[i][1] = x * sin(angle) + y * cos(angle);
      }
    }
  }

  T operator()(int i, int j) const { return matrix_[i][j]; }

  int getrows() { return rows_; }

  int getcols() { return cols_; }

  Matrix &operator=(const Matrix &other) {
    this->~Matrix();
    cols_ = other.cols_;
    rows_ = other.rows_;
    matrix_ = new value_type *[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix_[i] = new value_type[cols_];
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
    return *this;
  }

  T &operator()(int row, int col) {
    value_type *value;
    if (row < rows_ && col < cols_) {
      value = &matrix_[row][col];
    } else if (col < cols_) {
      setrowcol(row + 1, cols_);
      value = &matrix_[row][col];
    } else if (row < rows_) {
      setrowcol(rows_, col + 1);
      value = &matrix_[row][col];
    } else {
      setrowcol(row + 1, col + 1);
      value = &matrix_[row][col];
    }
    return *value;
  }

 private:
  int rows_, cols_;
  value_type **matrix_;
};
}  // namespace s21

#endif  // CPP4_MATRIX_H
