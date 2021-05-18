//----------------------------------------------------------------------
// NAME: S. Bowers
// FILE: adjacency_list.h
// DATE: Spring 2021
// DESC: Adjacency list implementation of the graph interface
//----------------------------------------------------------------------

#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

#include "graph.h"


class AdjacencyList : public Graph
{
public:

  // default constructor
  AdjacencyList(int vertex_count);

  // destructor
  ~AdjacencyList();

  // copy constructor
  AdjacencyList(const AdjacencyList& rhs);

  // assignment operator
  AdjacencyList& operator=(const AdjacencyList& rhs);

  // add or update an edge between existing vertices in the graph
  void set_edge(int v1, int edge_label, int v2);

  // check if the given edge is in the graph
  bool has_edge(int v1, int v2) const;  

  // returns true if there is an edge between v1 and v2 in the graph
  // the output parameter returns the edge label
  bool get_edge(int v1, int v2, int& edge) const; 
  
  // get all vertices on an outgoing edge from given vertex
  void connected_to(int v1, std::list<int>& vertices) const;

  // get all vertices on an incoming edge to given vertex
  void connected_from(int v2, std::list<int>& vertices) const;

  // get all vertices adjacent to a vertex, that is, connected to or connected
  // from the vertex (may return duplicate vertices)
  void adjacent(int v, std::list<int>& vertices) const;

  // get number of nodes in the graph
  int vertex_count() const; 

  // get number of edges in the graph
  int edge_count() const; 

  // remove an edge from a graph
  void remove_edge(int v1, int v2);
  
private:

  int number_of_vertices;
  int number_of_edges;

  struct Node {
    int edge;
    int vertex;
    Node* next;
  };
  
  // linked-list array of out edges (for connected_to)
  Node** adj_list_out;
  // linked-list array of in edges (for connected_from)
  Node** adj_list_in;
  
  // helper function to delete adj_list
  void make_empty();

};



#endif

