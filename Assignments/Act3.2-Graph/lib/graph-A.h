#pragma once
#include <memory>
#include <string>
#include <iostream>

// Grafo dirigido y ponderado
class GraphAdjacent {
private:
    int matrix[8][8];
    std::string vertices[8];
    int size;
public:
    GraphAdjacent();
    void addVertex(std::string vertex);
    void addEdge(std::string from, std::string to);
    void printGraph();
    int findVertexIndex(std::string vertex);
};

GraphAdjacent::GraphAdjacent() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            matrix[i][j] = 0;
        }
        vertices[i] = "";
    }
    size = 0;
}

void GraphAdjacent::addVertex(std::string vertex) {
    if (size < 8) {
        vertices[size] = vertex;
        size++;
    }
}

int GraphAdjacent::findVertexIndex(std::string vertex) {
    for (int i = 0; i < size; ++i) {
        if (vertices[i] == vertex) {
            return i;
        }
    }
    return -1; // Vertex not found
}

void GraphAdjacent::addEdge(std::string from, std::string to) {
    int fromIndex = findVertexIndex(from);
    int toIndex = findVertexIndex(to);

    if (fromIndex != -1 && toIndex != -1) {
        matrix[fromIndex][toIndex] = 1; // Assuming weight of 1 for simplicity
    }
}

void GraphAdjacent::printGraph() {
    std::cout << "Graph adjacency matrix:\n";
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}