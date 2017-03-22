#include "Matrix.h"
#include <stdio.h>
void print_matrix(Storage* s);
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

    Matrix m1 = Matrix(s1, 0, 0, 1, 1);
    Matrix m2 = Matrix(s1, 0, 2, 1, 2);

    //Storage* s = Matrix::con_matrix_multiply(m1, m2);
    Storage* s = m1.add(m2);
    print_matrix(s);
    return 0;
}

void print_matrix(Storage* s) {
    size_t row = s->rowCount;
    size_t column = s->columnCount;
    for (size_t i = 0; i < s->rowCount; i++)
    {
        for (size_t j = 0; j < s->columnCount; j++)
        {
            printf("%d ", s->elements[i*row + j]);
        }
        printf("\n");
    }
}
