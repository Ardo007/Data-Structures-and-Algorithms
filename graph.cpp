#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Graph {
    private:
        int numOfVerticies {};
        vector<unordered_set<int>> vec {};
        bool isDirected {};

        public: 
            Graph(int n, bool type) : vec{vector<unordered_set<int>>(n)}, numOfVerticies{n}, isDirected{type} {}


            void addEdge(int x, int y) {
                vec.at(x).insert(y);
                if(!isDirected) {
                    vec.at(y).insert(x);
                }
            }


            bool isEdge(int x, int y) {
                return vec.at(x).contains(y);
            }



};




int main() {


    
    return 0;
}


