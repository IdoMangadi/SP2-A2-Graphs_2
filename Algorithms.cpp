// ID: 315310250
// EMAIL: IDOIZHAR.Mangadi@msmail.ariel.ac.il
// GMAIL: idomangadi@gmail.com

/**
 * In this file i implemented algorithms on graphs mentioned in the Algorithms.hpp file.
 * To do this i used: Course Algorithms 1 from last semester (lectures), 
 * wikipedia https://he.wikipedia.org/wiki/%D7%92%D7%A8%D7%A3_%D7%A7%D7%A9%D7%99%D7%A8
 * and ChatGPT.
*/

#include <iostream>
#include <queue>
#include "Algorithms.hpp"

#define INT_MAX std::numeric_limits<int>::max()

namespace ariel{
    
    namespace Algorithms{

        // ------------------------------------------------ //
        // ------------------IS CONNECTED------------------ //
        // ------------------------------------------------ //
        /**
         * A simple implementation of DFS:
        */ 
        void dfs(Graph &g, size_t v, std::vector<int> &visited){

            visited[v] = 1;  // marking the vertix as visited
            for(size_t i=0; i<g.size(); i++){ // going over the neighbours and if not visited, operating dfs on them
                if(g.adj_matrix[v][i] != 0 && visited[i] == 0) {
                    dfs(g, i, visited);
                }
            }
        }

        /**
         * A simple util function to check whethear a graph is directed or not
        */
        bool isDirected(Graph &g){
            for(size_t i=0; i<g.size(); i++){  // going over all the verteces
                for(size_t j=0; j<g.size(); j++){
                    if(g.adj_matrix[i][j] != g.adj_matrix[j][i]){ 
                        return true;
                    }
                }
            }
            return false;
        }

        int isConnected(Graph &g){
            size_t n = g.size();
            if( n == 0) return 1;

            // checking if it is a directed or undirected graph:
            bool directed = isDirected(g);
            

            std::vector<int> visited(g.size(), 0); // craeting a visited vector with 0's
            if(directed){
                // in this case we do n dfs's:
                for(size_t i=0; i<n; i++){
                    std::fill(visited.begin(), visited.end(), 0); // filling "visited" with 0's.
                    dfs(g, i, visited);
                    for(int v : visited){  // going all over the vertices
                        if( v == 0){  // means we didnt reach to one of the vertices
                            return 0;
                        }
                    }
                }

            }
            else{  // the graph is undirected:
                dfs(g, 0, visited);  // operating dfs one time on the graph
                for(int v : visited){  // going all over the vertices
                    if( v == 0){  // means we didnt reach to one of the vertices
                        return 0;
                    }
                }
            }

            return 1;  // means all validations went ok, the graph is strong connected. 
        }


        // ------------------------------------------------ //
        // ------------------SHORTEST PATH----------------- //
        // ------------------------------------------------ //

        std::string shortestPath(Graph &g, size_t src, size_t dst){
            size_t n = g.adj_matrix.size();
            if( n == 0 || src > n-1 || dst > n-1) return "-1";  // validation check

            std::vector<int> dist(n, std::numeric_limits<int>::max()); // Initialize distances to infinity
            std::vector<int> parent(n, -1); // To store the parent of each vertex in the shortest path (init with -1)
            std::vector<int> path; // to store the shortest path from src to dst

            dist[src] = 0; // init the distance from src to itself to 0

            // Relax edges |V|-1 times:
            for (size_t i = 0; i < n-1; i++) { // notice (n-1)
                for (size_t j = 0; j < n; j++) {  // going over the edges:
                    for (size_t v = 0; v < n; v++) {
                        if (g.adj_matrix[j][v] != 0 && dist[j] != std::numeric_limits<int>::max() && dist[j] + g.adj_matrix[j][v] < dist[v]) {
                            dist[v] = dist[j] + g.adj_matrix[j][v];
                            parent[v] = j;
                        }
                    }
                }
            }

            // Check for negative cycles (one last relaxing)
            for (size_t u = 0; u < n; ++u) {
                for (size_t v = 0; v < n; ++v) {
                    if (g.adj_matrix[u][v] != 0 && dist[u] != std::numeric_limits<int>::max() && dist[u] + g.adj_matrix[u][v] < dist[v]) {
                        // Negative cycle found
                        // std::cout << "Graph contains negative cycle" << std::endl;
                        return "-1";
                    }
                }
            }
            
            // Check for empty path:
            if(parent[dst] == -1){
                return "-1";
            }

            // Reconstruct the shortest path
            for (int v = dst; v != -1; v = parent[(unsigned int)v]) {
                path.push_back(v);
            }
            std::reverse(path.begin(), path.end());  // reversing the path
            // converting to string:
            std::string result = "";
            for(size_t i=0; i<path.size(); i++){
                result += std::to_string(path[i]);
                if(i != path.size()-1){
                    result += "->";
                }
            }

            return result;
        }
        

        // ------------------------------------------------ //
        // ---------------------CYCLES--------------------- //
        // ------------------------------------------------ //

        // Simple implementation of dfs regarding cycles finding using the DAG theorem.
        enum Color { WHITE, GREY, BLACK };
        // directed graphs version:
        bool hasCycleUtil_directed(Graph &g, size_t u, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &cycleVertices) {
            color[u] = GREY; // Mark the current vertex as visited but not finished

            for (size_t v = 0; v < g.adj_matrix[u].size(); ++v) {  // going over the neighbours:
                if (g.adj_matrix[u][v] != 0) {
                    if (color[v] == WHITE) {  // means neighbour hasnt visited yet
                        parent[v] = u;
                        if (hasCycleUtil_directed(g, v, color, parent, cycleVertices)) {  // recursive call (implementing dfs principle)
                            return true;
                        }
                    } else if (color[v] == GREY) {  // means neighbour was visited already
                        int current = u;  // holding the cycle:
                        cycleVertices.push_back(v);
                        while (current != v) {
                            cycleVertices.push_back(current);
                            current = parent[static_cast<size_t>(current)];
                        }
                        cycleVertices.push_back(v);  // Adding the starting vertex to complete the cycle
                        std::reverse(cycleVertices.begin(), cycleVertices.end());
                        return true;
                    }
                }
            }

            color[u] = BLACK; // Mark the current vertex as finished
            return false;
        }
        // undirected graphs version:
        bool hasCycleUtil_undirected(Graph &g, size_t u, std::vector<Color> &color, std::vector<int> &parent, std::vector<int> &cycleVertices) {
            color[u] = GREY; // Mark the current vertex as visited but not finished

            for (size_t v = 0; v < g.adj_matrix[u].size(); ++v) {  // going over the neighbours:
                if (g.adj_matrix[u][v] != 0) {
                    if (color[v] == WHITE) {  // means neighbour hasnt visited yet
                        parent[v] = u;
                        if (hasCycleUtil_undirected(g, v, color, parent, cycleVertices)) {  // recursive call (implementing dfs principle)
                            return true;
                        }
                    } else if (color[v] == GREY && parent[u] != v) {  // means neighbour was visited already
                        int current = u;  // holding the cycle:
                        cycleVertices.push_back(v);
                        while (current != v) {
                            cycleVertices.push_back(current);
                            current = parent[static_cast<size_t>(current)];
                        }
                        cycleVertices.push_back(v);  // Adding the starting vertex to complete the cycle
                        std::reverse(cycleVertices.begin(), cycleVertices.end());
                        return true;
                    }
                }
            }

            color[u] = BLACK; // Mark the current vertex as finished
            return false;
        }

        bool isContainsCycle(Graph &g) {
            size_t n = g.adj_matrix.size();
            std::vector<Color> color(n, WHITE); // Initialize all vertices as not visited
            std::vector<int> parent(n, -1); // To store the parent of each vertex in the DFS tree (init with -1)
            std::vector<int> cycleVertices;  // to store the cycle if founded

            if(isDirected(g)){
                // Perform DFS from each vertex
                for (size_t i = 0; i < n; ++i) {
                    if (color[i] == WHITE && hasCycleUtil_directed(g, i, color, parent, cycleVertices)) {
                        // Construct the cycle string
                        std::string cycle = "The cycle is: ";
                        for (size_t ver = 0; ver < cycleVertices.size(); ver++) {
                            cycle += std::to_string(cycleVertices[ver]);
                            if(ver < cycleVertices.size()-1){
                                cycle += "->";
                            }
                        }
                        std::cout << cycle << std::endl;
                        return true;
                    }
                }
                return false; // No cycle found
            }
            else{
                // Perform DFS from each vertex
                for (size_t i = 0; i < n; ++i) {
                    if (color[i] == WHITE && hasCycleUtil_undirected(g, i, color, parent, cycleVertices)) {
                        // Construct the cycle string
                        std::string cycle = "The cycle is: ";
                        for (size_t ver = 0; ver < cycleVertices.size(); ver++) {
                            cycle += std::to_string(cycleVertices[ver]);
                            if(ver < cycleVertices.size()-1){
                                cycle += "->";
                            }
                        }
                        std::cout << cycle << std::endl;
                        return true;
                    }
                }
                return false; // No cycle found
            }
        }



        // ------------------------------------------------ //
        // -------------------BIAPARTIT-------------------- //
        // ------------------------------------------------ //

        std::string isBipartite(Graph &g) {

            size_t n = g.adj_matrix.size();
            if( n == 0) return "0";

            std::vector<int> colors(n, 0); // 0: uncolored, 1: group 1, 2: group 2
            size_t counter_2 = 0;  // to count how many vertices are colored in 2

            for (size_t i = 0; i < n; ++i) {
                if (colors[i] != 0) continue;

                std::queue<size_t> q;
                q.push(i);
                colors[i] = 1;

                while (!q.empty()) {
                    size_t node = q.front();
                    q.pop();

                    for (size_t neighbor = 0; neighbor < n; ++neighbor) {
                        if (g.adj_matrix[node][neighbor] != 0) {  // means there is an edge between them
                            if (colors[neighbor] == 0) {
                                colors[neighbor] = (colors[node] == 1) ? 2 : 1;
                                if(colors[neighbor] == 2) counter_2++;
                                q.push(neighbor);
                            } else if (colors[neighbor] == colors[node]) {
                                return "0"; // Not bipartite
                            }
                        }
                    }
                }
            }

            std::string group1 = "";
            std::string group2 = "";
            size_t counter_1 = n - counter_2;  // counter_1/2 represents how many 1 colored verteces there are left to add.

            for (size_t i = 0; i < n; ++i) {
                if (colors[i] == 1){
                    group1 += std::to_string(i);
                    if(counter_1 != 1) group1 += ", ";
                    counter_1--;  
                }
                else {
                    group2 += std::to_string(i);
                    if(counter_2 != 1) group2 += ", ";
                    counter_2--;
                }
            }

            return "The graph is bipartite: A={" + group1 + "}, B={" + group2 + "}";
        }


        
        // ------------------------------------------------ //
        // ----------------NEGATIVE CYCLES----------------- //
        // ------------------------------------------------ //

        std::string negativeCycle(Graph& g) {

            if(isDirected(g) == false){
                return "-1";
            }

            size_t n = g.size();
            if( n == 0) return "Empty graph";

            std::vector<int> dist(n, INT_MAX);
            std::vector<int> parent(n, -1); // To track the path
            std::vector<bool> visited(n, false);

            // Assume vertex 0 as the source
            dist[0] = 0;

            // Relax edges |V|-1 times
            for (size_t i = 0; i < n - 1; ++i) {
                bool relaxed  = false;
                for (size_t u = 0; u < n; ++u) {
                    for (size_t v = 0; v < n; ++v) {
                        if (g.adj_matrix[u][v] != 0 && dist[u] != INT_MAX && dist[u] + g.adj_matrix[u][v] < dist[v]) {
                            dist[v] = dist[u] + g.adj_matrix[u][v];
                            parent[v] = u;
                            relaxed = true;
                            // std::cout << "u: " << u << " dist: " << dist[u] << ", v: " << v << " dist: " << dist[v] << std::endl;
                        }
                    }
                }
                if(!relaxed) { break; }
            }
            
            // Check for negative cycle
            for (size_t u = 0; u < n; ++u) {
                for (size_t v = 0; v < n; ++v) {
                    if (g.adj_matrix[u][v] != 0 && dist[u] != INT_MAX && dist[u] + g.adj_matrix[u][v] < dist[v]) {
                        // Negative cycle found
                        std::vector<int> cand_cycle;
                        int curr = u;
                        while (!visited[(size_t)curr]) {
                            cand_cycle.push_back(curr);
                            visited[(size_t)curr] = true;
                            curr = parent[(size_t)curr];
                        }
                        cand_cycle.push_back(curr);
                        std::vector<int> cycle;
                        if(v != (size_t)curr){  // means we got into a different negative cycle
                            cycle.push_back(curr);
                            int curr_2 = parent[(size_t)curr];
                            while(curr_2 != curr){
                                cycle.push_back(curr_2);
                                curr_2 = parent[(size_t)curr_2];
                            }
                            cycle.push_back(curr);
                        }
                        else{
                            cycle = cand_cycle;
                        }
                        std::reverse(cycle.begin(), cycle.end());
                        std::string cyclePath = std::to_string(cycle[0]);
                        for (size_t i = 1; i < cycle.size(); ++i) {
                            cyclePath += "->" + std::to_string(cycle[i]);
                        }
                        return cyclePath;
                    }
                }
            }

            return "No negative cycle"; // No negative cycle
        }

    }  // namespace algorithms
}  // namespace ariel
