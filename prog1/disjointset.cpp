#include "disjointset.h"

DisjointSet::DisjointSet(int vertex)
    : DisjointSet(vertex, this)
{
}
DisjointSet::DisjointSet(int vertex, DisjointSet* parent)
    : vertex(vertex)
    , rank(0)
    , parent(parent)
{   
}

DisjointSet* DisjointSet::find(DisjointSet* s)
{
	while (s->parent != s)
        s = s->parent; 
    return s;
}

DisjointSet* DisjointSet::link(DisjointSet* s1, DisjointSet* s2)
{
    if (s1->rank > s2->rank)
    {
        s2->parent = s1;
        return s1;
    }
    else if (s1->rank == s2->rank)
    {
        s2->parent = s1;
        s1->rank += 1;
        return s1;
    } 
    else
    {
        s1->parent = s2;
        return s2;
    }
}

void DisjointSet::Union(DisjointSet* s1, DisjointSet* s2)
{
    link(DisjointSet::find(s1), DisjointSet::find(s2));
}