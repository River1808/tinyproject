#ifndef LINEARSYSTEM_HPP
#define LINEARSYSTEM_HPP

#include <iostream>
#include <cmath>
#include "matrix.hpp"
#include "vector.hpp"
using namespace std;

class LinearSystem {
protected:
    int mSize;
    Matrix* mpA;
    Vector* mpb;
public: 
    LinearSystem (int size, Matrix* A, Vector* b);
    virtual Vector Solve();
    LinearSystem(const LinearSystem&);
    LinearSystem& operator = (const LinearSystem&) = delete;
};

class PosSymLinSystem : public LinearSystem {
public: 
    PosSymLinSystem(int size, Matrix* A, Vector* b);
    bool isPositiveDefinite();
    bool isSymmetric();
    Vector Solve() override;
};

class NonSquareLinSystem {
protected:
    Matrix* mpA;
    Vector* mpb;
    int mRows, mCols;
public:
    NonSquareLinSystem(Matrix* A, Vector* b);
    
    Vector SolveMoorePenrose();
    Vector SolveTikhonov(double lambda = 0.1);
};

#endif // LINEARSYSTEM_HPP