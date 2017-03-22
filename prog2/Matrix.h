#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>

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
    int* operator[](int index);

public:
    static Storage* con_matrix_multiply(Matrix& m1, Matrix& m2);
    Storage* add(Matrix& m2);

private:
    int* getRow(int index);
};

#endif