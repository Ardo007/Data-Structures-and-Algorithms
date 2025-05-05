#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

class Graph {
    private:

        int numOfVerticies {};
        vector<unordered_set<int>> vec {};
        bool isDirected {};


        void dfsHelper(int vertex, vector<bool>& marked) {
            marked[vertex] = true;
            cout << vertex <<" ";

            for(auto v : vec[vertex]) {
                
                if(!marked[v]){
                    dfsHelper(v, marked);
                }
            }
        }

    public: 
        Graph(int n, bool type) : vec{vector<unordered_set<int>>(n)}, numOfVerticies{n}, isDirected{type} {}


        // adds an edge
        void addEdge(int x, int y) {
            vec.at(x).insert(y);
            if(!isDirected) {
                vec.at(y).insert(x);
            }
        }

        // checks if there is an edge between 2 vertices 
        bool isEdge(int x, int y) {
            return vec.at(x).contains(y);
        }
        

        // prints the vertices connected to the vertex x
        void isAdjacentTo(int x) {
            for(int neighbour : vec.at(x)) {
                cout << neighbour << ' ';
            }
            cout << endl;
        }

        // prints all vertices and their neighbours 
        void print() {
            for(int i = 0; i < numOfVerticies; i++) {
                cout << "the Neighbours of vertex " << i << " are: ";
                for(int neighbour : vec.at(i)) {
                    cout << neighbour << " ";
                }
                cout << endl;
            }
        }


        void dfs(unsigned vertex) {
            vector<bool> visited(numOfVerticies, false);
            dfsHelper(vertex, visited);
            cout << endl;
        }


        void bfs(unsigned vertex, unsigned destVertex) {
            vector<bool> visited(numOfVerticies, false);
            queue<unsigned> visitQueue;
            vector<unsigned> edgeTo(numOfVerticies);

            visitQueue.push(vertex);
            visited[vertex] = true;

            while(!visitQueue.empty()) {
                unsigned x = visitQueue.front();
                visitQueue.pop();
                // cout << "Now visiting " << x << '\n';

                for(auto u : vec[x]) {
                    if(!visited[u]) {
                        visitQueue.push(u);
                        visited[u] = true;
                        edgeTo[u] = x;
                    }
                }
            }


            unsigned u = destVertex;
            cout << u;
            while(u != vertex) {
                u = edgeTo[u];
                cout << "-" << u;
            }

        }

    

};




int main() {
    // Graph G(5, false);
    // G.addEdge(1, 0);
    // G.addEdge(0, 3);
    // G.addEdge(2, 1);
    // G.addEdge(2, 3);
    // G.addEdge(3, 1);
    // G.addEdge(2, 4);

    // G.isAdjacentTo(2);

    // G.print();

    // cout << "##########################\n";

    // Graph directG(5, true);
    // directG.addEdge(1, 0);
    // directG.addEdge(0, 3);
    // directG.addEdge(2, 1);
    // directG.addEdge(2, 3);
    // directG.addEdge(3, 1);

    // directG.isAdjacentTo(0);

    // directG.print();

    // cout << "##########################\n";


    Graph GR(16, false);

    for(unsigned i = 0; i < 16; ++i)
    {
        if(i % 4 != 3)
        {
            GR.addEdge(i, i+1);
        }
    }
    for(unsigned i = 0; i < 12; ++i)
    {
        GR.addEdge(i, i+4);
    }

    GR.print();

    GR.dfs(3);
    
    GR.bfs(3, 0);


    return 0;
}


