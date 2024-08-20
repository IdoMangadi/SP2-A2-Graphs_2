// ID: 315310250
// EMAIL: IDOIZHAR.Mangadi@msmail.ariel.ac.il
// GMAIL: idomangadi@gmail.com

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include "Graph.hpp"

namespace ariel{
    /**
     * Namespace for algorithms on graphs.
    */
    namespace Algorithms{
        /**
         * Function to determine if a given Graph is strong connected for directed or undirected graph.
         * In case of directed graph, this function uses the kosaraju algorithm.
         * In case of undirected graph, this function uses the DFS algorithm.
         * returns: 1 for strong connected and 0 for not strong connected.
        */
        int isConnected(Graph &g);
        /**
         * Function to return the shortest path from src to dst using bellman ford algorithm.
         * The choice to use this algorithm is because we want to detect a negative cycle.
         * returns: the shortest path as a string, "-1" if there is no such path at all or if there is a negative cycle.
        */
        std::string shortestPath(Graph &g, size_t src, size_t dst);
        /**
         * Function to determine if a given graph contains a cycle using the basic DAG theorem.
         * (graph is a DAG if and only if there is no back edges in it).
        */
        bool isContainsCycle(Graph &g); 
        /**
         * Function to determine whethear a given graph is biapartite or not.
         * (graph is bipartite if and only it can be colored with 2 colors).
         * retutn: the groups of vertices or "0" if it is not a biapartite graph.
        */
        std::string isBipartite(Graph &g);
        /**
         * Function to determine whethear there is a negative cycle in a given *directed* graph.
         * this function uses the Bellman-Ford algorithm.
         * return: the negative cycle or "-1" if there is no negative cycle in the graphor if its a undirected graph.
        */
        std::string negativeCycle(Graph &g);
    }
}


#endif // ALGORITHMS_HPP