#include "Matrix.h"

void print_matrix(Matrix* m);
int main()
{
    const size_t dim = 5;
    int* a1 = new int[dim*dim]{
        1, 1, 1, 1, 1,
        1, 2, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        
    };
    int* a2 = new int[dim*dim]{
        1, 1, 1, 1, 1,
        1, 3, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 1,
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

    Matrix m1 = Matrix(s1, 0, 0, dim - 1, dim - 1);
    Matrix m2 = Matrix(s2, 0, 0, dim - 1, dim - 1);

    int i = m1.getElement(3, 1);
    Matrix* m = Matrix::multiply(&m1, &m2);
    Matrix* mm = Matrix::con_matrix_multiply(&m1, &m2);
    m->print();
    printf("\n");
    mm->print();
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