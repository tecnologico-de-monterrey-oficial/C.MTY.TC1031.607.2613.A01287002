#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <memory>

struct Edge {
    std::string source;
    std::string target;
    int weight;

    Edge() : source(""), target(""), weight(0) {}
    Edge(const std::string& src, const std::string& tgt, int w)
        : source(src), target(tgt), weight(w) {}
};

class Graph {
public:
    Graph();
    int getVertexIndex(const std::string& vertex) const;
    void addEdge(const Edge& edge);
    void addVertex(const std::string& vertex);
    void print() const;
private:
    std::vector<std::string> vertices;
    std::vector<std::vector<Edge>> adjacencyList;
};

Graph::Graph() {}

int Graph::getVertexIndex(const std::string& vertex) const {
    for (size_t i = 0; i < vertices.size(); ++i) {
        if (vertices[i] == vertex) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

void Graph::addVertex(const std::string& vertex) {
    vertices.push_back(vertex);
    adjacencyList.push_back(std::vector<Edge>());
}

void Graph::addEdge(const Edge& edge) {
    int srcIndex = getVertexIndex(edge.source);
    int tgtIndex = getVertexIndex(edge.target);

    if (srcIndex != -1 && tgtIndex != -1) {
        adjacencyList[srcIndex].push_back(edge);
    } else {
        std::cerr << "No se ha encontrado uno o ambos vértices." << std::endl;
    }
}

void Graph::print() const {
    for (size_t i = 0; i < vertices.size(); ++i) {
        std::cout << vertices[i] << " -> ";
        for (const auto& edge : adjacencyList[i]) {
            std::cout << "(" << edge.target << ", " << edge.weight << ") ";
        }
        std::cout << std::endl;
    }
}