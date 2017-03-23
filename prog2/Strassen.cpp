// Programming assignment 2
#include "Matrix.h"
#include <stdlib.h> 
#include <time.h> 
#include <chrono>

using namespace std;
void print_matrix(Matrix* m);
int main()
{
    const size_t dim = 300;
    int* a1 = new int[dim*dim];
    int* a2 = new int[dim*dim];
    srand (time(NULL));
     
    for (size_t i = 0; i < dim * dim; i++)
    {
        a1[i] = rand() % 2;
        a2[i] = rand() % 2;
    }

    Storage* s1 = new Storage(a1, dim, dim);
    Storage* s2 = new Storage(a2, dim, dim);

    Matrix m1 = Matrix(s1, 0, 0, dim - 1, dim - 1);
    Matrix m2 = Matrix(s2, 0, 0, dim - 1, dim - 1);

    auto sstart = chrono::steady_clock::now();
    Matrix* m = Matrix::multiply(&m1, &m2);
    auto sfinish = chrono::steady_clock::now();
    auto cstart = chrono::steady_clock::now();
    Matrix* mm = Matrix::con_matrix_multiply(&m1, &m2);
    auto cfinish = chrono::steady_clock::now();
    //m->print();
    printf("%ld: Strassen\n", (sfinish - sstart).count());
    //mm->print();
    printf("%ld: Conventional\n", (cfinish - cstart).count());
    return 0;
}