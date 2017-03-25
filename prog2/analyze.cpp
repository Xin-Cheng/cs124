#include <iostream>
#include <fstream>
#include <vector>
#include <cstddef>
using namespace std;

int time(size_t dimension, size_t cross);
void calculate(size_t dimension, vector<vector<int>>& result);

int main()
{
    size_t dimension = 1024;
    vector<vector<int>> result(dimension, vector<int>(dimension));
    calculate(dimension, result);
    return 0;
}

void calculate(size_t dimension, vector<vector<int>>& result)
{
    ofstream outputFile;
    outputFile.open("result.csv");
    for (size_t dim = 1; dim <= dimension; dim++)
    {
        for (size_t point = 1; point <= dimension; point++)
        {
            result[dim - 1][point - 1] = time(dim, point);
            outputFile << result[dim - 1][point - 1] << "\t";
        }
        outputFile << endl;
    }
    outputFile.close();
}

int time(size_t dimension, size_t cross)
{
    const int MULTIPLY_TIMES = 7;
    const int ADDITION_TIMES = 18;
    if (dimension <= cross)
        return dimension*dimension*dimension;
    else
        return (MULTIPLY_TIMES * time(dimension / 2, cross) + ADDITION_TIMES * (dimension / 2) * (dimension / 2));
}