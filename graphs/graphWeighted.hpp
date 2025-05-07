#ifndef GRAPHWEIGHTED_CPP_
#define GRAPHWEIGHTED_CPP_


#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

class GraphWeighted {
    private:

        int numOfVerticies {};
        vector<list<pair<int, int>>> graphList {};
        bool isDirected {};


    public: 
        GraphWeighted(int n, bool type = false) : graphList{vector<list<pair<int, int>>>(n)}, numOfVerticies{n}, isDirected{type} {}


        void addEdge(int x, int y, int w) {
            graphList[x].push_back({y, w});
            if(!isDirected) {
                graphList[y].push_back({x, w});
            }
        }
        
        void addVertex() {
            graphList.push_back({});
            numOfVerticies++;
        }

        void removeVertex(int x) {
            graphList.at(x).clear();
            numOfVerticies--;
        }


        int getVerticies() {
            return numOfVerticies;
        }

        vector<list<pair<int, int>>> &getGraphList() {
            return graphList;
        }



        void print() {
            for(int i = 0; i < numOfVerticies; i++) {
                cout << "the Neighbours of vertex " << i << " are: ";
                for(auto neighbour : graphList.at(i)) {
                    cout << neighbour.second << ", ";
                }
                cout << endl;
            }
        }


    

};






#endif //GRAPHWEIGHTED_HPP_