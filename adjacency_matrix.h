//----------------------------------------------------------------------
// NAME: S. Bowers
// FILE: adjacency_matrix.h
// DATE: Spring 2021
// DESC: Adjacency matrix implementation of the graph interface
//----------------------------------------------------------------------

#ifndef ADJACENCY_MATRIX_H
#define ADJACENCY_MATRIX_H

#include "graph.h"


class AdjacencyMatrix : public Graph
{
public:

  // default constructor
  AdjacencyMatrix(int vertex_count);

  // destructor
  ~AdjacencyMatrix();

  // copy constructor
  AdjacencyMatrix(const AdjacencyMatrix& rhs);

  // assignment operator
  AdjacencyMatrix& operator=(const AdjacencyMatrix& rhs);

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

  // remove an edge from the graph
  void remove_edge(int v1, int v2);
  
private:

  int number_of_vertices;
  int number_of_edges;

  // an array of pointers to int
  int** adj_matrix; 

  // return the matrix index for edge x->y
  int index(int x, int y) const;

  // delete the adjacency matrix
  void make_empty();
  
};


#endif

