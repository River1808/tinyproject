#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

using namespace std;

class Vector {
private:
    int mSize;
    double* mData;
public:
    // Constructor
    Vector(int size);
    Vector() : mSize(0), mData(nullptr) {}
    // Copy constructor
    Vector(const Vector& other);

    // Destructor
    ~Vector();

    // Assignment operator
    Vector& operator=(const Vector& other);

    // Unary operators
    Vector operator+() const;
    Vector operator-() const;
    Vector(const double* data, int size);
    // Binary operators
    Vector operator+(const Vector& rhs) const;
    Vector operator-(const Vector& rhs) const;
    Vector operator*(double scalar) const;
    double operator*(const Vector& rhs) const; 
    // Friend function for scalar * vector
    friend Vector operator*(double scalar, const Vector& vec);
    // Prefix increment
    Vector& operator++();        // ++v
    // Postfix increment
    Vector operator++(int);      // v++
    // Prefix decrement
    Vector& operator--();        // --v
    // Postfix decrement
    Vector operator--(int);      // v--
    // Indexing operators
    double& operator[](int index);
    const double& operator[](int index) const;

    double& operator()(int index);
    const double& operator()(int index) const;

    // Get vector size
    int size() const;
    double* data() const;

    // Display function
    void display() const;
};

#endif // VECTOR_HPP