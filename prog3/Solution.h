#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Solution
{
public:
    vector<int> solution;
public:
    Solution();
    Solution(vector<int> solution);
    virtual ~Solution();
public:
    virtual Solution* move() = 0;
    virtual long long residue(vector<long long> input) = 0;
};

class RandomSolution:public Solution
{
public:
    RandomSolution();
    RandomSolution(vector<int> solution);
    virtual ~RandomSolution();
public:
    virtual Solution* move();
    virtual long long residue(vector<long long> input);
};

class PartitionedSolution :public Solution
{
public:
    PartitionedSolution();
    PartitionedSolution(vector<int> solution);
    virtual ~PartitionedSolution();
public:
    virtual Solution* move();
    virtual long long residue(vector<long long> input);
};

#endif // !SOLUTION_H