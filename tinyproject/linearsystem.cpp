#include <iostream>
#include <cmath>
#include <cassert>
#include "linearsystem.hpp"

using namespace std;

// Constructor
LinearSystem::LinearSystem(int size, Matrix* A, Vector* b) {
    if (!A || !b) {
        cout << "Matrix or vector is null." << endl;
        mSize = 0;
        mpA = nullptr;
        mpb = nullptr;
        return;
    }
    assert(b->size() == size);
    
    mSize = size;
    mpA = A;
    mpb = b;
}

// Copy constructor
LinearSystem::LinearSystem(const LinearSystem& other) {
    mSize = other.mSize;
    if (mSize > 0) {
        mpA = new Matrix(*other.mpA);
        mpb = new Vector(*other.mpb);
    } else {
        mpA = nullptr;
        mpb = nullptr;
    }
}
 
Vector LinearSystem::Solve() {
    if (mSize == 0 || mpA == nullptr || mpb == nullptr) {
        cout << "Invalid system." << endl;
        return Vector();
    }

    // Gaussian elimination
    Matrix A = *mpA;
    Vector b = *mpb;

    for (int i = 1; i <= mSize; i++) {
        int pivot = i;          // Find pivot row
        for (int j = i + 1; j <= mSize; j++) {
            if (fabs(A(j, i)) > fabs(A(pivot, i))) {
                pivot = j;
            }
        }

        for (int k = 1; k <= mSize; k++) {
            swap(A(i, k), A(pivot, k)); // Swap rows
        }
        swap(b(i), b(pivot)); // Swap corresponding b values

        for (int j = i + 1; j <= mSize; j++) {
            double factor = A(j, i) / A(i, i);
            for (int k = i; k <= mSize; k++) {
                A(j, k) -= factor * A(i, k); // Eliminate below
            }
            b(j) -= factor * b(i);
        }
    }

    // Back substitution
    Vector x(mSize);
    for (int i = mSize; i >= 1; i--) {
        double sum = b(i);
        for (int j = i + 1; j <= mSize; j++) {
            sum -= A(i, j) * x(j);
        }
        x(i) = sum / A(i, i);
    }

    Vector result = Vector(mSize);
    for(int i = 1; i <= mSize; i++) {
        result[i - 1] = x(i);
    }

    return result;
}

PosSymLinSystem::PosSymLinSystem(int size, Matrix* A, Vector* b) : LinearSystem(size, A, b) {
    if (!isSymmetric()) {
        cout << "Matrix is not symmetric." << endl;
        mSize = 0;
        mpA = nullptr;
        mpb = nullptr;
    }
}

bool PosSymLinSystem::isSymmetric() {
    if (mpA == nullptr) return false;
    for (int i = 1; i <= mSize; ++i) {
        for (int j = 1; j <= mSize; ++j) {
            if ((*mpA)(i, j) != (*mpA)(j, i)) {
                return false;
            }
        }
    }
    return true;
}

bool PosSymLinSystem::isPositiveDefinite() {
    if (!isSymmetric()) return false;

    Matrix A = *mpA;
    int first_pivot = A(1, 1);  // Get the first pivot;

    for (int i = 1; i <= mSize; i++) {
        Matrix sub_matrix = Matrix(i, i);
        for (int j = 1; j <= i; j++) {
            for (int k = 1; k <= i; k++) {
                sub_matrix(j, k) = A(j, k);
            }
        }

        if (sub_matrix.Determinant() <= 0) return false;
    }

    return true;
}

Vector PosSymLinSystem::Solve() {
    if (!(isSymmetric() && isPositiveDefinite())) {
        cout << "Matrix is not positive definite or symmetric." << endl;
        return Vector();
    }
    int maxIter = 1000;
    double tolerance = 1e-10;
    Vector x(mSize);
    Vector r = *mpb - (*mpA) * x; // Initial residual
    Vector p = r; // Initial search direction
    double rsold = r * r; // Initial residual squared
    for (int iter = 0; iter < maxIter; ++iter) {
        if (sqrt(rsold) < tolerance) break; // Convergence check

        Vector Ap = (*mpA) * p; // Matrix-vector product
        double pAp = p * Ap;
        if (fabs(pAp) < 1e-14) {
            cout << "Breakdown in CG: p*Ap is zero." << endl;
            break;
        }
        double alpha = rsold / pAp; // Step size
        x = x + alpha * p; // Update solution
        r = r - alpha * Ap; // Update residual
        double rsnew = r * r; // New residual squared

        if (sqrt(rsnew) < tolerance) break; // Convergence check

        p = r + (rsnew / rsold) * p; // Update search direction
        rsold = rsnew; // Update residual squared for next iteration
    }

    return x; // Return the solution vector
}

NonSquareLinSystem::NonSquareLinSystem(Matrix* A, Vector* b) {
    if (!A || !b) {
        cout << "Matrix or vector is null." << endl;
        mRows = 0;
        mCols = 0;
        mpA = nullptr;
        mpb = nullptr;
        return;
    }
    mRows = A->NumRows();
    mCols = A->NumCols();
    mpA = A;
    mpb = b;
}

//Solve using Moore-Penrose pseudo-inverse
Vector NonSquareLinSystem::SolveMoorePenrose() {       // A+ = (A^T * A)^-1 * A^T
    Matrix Aplus = mpA->PseudoInverse();
    Vector x = Vector(mCols);
    x = Aplus * (*mpb);
    return x;
}

// Solve using Tikhonov regularization
Vector NonSquareLinSystem::SolveTikhonov(double Lambda) {      // A+ = (A^T * A + Lambda * I)^-1 * A^T
    Matrix At = mpA->Transpose();
    Matrix AtA = At * (*mpA);
    Matrix I(mCols, mCols);
    for (int i = 1; i <= mCols; i++) {
        I(i, i) = 1.0; // Identity matrix
    }

    Matrix regularized = AtA + Lambda * I;
    Matrix reg_inverse = regularized.Inverse();
    Matrix A_plus = reg_inverse * At;
    Vector x = Vector(mCols);
    x = A_plus * (*mpb);

    return x;
}