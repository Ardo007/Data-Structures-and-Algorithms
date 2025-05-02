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


        void dfs() {

        }

        void bfs(){

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



    
    return 0;
}


