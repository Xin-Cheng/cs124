#include "heap.h"
#include <time.h>

using namespace std;
long long MAX_RAND = 1000000000000;

int main()
{
    Heap h;
    srand(time(NULL));
    for (int i = 0; i < 100; i++)
    {
        long long r1 = rand();
        long long r2 = (r1 << 32) | rand();
        h.insert(r2 % MAX_RAND + 1);
    }
    long long arr[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    // int arr[] = { 10, 8, 7, 6, 5 };
    // Heap h(arr, sizeof(arr)/sizeof(long long));
    long long diff = h.kk();
    return 0;
}

