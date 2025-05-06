#ifndef GRAPH_CPP_
#define GRAPH_CPP_


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






#endif