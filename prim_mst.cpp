//
// Created by Deepak Lalchandani on 2019-05-29.
//

class Edge {
public:
    // initializes private variables
    explicit Edge(unsigned int s, unsigned int d, double w);
    // return source
    unsigned int Source();
    // return destination
    unsigned int Destination();
    // return weight
    double Weight();

private:
    unsigned int source, destination;
    double weight;
};

Edge::Edge(unsigned int s, unsigned int d, double w) {
    source = s;
    destination = d;
    weight = w;
}

unsigned int Edge::Source() {
    return source;
}

unsigned int Edge::Destination() {
    return destination;
}

double Edge::Weight() {
    return weight;
}


class Vertex {
 public:
    explicit Vertex();
    void AddEdge(Edge* e);
    std::vector<Edge*> CollectionEdges();

 private:
    std::vector<Edge*> edges;
    int num_edges;
};

Vertex::Vertex() {
    num_edges = 0;
}

void Vertex::AddEdge(Edge* e) {
    edges[num_edges] = e;
    num_edges++;
}

std::vector<Edge*> Vertex::CollectionEdges() {
    return edges;
}


class Graph {
 public:
    explicit Graph();
    void AddVertex(Vertex* v);
    std::vector<Vertex*> CollectionVertices();

 private:
    std::vector<Vertex*> vertices;
    int num_vertices;
};

Graph::Graph() {
    num_vertices = 0;
}

void Graph::AddVertex(Vertex *v) {
    vertices[num_vertices] = v;
    num_vertices++;
}

std::vector<Vertex *> Graph::CollectionVertices() {
    return vertices;
}
