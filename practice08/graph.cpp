#include "graph.h"


/// Vertex constructor
Vertex::Vertex(char name) {
    _name = name;
}


/// Connect this to the <vertex>
void Vertex::addNeighbor(Vertex *vertex) {
    neighbors.push_back(vertex);
}


/// Return name
char Vertex::getName() const {
    return _name;
}


/// Return neighbors
std::vector<Vertex*> Vertex::getNeighbors() const {
    return neighbors;
}


/// Graph constructor from adjacency matrix
void Graph::setVertices(const std::vector<char> &names, const std::vector<std::vector<int>> &weights) {
    // Create all vertices
    for (auto &name : names)
        vertices.push_back(new Vertex(name));

    // Add edges between the vertices
    for (int i = 0; i < vertices.size(); ++i)
        for (int j = 0; j < vertices.size(); ++j)
            if (i != j && weights[i][j] != 0)
                vertices[i]->addNeighbor(vertices[j]);
}


/// Return true if empty else false
bool Graph::empty() const {
    return vertices.empty();
}


/// Return size
int Graph::size() const {
    return vertices.size();
}


/// Return vector of pointers to the vertices
std::vector<Vertex*> Graph::getVertices() const {
    return vertices;
}