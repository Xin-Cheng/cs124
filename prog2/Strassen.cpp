#include "Matrix.h"

void print_matrix(Matrix* m);
int main()
{
    const size_t dim = 3;
    int* a1 = new int[dim*dim]{
        1, 1, 1,
        1, 2, 1,
        1, 1, 1
    };
    int* a2 = new int[dim*dim]{
        1, 1, 1,
        1, 3, 1,
        1, 1, 1
    };
    //const size_t dim = 2;
    //int* a1 = new int[dim*dim]{
    //    1, 1,
    //    1, 2,
    //};
    //int* a2 = new int[dim*dim]{
    //    1, 1,
    //    1, 3,
    //};

    Storage* s1 = new Storage(a1, dim, dim);
    Storage* s2 = new Storage(a2, dim, dim);

    Matrix m1 = Matrix(s1, 0, 0, 2, 2);
    Matrix m2 = Matrix(s2, 0, 0, 2, 2);

    int i = m1.getElement(3, 1);
    Matrix* m = Matrix::multiply(&m1, &m2);
    Matrix* mm = Matrix::con_matrix_multiply(&m1, &m2);
    print_matrix(m);
    print_matrix(mm);
    int j = 0;
    //Matrix* m = m1.multiply(m2);
    //Storage* s = Matrix::con_matrix_multiply(m1, m2);
    //Matrix* m = m1.add(m2);
    //Matrix* s = m1.subtract(m2);
    //Matrix* m = m1.multiply(m2);
    //Matrix a = Matrix(s1, 0, 0, 1, 1);
    //Matrix b = Matrix(s1, 0, 2, 1, 2);
    //Matrix c = Matrix(s1, 2, 0, 2, 1);
    //Matrix d = Matrix(s1, 2, 2, 2, 2);
    //print_matrix(&a);
    //print_matrix(&b);
    //print_matrix(&c);
    //print_matrix(&d);
    //Matrix* m = Matrix::concatenate(a, b, c, d);
    //print_matrix(m);
    return 0;
}

void print_matrix(Matrix* m) {
    size_t row = m->bottom - m->top + 1;
    size_t column = m->right - m->left + 1;
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < column; j++)
        {
            printf("%d ", m->getElement(i, j));
        }
        printf("\n");
    }
}