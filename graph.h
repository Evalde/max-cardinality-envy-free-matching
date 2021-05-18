//----------------------------------------------------------------------
// NAME: S. Bowers and Alex Weaver
// FILE: graph.h
// DATE: Spring 2021
// DESC: A directed graph consists of vertices and edges. Each vertex
// has a unique identifier (from 0 to n-1) and each edge has a
// (non-unique) integer label.
//----------------------------------------------------------------------

#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <set>
#include <unordered_map>
#include <vector>

// shortened hash-table map name for convenience
typedef std::unordered_map<int,int> Map;
typedef std::set<int> Set;


class Graph
{
public:

  // default destructor
  virtual ~Graph() {};

  // add or update an edge between existing vertices in the graph
  virtual void set_edge(int v1, int edge_label, int v2) = 0;

  // check if the given edge is in the graph
  virtual bool has_edge(int v1, int v2) const = 0;  

  // returns true if there is an edge between v1 and v2 in the graph
  // the output parameter returns the edge label
  virtual bool get_edge(int v1, int v2, int& edge) const = 0; 

  // remove edge between v1 and v2 if the edge exists
  virtual void remove_edge(int v1, int v2) = 0;
  
  // get all vertices on an outgoing edge from given vertex
  virtual void connected_to(int v1, std::list<int>& vertices) const = 0;

  // get all vertices on an incoming edge to given vertex
  virtual void connected_from(int v2, std::list<int>& vertices) const = 0;

  // get all vertices adjacent to a vertex, that is, connected to or connected
  // from the vertex (may return duplicate vertices)
  virtual void adjacent(int v, std::list<int>& vertices) const = 0;

  // get number of nodes in the graph
  virtual int vertex_count() const = 0; 

  // get number of edges in the graph
  virtual int edge_count() const = 0; 

  //----------------------------------------------------------------------
  // Determine if the graph is bipartite (i.e., 2-colorable)
  //
  // Inputs:
  //   None
  // Outputs:
  //   returns  -- true if the graph is bipartite, false otherwise
  //   coloring -- mapping from each graph vertex to its corresponding
  //               color (either 0 or 1) if graph is bipartite
  //----------------------------------------------------------------------
  bool bipartite_graph(Map& coloring) const;

  //----------------------------------------------------------------------
  // Find a maximum matched graph using the augmenting paths algorithm
  // from the textbook.
  //
  // Conditions: Finds a matching only if the current graph is bipartite
  //
  // Output:
  //   max_matched_graph -- A graph with same vertices as original
  //                        graph, containing the edges in the
  //                        matching. The output graph is assumed to
  //                        be initialized with the same number of
  //                        vertices, but without any edges.
  // Returns:
  //   true if the current graph is bipartite, false otherwise
  //----------------------------------------------------------------------
  bool bipartite_graph_matching(Graph& max_matched_graph) const;

  //----------------------------------------------------------------------
  // Semester Project graph operation
  //----------------------------------------------------------------------
  
  //----------------------------------------------------------------------
  // Finds a maximum-size envy free matching using bipartite graph matching.
  //
  // Conditions: Finds a matching only if the current graph is bipartite
  //
  // Output:
  //  max_efm_graph -- A graph with same vertices as original
  //                   graph, containing the edges in the
  //                   matching. The output graph is assumed to
  //                   be initialized with the same number of
  //                   vertices, but without any edges.
  //
  // Returns: true if the graph is bipartite, false if not
  //----------------------------------------------------------------------
  bool max_size_envy_free_matching(Graph& max_efm_graph) const; 
};


#endif
