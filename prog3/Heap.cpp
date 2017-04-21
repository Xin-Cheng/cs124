#include "Heap.h"

using namespace std;

Heap::Heap()
    : size(0)
{
}
Heap::Heap(long long* arr, int size)
    : size(size)
{
    this->elements = vector<long long>(arr, arr + size);
}
Heap::~Heap()
{
}

void Heap::insert(long long value)
{
    this->elements.push_back(value);
    this->size++;
    int idx = this->size - 1;
    for (; idx > 0 && value > this->elements[(idx - 1) / 2]; idx = (idx - 1) / 2)
        this->elements[idx] = this->elements[(idx - 1) / 2];
    this->elements[idx] = value;
}

long long Heap::deleteMax()
{
    long long max = this->elements[0];
    this->elements[0] = this->elements[this->size - 1];
    this->elements.pop_back();
    this->size--;
    maxHeapify(0);
    return max;
}

void Heap::buildHeap()
{
    for (int i = this->size / 2 - 1; i >= 0; i--)
        maxHeapify(i);
}
void Heap::maxHeapify(int idx)
{
    int child;
    long long temp = this->elements[idx];
    int size = this->size;
    for (; idx * 2 + 1 < size; idx = child)
    {
        child = idx * 2 + 1;
        if (child < size - 1 && this->elements[child + 1] > this->elements[child])
            child++;
        if (this->elements[child] > temp)
            this->elements[idx] = this->elements[child];
        else
            break;
    }
    this->elements[idx] = temp;
}

long long Heap::kk()
{
    this->buildHeap();
    int size = this->size;     
    while (size > 2)
    {
        long long max = deleteMax();
        long long nextMax = deleteMax();
        insert(max - nextMax);
        size = this->size;
    }
    return size == 1 ? this->elements[0] : abs(this->elements[0] - this->elements[1]);
}
