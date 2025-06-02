#include "matrix.hpp"
#include <cassert>
#include <iostream>
using namespace std;

// Default constructor
Matrix::Matrix() : mNumRows(0), mNumCols(0), mData(nullptr) {}

// Constructor with dimensions
Matrix::Matrix(int numRows, int numCols) : mNumRows(numRows), mNumCols(numCols) {
    assert(numRows > 0 && numCols > 0);
    mData = new double*[mNumRows];
    for (int i = 0; i < mNumRows; ++i)
        mData[i] = new double[mNumCols]();
    for (int i = 0; i < mNumRows; ++i) {
        for (int j = 0; j < mNumCols; ++j) {
            mData[i][j] = 0.0; // Initialize to zero
        }
    }
}

// Copy constructor
Matrix::Matrix(const Matrix& other) : mNumRows(other.mNumRows), mNumCols(other.mNumCols) {
    mData = new double*[mNumRows];
    for (int i = 0; i < mNumRows; ++i) {
        mData[i] = new double[mNumCols]();
        for (int j = 0; j < mNumCols; ++j)
            mData[i][j] = other.mData[i][j];
    }
}

Matrix::Matrix(double** data, int rows, int cols) : mNumRows(rows), mNumCols(cols) {
    assert(data != nullptr && rows > 0 && cols > 0);
    mData = new double*[mNumRows];
    for (int i = 0; i < mNumRows; ++i) {
        mData[i] = new double[mNumCols];
        for (int j = 0; j < mNumCols; ++j) {
            mData[i][j] = data[i][j];
        }
    }
}

// Destructor
Matrix::~Matrix() {
    for (int i = 0; i < mNumRows; ++i)
        delete[] mData[i];
    delete[] mData;
}

// Accessors
int Matrix::NumRows() const {
    return mNumRows;
}

int Matrix::NumCols() const {
    return mNumCols;
}

// Element access (non-const)
double& Matrix::operator()(int i, int j) {
    assert(i >= 1 && i <= mNumRows);
    assert(j >= 1 && j <= mNumCols);
    return mData[i - 1][j - 1];
}

// Element access (const)
double Matrix::operator()(int i, int j) const {
    assert(i >= 1 && i <= mNumRows);
    assert(j >= 1 && j <= mNumCols);
    return mData[i - 1][j - 1];
}

// Assignment operator
Matrix& Matrix::operator=(const Matrix& rhs) {
    if (this != &rhs) {
        // Free existing memory
        for (int i = 0; i < mNumRows; ++i)
            delete[] mData[i];
        delete[] mData;

        // Copy dimensions
        mNumRows = rhs.mNumRows;
        mNumCols = rhs.mNumCols;

        // Allocate new memory and copy data
        mData = new double*[mNumRows];
        for (int i = 0; i < mNumRows; ++i) {
            mData[i] = new double[mNumCols];
            for (int j = 0; j < mNumCols; ++j)
                mData[i][j] = rhs.mData[i][j];
        }
    }
    return *this;
}

// Matrix addition
Matrix Matrix::operator+(const Matrix& rhs) const {
    assert(mNumRows == rhs.mNumRows && mNumCols == rhs.mNumCols);
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result(i + 1, j + 1) = mData[i][j] + rhs.mData[i][j];
    return result;
}

// Matrix subtraction
Matrix Matrix::operator-(const Matrix& rhs) const {
    assert(mNumRows == rhs.mNumRows && mNumCols == rhs.mNumCols);
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result(i + 1, j + 1) = mData[i][j] - rhs.mData[i][j];
    return result;
}

// Unary minus operator
Matrix Matrix::operator-() const {
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i) {
        for (int j = 0; j < mNumCols; ++j) {
            result.mData[i][j] = -mData[i][j];
        }
    }
    return result;
}

// Matrix multiplication
Matrix Matrix::operator*(const Matrix& rhs) const {
    assert(mNumCols == rhs.mNumRows);
    Matrix result(mNumRows, rhs.mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < rhs.mNumCols; ++j)
            for (int k = 0; k < mNumCols; ++k)
                result(i + 1, j + 1) += mData[i][k] * rhs.mData[k][j];
    return result;
}

// Scalar multiplication
Matrix Matrix::operator*(double scalar) const {
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result(i + 1, j + 1) = mData[i][j] * scalar;
    return result;
}

// Matrix * Vector multiplication
Vector Matrix::operator*(const Vector& vec) const {
    assert(mNumCols == vec.size());  // Make sure dimensions match
    Vector result(mNumRows);

    for (int i = 0; i < mNumRows; ++i) {
        double sum = 0;
        for (int j = 0; j < mNumCols; ++j) {
            sum += mData[i][j] * vec(j + 1);  // Assuming 1-based indexing in your Vector
        }
        result(i + 1) = sum;  // Assuming 1-based indexing
    }

    return result;
}

Matrix& Matrix::operator++() {
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            mData[i][j] += 1;
    return *this;
}
Matrix Matrix::operator++(int) {
    Matrix temp(*this);  
    ++(*this);           
    return temp;         
}
Matrix& Matrix::operator--() {
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            mData[i][j] -= 1;
    return *this;
}
Matrix Matrix::operator--(int) {
    Matrix temp(*this);  
    --(*this);           
    return temp;         
}

// Determinant calculation (recursive)
double Matrix::Determinant() const {
    assert(mNumRows == mNumCols);
    if (mNumRows == 1)
        return mData[0][0];
    if (mNumRows == 2)
        return mData[0][0] * mData[1][1] - mData[0][1] * mData[1][0];

    double det = 0.0;
    for (int k = 0; k < mNumCols; ++k) {
        Matrix sub(mNumRows - 1, mNumCols - 1);
        for (int i = 1; i < mNumRows; ++i) {
            int colCount = 0;
            for (int j = 0; j < mNumCols; ++j) {
                if (j != k) {
                    sub(i, ++colCount) = mData[i][j];
                }
            }
        }
        det += (k % 2 == 0 ? 1 : -1) * mData[0][k] * sub.Determinant();
    }
    return det;
}

// Matrix inverse using Gauss-Jordan elimination
Matrix Matrix::Inverse() const {
    assert(mNumRows == mNumCols);
    int n = mNumRows;
    Matrix result(n, n), augmented(n, 2 * n);

    // Create augmented matrix [A | I]
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            augmented(i, j) = (*this)(i, j);
            augmented(i, j + n) = (i == j) ? 1.0 : 0.0;
        }

    // Gauss-Jordan elimination
    for (int i = 1; i <= n; ++i) {
        double pivot = augmented(i, i);
        for (int j = 1; j <= 2 * n; ++j)
            augmented(i, j) /= pivot;
        for (int k = 1; k <= n; ++k) {
            if (k != i) {
                double factor = augmented(k, i);
                for (int j = 1; j <= 2 * n; ++j)
                    augmented(k, j) -= factor * augmented(i, j);
            }
        }
    }

    // Extract inverse matrix
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            result(i, j) = augmented(i, j + n);

    return result;
}

// Pseudo-inverse using (A^T * A)^-1 * A^T
Matrix Matrix::PseudoInverse() const {
    Matrix At(mNumCols, mNumRows);
    for (int i = 1; i <= mNumRows; ++i)
        for (int j = 1; j <= mNumCols; ++j)
            At(j, i) = (*this)(i, j);
    Matrix AtA = At * (*this);
    return AtA.Inverse() * At;
}

// Transpose
Matrix Matrix::Transpose() const {
    Matrix result(mNumCols, mNumRows);
    for (int i = 1; i <= mNumRows; ++i)
        for (int j = 1; j <= mNumCols; ++j)
            result(j, i) = (*this)(i, j);
    return result;
}

// Display matrix
void Matrix::display() const {
    for (int i = 0; i < mNumRows; ++i) {
        for (int j = 0; j < mNumCols; ++j)
            cout << mData[i][j] << " ";
        cout << endl;
    }
}

// Scalar * Matrix operator (non-member)
Matrix operator*(double scalar, const Matrix& mat) {
    return mat * scalar;
}
