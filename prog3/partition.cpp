/// Programming assignment 3
/// HUID: 51272056
#include "Heap.h"
#include "Solution.h"
#include "ctime"
#include <math.h>
#include <typeinfo>
#include <string>
#include <fstream>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
#define MAX_RAND 1000000000000
#define MAX_ITER 25000
#define LENGTH 100

Solution* repeatedRandom(Solution* s, Heap& h);
Solution* hillClimbing(Solution* s, Heap& h);
Solution* simulatedAnneal(Solution* s, Heap& h);

void compare(Solution* s, Solution* p, Heap& h, int times);

int main(int argc, char *argv[])
{
    Heap h;
    if (argc == 2)
    {
        long long value;
        FILE* file = fopen(argv[1], "r");
        for (int i = 0; i < LENGTH && fscanf(file, "%lld", &value) == 1; i++)
            h.insert(value);
        fclose (file);
    }
    Solution* s = new RandomSolution();
    Solution* p = new PartitionedSolution();
    srand(time(NULL));
    for (int i = 0; i < LENGTH; i++)
    {
        long long r1 = rand();
        long long r2 = (r1 << 32) | rand();
        if (argc != 2)
            h.insert(r2 % MAX_RAND + 1);
        r1 % 2 ? s->solution.push_back(1) : s->solution.push_back(-1);
        p->solution.push_back(r1 % LENGTH);
    }
    printf("%lld\n", h.kk());
    if (argc == 3)
        compare(s, p, h, atoi(argv[2]));
    return 0;
}

void compare(Solution* s, Solution* p, Heap& h, int times)
{
    vector<string> timeTitle = { "RRS_Time", "RRP_Time", "HCS_Time", "HCP_Time", "SAS_Time", "SAP_Time" };
    vector<vector<double>> timeTable;
    vector<string> residueTitle = { "KK", "RRS", "RRP", "HCS", "HCP", "SAS", "SAP" };
    vector<vector<long long>> residueTable;

    int iteration = times;
    for (int i = 0; i < iteration; i++)
    {
        vector<double> timeRow;
        vector<long long> residueRow;
        clock_t itBegin = clock();
        Solution* rrs = repeatedRandom(s, h);
        clock_t itEnd = clock();
        timeRow.push_back(((double)(itEnd - itBegin)) / CLOCKS_PER_SEC);

        itBegin = clock();
        Solution* rrp = repeatedRandom(p, h);
        itEnd = clock();
        timeRow.push_back(((double)(itEnd - itBegin)) / CLOCKS_PER_SEC);

        itBegin = clock();
        Solution* hcs = hillClimbing(s, h);
        itEnd = clock();
        timeRow.push_back(((double)(itEnd - itBegin)) / CLOCKS_PER_SEC);

        itBegin = clock();
        Solution* hcp = hillClimbing(p, h);
        itEnd = clock();
        timeRow.push_back(((double)(itEnd - itBegin)) / CLOCKS_PER_SEC);

        itBegin = clock();
        Solution* sas = simulatedAnneal(s, h);
        itEnd = clock();
        timeRow.push_back(((double)(itEnd - itBegin)) / CLOCKS_PER_SEC);

        itBegin = clock();
        Solution* sap = simulatedAnneal(p, h);
        itEnd = clock();
        timeRow.push_back(((double)(itEnd - itBegin)) / CLOCKS_PER_SEC);

        residueRow.push_back(h.kk());
        residueRow.push_back(rrs->residue(h.elements));
        residueRow.push_back(rrp->residue(h.elements));
        residueRow.push_back(hcs->residue(h.elements));
        residueRow.push_back(hcp->residue(h.elements));
        residueRow.push_back(sas->residue(h.elements));
        residueRow.push_back(sap->residue(h.elements));

        timeTable.push_back(timeRow);
        residueTable.push_back(residueRow);
    }

    ofstream timeFile;
    timeFile.open("time.csv");
    ostream_iterator<string> timeIterator(timeFile, "\t");
    copy(timeTitle.begin(), timeTitle.end(), timeIterator);
    timeFile << endl;

    ofstream residueFile;
    residueFile.open("residue.csv");
    ostream_iterator<string> residuIterator(residueFile, "\t");
    copy(residueTitle.begin(), residueTitle.end(), residuIterator);
    residueFile << endl;

    for (int i = 0; i < iteration; i++)
    {
        ostream_iterator<double> timeIterator(timeFile, "\t");
        copy(timeTable[i].begin(), timeTable[i].end(), timeIterator);
        timeFile << endl;
        ostream_iterator<long long> residuIterator(residueFile, "\t");
        copy(residueTable[i].begin(), residueTable[i].end(), residuIterator);
        residueFile << endl;
    }
    timeFile.close();
    residueFile.close();
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