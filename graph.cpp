#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>

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


        void dfs(int vertex) {
            vector<bool> visited(numOfVerticies, false);
            dfsHelper(vertex, visited);
            cout << endl;
        }

    

};




int main() {
    Graph G(5, false);
    G.addEdge(1, 0);
    G.addEdge(0, 3);
    G.addEdge(2, 1);
    G.addEdge(2, 3);
    G.addEdge(3, 1);
    G.addEdge(2, 4);

    G.isAdjacentTo(2);

    G.print();

    cout << "##########################\n";

    Graph directG(5, true);
    directG.addEdge(1, 0);
    directG.addEdge(0, 3);
    directG.addEdge(2, 1);
    directG.addEdge(2, 3);
    directG.addEdge(3, 1);

    directG.isAdjacentTo(0);

    directG.print();

    cout << "##########################\n";


    Graph G3(6, false);
    G3.addEdge(0, 4);
    G3.addEdge(0, 5);
    G3.addEdge(4, 5);
    G3.addEdge(1, 3);
    G3.addEdge(1, 2);
    G3.addEdge(2, 3);

    G3.dfs(4);
    
    return 0;
}


