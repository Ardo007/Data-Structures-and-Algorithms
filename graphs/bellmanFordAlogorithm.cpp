#include <iostream>
#include <limits>
#include "graphWeighted.hpp"
using namespace std;

const int MAX = numeric_limits<int>::max();

void bellmanFord(int source, GraphWeighted& g) {
    int size = g.getVerticies();
    vector<double> bestDist(size, MAX);   // vector to store the best dist to each vertex

    // weight at source is 0
    bestDist.at(source) = 0.0;

    // relax every edge V - 1 times. V is the number of vertices
    for(int pass = 0; pass < size - 1; pass++) {

        for(int u = 0; u < size; u++) {

            for(auto &edge : g.getGraphList()[u]) {

                int v = edge.first;
                double w = edge.second;

                if(bestDist[u] != MAX && (bestDist[v] > bestDist[u] + w)){
                    bestDist[v] = bestDist[u] + w;
                }

            }

        }
          
    }

    // one extra scan to dectect if there is a negative weight cycle;

    for(int u = 0; u < size; u++) {

        for(auto &edge : g.getGraphList()[u]) {
            int v = edge.first;
            double w = edge.second;

            if(bestDist[u] != MAX && (bestDist[v] > bestDist[u] + w)){
                cout << "Negative weight cycle dedtected\n";
                return;
            }
            
        }
    }


    for(int i = 0; i < size; i++) {
        cout << i << ": " << bestDist[i] << endl;
    }

}


int main() {

    GraphWeighted g(3, true);

    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, -1);
    g.addEdge(2, 0, -1);

    bellmanFord(0, g);



    return 0;
}