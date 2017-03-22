#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

class DisjointSet
{
public:
    // should take edge as vertex, int for debug
    int vertex;
    int rank;
    DisjointSet* parent;

public:
    // constructers
    DisjointSet(int vertex);
    DisjointSet(int vertex, DisjointSet* parent);

public:
    static DisjointSet* find(DisjointSet* s);
    static DisjointSet* link(DisjointSet* s1, DisjointSet* s2);
    static void Union(DisjointSet* s1, DisjointSet* s2);
};

#endif