// Programming assignment 2
#include "Matrix.h"
#include <stdlib.h> 
#include <time.h> 
#include <chrono>
#include <string>

using namespace std;

const size_t CrossPoint = 90;

void run(int dimension, FILE* file);
void test();
void explore();
void showUsage();

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        showUsage();
        return -1;
    }

    switch (*argv[1])
    {
    case '0':
    {
        int dimension = atoi(argv[2]);
        FILE* file = fopen(argv[3], "r");
        if (dimension < 1)
        {
            printf("bad dimension number: %d\n", dimension);
            exit(-1);
        }
        if (file == nullptr)
        {
            printf("can't open file: %s\n", argv[3]);
            exit(-1);
        }
        run(dimension, file);
    }
    break;
    case '1':
        test();
        break;
    case '2':
        explore();
        break;
    default:
        break;
    }

    return 0;
}

void run(int dimension, FILE* file)
{
    vector<int> s1(dimension * dimension);
    vector<int> s2(dimension * dimension);
    vector<int> product(dimension * dimension);
    Matrix m = Matrix(0, 0, dimension, dimension);

    int value;
    size_t count1 = 0;
    while (count1 < dimension * dimension && fscanf(file, "%d", &value) == 1)
        s1[count1++] = value;
    size_t count2 = 0;
    while (count2 < dimension * dimension && fscanf(file, "%d", &value) == 1)
        s2[count2++] = value;

    if (count2 < dimension * dimension)
    {
        printf("bad file format\n");
        exit(-1);
    }

    Matrix::multiply(s1, m, s2, m, product, CrossPoint);
    m.printDiagonal(product);
}

void test()
{
    const size_t dim = 1024;
    vector<int> s1(dim * dim);
    vector<int> s2(dim * dim);
    vector<int> product(dim * dim);
    vector<int> con_product(dim * dim);
    Matrix m = Matrix(0, 0, dim, dim);

    srand(time(NULL));
    for (size_t i = 0; i < dim * dim; i++)
    {
        s1[i] = rand() % 2;
        s2[i] = rand() % 2;
    }

    //Matrix::con_matrix_multiply(s1, m, s2, m, product); 
    auto sstart = chrono::steady_clock::now();
    Matrix::multiply(s1, m, s2, m, product, CrossPoint);
    auto sfinish = chrono::steady_clock::now();
    auto cstart = chrono::steady_clock::now();
    Matrix::con_matrix_multiply(s1, m, s2, m, con_product);
    auto cfinish = chrono::steady_clock::now();
    printf("%ld\n", CrossPoint);
    printf("%ld: Strassen\n", (sfinish - sstart).count());
    printf("%ld: Conventional\n", (cfinish - cstart).count());
}

void explore()
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
    for (size_t dim = CROSS; dim < DIMENSION; dim += 10)
    {
        vector<int> product(DIMENSION*DIMENSION);
        Matrix m = Matrix(0, 0, dim, dim);
        for (size_t cross = CROSS; cross < maxCross; cross += 5)
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

void showUsage()
{
    printf("usage: ./strassen 0 dimension inputfile\n");
}