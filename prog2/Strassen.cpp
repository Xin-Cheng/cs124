// Programming assignment 2
#include "Matrix.h"
#include <stdlib.h> 
#include <time.h> 
#include <chrono>

using namespace std;

int main()
{
    const size_t dim = 1024;
    vector<int> s1 (dim*dim);
    vector<int> s2 (dim*dim);
    vector<int> product (dim*dim);
    vector<int> con_product (dim*dim);
    Matrix m = Matrix(0, 0, dim, dim);

    srand (time(NULL));
    for (size_t i = 0; i < dim * dim; i++)
    {
        s1[i] = rand() % 2;
        s2[i] = rand() % 2;
    }  

    //Matrix::con_matrix_multiply(s1, m, s2, m, product); 
    auto sstart = chrono::steady_clock::now();
    Matrix::multiply(s1, m, s2, m, product); 
    auto sfinish = chrono::steady_clock::now();
    // m.print(product); 
    auto cstart = chrono::steady_clock::now();
    Matrix::con_matrix_multiply(s1, m, s2, m, con_product); 
    auto cfinish = chrono::steady_clock::now();
    // m.print(con_product); 
    printf("%ld: Strassen\n", (sfinish - sstart).count());
    printf("%ld: Conventional\n", (cfinish - cstart).count());
    return 0;
}