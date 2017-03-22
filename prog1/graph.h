#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include "vertex.h"

using namespace std;

class Edge
{
public:
    int src; // src vertex
    int dest; // dest vertex
    double weight; // weight

    Edge(int src, int dest, double weight) : src(src), dest(dest), weight(weight) { }
};

static bool edgeCompare(const Edge &e1, const Edge &e2)
{
    return (e1.weight < e2.weight);
}

class Graph
{
public:
    int d; // dimension
    int n; // number of vertices
    vector<Vertex> Vertices;
    vector<Edge> Edges;
    Graph(int d, int n);
};

#endif