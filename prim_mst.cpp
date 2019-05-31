// @copyright 2019 Urmi Lalchandani and Shivani Parekh

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
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
  std::vector<Edge> GetEdges();
  bool ContainsEdge(Edge &e);

private:
  std::vector<Edge> edges;
};
Vertex::Vertex() {}
void Vertex::AddEdge(Edge e) {
  edges.push_back(e);
}
std::vector<Edge> Vertex::GetEdges() {
  return edges;
}
bool Vertex::ContainsEdge(Edge &e) {
  bool contains = false;
  std::vector<Edge> edge_vec = GetEdges();
  for (auto &ed: edge_vec) {
    if (ed.Destination() == e.Destination())
      contains = true;
  }
  return contains;
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
        for(Edge e : v.GetEdges()) {
            std::cout << "source " << e.Source() << " destination " << e.Destination() << " weight " << e.Weight() << std::endl;
        }
        i++;
    }
}
size_t Graph::GetNumEdges() {
  size_t num_edges = 0;
  for (auto &v : Vertices()){
    num_edges+= v.GetEdges().size();
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
  static const double inf = std::numeric_limits<double>::infinity();
  std::vector<double> dist;  // dist from src to v
  std::vector<bool> marked;  // has vertex already been visited?

  for (Vertex v : graph.Vertices()) {
    dist.push_back(inf);
    marked.push_back(false);
    Edge e(0, 0, 0);
    edge.push_back(e);
  }

  // for each vertex in graph.Vertices()
  for(unsigned int i = 0; i < graph.Vertices().size(); i++) {
    // skip visited vertex
    if (marked[i]) {
      continue;
    }

    dist[i] = 0;  // distance to itself is 0
    // for each v search edge list
    // find smallest edge for that v
    pqueue.Push(dist[i], i);

    while (pqueue.Size() > 0) {
      // get destination(vertex) w/ smallest weight
      unsigned int u = pqueue.Top();
      pqueue.Pop();
      marked[u] = true;

      for (Edge neighbor : graph.Vertices()[u].GetEdges()) {
        unsigned int v;
        if (neighbor.Source() == u) {
            v = neighbor.Destination();
        }
        if (neighbor.Destination() == u) {
            v = neighbor.Source();
        }

        if (marked[v]) {
            continue;
        }

        if (neighbor.Weight() < dist[v]) {
          dist[v] = neighbor.Weight();
          edge[v] = neighbor;
          if (pqueue.Contains(v)) {
            pqueue.ChangeKey(dist[v], v);
          } else {
            pqueue.Push(dist[v], v);
          }
        }
      }
    }
  }


  if (edge.size() == 2) {
      std::cout << "0.00000" << std::endl;
  }
  else {
      double total_weight = 0;
      for (unsigned int index = 1; index < edge.size(); index++) {
          Edge e = edge[index];
          std::cout.precision(5);
          std::cout << std::setfill('0') << std::setw(4) << e.Source();
          std::cout << "-" << std::setfill('0') << std::setw(4) << e.Destination();
          std::cout << " (" << std::fixed << e.Weight() << ")" << std::endl;
          total_weight += e.Weight();
      }
      std::cout << total_weight << std::endl;
  }
}

// MAIN FUNCTION
int main(int argc, char *argv[]) {
  // getting correct number arguments
  if (argc != 2) {
    std::cerr << "Usage ./prim_mst <graph.dat>" << std::endl;
    return 1;
  }
  // open file
  std::ifstream ifs;
  ifs.open(argv[1]);
  if (!ifs.is_open()) {
    std::cerr << "Error: cannot open file " << argv[1] << std::endl;
    return 1;
  }

  // get first line containing the number of vertices
  // check for valid size
  std::string line = ifs.getline();
  int i = 0;
  bool invalid = false;

  while (line[i]) {
    if (isalpha(line[i])) {
      invalid = true;
    }
  }
  if (invalid) {
    std::cerr << "Error: invalid graph size " << std::endl;
    return 1;
  }
  // number of vertices
  size_t capacity = std::stoul(line);


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

    // check for invalid input
    if (source >= capacity) {
      std::cerr << "Invalid source vertex number " <<
        source << std::endl;
      return 1;
    }
    if (destination >= capacity) {
      std::cerr << "Invalid destination vertex number "
        << destination << std::endl;
      return 1;
    }
    if (weight < 0)
      std::cerr << "Invalid weight " << weight << std::endl;

    Edge e(source, destination, weight);
    // vertices[source] gives a Vertex*
    if (!vertices[source].ContainsEdge(e)) {
      vertices[source].AddEdge(e);
      vertices[destination].AddEdge(e);
    }
  }

  Graph g(vertices);

  MST m;
  m.Prim(g);

  ifs.close();

  return 0;
}
