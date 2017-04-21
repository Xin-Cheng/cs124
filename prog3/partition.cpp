#include "Heap.h"
#include "Solution.h"

using namespace std;
#define MAX_RAND 1000000000000
#define MAX_ITER 25000

Solution* repeatedRandom(Solution* s, Heap& input);
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
    // long long rs = s->residue(h.elements);
    // long long rp = p->residue(h.elements);
    // long long rk = h.kk();
    Solution* ss = repeatedRandom(s, h);
    return 0;
}

Solution* repeatedRandom(Solution* s, Heap& input)
{
    for (int i = 0; i < MAX_ITER; i++)
    {
        Solution* sp = s->move();
        long long spr = sp->residue(input.elements);
        long long sr = s->residue(input.elements);
    }
    return s;
}

