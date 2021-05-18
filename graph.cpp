//----------------------------------------------------------------------
// NAME: Alex Weaver
// FILE: graph.cpp
// DATE: Spring 2021
// DESC: Implementation of graph.h
//----------------------------------------------------------------------

#include <iostream> 
#include <string>
#include <queue>
#include <stack>
#include <list>
#include <set>
#include <algorithm>
#include "graph.h"

using namespace std;

// Bipartite Graph
bool Graph::bipartite_graph(Map& coloring) const {
    queue<int> q;
    list<int> vertices;

    coloring[0] = 0;
    q.push(0);

    while(!q.empty()){
        vertices.clear();
        int curr = q.front();
        q.pop();

        adjacent(curr, vertices);
        for(auto const& v: vertices){
            if(coloring.find(v) == coloring.end()){
                q.push(v);
                if(coloring[curr] == 0){
                    coloring[v] = 1;
                }
                else{
                    coloring[v] = 0;
                }
            }
            else{
                if(coloring[curr] == coloring[v]){
                    return false;
                }
            }
        }
        if(q.empty()){
            for(int i = 0; i < vertex_count(); i++){
                if(coloring.find(i) == coloring.end()){
                    q.push(i);
                    break;
                }
            }
        }
    }
    return true;
}

// Bipartite Graph Matching
bool Graph::bipartite_graph_matching(Graph& max_matched_graph) const{
    Map coloring;
    
    bool is_bipratite = bipartite_graph(coloring);
    if (is_bipratite == false) {
        return false;
    }

    // lists needed for matching
    set<int> v1;
    set<int> v2;
    
    // fills v1 and v2
    for (auto& t : coloring) {
        if (t.second == 0) 
            v1.insert(t.first);
        else 
            v2.insert(t.first);
    }

    // modified bfs starts here
    queue<int> q;
    list<int> vertices;
    int v, w;
    Map temp;

    // matched true means it is in matching
    int *mate = new int[vertex_count()];
    bool *matched = new bool[vertex_count()];
    for(int i = 0; i < vertex_count(); i++){
        mate[i] = -1;
        matched[i] = false;
    }

    for(int i: v1){
        q.push(i);
    }
    
    while (!q.empty()){
        vertices.clear();
        w = q.front();
        q.pop();

        adjacent(w, vertices);
        if(v1.find(w) != v1.end()){
            for (int u: vertices){
                if(v2.find(u) != v2.end()){
                    if (!matched[u]){
                        // put (w, u) in matching
                        max_matched_graph.set_edge(w, 0, u);
                        matched[w] = true;
                        matched[u] = true;
                        mate[w] = u;
                        mate[u] = w;
                        v = w;
                        while(temp.count(v) > 0){
                            u = temp[v];
                            max_matched_graph.remove_edge(v, u);
                            matched[v] = false;
                            matched[u] = false;
                            mate[v] = -1;
                            mate[u] = -1;
                            v = temp[u];
                            max_matched_graph.set_edge(v, 0, u);
                            matched[v] = true;
                            matched[u] = true;
                            mate[v] = u;
                            mate[u] = v;
                        }

                        // remove all vertex labels
                        temp.clear();
                        while(!q.empty()){
                            q.pop();
                        }

                        // reinitialize q with all free vertices
                        for(int i: v1){
                            if(!matched[i]){
                                q.push(i);
                            }
                        }
                        break;
                    }
                    else{
                        if(!max_matched_graph.has_edge(w, u) && temp.count(u) == 0){
                            temp[u] = w;
                            q.push(u);
                        }
                    }
                }
            }
        }
        else{
            v = mate[w];
            mate[v] = w;
            temp[v] = w;
            q.push(v);
        }
    }
    return true;
}

bool Graph::max_size_envy_free_matching(Graph& max_efm_graph) const{
    Map coloring;
    list<int> vertices;
    list<int> vertices2;
    queue<int> q;
    int curr;
    
    // check if graph is bipartite
    // if no, return false
    bool is_bipratite = bipartite_graph(coloring);
    if (is_bipratite == false) {
        return false;
    }

    // init sets X and Y
    set<int> X;
    set<int> Y;
    
    // fill sets X and Y
    for (auto& t : coloring) {
        if (t.second == 0) 
            X.insert(t.first);
        else 
            Y.insert(t.first);
    }

    bool *visited = new bool[X.size()];
    for(int i = 0; i < X.size(); i++){
        visited[i] = false;
    }

    // find maximum cardinality matching M in G
    bipartite_graph_matching(max_efm_graph);

    // if M is empty, M is max EFM
    if(max_efm_graph.edge_count() == 0){
        return true;
    }

    // ALGO STARTS HERE
    // add all unmatched x in X to queue
    for(auto const x : X){
        vertices.clear();
        max_efm_graph.adjacent(x, vertices);
        if(vertices.size() == 0){
            q.push(x);
        }
    }

    // if unmatched x has adjacent nodes y in G that are matched in M
    // remove the edge from the matching, unmatching the y from its neighbor
    // finalized M after q is emptied is max EFM
    while(!q.empty()){
        vertices.clear();
        curr = q.front();
        visited[curr] = true;
        q.pop();
        adjacent(curr, vertices);
        for(auto const y : vertices){
            vertices2.clear();
            // if y is matched in M
            max_efm_graph.adjacent(y, vertices2);
            if(vertices2.size() > 0){
                for(auto const v : vertices2){
                    if(!visited[v]){
                        q.push(v);
                    }
                    max_efm_graph.remove_edge(v, y);
                    max_efm_graph.remove_edge(y, v);
                }
            }
        }
    }

    return true;
}