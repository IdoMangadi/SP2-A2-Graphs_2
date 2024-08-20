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
#include <stack>
#include "Algorithms.hpp"

#define INT_MAX numeric_limits<int>::max()

using namespace std;

namespace ariel{
    
    namespace Algorithms{

        // ------------------------------------------------------------------------------------------------------------------UTILITIES--------------------
        enum Color { WHITE, GREY, BLACK };
        /**
         * A simple implementation of DFS:
        */ 
        void dfs(Graph &g, size_t v, vector<int> &visited){

            visited[v] = 1;  // marking the vertix as visited
            for(size_t i=0; i<g.size(); i++){ // going over the neighbours and if not visited, operating dfs on them
                if(g.getGraph()[v][i] != 0 && visited[i] == 0) {
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
                    if(g.getGraph()[i][j] != g.getGraph()[j][i]){ 
                        return true;
                    }
                }
            }
            return false;
        }
        /**
         * utility function to fill the stack with the vertices in order of their finish time
         */
        void fillOrder(const Graph &g, size_t v, vector<int> &visited, stack<size_t> &Stack) {
            visited[v] = 1;
            for(size_t i = 0; i < g.size(); i++) {
                if(g.getGraph()[v][i] != 0 && !visited[i]) {
                    fillOrder(g, i, visited, Stack);
                }
            }
            Stack.push(v);
        }
        /**
         * utility function to create a transposed graph and return it
         */
        Graph getTranspose(const Graph &g) {
            size_t n = g.size();
            Graph gT;
            vector <vector<int>> transposeMatrix(g.size(), vector<int>(g.size(), 0));  // creating a matrix with the same size as the original matrix
            for(size_t i = 0; i < n; i++) {
                for(size_t j = 0; j < n; j++) {
                    transposeMatrix[j][i] = g.getGraph()[i][j];  // transposing the matrix
                }
            }
            gT.loadGraph(transposeMatrix);  // loading the transposed matrix into the graph
            return gT;
        }
        /**
        * @brief Checks if a directed graph is strongly connected.
        * 
        * This function uses Kosaraju's algorithm to check if the graph is strongly connected.
        * It performs a DFS to fill a stack with vertices in the order of their finish time.
        * Then, it transposes the graph and performs another DFS starting from the vertex
        * at the top of the stack. If all vertices are visited in this second DFS, the graph
        * is strongly connected.
         */
        int isStronglyConnected(Graph &g) {
            size_t n = g.size();
            vector<int> visited(n, 0);
            stack<size_t> Stack;  // creating a stack to store the vertices in order of their finish time

            for(size_t i = 0; i < n; i++) {
                if(!visited[i]) {
                    fillOrder(g, i, visited, Stack);
                }
            }

            Graph gT = getTranspose(g);
            fill(visited.begin(), visited.end(), 0);

            size_t v = Stack.top();
            Stack.pop();
            dfs(gT, v, visited);

            for(int i : visited) {
                if(i == 0) {
                    return 0;
                }
            }

            return 1;
        }

        /**
         * A simple util function to make relaxation |V|-1 times
         * params: dist - the distances vector, parent - the parent vector, g - the graph
         */
        void relaxNminus1(Graph &g, vector<int> &dist, vector<int> &parent){
            size_t n = g.size();
            for (size_t i = 0; i < n - 1; ++i) {
                bool relaxed  = false;
                for (size_t u = 0; u < n; ++u) {
                    for (size_t v = 0; v < n; ++v) {
                        if (g.getGraph()[u][v] != 0 && dist[u] != INT_MAX && dist[u] + g.getGraph()[u][v] < dist[v]) {
                            dist[v] = dist[u] + g.getGraph()[u][v];
                            parent[v] = u;
                            relaxed = true;
                        }
                    }
                }
                if(!relaxed) { break; }
            }
        }

        // ------------------------------------------------------------------------------------------------------------------IS CONNECTED------------------

        int isConnected(Graph &g){
            size_t n = g.size();
            if(n == 0) return 1;  // an empty graph is considered as strong connected

            // checking if it is a directed or undirected graph:
            bool directed = isDirected(g);
            
            if(directed){
                return isStronglyConnected(g);
            }
            else{  // the graph is undirected:
                vector<int> visited(n, 0);  // creating a vector to mark the visited vertices
                dfs(g, 0, visited);  // operating dfs one time on the graph
                for(int v : visited){  // going all over the vertices
                    if(v == 0) return 0; // means we didnt reach to one of the vertices
                }
            }

            return 1;  // means all validations went ok, the graph is strong connected. 
        }

        // -----------------------------------------------------------------------------------------------------------------SHORTEST PATH-----------------

        string shortestPath(Graph &g, size_t src, size_t dst){
            size_t n = g.getGraph().size();
            if( n == 0 || src > n-1 || dst > n-1) return "-1";  // validation check

            vector<int> dist(n, numeric_limits<int>::max()); // Initialize distances to infinity
            vector<int> parent(n, -1); // To store the parent of each vertex in the shortest path (init with -1)
            vector<int> path; // to store the shortest path from src to dst

            dist[src] = 0; // init the distance from src to itself to 0

            relaxNminus1(g, dist, parent);  // Relax edges |V|-1 times

            // Check for negative cycles (one last relaxing)
            for (size_t u = 0; u < n; ++u) {
                for (size_t v = 0; v < n; ++v) {
                    if (g.getGraph()[u][v] != 0 && dist[u] != numeric_limits<int>::max() && dist[u] + g.getGraph()[u][v] < dist[v]) {
                        // Negative cycle found
                        // cout << "Graph contains negative cycle" << endl;
                        return "-1";
                    }
                }
            }
            
            // Check for empty path:
            if(parent[dst] == -1){
                return "-1";
            }

            // Reconstruct the shortest path:
            for (int v = dst; v != -1; v = parent[(unsigned int)v]) {
                path.push_back(v);
            }
            reverse(path.begin(), path.end());  // reversing the path
            // converting to string:
            string result = "";
            for(size_t i=0; i<path.size(); i++){
                result += to_string(path[i]);
                if(i != path.size()-1){
                    result += "->";
                }
            }

            return result;
        }
        
        // ---------------------------------------------------------------------------------------------------------------------CYCLES-------------------

        // Simple implementation of dfs regarding cycles finding using the DAG theorem.
        // directed graphs version:
        bool hasCycleUtil_directed(Graph &g, size_t u, vector<Color> &color, vector<int> &parent, vector<int> &cycleVertices) {
            color[u] = GREY; // Mark the current vertex as visited but not finished

            for (size_t v = 0; v < g.getGraph()[u].size(); ++v) {  // going over the neighbours of u:
                if (g.getGraph()[u][v] != 0) {
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
                        reverse(cycleVertices.begin(), cycleVertices.end());
                        return true;
                    }
                }
            }

            color[u] = BLACK; // Mark the current vertex as finished
            return false;
        }
        // undirected graphs version:
        bool hasCycleUtil_undirected(Graph &g, size_t u, vector<Color> &color, vector<int> &parent, vector<int> &cycleVertices) {
            color[u] = GREY; // Mark the current vertex as visited but not finished

            for (size_t v = 0; v < g.getGraph()[u].size(); ++v) {  // going over the neighbours:
                if (g.getGraph()[u][v] != 0) {
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
                        reverse(cycleVertices.begin(), cycleVertices.end());
                        return true;
                    }
                }
            }

            color[u] = BLACK; // Mark the current vertex as finished
            return false;
        }

        bool isContainsCycle(Graph &g) {
            size_t n = g.getGraph().size();
            vector<Color> color(n, WHITE); // Initialize all vertices as not visited
            vector<int> parent(n, -1); // To store the parent of each vertex in the DFS tree (init with -1)
            vector<int> cycleVertices;  // to store the cycle if founded

            if(isDirected(g)){
                // Perform DFS from each vertex
                for (size_t i = 0; i < n; ++i) {
                    if (color[i] == WHITE && hasCycleUtil_directed(g, i, color, parent, cycleVertices)) {
                        // Construct the cycle string
                        string cycle = "The cycle is: ";
                        for (size_t ver = 0; ver < cycleVertices.size(); ver++) {
                            cycle += to_string(cycleVertices[ver]);
                            if(ver < cycleVertices.size()-1){
                                cycle += "->";
                            }
                        }
                        cout << cycle << endl;
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
                        string cycle = "The cycle is: ";
                        for (size_t ver = 0; ver < cycleVertices.size(); ver++) {
                            cycle += to_string(cycleVertices[ver]);
                            if(ver < cycleVertices.size()-1){
                                cycle += "->";
                            }
                        }
                        cout << cycle << endl;
                        return true;
                    }
                }
                return false; // No cycle found
            }
        }

        // ---------------------------------------------------------------------------------------------------------------------BIAPARTIT----------------
        
        string isBipartite(Graph &g) {

            size_t n = g.getGraph().size();
            if(n == 0) return "0";

            vector<int> colors(n, 0); // 0: uncolored, 1: group 1, 2: group 2
            size_t counter_2 = 0;  // to count how many vertices are colored in 2

            for (size_t i = 0; i < n; ++i) {  // going over all the vertices
                if (colors[i] != 0) continue;  // if the vertex is already colored, continue

                queue<size_t> q;  // creating a queue to operate bfs
                q.push(i);
                colors[i] = 1;

                while (!q.empty()) {
                    size_t node = q.front();
                    q.pop();

                    for (size_t neighbor = 0; neighbor < n; ++neighbor) {
                        if (g.getGraph()[node][neighbor] != 0) {  // means there is an edge between them
                            if (colors[neighbor] == 0) {
                                colors[neighbor] = (colors[node] == 1) ? 2 : 1;  // coloring the neighbor with the opposite color of the node
                                if(colors[neighbor] == 2) counter_2++;
                                q.push(neighbor);
                            } else if (colors[neighbor] == colors[node]) {
                                return "0"; // Not bipartite
                            }
                        }
                    }
                }
            }

            string group1 = "";
            string group2 = "";
            size_t counter_1 = n - counter_2;  // counter_1/2 represents how many 1 colored verteces there are left to add.

            for (size_t i = 0; i < n; ++i) {
                if (colors[i] == 1){
                    group1 += to_string(i);
                    if(counter_1 != 1) group1 += ", ";
                    counter_1--;  
                }
                else {
                    group2 += to_string(i);
                    if(counter_2 != 1) group2 += ", ";
                    counter_2--;
                }
            }

            return "The graph is bipartite: A={" + group1 + "}, B={" + group2 + "}";
        }


        // ------------------------------------------------------------------------------------------------------------------NEGATIVE CYCLES-------------

        string negativeCycle(Graph& g) {

            if(isDirected(g) == false){
                return "-1";
            }

            size_t n = g.size();
            if( n == 0) return "Empty graph";

            vector<int> dist(n, INT_MAX);
            vector<int> parent(n, -1); // To track the path
            vector<bool> visited(n, false);

            // Assume vertex 0 as the source
            dist[0] = 0;

            relaxNminus1(g, dist, parent);  // Relax edges |V|-1 times
            
            // Check for negative cycle
            for (size_t u = 0; u < n; ++u) {
                for (size_t v = 0; v < n; ++v) {
                    if (g.getGraph()[u][v] != 0 && dist[u] != INT_MAX && dist[u] + g.getGraph()[u][v] < dist[v]) {  // Relaxation happened
                        // Negative cycle found
                        vector<int> cand_cycle;
                        int curr = u;
                        while (!visited[(size_t)curr]) {  // If we reach a visited vertex, we have found the cycle
                            cand_cycle.push_back(curr);  // Add the vertex to the cycle
                            visited[(size_t)curr] = true;  // Mark the vertex as visited
                            curr = parent[(size_t)curr];  // Move to the parent
                        }
                        cand_cycle.push_back(curr);
                        // NOTE: it is possible that the cand_cycle contains another negative cycle.
                        //       so that the parent of the first vertex in the cycle is not the last vertex in the inner cycle.
                        vector<int> cycle;
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
                        reverse(cycle.begin(), cycle.end());
                        string cyclePath = to_string(cycle[0]);
                        for (size_t i = 1; i < cycle.size(); ++i) {
                            cyclePath += "->" + to_string(cycle[i]);
                        }
                        return cyclePath;
                    }
                }
            }

            return "No negative cycle"; // No negative cycle
        }

    }  // namespace algorithms
}  // namespace ariel
