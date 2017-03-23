#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
#include <stdio.h>
class Storage
{
public:
    int* elements;
    size_t rowCount;
    size_t columnCount;

public:
    Storage(int* elements, size_t rowCount, size_t columnCount);
    Storage(size_t rowCount, size_t columnCount);
    ~Storage();
};

class Matrix
{
public:
    Storage* storage;
    size_t top, left, bottom, right;

public:
    Matrix(Storage* storage, size_t top, size_t left, size_t bottom, size_t right);
    ~Matrix();

public:
    int getElement(size_t row, size_t column);

public:
    void print();
    static Matrix* con_matrix_multiply(Matrix* m1, Matrix* m2);
    static Matrix* add(Matrix* m1, Matrix* m2);
    static Matrix* subtract(Matrix* m1, Matrix* m2);
    static Matrix* multiply(Matrix* m1, Matrix* m2);
    static Matrix* concatenate(Matrix* a, Matrix* b, Matrix* c, Matrix* d);

private:
    bool isScaler();
};

#endif