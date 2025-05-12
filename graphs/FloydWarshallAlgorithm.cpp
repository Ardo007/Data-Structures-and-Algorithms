#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include "graphWeighted.hpp"

using namespace std;

const int INF = numeric_limits<int>::max();

void FloydWarlshall(GraphWeighted G) {
    int size = G.getVerticies();
    vector<vector<int>> matrixGraph(size, vector<int>(size, INF));

    for(int i = 0; i < size; i++) {
        matrixGraph[i][i] = 0;
    }

    for(int u = 0; u < size; u++) {
        for(auto& [v, w] : G.getGraphList()[u]) {
            matrixGraph[u][v] = w;
        }
    }


    for(int k = 0; k < size; k++) {

        for(int i = 0; i < size; i++) {

            for(int j = 0; j < size; j++) {

                if(matrixGraph[i][k] != INF && matrixGraph[k][j] != INF){
                    if(matrixGraph[i][j] > matrixGraph[i][k] + matrixGraph[k][j]) {
                        matrixGraph[i][j] = matrixGraph[i][k] + matrixGraph[k][j];
                    }
                }
            }
        }
    }


for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
        if (matrixGraph[i][j] == INF)
            cout << setw(5) <<"INF ";
        else
            cout << setw(5) <<matrixGraph[i][j] << " ";
    }
    cout << endl;
}

}



int main() {

    GraphWeighted g(4, true);

    g.addEdge(0, 2, -2); 
    g.addEdge(2, 3, 2);  
    g.addEdge(3, 1, -1); 
    g.addEdge(1, 0, 4);  
    g.addEdge(1, 2, 3);  

    FloydWarlshall(g);


    return 0;
}
