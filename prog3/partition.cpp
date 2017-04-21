#include "Heap.h"
#include "Solution.h"

using namespace std;
long long MAX_RAND = 1000000000000;

int main()
{
    Heap h;
    Solution* s = new RandomSolution();
    Solution* p = new PartitionedSolution();
    srand(time(NULL));
    for (int i = 0; i < 10; i++)
    {
        long long r1 = rand();
        long long r2 = (r1 << 32) | rand();
        // h.insert(r2 % MAX_RAND + 1);
        h.insert(r1 % 10 + 1);
        r1 % 2 ? s->solution.push_back(1) : s->solution.push_back(-1);
        p->solution.push_back(r1 % 10);
    }
    long long rs = s->residue(h.elements);
    long long rp = p->residue(h.elements);
    long long rk = h.kk();
    return 0;
}

