// @copyright 2019 Urmi Lalchandani and Shivani Parekh

#include <iostream>
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
  const double inf = std::numeric_limits<double>::infinity();
  std::vector<double> dist;  // dist from src to v
  std::vector<bool> marked;  // has vertex already been visited?

  for (Vertex v : graph.Vertices()) {
    dist.push_back(inf);
    marked.push_back(false);
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
    unsigned int prev = static_cast<unsigned int>(inf);

    while (pqueue.Size() > 0) {
      // get destination(vertex) w/ smallest weight
      unsigned int u = pqueue.Top();
      pqueue.Pop();
      marked[u] = true;
      std::cout<<"u is "<< u<<std::endl;

      Edge curr(prev, u, dist[u]);
      edge.push_back(curr);

      for (Edge neighbor : graph.Vertices()[u].GetEdges()) {
        unsigned int v;
        if (neighbor.Source() == u) {
            v = neighbor.Destination();
        }
        if (neighbor.Destination() == u) {
            v = neighbor.Source();
        }
        std::cout << "v is " << v << "\n";

        if (marked[v]) {
            continue;
        }
        std::cout << "neighbors weight: " << neighbor.Weight() << std::endl;
        std::cout << "dist[v]: " << dist[v] << std::endl;

        if (neighbor.Weight() < dist[v]) {
          dist[v] = neighbor.Weight();
//          edge.push_back(neighbor);
          std::cout << "edge: source " << neighbor.Source() << " destination: " << neighbor.Destination() << " weight: " << neighbor.Weight() << std::endl;
          if (pqueue.Contains(v)) {
            pqueue.ChangeKey(dist[v], v);
          } else {
            pqueue.Push(dist[v], v);
          }
        }

      }

      prev = u;

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

        Edge e1(source, destination, weight);
        Edge e2(destination, source, weight);
        // vertices[source] gives a Vertex*
        if (!vertices[source].ContainsEdge(e1)) {
          vertices[source].AddEdge(e1);
          vertices[destination].AddEdge(e2);
        }
    }

    Graph g(vertices);
//    g.Printer(g);

    MST m;
    m.Prim(g);

    ifs.close();

    return 0;
}



/*
 *
 * void MST::Prim(Graph graph) {
  // key = weight index = dest_vert
  IndexMinPQ<double> pqueue(graph.GetNumEdges());
  const double inf = std::numeric_limits<double>::infinity();
  std::vector<double> dist;  // dist from src to v
//  std::vector<Edge> edge();  // best edge to v
  std::vector<bool> marked;  // has vertex already been visited?

  for (Vertex v : graph.Vertices()) {
    dist.push_back(inf);
//    edge.push_back(nullptr);
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
    pqueue.Push(dist[i], i);

//    std::vector<Edge> leftover_edges;

    while (pqueue.Size() > 0) {
      // get destination(vertex) w/ smallest weight
      unsigned int u = pqueue.Top();
      pqueue.Pop();
      marked[u] = true;
//      std::cout << "marked " << u << " " << std::endl;

//      std::vector<Edge> possible_neighbors;

//      for (Edge e : graph.Vertices()[u].GetEdges()) {
         //  if its not a repeat
//          leftover_edges.push_back(e);
//      }


      // print leftover edges
//      for (Edge e : leftover_edges) {
//          std::cout << "leftover edge " << e.Source() << " to " << e.Destination() << " weight " << e.Weight() << std::endl;
//      }

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
          edge.push_back(neighbor);
          if (pqueue.Contains(v)) {
            pqueue.ChangeKey(dist[v], v);
          } else {
            pqueue.Push(dist[v], v);
          }
        }
      }

      // find smallest neighbor
//      Edge smallest(0, 0, inf);
//      for (Edge e : leftover_edges) {
//          std::cout << "possible edge source " << e.Source() << " destination " << e.Destination() << " weight " << e.Weight() << std::endl;
//          if (e.Weight() < smallest.Weight()) {
//              smallest = e;
//          }
//      }
//      edge.push_back(smallest);
//        std::cout << "smallest " << smallest.Source() << " to " << smallest.Destination() << " weight " << smallest.Weight() << std::endl;

      // remove from leftover edges
//      for (int l = 0; l < leftover_edges.size(); l++) {
//          if ((leftover_edges[l].Source() == smallest.Source() && leftover_edges[l].Destination() == smallest.Destination())) { // || (leftover_edges[l].Source() == smallest.Destination() && leftover_edges[l].Destination() == smallest.Source())) {
//              if (leftover_edges[l].Weight() == smallest.Weight()) {
//                  leftover_edges[l] = leftover_edges[leftover_edges.size() - 1];
//                  leftover_edges.pop_back();
//              }
//          }
//      }
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
 */