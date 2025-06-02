#include "Tests.h"
//Original file, cannot run use Tests.cpp instead
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>

#include "LinearSystem.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"

using namespace std;

bool test1()
{
    cout << YELLOW << "TEST 1" << RESET << "\n";

    Vector v(3);
    v(1) = 3;
    v(2) = 1;
    v(3) = 4;

    v.display();
    cout << "Expected: [3, 1, 4]\n";

    return v(1) == 3 && v(2) == 1 && v(3) == 4;
}

bool test2()
{
    cout << YELLOW << "TEST 2" << RESET << "\n";

    double data[] = {1, 5, 9};
    Vector v(data, 3);

    v.display();
    cout << "Expected: [1, 5, 9]\n";

    return v(1) == 1 && v(2) == 5 && v(3) == 9;
}

bool test3()
{
    cout << YELLOW << "TEST 3" << RESET << "\n";

    double data[] = {2, 6, 5};
    Vector v1(data, 3);
    Vector v2(v1);

    cout << "v1 = ";
    v1.display();
    cout << "v2 = ";
    v2.display();
    cout << "Expected: v1 == v2\n";

    return v2(1) == 2 && v2(2) == 6 && v2(3) == 5;
}

bool test4()
{
    cout << YELLOW << "TEST 4" << RESET << "\n";

    double data[] = {3, 5, 8, 9};
    Vector v(data, 4);
    Vector v1 = -v;

    cout << "v1 = ";
    v1.display();
    cout << "v = ";
    v.display();
    cout << "Expected: v1 = [-3, -5, -8, -9]\n";

    return v1(1) == -3 && v1(2) == -5 && v1(3) == -8 && v1(4) == -9;
}

bool test5()
{
    cout << YELLOW << "TEST 5" << RESET << "\n";

    double data[] = {7, 9, 3, 2, 3};
    Vector v(data, 5);
    Vector v1 = ++v;
    Vector v2 = v++;

    cout << "v1 = ";
    v1.display();
    cout << "v2 = ";
    v2.display();
    cout << "v = ";
    v.display();
    cout << "Expected: v1 = v2 = [8, 10, 4, 3, 4]; v = [9, 11, 5, 4, 5]\n";

    return v1(1) == 8 && v2(1) == 8 && v(1) == 9;
}

bool test6()
{
    cout << YELLOW << "TEST 6" << RESET << "\n";

    double data[] = {8, 4, 6};
    Vector v(data, 3);
    Vector v1 = --v;
    Vector v2 = v--;

    cout << "v1 = ";
    v1.display();
    cout << "v2 = ";
    v2.display();
    cout << "v = ";
    v.display();
    cout << "Expected: v1 = v2 = [7, 4, 5]; v = [6, 3, 4]\n";

    return v1(1) == 7 && v2(1) == 7 && v(1) == 6;
}

bool test7()
{
    cout << YELLOW << "TEST 7" << RESET << "\n";

    double data1[] = {2, 6, 4, 3};
    Vector v1(data1, 4);
    double data2[] = {3, 8, 3, 2};
    Vector v2(data2, 4);
    Vector v = v1 + v2;
    Vector vv = v;
    vv = vv + v2;

    cout << "v1 = ";
    v1.display();
    cout << "v2 = ";
    v2.display();
    cout << "v = v1 + v2\nv = ";
    v.display();
    cout << "Expected: v = [5, 14, 7, 5]\n";
    cout << "v += v2\nv= ";
    vv.display();
    cout << "Expected: v = [8, 22, 10, 7]\n";

    return v(1) == 5 && v(2) == 14 && v(3) == 7 && v(4) == 5 && vv(1) == 8 &&
           vv(2) == 22 && vv(3) == 10 && vv(4) == 7;
}

bool test8()
{
    cout << YELLOW << "TEST 8" << RESET << "\n";

    double data1[] = {2, 6, 4, 3};
    Vector v1(data1, 4);
    double data2[] = {3, 8, 3, 2};
    Vector v2(data2, 4);
    Vector v = v1 - v2;
    Vector vv = v;
    vv = vv - v2;

    cout << "v1 = ";
    v1.display();
    cout << "v2 = ";
    v2.display();
    cout << "v = v1 + v2\nv = ";
    v.display();
    cout << "Expected: v = [-1, -2, 1, 1]\n";
    cout << "v -= v2\nv =  ";
    vv.display();
    cout << "Expected: v = [-4, -10, -2, -1]\n";

    return v(1) == -1 && v(2) == -2 && v(3) == 1 && v(4) == 1 && vv(1) == -4 &&
           vv(2) == -10 && vv(3) == -2 && vv(4) == -1;
}

bool test9()
{
    cout << YELLOW << "TEST 9" << RESET << "\n";

    double data1[] = {2, 6, 4, 3};
    Vector v1(data1, 4);
    double data2[] = {3, 8, 3, 2};
    Vector v2(data2, 4);
    double v = v1 * v2;
    v1 = v1 * 5;
    cout << "5 * v1 = ";
    v1.display();
    cout << "v2 = ";
    v2.display();
    cout << "v = v1 * v2 = " << v << endl;
    cout << "Expected: v1 = [10, 30, 20, 15]; v = 72\n";

    return v1(1) == 10 && v1(2) == 30 && v1(3) == 20 && v1(4) == 15 && v == 72;
}

bool test10()
{
    cout << YELLOW << "TEST 10" << RESET << "\n";

    Matrix m(2, 2);
    m(1, 1) = 7;
    m(1, 2) = 9;
    m(2, 1) = 5;
    m(2, 2) = 0;

    m.display();
    cout << "Expected: [[7, 9], [5, 0]]\n";

    return m(1, 1) == 7 && m(1, 2) == 9 && m(2, 1) == 5 && m(2, 2) == 0;
}

bool test31()
{
    cout << YELLOW << "TEST 31" << RESET << "\n";

    double **data = new double *[2];
    data[0] = new double[2]{2, 8};
    data[1] = new double[2]{8, 4};
    Matrix m(data, 2, 2);

    m.display();
    cout << "Expected: [[2, 8], [8, 4]]\n";

    return m(1, 1) == 2 && m(1, 2) == 8 && m(2, 1) == 8 && m(2, 2) == 4;
}

bool test11() {
    cout << YELLOW << "TEST 11" << RESET << "\n";

    // 2x3 pseudo-inverse matrix test
    Matrix m3(2, 3);
    m3(1, 1) = 5;
    m3(1, 2) = -8;
    m3(1, 3) = 2;
    m3(2, 1) = 0;
    m3(2, 2) = 7;
    m3(2, 3) = -2;
    cout << "Pseudo-inverse of m3: ";
    m3.PseudoInverse().display();
    cout << "Expected: [[0.199398043641836, 0.225733634311512]," << endl;
    cout << "	[−0.00300978179082, 0.128668171557562]," << endl;
    cout << "	[−0.010534236267871, −0.049661399548533]]" << endl;

    // 5x3 pseudo-inverse matrix test
    Matrix m4(5, 3);
    m4(1, 1) = 5;
    m4(1, 2) = -8;
    m4(1, 3) = 2;
    m4(2, 1) = 0;
    m4(2, 2) = 7;
    m4(2, 3) = -2;
    m4(3, 1) = 2;
    m4(3, 2) = 9;
    m4(3, 3) = -3;
    m4(4, 1) = -4;
    m4(4, 2) = -1;
    m4(4, 3) = 8;
    m4(5, 1) = 0;
    m4(5, 2) = 0;
    m4(5, 3) = -3;
    cout << "Pseudo-inverse of m4: ";
    m4.PseudoInverse().display();
    cout << "Expected: [[0.148736738954454, 0.030732961242952, 0.107139306662122, -0.010509422975871, -0.056495249456776]," << endl; 
    cout << "[−0.005879596097312, 0.045457514947524, 0.073813074290259, 0.02955704202349, -0.029219036257509]," << endl; 
    cout << "	[0.064249499382216, 0.020169570959908, 0.053308337948958, 0.10696604320225, -0.07201227046142]]" << endl;

    return true;
}

bool test12()
{
    cout << YELLOW << "TEST 12" << RESET << "\n";

    double **data = new double *[2];
    data[0] = new double[2]{1, 9};
    data[1] = new double[2]{7, 1};
    Matrix m1(data, 2, 2);
    Matrix m(m1);

    m.display();
    cout << "Expected: [[1, 9], [7, 1]]\n";

    return m(1, 1) == 1 && m(1, 2) == 9 && m(2, 1) == 7 && m(2, 2) == 1;
}

bool test13()
{
    cout << YELLOW << "TEST 13" << RESET << "\n";

    double **data = new double *[2];
    data[0] = new double[2]{3, 5};
    data[1] = new double[2]{8, 9};
    Matrix m(data, 2, 2);
    Matrix m1 = -m;

    cout << "m1 = \n";
    m1.display();
    cout << "m = \n";
    m.display();
    cout << "Expected: m1 = [[-3, -5], [-8, -9]]\n";

    return m1(1, 1) == -3 && m1(1, 2) == -5 && m1(2, 1) == -8 && m1(2, 2) == -9;
}

bool test14()
{
    cout << YELLOW << "TEST 14" << RESET << "\n";

    double **data = new double *[2];
    data[0] = new double[2]{7, 9};
    data[1] = new double[2]{3, 2};
    Matrix m(data, 2, 2);
    Matrix m1 = ++m;
    Matrix m2 = m++;

    cout << "m1 = \n";
    m1.display();
    cout << "m2 = \n";
    m2.display();
    cout << "m = \n";
    m.display();
    cout << "Expected: m1 = m2 = [[8, 10], [4, 3]]; m = [[9, 11], [5, 4]]\n";

    return m1(1, 1) == 8 && m2(1, 1) == 8 && m(1, 1) == 9;
}

bool test15()
{
    cout << YELLOW << "TEST 15" << RESET << "\n";

    double **data = new double *[2];
    data[0] = new double[2]{7, 9};
    data[1] = new double[2]{3, 2};
    Matrix m(data, 2, 2);
    Matrix m1 = --m;
    Matrix m2 = m--;

    cout << "m1 = \n";
    m1.display();
    cout << "m2 = \n";
    m2.display();
    cout << "m = \n";
    m.display();
    cout << "Expected: m1 = m2 = [[6, 8], [2, 1]]; m = [[5, 7], [1, 0]]\n";

    return m1(1, 1) == 6 && m2(1, 1) == 6 && m(1, 1) == 5;
}

bool test16()
{
    cout << YELLOW << "TEST 16" << RESET << "\n";

    double **data1 = new double *[2];
    data1[0] = new double[2]{10, 10};
    data1[1] = new double[2]{10, 10};
    Matrix m1(data1, 2, 2);

    double **data2 = new double *[2];
    data2[0] = new double[2]{1, 2};
    data2[1] = new double[2]{3, 5};
    Matrix m2(data2, 2, 2);
    Matrix m3 = m1 + m2;
    Matrix m4 = m1;
    m4 = m4 + m2;

    cout << "m3 = \n";
    m3.display();
    cout << "m4 = \n";
    m4.display();
    cout << "Expected: m3 = m4 = [[11, 12], [13, 15]]\n";

    return m3(1, 1) == 11 && m3(1, 2) == 12 && m3(2, 1) == 13 &&
           m3(2, 2) == 15 && m4(1, 1) == 11 && m4(1, 2) == 12 &&
           m4(2, 1) == 13 && m4(2, 2) == 15;
}

bool test17()
{
    cout << YELLOW << "TEST 17" << RESET << "\n";

    double **data1 = new double *[2];
    data1[0] = new double[2]{10, 10};
    data1[1] = new double[2]{10, 10};
    Matrix m1(data1, 2, 2);

    double **data2 = new double *[2];
    data2[0] = new double[2]{1, 2};
    data2[1] = new double[2]{3, 5};
    Matrix m2(data2, 2, 2);
    Matrix m3 = m1 - m2;
    Matrix m4 = m1;
    m4 = m4 - m2;

    cout << "m3 = \n";   
    m3.display();
    cout << "m4 = \n";
    m4.display();
    cout << "Expected: m3 = m4 = [[9, 8], [7, 5]]\n";

    return m3(1, 1) == 9 && m3(1, 2) == 8 && m3(2, 1) == 7 && m3(2, 2) == 5 &&
           m4(1, 1) == 9 && m4(1, 2) == 8 && m4(2, 1) == 7 && m4(2, 2) == 5;
}

bool test18()
{
    cout << YELLOW << "TEST 18" << RESET << "\n";

    double **data1 = new double *[2];
    data1[0] = new double[2]{2, 4};
    data1[1] = new double[2]{6, 8};
    Matrix m1(data1, 2, 2);

    double **data2 = new double *[2];
    data2[0] = new double[2]{1, 2};
    data2[1] = new double[2]{3, 5};
    Matrix m2(data2, 2, 2);
    Matrix m3 = m1 * m2;
    Matrix m4 = m1;
    m4 = m4 * m2;

    cout << "m3 = \n";
    m3.display();
    cout << "m4 = \n";
    m4.display();
    cout << "Expected: m3 = m4 = [[14, 24], [30, 52]]\n";

    return m3(1, 1) == 14 && m3(1, 2) == 24 && m3(2, 1) == 30 &&
           m3(2, 2) == 52 && m4(1, 1) == 14 && m4(1, 2) == 24 &&
           m4(2, 1) == 30 && m4(2, 2) == 52;
}

bool test19()
{
    cout << YELLOW << "TEST 19" << RESET << "\n";

    double **data1 = new double *[2];
    data1[0] = new double[2]{2, 4};
    data1[1] = new double[2]{6, 8};
    Matrix m1(data1, 2, 2);

    double data2[] = {5, 10};
    Vector v(data2, 2);
    Vector v3 = m1 * v;
    Matrix m4 = m1;
    Vector v4 = m4 * v;

    cout << "v3 = \n";
    v3.display();
    cout << "v4 = \n";
    v4.display();
    cout << "Expected: v3 = v4 = [50, 110]\n";

    return v3(1) == 50 && v3(2) == 110 && v4(1) == 50 && v4(2) == 110;
}

bool test20()
{
    cout << YELLOW << "TEST 18" << RESET << "\n";

    double **data1 = new double *[2];
    data1[0] = new double[2]{1, 2};
    data1[1] = new double[2]{3, 5};
    Matrix m1(data1, 2, 2);
    double k = 1.5;
    Matrix m2 = m1 * k;
    Matrix m3 = m1;
    m3 = m3 * k;

    cout << "m2 = \n";
    m2.display();
    cout << "m3 = \n";
    m3.display();
    cout << "Expected: m2 = m3 = [[1.5, 3], [4.5, 7.5]]\n";

    return m2(1, 1) == 1.5 && m2(1, 2) == 3 && m2(2, 1) == 4.5 &&
           m2(2, 2) == 7.5 && m3(1, 1) == 1.5 && m3(1, 2) == 3 &&
           m3(2, 1) == 4.5 && m3(2, 2) == 7.5;
}


bool test21()
{
    double **data1 = new double *[4];
    data1[0] = new double[4]{3, 1, 4, 1};
    data1[1] = new double[4]{5, 9, 2, 6};
    data1[2] = new double[4]{5, 3, 5, 8};
    data1[3] = new double[4]{9, 7, 9, 3};
    Matrix m1(data1, 4, 4);
    float d = m1.Determinant();
    cout << "det (\n";
    m1.display();
    cout << "\n) = " << d << "\n";
    cout << "Expected: 98\n";
    return d == 98;
}

bool test22()
{
    // NOT IMPLEMENTED
    return true;
}

bool test23()
{
    cout << YELLOW << "TEST 23" << RESET << "\n";
    Matrix A1(3, 3);
    A1(1, 1) = 2;
    A1(1, 2) = 1;
    A1(1, 3) = -1;
    A1(2, 1) = -3;
    A1(2, 2) = -1;
    A1(2, 3) = 2;
    A1(3, 1) = -2;
    A1(3, 2) = 1;
    A1(3, 3) = 2;

    double b1_arr[] = {8, -11, -3};
    Vector b1(b1_arr, 3);

    LinearSystem sys1(3, &A1, &b1);
    Vector x1 = sys1.Solve();
    cout << "LinearSystem::Solve() solution: ";
    x1.display();
    cout << " (Expected: [2, 3, -1])" << endl;
    return true;
}

bool test24()
{
    cout << YELLOW << "TEST 24" << RESET << "\n";

    Matrix A(3, 3);
    A(1, 1) = 25;
    A(1, 2) = 15;
    A(1, 3) = -5;
    A(2, 1) = 15;
    A(2, 2) = 18;
    A(2, 3) = 0;
    A(3, 1) = -5;
    A(3, 2) = 0;
    A(3, 3) = 11;

    double b_arr[] = {35, 33, 6};
    Vector b(b_arr, 3);

    PosSymLinSystem sys(3, &A, &b);
    Vector x = sys.Solve();
    cout << "x = ";
    x.display();
    cout << " (Expected: [1, 1, 1])" << endl;

    return true;
}

bool test25()
{
    cout << YELLOW << "TEST 25" << RESET << "\n";
    Matrix m2(2, 2);
    m2(1, 1) = 4;
    m2(1, 2) = 6;
    m2(2, 1) = 3;
    m2(2, 2) = 8;
    double det = m2.Determinant();
    cout << "Determinant: " << det << " (Expected: 14)" << endl;
    return true;
}

bool test26()
{
    cout << YELLOW << "TEST 26" << RESET << "\n";
    Matrix m3(3, 3);
    m3(1, 1) = 6;
    m3(1, 2) = 1;
    m3(1, 3) = 1;
    m3(2, 1) = 4;
    m3(2, 2) = -2;
    m3(2, 3) = 5;
    m3(3, 1) = 2;
    m3(3, 2) = 8;
    m3(3, 3) = 7;
    double det = m3.Determinant();
    cout << "Determinant: " << det << " (Expected: -306)" << endl;
    return fabs(det + 306) < 1e-4;
}

bool test27()
{
    cout << YELLOW << "TEST 27" << RESET << "\n";
    Matrix m4(2, 2);
    m4(1, 1) = 1;
    m4(1, 2) = 2;
    m4(2, 1) = 2;
    m4(2, 2) = 4;
    double det = m4.Determinant();
    cout << "Determinant: " << det << " (Expected: 0)" << endl;
    return fabs(det) < 1e-4;
}

bool test28()
{
    cout << YELLOW << "TEST 28" << RESET << "\n";
    Matrix A_spd(2, 2);
    A_spd(1, 1) = 4;
    A_spd(1, 2) = 1;
    A_spd(2, 1) = 1;
    A_spd(2, 2) = 3;
    double b_spd_arr[] = {1, 2};
    Vector b_spd(b_spd_arr, 2);
    PosSymLinSystem sys_spd(2, &A_spd, &b_spd);
    Vector x_spd = sys_spd.Solve();
    cout << "x = ";
    x_spd.display();
    cout << " (Expected: [0.0909,0.6364])" << endl;
    return fabs(x_spd(1) - 0.0909) < 1e-4 && fabs(x_spd(2) - 0.6364) < 1e-4;
}

bool test29()
{
    cout << YELLOW << "TEST 29 " << RESET << "\n";
    Matrix A_id(3, 3);
    A_id(1, 1) = 1;
    A_id(1, 2) = 0;
    A_id(1, 3) = 0;
    A_id(2, 1) = 0;
    A_id(2, 2) = 1;
    A_id(2, 3) = 0;
    A_id(3, 1) = 0;
    A_id(3, 2) = 0;
    A_id(3, 3) = 1;
    double b_id_arr[] = {7, 8, 9};
    Vector b_id(b_id_arr, 3);
    PosSymLinSystem sys_id(3, &A_id, &b_id);
    Vector x_id = sys_id.Solve();
    cout << "x = ";
    x_id.display();
    cout << " (Expected: [7, 8, 9])" << endl;
    return fabs(x_id(1) - 7) < 1e-4 && fabs(x_id(2) - 8) < 1e-4 &&
           fabs(x_id(3) - 9) < 1e-4;
}

bool test30()
{
    // cout << YELLOW << "TEST 30 " << RESET << "\n";
    // Matrix A_hilb(3, 3);
    // A_hilb(1, 1) = 1.0;
    // A_hilb(1, 2) = 1.0 / 2.0;
    // A_hilb(1, 3) = 1.0 / 3.0;
    // A_hilb(2, 1) = 1.0 / 2.0;
    // A_hilb(2, 2) = 1.0 / 3.0;
    // A_hilb(2, 3) = 1.0 / 4.0;
    // A_hilb(3, 1) = 1.0 / 3.0;
    // A_hilb(3, 2) = 1.0 / 4.0;
    // A_hilb(3, 3) = 1.0 / 5.0;
    // double b_hilb_arr[] = {1, 1, 1};
    // Vector b_hilb(b_hilb_arr, 3);
    // PosSymLinSystem sys_hilb(3, &A_hilb, &b_hilb);
    // Vector x_hilb = sys_hilb.Solve();
    // cout << "x = ";
    // x_hilb.display();
    // cout << "(Hilbert-like 3x3)" << endl;
    // // No exact expected value, just check solution is finite
    // return isfinite(x_hilb(1)) && isfinite(x_hilb(2)) && isfinite(x_hilb(3));

    cout << CYAN << "PART B\n\n"
         << YELLOW << "TEST 30" << RESET << "\n";

    // Extract data from .data file
    ifstream file("machine.data"); // Open the dataset file
    string line;

    // 209x6 Matrix to store attributes
    Matrix A(209, 6);
    // Create an array to hold PRP values
    double arr_PRP[209];

    // Indexting from 1
    int rows = 1;
    int cols = 1;

    while (getline(file, line))
    {
        stringstream ss(line);
        string value;

        int attributesCount =
            0;                   // Track how many of the six attributes we've processed
        int ignoreNameCount = 0; // Skip vendor name and model name
        int loopsCount = 0;      // Ensure we only process up to the PRP column

        while (getline(ss, value, ',') && loopsCount < 9)
        {
            if (ignoreNameCount < 2)
            {
                ignoreNameCount++;
                loopsCount++;
                continue; // Skip vendor and model
            }

            // Store predictive attributes into the matrix
            if (attributesCount < 6)
            {
                A(rows, cols) = stoi(value);
                cols++;
                attributesCount++;
                loopsCount++;
                continue;
            }

            arr_PRP[rows - 1] = stoi(value); // Store PRP into the array
            loopsCount++;
        }

        cols = 1; // Reset column for next row
        rows++;
    }
    file.close(); // Clean up

    Vector b(arr_PRP, 209); // Convert the array to a Vector

    // Split the data randomly. Ratio 80 : 20
    Matrix A_train(167, 6);
    Vector b_train(167);
    Matrix A_test(42, 6);
    Vector b_test(42);

    srand(time(0)); // seed the random number. Make it random everytime we run
                    // the program

    int ate0Percent = 0;       // count until 167 (80%)
    int tu0Percent = 0;        // count until 42 (20%)
    int currentRows_train = 1; // For () in matrix
    int currentRows_test = 1;

    for (int i = 1; i <= 209; i++)
    {
        int ratio = rand() % 10;

        if ((ratio <= 8 && ate0Percent < 167) ||
            (ratio > 8 && tu0Percent >= 42))
        {
            for (int j = 1; j <= 6; j++)
            {
                A_train(currentRows_train, j) = A(i, j);
            }

            b_train(currentRows_train) = b(i);
            currentRows_train++;
            ate0Percent++;
        }
        else if (tu0Percent < 42)
        {
            for (int j = 1; j <= 6; j++)
            {
                A_test(currentRows_test, j) = A(i, j);
            }

            b_test(currentRows_test) = b(i);
            currentRows_test++;
            tu0Percent++;
        }
    }

    // Solve for x;
    NonSquareLinSystem system(&A_train, &b_train);
    Vector result = system.SolveMoorePenrose(); // Solve the normal equations

    // Now calculate RMSE
    double sumSquaredError = 0.0;

    for (int i = 1; i <= 42; i++)
    {
        double predicted = 0.0;

        for (int j = 1; j <= 6; j++)
        {
            predicted += A_test(i, j) * result(j);
        }

        double error = b_test(i) - predicted;
        sumSquaredError += error * error;
    }

    double RMSE = sqrt(sumSquaredError / 42);

    // Print result

    cout << "RMSE: " << RMSE << endl;
    cout << "RESULT: ";
    result.display();
    return true;
}
