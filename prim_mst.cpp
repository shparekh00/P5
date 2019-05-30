#include "index_min_pq.h"

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
    explicit Graph(int num);
    void AddVertex(Vertex* v);

 private:
    int num_vertices;
    std::array<Vertex*, num_vertices> vertices[];
};

Graph::Graph(std::array<Vertex*> v[]) {
    vertices = v;
}

void Graph::AddVertex(Vertex *v) {
    vertices[num_vertices] = v;
    num_vertices++;
}


class MST {
public:
    MST();
    void Prim(Graph graph);

private:
    Graph graph;
};

MST::MST() {
}

void MST::Prim(Graph graph) {
    IndexMinPQ pqueue;

}




int main(int argc, char*[] argv) {
    std::ifstream ifs;
    ifs.open(argv[1]);
    if (!ifs.is_open()) {
        std::cerr << "Error: cannot open file " << argv[1];
        return 1;
    }

    int capacity;
    ifs >> capacity;
    std::array<Vertex*, capacity> vertices[];

    // read in vertices
    while(!ifs.eof()) {
        unsigned int source, destination;
        double weight;

        ifs >> source >> destination >> weight;
        Edge e(source, destination, weight);

        // vertex
        vertices[source].AddEdge(e);
    }

    Graph g(vertices);

    std::cout <<

    MST::Prim(g);
    return 0;
}
