// ID: 315310250
// EMAIL: IDOIZHAR.Mangadi@msmail.ariel.ac.il
// GMAIL: idomangadi@gmail.com

# Graph Algorithms

This project implements various graph algorithms such as finding whether a graph is strongly connected,
finding the shortest path, checking for cycles, determining if a graph is bipartite, and detecting negative cycles.
moreover, this project allows operations on graph such as arithmetic operations and comparisons. 

## Project Structure

The project is divided into two main parts:

1. **Graph**: Contains the implementation of the `Graph` class.
   - `Graph.hpp`: Header file containing the declaration of the `Graph` class.
   - `Graph.cpp`: Source file containing the implementation of the `Graph` class methods.

2. **Algorithms**: Contains the implementation of various graph algorithms.
   - `Algorithms.hpp`: Header file containing the declaration of the `Algorithms` namespace and its functions.
   - `Algorithms.cpp`: Source file containing the implementation of the graph algorithms.

## Graph Class

The `Graph` class is responsible for representing a graph. It contains an adjacency matrix to store the graph's edges.

### Methods:

1. `Graph()`: Constructor to initialize an empty graph.
   `Graph(Graph& g1)`: Constructor to perform a deep copy to the graph.

2. `loadGraph(const std::vector<std::vector<int>> &input_matrix)`: Copies a given matrix into the graph's adjacency matrix.
   - **Parameters**: `input_matrix` - The matrix to be copied.
   - **Return Type**: `void`

3. `printGraph() const`: Prints all the values of the graph.
   - **Return Type**: `void`

4. `size() const`: Returns the size of the square graph.
   - **Return Type**: `size_t`

5. `getGraph() const`: Returns the adjacency matrix of the graph.
   - **Return Type**: `std::vector<std::vector<int>>`

6. Aritmetic operands, for graphs g1, g2: +g1, -g1, g1++, ++g1, g1+g2, g1--, --g1, g1-g2, g1*int, g1/int, g1*g2 

7. Comparison operands: for graphs G1 and G2: G1<G2 if: graph G1 is strictly contained in graph G2.
                                                        If no graph is strictly contained in the other and the graphs are not equal,
                                                        then graph G2 is larger than graph G1 if the number of edges in G2 is greater than the number of edges in G1.
                                                        If, nevertheless, the number of edges is the same,
                                                        then graph G2 is larger than graph G1 if the representing matrix of G2 has a higher order than that of G1.
                                              G1==G2 if: the graphs has identical adjency matrices or if neither G1<G2 and G1>G2.
                                              and the rest operands such <= , >= , != are according to this two roles.

8. Output stream: the graph can be directed into output stream using overloading of the << operator. 
                  it will provide a visual demonstration of the adjency matrix of the graph. 

## Algorithms Namespace

The `Algorithms` namespace contains various graph algorithms.

### Functions:

1. `isConnected(Graph &g)`: Determines if a given graph is strongly connected for directed or undirected graphs.
   - **Return Type**: `int` - 1 for strongly connected, 0 for not strongly connected.

2. `shortestPath(Graph &g, size_t src, size_t dst)`: Returns the shortest path from source to destination using the Bellman-Ford algorithm.
   - **Return Type**: `std::string` - The shortest path as a string.

3. `isContainsCycle(Graph &g)`: Determines if a given graph contains a cycle.
   - **Return Type**: `bool` - True if the graph contains a cycle, false otherwise.

4. `isBipartite(Graph &g)`: Determines if a given graph is bipartite.
   - **Return Type**: `std::string` - "The graph is bipartite: A={...}, B={...}" or "0" if the graph is not bipartite.

5. `negativeCycle(Graph &g)`: Determines if there is a negative cycle in a given directed graph.
   - **Return Type**: `std::string` - The negative cycle as a string or "No negative cycle" if there is none.

