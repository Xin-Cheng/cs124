#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
class Matrix
{
public:
    size_t top, left, dimension, storageD;

public:
    Matrix(size_t top, size_t left, size_t dimension, size_t storageD);
    ~Matrix();

public:
    void print(vector<int>& storage);
    static void con_matrix_multiply(vector<int>& s1, Matrix m1, vector<int>& s2, Matrix m2, vector<int>& result);
    static void add(vector<int>& s1, Matrix m1, vector<int>& s2, Matrix m2, vector<int>& result);
    static void subtract(vector<int>& s1, Matrix m1, vector<int>& s2, Matrix m2, vector<int>& result);
    static void multiply(vector<int>& s1, Matrix m1, vector<int>& s2, Matrix m2, vector<int>& result, size_t cross);
    static void concatenate(vector<int>& s1, vector<int>& s2, vector<int>& s3, vector<int>& s4, vector<int>& result, Matrix& m);
};

#endif