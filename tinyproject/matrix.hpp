#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <cassert>
#include "vector.hpp" // Include the Vector class header instead of .cpp

class Matrix {
private:
    int mNumRows;
    int mNumCols;
    double** mData;

public:
    Matrix();
    Matrix(int numRows, int numCols);
    Matrix(const Matrix& other);
    Matrix(double** data, int rows, int cols);
    ~Matrix();

    // Accessors
    int NumRows() const;
    int NumCols() const;

    // Operators
    double& operator()(int i, int j);
    double operator()(int i, int j) const;
    Matrix& operator=(const Matrix& rhs);
    Matrix operator+(const Matrix& rhs) const;
    Matrix operator-(const Matrix& rhs) const;
    Matrix operator*(const Matrix& rhs) const;
    Matrix operator*(double scalar) const;
    Vector operator*(const Vector& vec) const;
    Matrix& operator++();
    Matrix operator++(int);
    Matrix operator--(int);
    Matrix& operator--();
    Matrix operator-() const;


    // Matrix operations
    double Determinant() const;
    Matrix Inverse() const;
    Matrix PseudoInverse() const;
    Matrix Transpose() const;
    void display() const;
};

// Scalar * Matrix
Matrix operator*(double scalar, const Matrix& mat);

#endif // MATRIX_HPP
