#include "Heap.h"
#include "Solution.h"
#include <math.h>
#include <typeinfo>

using namespace std;
#define MAX_RAND 1000000000000
#define MAX_ITER 25000

Solution* repeatedRandom(Solution* s, Heap& h);
Solution* hillClimbing(Solution* s, Heap& h);
Solution* simulatedAnneal(Solution* s, Heap& h);
void compare(Solution* s, Solution* p, Heap& h);

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
    compare(s, p, h);
    return 0;
}

void compare(Solution* s, Solution* p, Heap& h)
{
    // Solution* rrs = repeatedRandom(s, h);
    // Solution* rrp = repeatedRandom(p, h);
    // Solution* hcs = hillClimbing(s, h);
    // Solution* hcp = hillClimbing(p, h);
    Solution* sas = simulatedAnneal(s, h);
    Solution* sap = simulatedAnneal(p, h);
    long long kr = h.kk();
    // long long rrsr = rrs->residue(h.elements);
    // long long rrpr = rrp->residue(h.elements);
    // long long hcsr = hcs->residue(h.elements);
    // long long hcpr = hcp->residue(h.elements);
    long long sasr = sas->residue(h.elements);
    long long sapr = sap->residue(h.elements);
    int cdd = 0;
}

Solution* repeatedRandom(Solution* s, Heap& h)
{
    for (int i = 0; i < MAX_ITER; i++)
    {
        Solution* sp = s->random();
        long long spr = sp->residue(h.elements);
        long long sr = s->residue(h.elements);
        if (spr < sr)
            s = sp;
    }
    return s;
}

Solution* hillClimbing(Solution* s, Heap& h)
{
    for (int i = 0; i < MAX_ITER; i++)
    {
        Solution* sp = s->move();
        long long spr = sp->residue(h.elements);
        long long sr = s->residue(h.elements);
        if (spr < sr)
            s = sp;
    }
    return s;
}

Solution* simulatedAnneal(Solution* s, Heap& h)
{
    Solution* spp;
    if (typeid(s) == typeid(RandomSolution))
        spp = new RandomSolution(s->solution);
    else
        spp = new PartitionedSolution(s->solution);

    for (int i = 0; i < MAX_ITER; i++)
    {
        Solution* sp = s->move();
        long long spr = sp->residue(h.elements);
        long long sr = s->residue(h.elements);
        if (spr < sr)
            s = sp;
        else
        {
            double tier = pow(10, 10) * pow(0.8, floor((double)i/300));
            double pr = exp((double)(sr - spr)/tier);
            if (pr > 0.5)
                s = sp;
        }
        if (s->residue(h.elements) < spp->residue(h.elements))
            spp = s;
    }
    return spp;
}