#include "Solution.h"
#include "Heap.h"

#define LENGTH 10

Solution::Solution()
{
}
Solution::Solution(vector<int> solution)
    :solution(solution)
{
}
Solution::~Solution()
{
}

RandomSolution::RandomSolution()
    :Solution()
{
}
RandomSolution::RandomSolution(vector<int> solution)
    :Solution(solution)
{
}
RandomSolution::~RandomSolution()
{
}
Solution* RandomSolution::move()
{
    vector<int> newSol;
    newSol = this->solution;
    srand(time(NULL));
    int i = rand() % LENGTH;
    int j = rand() % LENGTH;
    while (j == i)
        j = rand() % LENGTH;
    if (i % 2)
        newSol[i] *= -1;
    newSol[j] *= -1;
    return new RandomSolution (newSol);
}
Solution* RandomSolution::random()
{
    vector<int> newSol;
    srand(time(NULL));
    for (int i = 0; i < LENGTH; i++)
        rand() % 2 ? newSol.push_back(1) : newSol.push_back(-1);
    return new RandomSolution (newSol);
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
PartitionedSolution::PartitionedSolution(vector<int> solution)
    :Solution(solution)
{
}
PartitionedSolution::~PartitionedSolution()
{
}

Solution* PartitionedSolution::move()
{
    vector<int> newSol;
    newSol = this->solution;
    srand(time(NULL));
    int i = rand() % LENGTH;
    int j = rand() % LENGTH;
    while (newSol[i] == j)
        j = rand() % LENGTH;
    newSol[i] = j;
    return new PartitionedSolution (newSol);
}
Solution* PartitionedSolution::random()
{
    vector<int> newSol;
    srand(time(NULL));
    for (int i = 0; i < LENGTH; i++)
        newSol.push_back(rand() % LENGTH);
    return new RandomSolution (newSol);
}
long long PartitionedSolution::residue(vector<long long> input)
{
    long long a[LENGTH] = { 0 };
    for (int j = 0; j < LENGTH; j++)
        a[this->solution[j]] = a[this->solution[j]] + input[j];
    Heap h(a, LENGTH);
    return h.kk();
}