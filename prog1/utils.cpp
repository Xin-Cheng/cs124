#include <iostream>
#include <fstream>
#include <assert.h>
#include "utils.h"
#include "graph.h"

// display list of edges to console
void DisplayEdges(Graph G){
	std::vector<Edge>::iterator it;
    for( it = G.Edges.begin( ); it != G.Edges.end( ); ++it ) {
        cout << "(" << it->src+1 << ", " << it->dest+1 << "): " << it->weight << endl;
    }	
}

// display MST
void displayMST (vector<Edge>* mst)
{
	printf("Following are the edges in the constructed MST\n");
	std::vector<Edge>::iterator it;
    for (it = mst->begin(); it != mst->end(); ++it)
        printf("%d -- %d == %f\n", it->src+1, it->dest+1, it->weight);
}

// average weight of edges in MST
double averageMST (vector<Edge>* mst)
{
	double average;
	double sum = 0;
	std::vector<Edge>::iterator it;
    for (it = mst->begin(); it != mst->end(); ++it)
		sum += it->weight;
        
	average = sum/mst->size();
	//cout << "Average weight: " << average << endl;
	return average;
}

// max edge in MST
double maxMST (vector<Edge>* mst)
{
	double max = 0;
	std::vector<Edge>::iterator it;
    for (it = mst->begin(); it != mst->end(); ++it)
	{
		if(it->weight > max)
			max = it->weight;
	}
	//cout << "Max weight: " << max << endl;
	return max;
}

// export edges to a text file
void ExportEdges(Graph G){
	ofstream myfile;
	myfile.open ("example.txt");	
	std::vector<Edge>::iterator it;
    for( it = G.Edges.begin( ); it != G.Edges.end( ); ++it ) {
		myfile << it->src+1 << " " << it->dest+1 << " " <<  it->weight << endl;
    }	
	myfile.close();
}