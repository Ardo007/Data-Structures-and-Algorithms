#include <iostream>
#include <limits>
#include <algorithm>
#include "graphWeighted.hpp"
using namespace std;

const int MAX = numeric_limits<int>::max();

void dijkstras(GraphWeighted g, int source) {
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<> > queue {};
    vector<double> bestDistTo (g.getVerticies(), MAX);
    vector<bool> visited(g.getVerticies(), false);

    bestDistTo.at(source) = 0;

    queue.push({0.0, source});

    while(!queue.empty()) {
        int currentV = queue.top().second;

        queue.pop();

        if(visited[currentV]) {
            continue;
        }
        visited[currentV] = true;

        for(auto edge : g.getGraphList().at(currentV)) {
            int neighbour = edge.first;
            int weight = edge.second;

            if(bestDistTo[neighbour] > bestDistTo[currentV] + weight) {
                bestDistTo[neighbour] = bestDistTo[currentV] + weight;
                queue.push({bestDistTo[neighbour], neighbour});
            }
        }
    }

    for(int i = 0; i < bestDistTo.size(); i++) {
        cout << i << ": " << bestDistTo[i] << endl;
    }

}


int main() {


    GraphWeighted g(6, true);

    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 1);
    g.addEdge(2, 1, 2);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 3, 5);
    g.addEdge(3, 4, 3);
    g.addEdge(4, 5, 1);

    dijkstras(g, 0);



    return 0;
}
