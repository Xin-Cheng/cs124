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

int Matrix::getElement(size_t row, size_t column)
{
    int element = 0;
    size_t r = row + this->top;
    size_t c = column + this->left;
    if (r < this->storage->rowCount && c < this->storage->columnCount)
        element = this->storage->elements[r*(this->storage->columnCount) + c];
    return element;
}

Matrix* Matrix::add(Matrix* m1, Matrix* m2)
{
    size_t row = m1->bottom - m1->top + 1;
    size_t column = m1->right - m1->left + 1;
    Storage* s = new Storage(row, column);
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < column; j++)
        {
            s->elements[i*column + j] = m1->getElement(i, j)  + m2->getElement(i, j);
        }
    }
    Matrix* m = new Matrix(s, 0, 0, row - 1, column - 1);
    return m;
}

Matrix* Matrix::subtract(Matrix* m1, Matrix* m2)
{
    size_t row = m1->bottom - m1->top + 1;
    size_t column = m1->right - m1->left + 1;
    Storage* s = new Storage(row, column);
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < column; j++)
        {
            s->elements[i*column + j] = m1->getElement(i, j) - m2->getElement(i, j);
        }
    }
    Matrix* m = new Matrix(s, 0, 0, row - 1, column - 1);
    return m;
}


Matrix* Matrix::multiply(Matrix* m1, Matrix* m2)
{
    if (m1->isScaler())
        return Matrix::con_matrix_multiply(m1, m2);

    size_t dim = (m1->bottom - m1->top + 2)/2;
    
    // partition lhs
    size_t r = m1->top;
    size_t co = m1->left;
    Matrix* a = new Matrix(m1->storage, r, co, r+ dim - 1, co + dim - 1);
    Matrix* b = new Matrix(m1->storage, r, co + dim, r + dim - 1, co + 2 * dim - 1);
    Matrix* c = new Matrix(m1->storage, r + dim, co, r + 2 * dim - 1, co + dim - 1);
    Matrix* d = new Matrix(m1->storage, r + dim, co + dim, r + 2 * dim - 1, co + 2 * dim - 1);

    r = m2->top;
    co = m2->left;
    Matrix* e = new Matrix(m2->storage, r, co, r + dim - 1, co + dim - 1);
    Matrix* f = new Matrix(m2->storage, r, co + dim, r + dim - 1, co + 2 * dim - 1);
    Matrix* g = new Matrix(m2->storage, r + dim, co, r + 2 * dim - 1, co + dim - 1);
    Matrix* h = new Matrix(m2->storage, r + dim, co + dim, r + 2 * dim - 1, co + 2 * dim - 1);

    // compute seven products
    Matrix* p1 = Matrix::multiply(a, Matrix::subtract(f, h));
    Matrix* p2 = Matrix::multiply(Matrix::add(a, b), h);
    Matrix* p3 = Matrix::multiply(Matrix::add(c, d), e);
    Matrix* p4 = Matrix::multiply(d, Matrix::subtract(g, e));
    Matrix* p5 = Matrix::multiply(Matrix::add(a, d), Matrix::add(e, h));
    Matrix* p6 = Matrix::multiply(Matrix::subtract(b, d), Matrix::add(g, h));
    Matrix* p7 = Matrix::multiply(Matrix::subtract(a, c), Matrix::add(e, f));

    Matrix* aebg = Matrix::subtract(Matrix::add(p5, p4), Matrix::subtract(p2, p6));
    Matrix* afbh = Matrix::add(p1, p2);
    Matrix* cedg = Matrix::add(p3, p4);
    Matrix* cfdh = Matrix::subtract(Matrix::add(p5, p1), Matrix::add(p3, p7));

    bool trim = (m1->bottom - m1->top) % 2 == 0 ? true : false;
    Matrix* m = Matrix::concatenate(aebg, afbh, cedg, cfdh, trim);
    return m;
}

Matrix* Matrix::concatenate(Matrix* a, Matrix* b, Matrix* c, Matrix* d, bool trim)
{
    size_t row = c->bottom - c->top + 1 + (a->bottom - a->top + 1);
    size_t column = b->right - b->left + 1 + (a->right - a->left + 1);
    if (trim)
    {
        row--;
        column--;
    }
    Storage* s = new Storage(row, column);

    for (size_t i = 0; i < a->bottom + 1; i++)
    {
        for (size_t j = 0; j < column; j++)
        {
            if (j < a->right + 1)
                s->elements[i*column + j] = a->getElement(i, j);
            else
                s->elements[i*column + j] = b->getElement(i, j - (a->right + 1));
        }
    }
    // copy c and d
    for (size_t i = a->bottom + 1; i < row; i++)
    {
        for (size_t j = 0; j < column; j++)
        {
            if (j < a->right + 1)
                s->elements[i*column + j] = c->getElement(i - (a->bottom + 1), j);
            else
                s->elements[i*column + j] = d->getElement(i - (a->bottom + 1), j - (a->right + 1));
        }
    }
    Matrix* m = new Matrix(s, 0, 0, row - 1, column - 1);
    return m;
}

Matrix* Matrix::con_matrix_multiply(Matrix* m1, Matrix* m2)
{
    size_t row = m1->bottom - m1->top + 1;
    size_t column = m1->right - m1->left + 1;
    Storage* s = new Storage(row, column);
    Matrix* m = new Matrix(s, 0, 0, row - 1, column - 1);
    for (size_t i = 0; i < row; i++)
    {
        for (size_t k = 0; k < column; k++)
        {
            for (size_t j = 0; j < column; j++)
            {
                s->elements[i*column + j] += m1->getElement(i, k) * m2->getElement(k, j);
            }
        }
    }
    return m;
}

void Matrix::print()
{
    size_t row = this->bottom - this->top + 1;
    size_t column = this->right - this->left + 1;
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < column; j++)
        {
            printf("%d ", this->getElement(i, j));
        }
        printf("\n");
    }
}

bool Matrix::isScaler()
{
    if (this->right == this->left)
        return true;
    return false;
}