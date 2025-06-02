#include "vector.hpp"
#include <iostream>
#include <cassert>

using namespace std;

// Constructor
Vector::Vector(int size) {
    assert(size >= 0); // Ensure size is non-negative
    mSize = size;
    if (mSize == 0) {
        mData = nullptr; // Handle zero size case
    } else if (mSize > 0) {
        mData = new double[mSize](); // Allocate memory for data
    }
}

// Copy constructor
Vector::Vector(const Vector& other) {
    mSize = other.mSize;
    mData = new double[mSize];
    for (int i = 0; i < mSize; ++i)
        mData[i] = other.mData[i];
}

Vector::Vector(const double* data, int size) {
    assert(size >= 0); // Ensure size is non-negative
    mSize = size;
    if (mSize == 0) {
        mData = nullptr;
    } else {
        mData = new double[mSize]();
        if (data != nullptr) {
            for (int i = 0; i < mSize; ++i)
                mData[i] = data[i];
        }
    }
}

// Destructor
Vector::~Vector() {
    delete[] mData;
    mSize = 0;
}

// Get size
int Vector::size() const {
    return mSize;
}

// Get data
double* Vector::data() const {
    return mData;
}

// Assignment operator
Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        delete[] mData;
        mSize = other.mSize;
        if (mSize == 0) {
            mData = nullptr; // Handle zero size case
        } else if (mSize > 0) {
            mData = new double[mSize](); // Allocate memory for data
            for (int i = 0; i < mSize; ++i)
                mData[i] = other.mData[i];
        }
    }
    return *this;
}

// Unary +
Vector Vector::operator+() const {
    return *this;
}

// Unary -
Vector Vector::operator-() const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = -mData[i];
    return result;
}

// Vector + Vector
Vector Vector::operator+(const Vector& rhs) const {
    assert (mSize == rhs.mSize); // Ensure sizes match
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = mData[i] + rhs.mData[i];
    return result;
}

// Vector - Vector
Vector Vector::operator-(const Vector& rhs) const {
    assert (mSize == rhs.mSize); // Ensure sizes match
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = mData[i] - rhs.mData[i];
    return result;
}

// Vector * scalar
Vector Vector::operator*(double scalar) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = mData[i] * scalar;
    return result;
}

//vector * vector
double Vector::operator*(const Vector& rhs) const {
    assert (mSize == rhs.mSize); // Ensure sizes match
    double result = 0.0;
    for (int i = 0; i < mSize; ++i)
        result += mData[i] * rhs.mData[i];
    return result;
}

// scalar * Vector (friend)
Vector operator*(double scalar, const Vector& vec) {
    return vec * scalar;
}

// Prefix ++v
Vector& Vector::operator++() {
    for (int i = 0; i < mSize; ++i)
        ++mData[i];
    return *this;
}

// Postfix v++
Vector Vector::operator++(int) {
    Vector temp(*this);  // Copy current state
    ++(*this);           // Use prefix to increment
    return temp;         // Return original
}

// Prefix --v
Vector& Vector::operator--() {
    for (int i = 0; i < mSize; ++i)
        --mData[i];
    return *this;
}

// Postfix v--
Vector Vector::operator--(int) {
    Vector temp(*this);
    --(*this);
    return temp;
}

// operator[] (non-const)
double& Vector::operator[](int index) {
    assert(index >= 0 && index < mSize); // Ensure index is within bounds
    return mData[index];
}

// operator[] (const)
const double& Vector::operator[](int index) const {
    assert(index >= 0 && index < mSize); // Ensure index is within bounds
    return mData[index];
}

// operator() (non-const)
double& Vector::operator()(int index) {
    assert(index > 0 && index <= mSize); // Ensure index is within bounds
    return mData[index - 1];
}

// operator() (const)
const double& Vector::operator()(int index) const {
    assert(index > 0 && index <= mSize); // Ensure index is within bounds
    return mData[index - 1];
}

// Display
void Vector::display() const {
    cout << "[";
    for (int i = 0; i < mSize; ++i) {
        cout << mData[i];
        if (i != mSize - 1)
            cout << ", ";
    }
    cout << "]" << endl;
}
