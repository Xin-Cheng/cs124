// Programming assignment 2
#include "Matrix.h"
#include <stdlib.h> 
#include <time.h> 
#include <chrono>

using namespace std;

int main()
{
    const size_t dim = 300;
    vector<int> s1 (dim*dim);
    vector<int> s2 (dim*dim);
    // srand (time(NULL));
     
    // for (size_t i = 0; i < dim * dim; i++)
    // {
    //     a1[i] = rand() % 2;
    //     a2[i] = rand() % 2;
    // }
    for (size_t i = 0; i < dim * dim; i++)
    {
        s1[i] = 1;
        s2[i] = 2;
    }
    Matrix m = Matrix(0, 0, dim);
    // m.print(s1);
    // m.print(s2);
    // vector<int> sum (dim*dim);
    // Matrix::add(s1, m1, s2, m2, sum); 
    vector<int> product (dim*dim);
    Matrix::multiply(s1, m, s2, m, product); 
    //auto sstart = chrono::steady_clock::now();
    // vector<int> diff (dim*dim);
    // Matrix::subtract(s1, m1, s2, m2, diff); 
    //auto sfinish = chrono::steady_clock::now();
    //auto cstart = chrono::steady_clock::now();
    // Matrix* mm = Matrix::con_matrix_multiply(&m1, &m2);
    //auto cfinish = chrono::steady_clock::now();
    //m->print();
    //printf("%ld: Strassen\n", (sfinish - sstart).count());
    // m.print(product);
    //printf("%ld: Conventional\n", (cfinish - cstart).count());
    return 0;
}