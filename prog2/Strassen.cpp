// Programming assignment 2
#include "Matrix.h"
#include <stdlib.h> 
#include <time.h> 
#include <chrono>

using namespace std;
void test();

int main()
{
    const size_t dim = 1024;
    const size_t cross = 130;
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
    Matrix::multiply(s1, m, s2, m, product, cross); 
    auto sfinish = chrono::steady_clock::now();
    // m.print(product); 
    auto cstart = chrono::steady_clock::now();
    Matrix::con_matrix_multiply(s1, m, s2, m, con_product); 
    auto cfinish = chrono::steady_clock::now();
    // m.print(con_product); 
    printf("%ld\n", cross);
    printf("%ld: Strassen\n", (sfinish - sstart).count());
    printf("%ld: Conventional\n", (cfinish - cstart).count());
    return 0;
}

void test()
{
    const size_t DIMENSION = 1024;
    const size_t CROSS = 30;
    const size_t maxCross = 200;
    vector<int> s1(DIMENSION*DIMENSION);
    vector<int> s2(DIMENSION*DIMENSION);

    srand(time(NULL));
    for (size_t i = 0; i < DIMENSION * DIMENSION; i++)
    {
        s1[i] = rand() % 2;
        s2[i] = rand() % 2;
    }

    ofstream outputFile;
    outputFile.open("runtime.csv");
    for (size_t dim = CROSS; dim < DIMENSION; dim+=10)
    {
        vector<int> product(DIMENSION*DIMENSION);
        Matrix m = Matrix(0, 0, dim, dim);
        for (size_t cross = CROSS; cross < maxCross; cross+=5)
        {
            auto sstart = chrono::steady_clock::now();
            Matrix::multiply(s1, m, s2, m, product, cross);
            auto sfinish = chrono::steady_clock::now();
            outputFile << (sfinish - sstart).count() << "\t";
        }
        outputFile << endl;
    }
    outputFile.close();
}