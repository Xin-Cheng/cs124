#include "vertex.h"
#include <stdlib.h>
#include <math.h>

Vertex::Vertex(size_type dimension)
    : vector<double>(dimension)
{
    for (size_type i = 0; i < this->size(); i++)
    {
        this->at(i) = ((double) rand()) / RAND_MAX;
    }
}

Vertex::~Vertex()
{
}

double Vertex::distance(const Vertex* v1, const Vertex* v2)
{
    double d = 0.0;
    for (size_type i = 0; i < v1->size(); i++)
        d += (v1->at(i) - v2->at(i)) * (v1->at(i) - v2->at(i)); 
    return sqrt(d);
}