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
    size_t GetNumEdges();
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
size_t Graph::GetNumEdges() {
  size_t num_edges = 0;
  for (auto &v : Vertices()){
    num_edges+= v.CollectionEdges().size();
  }
  return num_edges;
}

// MIN SPANNING TREE CLASS
class MST {
public:
  MST();
  void Prim(Graph g);

private:
//  Graph graph;
  std::vector<Edge> edge;

};
MST::MST() {}
void MST::Prim(Graph graph) {
  // key = weight index = dest_vert
  IndexMinPQ<double> pqueue(graph.GetNumEdges());
  const double inf = std::numeric_limits<double>::infinity();
  std::vector<double> dist;  // dist from src to v
//  std::vector<Edge> edge();  // best edge to v
  std::vector<bool> marked;  // has vertex already been visited?

  for (Vertex v : graph.Vertices()) {
      dist.push_back(inf);
//      edge.push_back(nullptr);
      marked.push_back(false);
  }

  // for each vertex in graph.Vertices()
//  for (Vertex i : graph.Vertices()) {
  for(unsigned int i = 0; i < graph.Vertices().size(); i++) {
    // skip visited vertex
    if (marked[i]) {
      continue;
    }

    dist[i] = 0;  // distance to itself is 0
    // for each v search edge list
    // find smallest edge for that v
    pqueue.Push(dist[i], i); //

    while (pqueue.Size() > 0) {
      // get destination(vertex) w/ smallest weight
      unsigned int u = pqueue.Top();
      pqueue.Pop();
      marked[u] = true;

      std::vector<Edge> possible_neighbors;

      for (Edge neighbor : graph.Vertices()[u].CollectionEdges()) {
        if (marked[neighbor.Destination()]) {
          continue;
        }
        if (neighbor.Weight() < dist[neighbor.Destination()]) {
          dist[neighbor.Destination()] = neighbor.Weight();
          possible_neighbors.push_back(neighbor);
          if (pqueue.Contains(neighbor.Destination())) {
            pqueue.ChangeKey(dist[neighbor.Destination()], neighbor.Destination());
          } else {
            pqueue.Push(dist[neighbor.Destination()], neighbor.Destination());
          }
        }
      }

      // find smallest neighbor
      Edge smallest(0, 0, inf);
      for (Edge e : possible_neighbors) {
          if (e.Weight() < smallest.Weight()) {
              smallest = e;
          }
      }
      edge.push_back(smallest);
    }
  }

//  std::vector<Edge> sequence;
    std::cout << "MST" << std::endl;
    double total_weight = 0;
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
//        Edge e_flip(destination, source, weight);

        // vertices[source] gives a Vertex*
        vertices[source].AddEdge(e);
//        vertices[destination].AddEdge(e_flip);
    }

    Graph g(vertices);
    g.Printer(g);

    MST m;
    m.Prim(g);

    return 0;
}
