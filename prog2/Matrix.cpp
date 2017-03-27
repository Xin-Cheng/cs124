#include "Matrix.h"
#include <string.h>

using namespace std;

Matrix::Matrix(size_t top, size_t left, size_t dimension, size_t storageD)
    : top(top)
    , left(left)
    , dimension(dimension)
    , storageD(storageD)
{
}

Matrix::~Matrix()
{
}

void Matrix::add(vector<int>& s1, Matrix m1, vector<int>& s2, Matrix m2, vector<int>& result)
{
    size_t dim = m1.dimension;
    size_t bound = m1.storageD;
    size_t r1 = m1.top, r2 = m2.top, c1 = m1.left, c2 = m2.left;
    for (size_t i = 0; i < dim; i++)
        for (size_t j = 0; j < dim; j++)
        {
            int left = (i + r1) < bound && j + c1 < bound ? s1[(i + r1) * bound + j + c1] : 0;
            int right = (i + r2) < bound && j + c2 < bound ? s2[(i + r2) * bound + j + c2] : 0;
            result[i * dim + j] = left + right;
        }
}

void Matrix::subtract(vector<int>& s1, Matrix m1, vector<int>& s2, Matrix m2, vector<int>& result)
{
    size_t dim = m1.dimension;
    size_t bound = m1.storageD;
    size_t r1 = m1.top, r2 = m2.top, c1 = m1.left, c2 = m2.left;
    for (size_t i = 0; i < dim; i++)
        for (size_t j = 0; j < dim; j++)
        {
            int left = (i + r1) < bound && j + c1 < bound ? s1[(i + r1) * bound + j + c1] : 0;
            int right = (i + r2) < bound && j + c2 < bound ? s2[(i + r2) * bound + j + c2] : 0;
            result[i * dim + j] = left - right;
        }
}


void Matrix::multiply(vector<int>& s1, Matrix m1, vector<int>& s2, Matrix m2, vector<int>& result, size_t cross)
{
    size_t dimension = m1.dimension;
    if (dimension <= cross)
    {
        Matrix::con_matrix_multiply(s1, m1, s2, m2, result);
        return;
    }
    size_t dim = (dimension + 1) / 2, r = m1.top, co = m1.left, sd = m1.storageD;
    // partition lhs, rhs
    Matrix a = Matrix(r, co, dim, sd);
    Matrix b = Matrix(r, co + dim, dim, sd);
    Matrix c = Matrix(r + dim, co, dim, sd);
    Matrix d = Matrix(r + dim, co + dim, dim, sd);
    r = m2.top;
    co = m2.left;
    sd = m2.storageD;
    Matrix e = Matrix(r, co, dim, sd);
    Matrix f = Matrix(r, co + dim, dim, sd);
    Matrix g = Matrix(r + dim, co, dim, sd);
    Matrix h = Matrix(r + dim, co + dim, dim, sd);

    // compute seven products
    vector<int> pl(dim*dim);
    vector<int> pr(dim*dim);
    Matrix m = Matrix(0, 0, dim, dim);

    vector<int> p1(dim*dim);
    Matrix::subtract(s2, f, s2, h, pl);
    Matrix::multiply(s1, a, pl, m, p1, cross);

    vector<int> p2(dim*dim);
    Matrix::add(s1, a, s1, b, pl);
    Matrix::multiply(pl, m, s2, h, p2, cross);

    vector<int> p3(dim*dim);
    Matrix::add(s1, c, s1, d, pl);
    Matrix::multiply(pl, m, s2, e, p3, cross);

    vector<int> p4(dim*dim);
    Matrix::subtract(s2, g, s2, e, pl);
    Matrix::multiply(s1, d, pl, m, p4, cross);

    vector<int> p5(dim*dim);
    Matrix::add(s1, a, s1, d, pl);
    Matrix::add(s2, e, s2, h, pr);
    Matrix::multiply(pl, m, pr, m, p5, cross);

    vector<int> p6(dim*dim);
    Matrix::subtract(s1, b, s1, d, pl);
    Matrix::add(s2, g, s2, h, pr);
    Matrix::multiply(pl, m, pr, m, p6, cross);

    vector<int> p7(dim*dim);
    Matrix::subtract(s1, a, s1, c, pl);
    Matrix::add(s2, e, s2, f, pr);
    Matrix::multiply(pl, m, pr, m, p7, cross);

    vector<int> aebg(dim*dim);
    Matrix::add(p5, m, p4, m, aebg);
    Matrix::subtract(aebg, m, p2, m, aebg);
    Matrix::add(aebg, m, p6, m, aebg);

    vector<int> afbh(dim*dim);
    Matrix::add(p1, m, p2, m, afbh);

    vector<int> cedg(dim*dim);
    Matrix::add(p3, m, p4, m, cedg);

    vector<int> cfdh(dim*dim);
    Matrix::add(p5, m, p1, m, cfdh);
    Matrix::subtract(cfdh, m, p3, m, cfdh);
    Matrix::subtract(cfdh, m, p7, m, cfdh);

    Matrix mr = Matrix(0, 0, dimension, dimension);
    Matrix::concatenate(aebg, afbh, cedg, cfdh, result, mr);
}

void Matrix::concatenate(vector<int>& a, vector<int>& b, vector<int>& c, vector<int>& d, vector<int>& result, Matrix& m)
{
    size_t dimension = m.dimension;
    size_t dim = (dimension + 1) / 2;
    // copy ab
    for (size_t i = 0; i < dim; i++)
        for (size_t j = 0; j < dimension; j++)
            if (j < dim)
                result[i * dimension + j] = a[i * dim + j];
            else
                result[i * dimension + j] = b[i * dim + j - dim];
    // copy c and d
    for (size_t i = dim; i < dimension; i++)
        for (size_t j = 0; j < dimension; j++)
            if (j < dim)
                result[i * dimension + j] = c[(i - dim) * dim + j];
            else
                result[i * dimension + j] = d[(i - dim) * dim + j - dim];
}

void Matrix::con_matrix_multiply(vector<int>& s1, Matrix m1, vector<int>& s2, Matrix m2, vector<int>& result)
{
    size_t dim = m1.dimension;
    size_t r1 = m1.top, r2 = m2.top, c1 = m1.left, c2 = m2.left;
    size_t bound1 = m1.storageD;
    size_t bound2 = m2.storageD;
    for (size_t i = 0; i < dim; i++)
        for (size_t k = 0; k < dim; k++)
            for (size_t j = 0; j < dim; j++)
            {
                int left = i + r1 < bound1 && k + c1 < bound1 ? s1[(i + r1) * bound1 + k + c1] : 0;
                int right = k + r2 < bound2 && j + c2 < bound2 ? s2[(k + r2) * bound2 + j + c2] : 0;
                result[i * dim + j] += left * right;
            }                   
}

void Matrix::print(vector<int>& storage)
{
    size_t dim = this->dimension;
    size_t bound = this->storageD;
    for (size_t i = 0; i < dim; i++)
    {
        for (size_t j = 0; j < dim; j++)
            if (i + this->top < bound && j + this->left < bound)
                printf("%d ", storage[(i + this->top) * dim + j + this->left]);
            else
                printf("%d ", 0);

        printf("\n");
    }
    printf("\n");
}

void Matrix::printDiagonal(vector<int>& storage)
{
    size_t dim = this->dimension;
    size_t bound = this->storageD;
    for (size_t i = 0; i < dim; i++)
        printf("%d\n", storage[(i + this->top) * dim + i + this->left]);
    printf("\n");
}