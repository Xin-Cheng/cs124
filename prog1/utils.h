#include <cstdlib>
#include "graph.h"
#include <chrono>
using namespace std;

void DisplayEdges(Graph G);
void displayMST (vector<Edge>* mst);
void ExportEdges(Graph G);
vector<Edge>* Kruskals(Graph* G);
double averageMST (vector<Edge>* mst);
double maxMST (vector<Edge>* mst);