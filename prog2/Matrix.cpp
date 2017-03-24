#include "Matrix.h"
#include <string.h>

using namespace std;

Matrix::Matrix(size_t top, size_t left, size_t dimension)
    : top(top)
    , left(left)
    , dimension(dimension)
{
}

Matrix::~Matrix()
{
}

void Matrix::add(vector<int>& s1, Matrix m1, vector<int>& s2, Matrix m2, vector<int>& result)
{
    size_t dim = m1.dimension;
    size_t bound = sqrt(s1.size());
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
    size_t bound = sqrt(s1.size());
    size_t r1 = m1.top, r2 = m2.top, c1 = m1.left, c2 = m2.left;
    for (size_t i = 0; i < dim; i++)
        for (size_t j = 0; j < dim; j++)
        {
            int left = (i + r1) < bound && j + c1 < bound ? s1[(i + r1) * bound + j + c1] : 0;
            int right = (i + r2) < bound && j + c2 < bound ? s2[(i + r2) * bound + j + c2] : 0;
            result[i * dim + j] = left - right;
        }      
}


void Matrix::multiply(vector<int>& s1, Matrix m1, vector<int>& s2, Matrix m2, vector<int>& result)
{
    if (m1.dimension == 1)
    {
        Matrix::con_matrix_multiply(s1, m1, s2, m2, result);
        return;
    }

    size_t dim = (m1.dimension + 1)/2;   
    // partition lhs, rhs
    size_t r = m1.top;
    size_t co = m1.left;
    Matrix a = Matrix(r, co, dim);
    Matrix b = Matrix(r, co + dim, dim); 
    Matrix c = Matrix(r + dim, co, dim);   
    Matrix d = Matrix(r + dim, co + dim, dim);
    // a.print(s1);
    // b.print(s1);
    // c.print(s1);
    // d.print(s1);
    r = m2.top;
    co = m2.left;
    Matrix e = Matrix(r, co, dim);
    Matrix f = Matrix(r, co + dim, dim);
    Matrix g = Matrix(r + dim, co, dim);
    Matrix h = Matrix(r + dim, co + dim, dim);

    // compute seven products
    vector<int> pl (dim*dim);
    vector<int> pr (dim*dim);
    Matrix m = Matrix(0, 0, dim);
    
    vector<int> p1 (dim*dim);
    Matrix::subtract(s2, f, s2, h, pl);
    Matrix::multiply(s1, a, pl, m, p1); 
    // m.print(p1);
    vector<int> p2 (dim*dim);
    Matrix::add(s1, a, s1, b, pl);
    Matrix::multiply(pl, m, s2, h, p2); 
    // m.print(p2);
    vector<int> p3 (dim*dim);
    Matrix::add(s1, c, s1, d, pl);
    Matrix::multiply(pl, m, s2, e, p3); 

    vector<int> p4 (dim*dim);
    Matrix::subtract(s2, g, s2, e, pl);
    Matrix::multiply(s1, d, pl, m, p4);

    vector<int> p5 (dim*dim);
    Matrix::add(s1, a, s1, d, pl);
    Matrix::add(s2, e, s2, h, pr);
    Matrix::multiply(pl, m, pr, m, p5);

    vector<int> p6 (dim*dim);
    Matrix::subtract(s1, b, s1, d, pl);
    Matrix::add(s2, g, s2, h, pr);
    Matrix::multiply(pl, m, pr, m, p6);

    vector<int> p7 (dim*dim);
    Matrix::subtract(s1, a, s1, c, pl);
    Matrix::add(s2, e, s2, f, pr);
    Matrix::multiply(pl, m, pr, m, p7);
    
    vector<int> aebg (dim*dim);
    Matrix::add(p5, m, p4, m, aebg);
    Matrix::subtract(aebg, m, p2, m, aebg);
    Matrix::add(aebg, m, p6, m, aebg);

    vector<int> afbh (dim*dim);
    Matrix::add(p1, m, p2, m, afbh);

    vector<int> cedg (dim*dim);
    Matrix::add(p3, m, p4, m, cedg);

    vector<int> cfdh (dim*dim);
    Matrix::add(p5, m, p1, m, cfdh);
    Matrix::subtract(cfdh, m, p3, m, cfdh);
    Matrix::subtract(cfdh, m, p7, m, cfdh);

    size_t dimension = m1.dimension;
    Matrix mr = Matrix(0, 0, dimension);
    Matrix::concatenate(aebg, afbh, cedg, cfdh, result, mr);   
    // mr.print(result); 
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
                result[i * dimension + j] = c[ (i - dim) * dim + j];
            else
                result[i * dimension + j] = d[ (i - dim) * dim + j - dim];
}

void Matrix::con_matrix_multiply(vector<int>& s1, Matrix m1, vector<int>& s2, Matrix m2, vector<int>& result)
{
    size_t dim = m1.dimension;
    size_t r1 = m1.top, r2 = m2.top, c1 = m1.left, c2 = m2.left;
    if (dim == 1)
    {
        size_t bound1 = sqrt(s1.size());
        size_t bound2 = sqrt(s2.size());
        int left = r1 < bound1 && c1 < bound1 ? s1[r1 * bound1 + c1] : 0;
        int right = r2 < bound2 && c2 < bound2 ? s2[r2 * bound2 + c2] : 0;
        result[0] = left * right;
    }
    else
        for (size_t i = 0; i < dim; i++)
            for (size_t k = 0; k < dim; k++)
                for (size_t j = 0; j < dim; j++)
                    result[i * dim + j] += s1[(i + r1) * dim + k + c1] * s2[(k + r2) * dim + j + c2];
}

void Matrix::print(vector<int>& storage)
{
    size_t dim = this->dimension;
    size_t bound = sqrt(storage.size());
    for (size_t i = 0; i < dim; i++)
    {
        for (size_t j = 0; j < dim; j++)
            if (i + this->top < bound && j + this->left < bound)
                printf("%d ", storage[ (i + this->top) * dim + j + this->left]);
            else
                printf("%d ", 0);

        printf("\n");
    }
    printf("\n");
}