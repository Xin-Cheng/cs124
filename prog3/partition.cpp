#include "heap.h"

int main()
{
    //int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    int arr[] = { 10, 8, 7, 6, 5 };
    Heap h(arr, sizeof(arr)/sizeof(int));
    int diff = h.kk();
    return 0;
}