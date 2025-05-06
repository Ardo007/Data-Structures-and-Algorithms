#include <iostream>
#include "graph.hpp"

using namespace std;



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


