//----------------------------------------------------------------------
// Name: Alex Weaver
// File: project_tests.cpp
// Date: Spring 2021
// Desc: Unit tests for list and matrix graph implementations
//----------------------------------------------------------------------


#include <iostream>
#include <string>
#include <list>
#include <set>
#include <vector>
#include <gtest/gtest.h>
#include "graph.h"
#include "adjacency_list.h"
#include "adjacency_matrix.h"


using namespace std;


//----------------------------------------------------------------------
// Helper functions for testing
//----------------------------------------------------------------------

void print_graph(const Graph& g)
{
  int n = g.vertex_count();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (g.has_edge(i,j)) {
        int edge_label;
        g.get_edge(i, j, edge_label);
        cout << "(" << i << "," << edge_label << "," << j << ")" << endl;
      }
    }
  }
}

//----------------------------------------------------------------------
// Adjacency List Tests
//----------------------------------------------------------------------

TEST(AdjacencyListTest, Basic) {
  AdjacencyList g(5);
  g.set_edge(0, 0, 3);
  g.set_edge(1, 0, 3);
  g.set_edge(2, 0, 3);
  g.set_edge(2, 0, 4);
  AdjacencyList m(5);
  ASSERT_EQ(true, g.max_size_envy_free_matching(m));
  ASSERT_EQ(1, m.edge_count());
  ASSERT_EQ(true, m.has_edge(2, 4) or m.has_edge(4, 2));
}

TEST(AdjacencyListTest, Empty) {
  AdjacencyList g(5);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 4);
  AdjacencyList m(5);
  ASSERT_EQ(true, g.max_size_envy_free_matching(m));
  ASSERT_EQ(0, m.edge_count());
}

TEST(AdjacencyListTest, XSaturated) {
  AdjacencyList g(6);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 4);
  g.set_edge(4, 0, 5);
  AdjacencyList m(6);
  ASSERT_EQ(true, g.max_size_envy_free_matching(m));
  ASSERT_EQ(3, m.edge_count());
  ASSERT_EQ(true, m.has_edge(0, 1) or m.has_edge(1, 0));
  ASSERT_EQ(true, m.has_edge(2, 3) or m.has_edge(3, 2));
  ASSERT_EQ(true, m.has_edge(4, 5) or m.has_edge(5, 4));
}

TEST(AdjacencyListTest, NotBipartite){
  AdjacencyList g(3);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 0);
  AdjacencyList m(3);
  ASSERT_EQ(false, g.bipartite_graph_matching(m));
}

//----------------------------------------------------------------------
// Adjacency Matrix Tests
//----------------------------------------------------------------------

TEST(AdjacencyMatrixTest, Basic) {
  AdjacencyMatrix g(5);
  g.set_edge(0, 0, 3);
  g.set_edge(1, 0, 3);
  g.set_edge(2, 0, 3);
  g.set_edge(2, 0, 4);
  AdjacencyMatrix m(5);
  ASSERT_EQ(true, g.max_size_envy_free_matching(m));
  ASSERT_EQ(1, m.edge_count());
  ASSERT_EQ(true, m.has_edge(2, 4) or m.has_edge(4, 2));
}

TEST(AdjacencyMatrixTest, Advanced) {
  AdjacencyMatrix g(14);
  g.set_edge(0, 0, 8);
  g.set_edge(1, 0, 9);
  g.set_edge(1, 0, 10);
  g.set_edge(2, 0, 11);
  g.set_edge(3, 0, 9);
  g.set_edge(3, 0, 11);
  g.set_edge(4, 0, 8);
  g.set_edge(4, 0, 10);
  g.set_edge(4, 0, 11);
  g.set_edge(5, 0, 9);
  g.set_edge(5, 0, 10);
  g.set_edge(5, 0, 11);
  g.set_edge(6, 0, 10);
  g.set_edge(6, 0, 12);
  g.set_edge(7, 0, 11);
  g.set_edge(7, 0, 13);
  g.set_edge(7, 0, 14);
  AdjacencyMatrix m(14);
  ASSERT_EQ(true, g.max_size_envy_free_matching(m));
  ASSERT_EQ(2, m.edge_count());
  ASSERT_EQ(true, m.has_edge(6, 12) or m.has_edge(12, 6));
  ASSERT_EQ(true, m.has_edge(7, 13) or m.has_edge(13, 7));
}

TEST(AdjacencyMatrixTest, Empty) {
  AdjacencyMatrix g(5);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 4);
  AdjacencyMatrix m(5);
  ASSERT_EQ(true, g.max_size_envy_free_matching(m));
  ASSERT_EQ(0, m.edge_count());
}

TEST(AdjacencyMatrixTest, XSaturated) {
  AdjacencyMatrix g(6);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 3);
  g.set_edge(3, 0, 4);
  g.set_edge(4, 0, 5);
  AdjacencyMatrix m(6);
  ASSERT_EQ(true, g.max_size_envy_free_matching(m));
  ASSERT_EQ(3, m.edge_count());
  ASSERT_EQ(true, m.has_edge(0, 1) or m.has_edge(1, 0));
  ASSERT_EQ(true, m.has_edge(2, 3) or m.has_edge(3, 2));
  ASSERT_EQ(true, m.has_edge(4, 5) or m.has_edge(5, 4));
}

TEST(AdjacencyMatrixTest, NotBipartite){
  AdjacencyMatrix g(3);
  g.set_edge(0, 0, 1);
  g.set_edge(1, 0, 2);
  g.set_edge(2, 0, 0);
  AdjacencyMatrix m(3);
  ASSERT_EQ(false, g.bipartite_graph_matching(m));
}

//----------------------------------------------------------------------
// Extended Implementation
//----------------------------------------------------------------------

TEST(ExtendedImplementation, List) {
  AdjacencyList g(14);
  g.set_edge(0, 0, 8);
  g.set_edge(1, 0, 9);
  g.set_edge(1, 0, 10);
  g.set_edge(2, 0, 11);
  g.set_edge(3, 0, 9);
  g.set_edge(3, 0, 11);
  g.set_edge(4, 0, 8);
  g.set_edge(4, 0, 10);
  g.set_edge(4, 0, 11);
  g.set_edge(5, 0, 9);
  g.set_edge(5, 0, 10);
  g.set_edge(5, 0, 11);
  g.set_edge(6, 0, 10);
  g.set_edge(6, 0, 12);
  g.set_edge(7, 0, 11);
  g.set_edge(7, 0, 13);
  g.set_edge(7, 0, 14);
  AdjacencyList m(14);
  ASSERT_EQ(true, g.max_size_envy_free_matching(m));
  ASSERT_EQ(2, m.edge_count());
  ASSERT_EQ(true, m.has_edge(6, 12) or m.has_edge(12, 6));
  ASSERT_EQ(true, m.has_edge(7, 13) or m.has_edge(13, 7));
}

TEST(ExtendedImplementation, Matrix) {
  AdjacencyMatrix g(14);
  g.set_edge(0, 0, 8);
  g.set_edge(1, 0, 9);
  g.set_edge(1, 0, 10);
  g.set_edge(2, 0, 11);
  g.set_edge(3, 0, 9);
  g.set_edge(3, 0, 11);
  g.set_edge(4, 0, 8);
  g.set_edge(4, 0, 10);
  g.set_edge(4, 0, 11);
  g.set_edge(5, 0, 9);
  g.set_edge(5, 0, 10);
  g.set_edge(5, 0, 11);
  g.set_edge(6, 0, 10);
  g.set_edge(6, 0, 12);
  g.set_edge(7, 0, 11);
  g.set_edge(7, 0, 13);
  g.set_edge(7, 0, 14);
  AdjacencyMatrix m(14);
  ASSERT_EQ(true, g.max_size_envy_free_matching(m));
  ASSERT_EQ(2, m.edge_count());
  ASSERT_EQ(true, m.has_edge(6, 12) or m.has_edge(12, 6));
  ASSERT_EQ(true, m.has_edge(7, 13) or m.has_edge(13, 7));
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

