#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

void buildHeap(vector<int>& input);
void maxHeapify(vector<int>& input, int idx);
int kk(vector<int>& input);
void insert(vector<int>& input, int value);
int deleteMax(vector<int>& input);

int main()
{
    //int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    int arr[] = { 10, 8, 7, 6, 5 };
    vector<int> input(arr, arr + sizeof(arr)/sizeof(int));
    buildHeap(input);
    int diff = kk(input);
    return 0;
}

int kk(vector<int>& input)
{
    int size = input.size();     
    while (size > 2)
    {
        int max = deleteMax(input);
        int nextMax = deleteMax(input);
        insert(input, max - nextMax);
        size = input.size();
    }
    return size == 1 ? input[0] : abs(input[0] - input[1]);
}
void buildHeap(vector<int>& input)
{
    for (int i = input.size() / 2 - 1; i >= 0; i--)
        maxHeapify(input, i);
}
int deleteMax(vector<int>& input)
{
    int max = input[0];
    input[0] = input[input.size() - 1];
    input.pop_back();
    maxHeapify(input, 0);
    return max;
}
void insert(vector<int>& input, int value)
{
    input.push_back(value);
    int idx = input.size() - 1;
    for (; idx > 0 && value > input[(idx - 1) / 2]; idx = (idx - 1) / 2)
        input[idx] = input[(idx - 1) / 2];
    input[idx] = value;
}
void maxHeapify(vector<int>& input, int idx)
{
    int child;
    int temp = input[idx];
    int size = input.size();
    for (; idx * 2 + 1 < size; idx = child)
    {
        child = idx * 2 + 1;
        if (child < size - 1 && input[child + 1] > input[child])
            child++;
        if (input[child] > temp)
            input[idx] = input[child];
        else
            break;
    }
    input[idx] = temp;
}