#include "Heap.h"
#include "Solution.h"

using namespace std;
#define MAX_RAND 1000000000000
#define MAX_ITER 250000

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
        h.insert(r2 % MAX_RAND + 1);
        // h.insert(i);
        r1 % 2 ? s->solution.push_back(1) : s->solution.push_back(-1);
        p->solution.push_back(r1 % 10);
    }
    Solution* ss = repeatedRandom(s, h);
    Solution* pp = repeatedRandom(p, h);
    long long sr = ss->residue(h.elements);
    long long pr = pp->residue(h.elements);
    long long kr = h.kk();
    return 0;
}

Solution* repeatedRandom(Solution* s, Heap& input)
{
    for (int i = 0; i < MAX_ITER; i++)
    {
        Solution* sp = s->move();
        long long spr = sp->residue(input.elements);
        long long sr = s->residue(input.elements);
        if (spr < sr)
            s = sp;
    }
    return s;
}

