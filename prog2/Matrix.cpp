#include "Matrix.h"
#include <string.h>

using namespace std;

Storage::Storage(int* elements, size_t rowCount, size_t columnCount)
    : rowCount(rowCount)
    , columnCount(columnCount)
{
    size_t sz = sizeof(int)*rowCount*columnCount;
    this->elements = new int[sz];
    memcpy(this->elements, elements, sz);
}

Storage::Storage(size_t rowCount, size_t columnCount)
    : rowCount(rowCount)
    , columnCount(columnCount)
{
    size_t sz = sizeof(int)*rowCount*columnCount;
    this->elements = new int[sz];
    memset(this->elements, 0, sz);
}
Storage::~Storage()
{
    delete this->elements;
}

Matrix::Matrix(Storage* storage, size_t top, size_t left, size_t bottom, size_t right)
    : storage(storage)
    , top(top)
    , left(left)
    , bottom(bottom)
    , right(right)
{
}

Matrix::~Matrix()
{
}

int* Matrix::getRow(int index)
{
    int* p = this->storage->elements;
    p += (this->top + index)*(this->storage->columnCount) + this->left;
    return p;
}
int* Matrix::operator[](int index)
{
    return getRow(index);
}

Matrix* Matrix::add(Matrix& m2)
{
    size_t tr = this->bottom - this->top + 1;
    size_t mr = m2.bottom - m2.top + 1;
    size_t tc = this->right - this->left + 1;
    size_t mc = m2.right - m2.left + 1;
    size_t row = tr > mr ? tr : mr;
    size_t column = tc > mc ? tc : mc;
    Storage* s = new Storage(row, column);
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < column; j++)
        {
            int left = 0, right = 0;
            if (tr > i && tc > j)
                left = this->getRow(i)[j];
            if (mr > i && mc > j)
                right = m2[i][j];
            s->elements[i*column + j] = left + right;
        }
    }
    Matrix* m = new Matrix(s, 0, 0, row - 1, column - 1);
    return m;
}

Matrix* Matrix::subtract(Matrix& m2)
{
    size_t tr = this->bottom - this->top + 1;
    size_t mr = m2.bottom - m2.top + 1;
    size_t tc = this->right - this->left + 1;
    size_t mc = m2.right - m2.left + 1;
    size_t row = tr > mr ? tr : mr;
    size_t column = tc > mc ? tc : mc;
    Storage* s = new Storage(row, column);
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < column; j++)
        {
            int left = 0, right = 0;
            if (tr > i && tc > j)
                left = this->getRow(i)[j];
            if (mr > i && mc > j)
                right = m2[i][j];
            s->elements[i*column + j] = left - right;
        }
    }
    Matrix* m = new Matrix(s, 0, 0, row - 1, column - 1);
    return m;
}

Storage* Matrix::con_matrix_multiply(Matrix& m1, Matrix& m2)
{
    size_t dim = m1.bottom + 1;
    Storage* result = new Storage(dim, dim);
    for (size_t i = 0; i < dim; i++)
    {
        for (size_t k = 0; k < dim; k++)
        {
            for (size_t j = 0; j < dim; j++)
            {
                result->elements[i*dim + j] += m1[i][k] * m2[k][j];
            }
        }
    }
    return result;
}