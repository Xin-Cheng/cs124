#include <iostream>
#include "utils.h"
#include "graph.h"
#include "disjointset.h"

int main(int argc, char* argv[])
{
    //check inputs
    // if (argc < 5)
    // {
    //  	cout << "Usage: ./randmst debugflag numpoints numtrials dimension" << endl;
    //  	return 0;
    // }

    // debug input - input 1
    // int debugflag = atoi(argv[1]);

    // number of nodes - input 2
    // debug
    int n = atoi(argv[2]);

    // number of trials - input 3
    // int numTrials = atoi(argv[3]);

    // dimension - intput 4
    // debug
    int d = atoi(argv[1]);
    if (d < 0 || d > 4)
    {
        cout << "Dimension out of range! Should be 1 to 4." << endl;
        return 0;
    }

    // seed
    srand(time(NULL));
    // debug
    Graph G = Graph(d, n);
    Graph* graph = &G;
    // Kruskal
    vector<Edge>* mst = Kruskals(graph);
    // display MST to console
    displayMST(mst);

    // seed
    // srand(1);

    // default operation	
    // if (debugflag == 0)
    // {
    // 	// initialize graph	
    // 	double avgTrials = 0; // average of mst weight over trials
    // 	int numEdges;
    // 	int numEdgesMST;
    // 	auto t1 = std::chrono::high_resolution_clock::now();
    // 	for (int t = 0; t < numTrials; t++) {
    // 		Graph G = Graph(d, n);
    // 		Graph* graph = &G;
    // 		// Kruskal
    // 		vector<Edge>* mst = Kruskals(graph);
    // 		avgTrials += averageMST(mst);
    // 		numEdges = G.Edges.size();
    // 		numEdgesMST = mst->size();
    // 		cout <<  averageMST(mst) << endl; //TODO: remove
    // 		ExportEdges(G);
    // 	}
    // 	auto t2 = std::chrono::high_resolution_clock::now();
    // 	avgTrials /= numTrials; // take mean

    // 	cout << avgTrials <<  " " << n << " " << numTrials << " " << d << endl;

    // 	// TODO: remove this - just for debug
    // 	std::cout << "Kruskals took "
    // 	  << (std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count())/1000.0
    // 	  << " seconds\n";
    // 	cout << "Number of edges in simplified graph: " << numEdges << endl;
    // 	cout << "Number of edges in MST: " << numEdgesMST << endl;

    // } 
    // else if(debugflag == 500) {
    // 	// debug operation - compute maxWeight for different n's (upto what is specified in debugflag) 
    // 	for (int nt = 10; nt < debugflag; nt+=10)
    // 	{
    // 		// initialize graph	
    // 		double maxWeightTrials = 0; // average of mst weight over trials
    // 		double maxWeight;
    // 		for (int t = 0; t < numTrials; t++) {
    // 			Graph G = Graph(d, nt);
    // 			Graph* graph = &G;	
    // 			// Kruskal
    // 			vector<Edge>* mst = Kruskals(graph);	
    // 			maxWeight = maxMST(mst);
    // 			if (maxWeight > maxWeightTrials)
    // 				maxWeightTrials = maxWeight;
    // 		}		
    // 		cout << maxWeightTrials <<  " " << nt << " " << numTrials << " " << d << endl;
    // 	}

    // }

    return 0;
}