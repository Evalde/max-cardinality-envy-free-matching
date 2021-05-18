//----------------------------------------------------------------------
// NAME: Alex Weaver
// FILE: adjacency_list.cpp
// DATE: 2/2/21
// DESC: Adjacency list implementation of the graph interface
//----------------------------------------------------------------------

#include "adjacency_list.h"

using namespace std;

// helper function to delete adj_list
void AdjacencyList::make_empty() {
    Node* curr = new Node;
    Node* temp = new Node;
    for (int i = 0; i < number_of_vertices; ++i){
        curr = adj_list_in[i];
        if (curr != nullptr) {
            while (curr != nullptr) {
                temp = curr -> next;
                delete curr;
                curr = temp;
            }
       }
        curr = adj_list_out[i];
        if (curr != nullptr) {
            while (curr != nullptr) {
                temp = curr -> next;
                delete curr;
                curr = temp;
            }
        }
    }
    delete[] adj_list_in;
    adj_list_in = nullptr;
    delete[] adj_list_out;
    adj_list_out = nullptr;
}

//constructor
AdjacencyList::AdjacencyList(int vertex_count) {
    number_of_vertices = vertex_count;
    number_of_edges = 0;
    adj_list_out = new Node*[vertex_count];
    adj_list_in = new Node*[vertex_count];
    for (int i = 0; i < vertex_count; ++i){
        adj_list_in[i] = nullptr;
        adj_list_out[i] = nullptr;
    }
}

//destructor
AdjacencyList::~AdjacencyList() {
    make_empty();
}

//copy constructor
AdjacencyList::AdjacencyList(const AdjacencyList& rhs) {
    number_of_vertices = 0;
    number_of_edges = 0;
    adj_list_out = nullptr;
    adj_list_in  = nullptr;
    *this = rhs;
}

//asignment operator
AdjacencyList& AdjacencyList::operator=(const AdjacencyList& rhs) {
    std::list<int> vertices;
    if (adj_list_out == rhs.adj_list_out && adj_list_in == rhs.adj_list_in){
        return *this;
    }
    make_empty();
    number_of_vertices = rhs.number_of_vertices;
    number_of_edges = rhs.number_of_edges;
    int size = number_of_vertices;
    adj_list_out = new Node*[size];
    adj_list_in = new Node*[size];
    for (int i = 0; i < rhs.number_of_vertices; ++i){
        adj_list_in[i] = nullptr;
        adj_list_out[i] = nullptr;
    }
    for(int i = 0; i < rhs.number_of_vertices; i++){
        vertices.clear();
        rhs.connected_to(i, vertices);
        for (auto const& v: vertices){
            set_edge(i, 0, v);
        }
    }
    return *this;
}

// add or update an edge between existing vertices in the graph
void AdjacencyList::set_edge(int v1, int edge_label, int v2) {
    //checking to see if the edge label already exists in adj_list_in
    Node* temp = adj_list_out[v1];
    bool duplicate = false;
    //if there are no entries at adj_list_out[v1] this if statement will create one
    if(temp == nullptr){
      Node* set_me = new Node;
      set_me->vertex = v2;
      set_me->edge = edge_label;
      set_me->next = nullptr;
      adj_list_out[v1] = set_me;
    }
    //this code will check for duplicates and find the end of the current list to add the new node on
    else{
      //checking to see if the end of the list has been reached
      while(temp->next != nullptr){
        //checking for duplicates to avoid duplicate vertex entries
        if(temp->vertex == v2){
          temp->edge = edge_label;
          duplicate = true;
        }
        temp = temp->next;
      }
      //checking the last value in the list to avoid duplicate vertex entries
      if(temp->vertex == v2){
          temp->edge = edge_label;
          duplicate = true;
      }
      //if the end of the list has been reached and no duplicates have been found this will add the new edge
      if(duplicate == false){
        Node* set_me = new Node;
        set_me->vertex = v2;
        set_me->edge = edge_label;
        set_me->next = nullptr;
        temp->next = set_me;
      }
    }
    //the process now repeats for the adj_list_in list
    temp = adj_list_in[v2];
    if(temp == nullptr){
      Node* set_me = new Node;
      set_me->vertex = v1;
      set_me->edge = edge_label;
      set_me->next = nullptr;
      adj_list_in[v2] = set_me;
    }
    //this code will check for duplicates and find the end of the current list to add the new node on
    else{
      //checking to see if the end of the list has been reached
      while(temp->next != nullptr){
        //checking for duplicates to avoid duplicate vertex entries
        if(temp->vertex == v1){
          temp->edge = edge_label;
          duplicate = true;
          return;
        }
        temp = temp->next;
      }
      //checking the last value in the list to avoid duplicate vertex entries
      if(temp->vertex == v1){
          temp->edge = edge_label;
          return;
      }
      //if the end of the list has been reached and no duplicates have been found this will add the new edge
      Node* set_me = new Node;
      set_me->vertex = v1;
      set_me->edge = edge_label;
      set_me->next = nullptr;
      temp->next = set_me;
    }
    number_of_edges++;
}

// check if the given edge is in the graph
bool AdjacencyList::has_edge(int v1, int v2) const {
    Node* temp = new Node;
    temp = adj_list_out[v1];
    while(temp != nullptr){
      if(temp->vertex == v2){
        return true;
      }
      temp = temp->next;
    }
    return false;
} 

// returns true if there is an edge between v1 and v2 in the graph
// the output parameter returns the edge label
bool AdjacencyList::get_edge(int v1, int v2, int& edge) const {
    Node* temp = new Node;
    temp = adj_list_out[v1];
    while(temp != nullptr){
      if(temp->vertex == v2){
        edge = temp->edge;
        return true;
      }
      temp = temp->next;
    }
    return false;
}

// get all vertices on an outgoing edge from given vertex
void AdjacencyList::connected_to(int v1, std::list<int>& vertices) const {
    std::list<int>::iterator it;
    it = vertices.begin();

    if (adj_list_out[v1] == nullptr) {
        return;
    } 
    else {
        Node* cur = new Node;
        cur = adj_list_out[v1];
        while (cur != nullptr) {                          
            vertices.insert(it, cur -> vertex);
            it++;
            cur = cur -> next;
        }
    }
}

// get all vertices on an incoming edge to given vertex
void AdjacencyList::connected_from(int v2, std::list<int>& vertices) const {
    std::list<int>::iterator it;
    it = vertices.begin();

    if (adj_list_in[v2] == nullptr) {
        return;
    } 
    else {
        Node* cur = new Node;
        cur = adj_list_in[v2];
        while (cur != nullptr) {                          
            vertices.insert(it, cur -> vertex);
            it++;
            cur = cur -> next;
        }
    }
}

// get all vertices adjacent to a vertex, that is, connected to or connected
// from the vertex (may return duplicate vertices)
void AdjacencyList::adjacent(int v, std::list<int>& vertices) const {
    connected_to(v, vertices);
    connected_from(v, vertices);
}

// get number of nodes in the graph
int AdjacencyList::vertex_count() const {
    return number_of_vertices;
} 

// get number of edges in the graph
int AdjacencyList::edge_count() const {
    return number_of_edges;
}

// remove an edge from the graph
void AdjacencyList::remove_edge(int v1, int v2){
    if(has_edge(v1, v2)){
        Node* temp = new Node;
        Node* prev = NULL;

        // remove edge from out list
        temp = adj_list_out[v1];

        // if node to be removed is head
        if (temp->vertex == v2){
            adj_list_out[v1] = temp -> next;
            delete temp;
        }
        // else search until node is found, link list around node to delete, delete node
        else{
            while(temp != nullptr && temp->vertex != v2){
                prev = temp;
                temp = temp -> next;
            }
            prev->next = temp->next;
            delete temp;
        }

        // remove edge from in list
        temp = adj_list_in[v2];
        // if node to be removed is head
        if(temp->vertex == v1){
            adj_list_in[v2] = temp->next;
            delete temp;
        }
        else{
            while(temp != nullptr && temp->vertex != v1){
                prev = temp;
                temp = temp -> next;
            }
            prev->next = temp->next;
            delete temp;
        }

        number_of_edges--;
    }
}