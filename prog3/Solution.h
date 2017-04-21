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
    virtual ~Solution();
public:
    virtual void move() = 0;
    virtual long long residue(vector<long long> input) = 0;
};

class RandomSolution:public Solution
{
public:
    RandomSolution();
    virtual ~RandomSolution();
public:
    virtual void move();
    virtual long long residue(vector<long long> input);
};

class PartitionedSolution :public Solution
{
public:
    PartitionedSolution();
    virtual ~PartitionedSolution();
public:
    virtual void move();
    virtual long long residue(vector<long long> input);
};

#endif // !SOLUTION_H