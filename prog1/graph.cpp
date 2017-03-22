#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "graph.h"


using namespace std;

Graph::Graph(int d, int n)
    : d(d), n(n)
{
	// constant factor for graph simplification
	double k = 1.0;
	if (d > 1) 
		k = double(d)/(double(d)-1);

    // construct vertices
    for (int v = 0; v < n; v++)
        Vertices.push_back(Vertex(d));

    // Edges
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            // Calulate distance
            double distance = Vertex::distance(&Vertices[i], &Vertices[j]);
			
			// drop Edges
            // 1d case - max edge weight is proportional to k(n) = 2log(n)/n
            // higher dimension case - d/((d-1)*n^(1/d))
            if ((d == 1 && distance > (2*log(n)/n)) || (distance > (k / pow(n, 1/double(d)))))
                continue;

            Edges.push_back(Edge(i, j, distance));
        }
    }
}