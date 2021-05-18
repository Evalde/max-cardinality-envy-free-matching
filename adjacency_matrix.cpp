//----------------------------------------------------------------------
// NAME: Alex Weaver
// FILE: adjacency_matrix.cpp
// DATE: 2/2/21
// DESC: Adjacency matrix implementation of the graph interface
//----------------------------------------------------------------------

#include "adjacency_matrix.h"

using namespace std;

// delete the adjacency matrix
void AdjacencyMatrix::make_empty(){
    for (int i = 0; i < number_of_vertices * number_of_vertices; i++){
        delete[] adj_matrix[i];
    }
}

// return the matrix index for edge x->y
int AdjacencyMatrix::index(int x, int y) const{
    int v = vertex_count();
    int index = (x * v) + y;
    return index;
}

//constructor
AdjacencyMatrix::AdjacencyMatrix(int vertex_count){
    number_of_vertices = vertex_count;
    number_of_edges = 0;
    int size = vertex_count * vertex_count;
    adj_matrix = new int*[size];
    for (int i = 0; i < size; i++){
        adj_matrix[i] = nullptr;
    }
}

//destructor
AdjacencyMatrix::~AdjacencyMatrix(){
    make_empty();
    delete[] adj_matrix;
}

//copy constructor
AdjacencyMatrix::AdjacencyMatrix(const AdjacencyMatrix& rhs){
    number_of_vertices = 0;
    number_of_edges = 0;
    *this = rhs;
}

// assignment operator
AdjacencyMatrix& AdjacencyMatrix:: operator=(const AdjacencyMatrix& rhs){
    if(adj_matrix == rhs.adj_matrix){
        return *this;
    }
    make_empty();
    number_of_vertices = rhs.number_of_vertices;
    number_of_edges = rhs.number_of_edges;
    int size = number_of_vertices * number_of_vertices;
    adj_matrix = new int*[size];
    for (int i = 0; i < size; i++){
        if (rhs.adj_matrix[i] != nullptr){
            adj_matrix[i] = new int;
            *adj_matrix[i] = *rhs.adj_matrix[i];
        }
        else{
            adj_matrix[i] = nullptr;
        }
    }
}

// add or update an edge between existing vertices in the graph
void AdjacencyMatrix::set_edge(int v1, int edge_label, int v2){
    if (v1 > number_of_vertices || v2 > number_of_vertices) {
        return;
    }
    else {
        int i = index(v1, v2);
        if (adj_matrix[i] != nullptr) {
            *adj_matrix[i] = edge_label;
        } 
        else {
            adj_matrix[i] = new int;
            *adj_matrix[i] = edge_label;
            number_of_edges++;
        }
    }
}

// check if the given edge is in the graph
bool AdjacencyMatrix::has_edge(int v1, int v2) const{
    if(adj_matrix[index(v1,v2)]){
        return true;
    }
    else{
        return false;
    }
}

// returns true if there is an edge between v1 and v2 in the graph
// the output parameter returns the edge label
bool AdjacencyMatrix::get_edge(int v1, int v2, int& edge) const{
    if(has_edge(v1,v2)){
        edge = *adj_matrix[index(v1,v2)];
        return true;
    }
    else{
        return false;
    }
}
  
// get all vertices on an outgoing edge from given vertex
void AdjacencyMatrix::connected_to(int v1, std::list<int>& vertices) const{
    std::list<int>::iterator it;
    it = vertices.begin();
    // for (int i = (v1*number_of_vertices); i < (v1*number_of_vertices) + number_of_vertices; i++) {
    //     if (adj_matrix[i] != nullptr){
    //         vertices.insert(it, (i - number_of_vertices * v1));
    //         it++;
    //     }
    // }
    for(int i = 0; i < number_of_vertices; i ++){
        if (adj_matrix[v1 * number_of_vertices + i] != nullptr){
            vertices.insert(it, i);
            it++;
        }
    }
}

// get all vertices on an incoming edge to given vertex
void AdjacencyMatrix::connected_from(int v2, std::list<int>& vertices) const{
    std::list<int>::iterator it;
    it = vertices.begin();
    for(int i = 0; i < number_of_vertices; i++){
        if(adj_matrix[i * number_of_vertices + v2] != nullptr){
            vertices.insert(it, i);
            it++;
        }
    }
}

// get all vertices adjacent to a vertex, that is, connected to or connected
// from the vertex (may return duplicate vertices)
void AdjacencyMatrix::adjacent(int v, std::list<int>& vertices) const{
    std::list<int>::iterator it;
    it = vertices.begin();
    for(int i = 0; i < number_of_vertices; i ++){
        if (adj_matrix[v * number_of_vertices + i] != nullptr){
            vertices.insert(it, i);
            it++;
        }
    }
    for(int i = 0; i < number_of_vertices; i++){
        if(adj_matrix[i * number_of_vertices + v] != nullptr){
            vertices.insert(it, i);
            it++;
        }
    }
}

// get number of nodes in the graph
int AdjacencyMatrix::vertex_count() const{
    return number_of_vertices;
}

// get number of edges in the graph
int AdjacencyMatrix::edge_count() const{
    return number_of_edges;
} 

// remove an edge in the graph
void AdjacencyMatrix::remove_edge(int v1, int v2){
    if (has_edge(v1, v2)){
        int i = index(v1, v2);
        adj_matrix[i] = nullptr;
        number_of_edges--;
    }
}