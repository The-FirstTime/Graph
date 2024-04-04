#include "graph.h"
#include <iostream>

int main(){
    graph::Graph<std::string, int, double> myGraph;

    myGraph.addNode("A", 1);
    myGraph.addNode("B", 2);
    myGraph.addNode("C", 3);

    myGraph.addEdge("A", "B", 1.5);
    myGraph.addEdge("A", "C", 0.5);

    return 0;
}