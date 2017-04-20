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
    vector<int> elements;
public:
    Heap();
    Heap(int* arr, int sizes);
    ~Heap();
public:
    int kk();
    void insert(int value);
    int deleteMax();
private:
    void buildHeap();
    void maxHeapify(int idx);
};
#endif