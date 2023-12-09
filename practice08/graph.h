#ifndef ADS_GRAPH_H
#define ADS_GRAPH_H


#include <vector>


/// Node of the graph. Contains the <name> and map of adjacent <edges>
class Vertex {
    friend class Graph;

private:
    char _name;
    std::vector<Vertex*> neighbors;

public:
    // Constructor and setter
    explicit Vertex(char);
    void addNeighbor(Vertex*);

    // Accessors
    char getName() const;
    std::vector<Vertex*> getNeighbors() const;
};


/// Weighted undirected graph. Contains the <amount> and <vertices>
class Graph {
private:
    std::vector<Vertex*> vertices; // Store each vertex

public:
    // Constructor
    Graph() = default;
    void setVertices(const std::vector<char>&, const std::vector<std::vector<int>>&);

    // Accessors
    bool empty() const;
    int size() const;
    std::vector<Vertex*> getVertices() const;
};


#endif //ADS_GRAPH_H
