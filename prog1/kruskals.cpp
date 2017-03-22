#include <algorithm>
#include "graph.h"
#include "disjointset.h"

using namespace std;

vector<Edge>* Kruskals(Graph* G){
	vector<DisjointSet> sets;
	vector<Edge>* mst = new vector<Edge>();
	// sort edge by weight	
	sort(G->Edges.begin(),G->Edges.end(), edgeCompare);		
	
	// make set
	for (int i = 0; i < G->n; i++) {
		DisjointSet* s = new DisjointSet(i);
		sets.push_back(*s);
	}		
	
	// Kruskals
	vector<Edge>::iterator it;
    for( it = G->Edges.begin( ); it != G->Edges.end( ); ++it ) {
		int src = it->src;
		int dest = it->dest;
		if (DisjointSet::find(&sets[src]) != DisjointSet::find(&sets[dest])) {
			mst->push_back(*it);
			DisjointSet::Union(&sets[src], &sets[dest]);
		}
		// early termination if we reached n=1 edges in mst
		if (mst->size() == G->n - 1)
			break;
    }
	return mst;
}