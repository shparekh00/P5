#include <iostream>
#include <fstream>
#include "index_min_pq.h"

// EDGE CLASS
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

// VERTEX CLASS
class Vertex {
 public:
    explicit Vertex();
    void AddEdge(Edge e);
    std::vector<Edge> CollectionEdges();

 private:
    std::vector<Edge> edges;
};
Vertex::Vertex() {}
void Vertex::AddEdge(Edge e) {
    edges.push_back(e);
}
std::vector<Edge> Vertex::CollectionEdges() {
    return edges;
}

// GRAPH CLASS
class Graph {
 public:
    explicit Graph(std::vector<Vertex> v);
    std::vector<Vertex> Vertices();
    void Printer(Graph g);
 private:
    std::vector<Vertex> vertices;
};
Graph::Graph(std::vector<Vertex> v) {
    vertices = v;
}
std::vector<Vertex> Graph::Vertices() {
    return vertices;
}
void Graph::Printer(Graph g) {
    int i = 0;
    for(Vertex v : g.vertices) {
        std::cout << i << std::endl;
        for(Edge e : v.CollectionEdges()) {
            std::cout << "source " << e.Source() << " destination " << e.Destination() << " weight " << e.Weight() << std::endl;
        }
        i++;
    }
}

// MIN SPANNING TREE CLASS
class MST {
public:
    MST();
    void Prim(Graph g);

private:
//    Graph graph;
};
MST::MST() {}
void MST::Prim(Graph graph) {
    IndexMinPQ<double> pqueue(graph.Vertices().size());
    std::vector<unsigned int> dist;
    std::vector<Edge> edge;
    std::vector<bool> marked;

    for (Vertex v : graph.Vertices()) {
        dist.push_back(HUGE_VAL);
        edge.push_back(nullptr);
        marked.push_back(false);
    }

    for (Vertex v : graph.Vertices()) {
        // skip visited vertex
        if (marked[v]) {
            continue;
        }

        dist[v] = 0;
        pqueue.Push(v, dist[v]);

        while (pqueue.Size() > 0) {
            unsigned int u = pqueue.Top();
            pqueue.Pop();

            marked[u] = true;

//            for (Vertex neighbor : u) {
//                if (marked[neighbor]) {
//                        continue;
//                }
//            }

        }

    }

//  std::vector<Edge> sequence;
    std::cout << "MST" << std::endl;
    int total_weight = 0;
    for (Edge e : edge) {
//      sequence.push_back(e);
        std::cout << e.Source() << "-" << e.Destination() << " (" << e.Weight() << ")" << std::endl;
        total_weight += e.Weight();
    }
    std::cout << total_weight;
//  return sequence;
}

// MAIN FUNCTION
int main(int argc, char *argv[]) {
    // open file
    std::ifstream ifs;
    ifs.open(argv[1]);
    if (!ifs.is_open()) {
        std::cerr << "Error: cannot open file " << argv[1];
        return 1;
    }

    // first number is the number of vertices
    int capacity;
    ifs >> capacity;

    // vector of empty vertices of size capacity
    std::vector<Vertex> vertices;
    for (int i = 0; i < capacity; ++i) {
        Vertex v;
        vertices.push_back(v);
    }

    // read in vertices
    unsigned int source, destination;
    double weight;
    while(!ifs.eof()) {
        // read one line to get an edge
        ifs >> source >> destination >> weight;
        Edge e(source, destination, weight);

        // vertices[source] gives a Vertex*
        vertices[source].AddEdge(e);
    }

    Graph g(vertices);
    g.Printer(g);

    MST m;
    m.Prim(g);

    return 0;
}
