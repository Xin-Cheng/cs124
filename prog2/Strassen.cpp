#include "Matrix.h"
#include <stdio.h>
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

    Storage* s1 = new Storage(a1, dim, dim);
    Storage* s2 = new Storage(a2, dim, dim);

    Matrix m1 = Matrix(s1, 2, 0, 2, 1);
    Matrix m2 = Matrix(s1, 0, 0, 1, 1);

    //Storage* s = Matrix::con_matrix_multiply(m1, m2);
    // Matrix* m = m1.add(m2);
    Matrix* m = m1.subtract(m2);
    print_matrix(m);
    return 0;
}

void print_matrix(Matrix* m) {
    size_t row = m->bottom - m->top + 1;
    size_t column = m->right - m->left + 1;
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < column; j++)
        {
            printf("%d ", (*m)[i][j]);
        }
        printf("\n");
    }
}