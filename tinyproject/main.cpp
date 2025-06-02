//for testing
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath> 
#include "linearsystem.hpp"
#include "matrix.hpp"
#include "vector.hpp"
#include "Tests.h"
using namespace std;

// int main() {
//     cout << "===== VECTOR TEST =====" << endl;
//     Vector n(3);
//     n[0] = 15; n[1] = 2; n[2] = 50;
    
//     Vector v(3);
//     v[0] = 5; v[1] = 20; v[2] = 30;

//     n.display();

//     cout << n(3) << endl;
//     cout << n[2] << endl; 

//     n(2) = 99;
//     n.display();

//     n[3] = 5; 
//     n(0) = 5; 
    
//     Vector c = n + v;
//     c.display();

//     Vector d = v - n;
//     d.display(); 
    
//     Vector f = 3.0 * n;
//     f.display(); 
    
//     Vector e = v * 2.0;
//     e.display();


//     cout << "\n===== MATRIX TEST =====" << endl;
//     Matrix A(2, 2);
//     A(1, 1) = 4; A(1, 2) = 3;
//     A(2, 1) = 3; A(2, 2) = 2;

//     cout << "Matrix A:" << endl;
//     A.display();

//     cout << "\nDeterminant of A: " << A.Determinant() << endl;
//     //Transpose
//     Matrix At = A.Transpose();
//     cout << "\nTranspose of A:\n";
//     At.display();
//     //Inverse
//     Matrix B = A.Inverse();
//     cout << "\nInverse of A:" << endl;
//     B.display();

//     Matrix result1 = A*B;
//     cout << "\nA * inverse_A:" << endl;
//     result1.display();
//     cout<<"\nMatrix C:\n";
//     Matrix C(2, 2);
//     C(1, 1) = 4; C(1, 2) = 7;
//     C(2, 1) = 2; C(2, 2) = 6;
//     C.display();
//     Matrix C1 = A*C;
//     cout<<"\n A * C: "<<endl;
//     C1.display();
    
//     Matrix Ascaled = A * 2.0;
//     cout << "\nA * 2.0:\n";
//     Ascaled.display();
//     Matrix Ascaled1 = 2.0*A;
//     cout << "\n2.0 * A:\n";
//     Ascaled1.display();
//     //Matrix x Vector
//     cout<<"\nMatrix * Vector: "<<endl;
//     Matrix M(2, 2);
//     M(1,1) = 1; M(1,2) = 2;
//     M(2,1) = 3; M(2,2) = 4;
//     cout<<"Vector M:"<<endl;
//     M.display();
//     Vector V(2);
//     V(1) = 5;
//     V(2) = 6;
//     cout<<"Vector V:"<<endl;
//     V.display();
//     Vector result = M * V;
//     cout << "M * V = ";
//     result.display();
//     // Pseudo-Inverse test (non-square matrix)
//     Matrix F(3, 2);
//     F(1,1) = 1; F(1,2) = 2;
//     F(2,1) = 3; F(2,2) = 4;
//     F(3,1) = 5; F(3,2) = 6;

//     cout << "\nMatrix F:\n";
//     F.display();

//     Matrix Fpinv = F.PseudoInverse();
//     cout << "\nPseudo-Inverse of F:\n";
//     Fpinv.display();

    
//     cout<<"\n===== Linear System TEST =====" << endl;
//     Matrix* X = new Matrix(2, 2);
//     (*X)(1,1) = 4; (*X)(1,2) = 1;
//     (*X)(2,1) = 1; (*X)(2,2) = 3;

//     // Step 2: Define vector b
//     Vector* b = new Vector(2);
//     (*b)(1) = 1;
//     (*b)(2) = 2;

//     // Step 3: Solve using PosSymLinSystem
//     PosSymLinSystem system(2, X, b);
//     double* x = system.Solve();

//     // Step 4: Output the result
//     if (x != nullptr) {
//         cout << "Solution x:" << endl;
//         for (int i = 0; i < 2; ++i)
//             cout << "x[" << i << "] = " << x[i] << endl;
//         delete[] x;
//     }

//     // A is 3x2 (overdetermined)
//     Matrix* A2 = new Matrix(3, 2);
//     (*A2)(1,1) = 1; (*A2)(1,2) = 2;
//     (*A2)(2,1) = 3; (*A2)(2,2) = 4;
//     (*A2)(3,1) = 5; (*A2)(3,2) = 6;

//     Vector* b2 = new Vector(3);
//     (*b2)(1) = 1;
//     (*b2)(2) = 2;
//     (*b2)(3) = 3;

//     NonSquareLinSystem nonsquareSystem(A2, b2);
    
//     Vector* x1 = nonsquareSystem.SolveMoorePenrose();
//     cout << "Moore-Penrose solution: " << endl;
//     x1->display();
//     delete x1;

//     Vector* x2 = nonsquareSystem.SolveTikhonov(0.1);
//     cout << "Tikhonov solution (lambda=0.1): " << endl;
//     x2->display();
//     delete x2;

//     cout<<"\n===== Part B =====" << endl;
    
//     const int total_instances = 209;
//     const int features_count = 6;
//     const double train_ratio = 0.8;
//     const int train_size = static_cast<int>(total_instances * train_ratio);
//     const int test_size = total_instances - train_size;

//     double features_all[total_instances][features_count];
//     double targets_all[total_instances];

//     ifstream fin("machine.data");
//     if (!fin) {
//         cerr << "Failed to open dataset file machine.data\n";
//         return 1;
// }

//     int idx = 0;
//     string line;
//     while (getline(fin, line) && idx < total_instances) {
//         istringstream iss(line);
//         string vendor, model;
//         int MYCT, MMIN, MMAX, CACH, CHMIN, CHMAX, PRP, ERP;

//         if (!(getline(iss, vendor, ',') &&
//             getline(iss, model, ',') &&
//           (iss >> MYCT) && iss.ignore(1) &&
//           (iss >> MMIN) && iss.ignore(1) &&
//           (iss >> MMAX) && iss.ignore(1) &&
//           (iss >> CACH) && iss.ignore(1) &&
//           (iss >> CHMIN) && iss.ignore(1) &&
//           (iss >> CHMAX) && iss.ignore(1) &&
//           (iss >> PRP) && iss.ignore(1) &&
//           (iss >> ERP))) {
//             continue;
//     }

//         features_all[idx][0] = MYCT;
//         features_all[idx][1] = MMIN;
//         features_all[idx][2] = MMAX;
//         features_all[idx][3] = CACH;
//         features_all[idx][4] = CHMIN;
//         features_all[idx][5] = CHMAX;
//         targets_all[idx] = PRP;

//         ++idx;
// }
//     fin.close();

//     if (idx < total_instances) {
//         cout << "Warning: only read " << idx << " instances." << endl;
// }

//     Matrix P(train_size, features_count);
//     Vector m(train_size);

//     for (int i = 0; i < train_size; ++i) {
//         for (int j = 0; j < features_count; ++j) {
//             P(i + 1, j + 1) = features_all[i][j];
//     }
//         m(i + 1) = targets_all[i];
// }

//     Matrix Pt = P.Transpose();
//     Matrix PtP = Pt * P;
//     Vector Ptm = Pt * m;

//     PosSymLinSystem regSystem(features_count, &PtP, &Ptm);
//     double* y = regSystem.Solve();

//     cout << "\nLearned regression parameters:\n";
//     for (int i = 0; i < features_count; ++i)
//         cout << "y[" << i << "] = " << x[i] << endl;

//     double rmse = 0.0;
//     for (int i = train_size; i < total_instances; ++i) {
//         double pred = 0.0;
//         for (int j = 0; j < features_count; ++j) {
//         pred += x[j] * features_all[i][j];
//     }
//         double error = pred - targets_all[i];
//         rmse += error * error;
// }
//     rmse = sqrt(rmse / test_size);

//     cout << "Test RMSE: " << rmse << endl;

//     delete[] y;

// }

void testing() {
    bool (*tests[TESTS_COUNT])() = {
        test1,  test2,  test3,  test4,  test5,  test6,  test7,  test8,
        test9,  test10, test11, test12, test13, test14, test15, test16,
        test17, test18, test19, test20, test21, test22, test23, test24,
        test25, test26, test27, test28, test29, test30, test31};

    int testsPassed = 0;
    for (int i = 0; i < TESTS_COUNT; i++) {
        bool passed = tests[i]();
        if (passed) {
            cout << GREEN << "Test " << (i + 1) << " passed" << RESET;
            testsPassed++;
        } else {
            cout << RED << "Test " << (i + 1) << " failed" << RESET;
        }
        cout << "\n\n";
    }

    if (testsPassed == TESTS_COUNT) {
        cout << GREEN;
    } else if (testsPassed == 0) {
        cout << RED;
    } else {
        cout << YELLOW;
    }

    cout << "Total Passed: " << testsPassed << "/" << TESTS_COUNT << "."
         << RESET << "\n";
}

int main() {
    testing();
}