#include "graph-A.h"
#include "graph.h"
#include <iostream>

int main() {
    // GraphAdjacent graph;

    // graph.addVertex("A");
    // graph.addVertex("B");
    // graph.addVertex("C");
    // graph.addVertex("D");

    // graph.addEdge("A", "B");
    // graph.addEdge("A", "C");
    // graph.addEdge("B", "D");
    // graph.addEdge("C", "D");

    // graph.printGraph();
    Graph graph;
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");

    graph.addEdge(Edge("A", "B", 5));
    graph.addEdge(Edge("B", "C", 3));

    graph.print();
    std::cout << std::endl;

    graph.addEdge(Edge("A", "C", 2));
    graph.print();

    return 0;
}