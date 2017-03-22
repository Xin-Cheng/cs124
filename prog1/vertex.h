#ifndef VERTEX_H
#define VERTEX_H

#include <cstddef>
#include <vector>
#include <math.h>

using namespace std;

class Vertex : virtual public vector<double>
{
public:
    Vertex(size_type dimension);
    ~Vertex();

public:
    static double distance(const Vertex* v1, const Vertex* v2);
};
#endif