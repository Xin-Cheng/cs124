#include "Solution.h"
#include "Heap.h"

#define LENGTH 10

Solution::Solution()
{
}
Solution::~Solution()
{
}

RandomSolution::RandomSolution()
    :Solution()
{
}
RandomSolution::~RandomSolution()
{
}
void RandomSolution::move()
{
    srand(time(NULL));
    int i = rand() % LENGTH;
    int j = rand() % LENGTH;
    while (j == i)
        j = rand() % LENGTH;
    if (i % 2)
        this->solution[i] *= -1;
    this->solution[j] *= -1;
}
long long RandomSolution::residue(vector<long long> input)
{
    long long p = 0;
    long long n = 0;
    for (int i = 0; i < LENGTH; i++)
        this->solution[i] == 1 ? p += input[i] : n += input[i];
    return abs(p - n);
}

PartitionedSolution::PartitionedSolution()
    :Solution()
{
}
PartitionedSolution::~PartitionedSolution()
{
}

void PartitionedSolution::move()
{
    srand(time(NULL));
    int i = rand() % LENGTH;
    int j = rand() % LENGTH;
    while (this->solution[i] == j)
        j = rand() % LENGTH;
    this->solution[i] = j;
}
long long PartitionedSolution::residue(vector<long long> input)
{
    long long a[LENGTH] = { 0 };
    for (int j = 0; j < LENGTH; j++)
        a[this->solution[j]] = a[this->solution[j]] + input[j];
    Heap h(a, LENGTH);
    return h.kk();
}