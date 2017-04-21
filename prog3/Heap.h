#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

class Heap
{
public:
    int size;
    vector<long long> elements;
public:
    Heap();
    Heap(long long* arr, int sizes);
    ~Heap();
public:
    long long kk();
    void insert(long long value);
    long long deleteMax();
private:
    void buildHeap();
    void maxHeapify(int idx);
};
#endif