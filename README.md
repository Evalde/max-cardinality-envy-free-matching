# Envy Free Matching
 This project finds a maximum cardinality, envy-free matching of a bipartite graph represented as either an adjacency list or adjacency matrix. The algorithm uses modified BFS logic to iterate through a queue of unmatched nodes within a maximum cardinality matching to remove envied matches. 
 
 [Testing](https://github.com/Evalde/max-cardinality-envy-free-matching/blob/main/project_tests.cpp) utilizes GoogleTest which can be found [here](https://github.com/google/googletest).

 # Setup

 ```sh
 cmake CMakeLists.txt
 make
 ```

 # References

 [Envy-free Matchings in Bipartite Graphs and their Applications to Fair Division](https://arxiv.org/pdf/1901.09527.pdf) by Elad Aigner-Horev and Erel Segal-Halevi