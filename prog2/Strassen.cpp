#include "Matrix.h"

void print_matrix(Matrix* m);
int main()
{
    const size_t dim = 7;
    int* a1 = new int[dim*dim]{
        1, 1, 1, 1, 1, 1, 1, 
        1, 2, 1, 1, 1,1, 1,
        1, 1, 1, 1, 1,1, 1,
        1, 1, 1, 1, 1,1, 1,
        1, 1, 1, 1, 1,1, 1,
        1, 1, 1, 1, 1,1, 1,
        1, 1, 1, 1, 1,1, 1    
    };
    int* a2 = new int[dim*dim]{
        1, 1, 1, 1, 1, 1, 1, 
        1, 3, 1, 1, 1,1, 1,
        1, 1, 1, 1, 1,1, 1,
        1, 1, 1, 1, 1,1, 1,
        1, 1, 1, 1, 1,1, 1,
        1, 1, 1, 1, 1,1, 1,
        1, 1, 1, 1, 1,1, 1
    };

    Storage* s1 = new Storage(a1, dim, dim);
    Storage* s2 = new Storage(a2, dim, dim);

    Matrix m1 = Matrix(s1, 0, 0, dim - 1, dim - 1);
    Matrix m2 = Matrix(s2, 0, 0, dim - 1, dim - 1);

    int i = m1.getElement(3, 1);
    Matrix* m = Matrix::multiply(&m1, &m2);
    Matrix* mm = Matrix::con_matrix_multiply(&m1, &m2);
    m->print();
    printf("\n");
    mm->print();
    return 0;
}