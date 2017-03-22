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

Matrix::Matrix(Storage* storage, size_t left, size_t top, size_t right, size_t bottom)
    : storage(storage)
    , left(left)
    , top(top)
    , right(right)
    , bottom(bottom)
{
}

Matrix::~Matrix()
{
}

int* Matrix::operator[](int index)
{
    int* p = this->storage->elements;
    p += (this->top + index)*(this->storage->columnCount) + this->left;
    return p;
}

Storage* Matrix::con_matrix_multiply(Matrix m1, Matrix m2)
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