// ID: 315310250
// EMAIL: IDOIZHAR.Mangadi@msmail.ariel.ac.il
// GMAIL: idomangadi@gmail.com

#include "Graph.hpp"

namespace ariel{
        
        void Graph::loadGraph(const std::vector<std::vector<int>> &input_matrix){
            
            if(input_matrix.size() == 0) throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
            if(input_matrix[0].size() == 0) throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
            
            size_t rows_number = input_matrix.size();
            for(const auto &col : input_matrix){ // going over all the rows
                if(col.size() != rows_number){
                    throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
                }
            }
            
            this->adj_matrix.clear();
            // loop over the rows:
            for(const auto &row : input_matrix){
                std::vector<int> new_row;  // creating a new row
                // loop over the cols:
                for(int value : row){
                    new_row.push_back(value);  // pushing into the new row
                }
                this->adj_matrix.push_back(new_row);  // pushing the new row into the adj matrix
            }
        }
    
        void Graph::printGraph(){
            size_t n = this->adj_matrix[0].size();
            size_t edges_counter = 0;
            for(size_t i=0; i<n; i++){
                for(size_t j=0; j<n; j++){
                    if(this->adj_matrix[i][j] != 0){
                        edges_counter++;
                    }
                }
            }
            printf("In this graph: %zu vertices and %zu edges.\n", n, edges_counter);
        }

        size_t Graph::size(){
            return this->adj_matrix[0].size();
        }

        std::ostream& operator<<(std::ostream& os, const Graph& graph){
            size_t graph_size = graph.adj_matrix.size();
            for(const auto& row : graph.adj_matrix){
                os << "[";
                for(size_t i=0; i<graph_size-1; i++){
                    os << row[i] << " ";
                }
                os << row[graph_size-1] << "]" << std::endl;  // adding the last value of the row
            }
            return os;
        }

        Graph Graph::operator+(const Graph& g1) const{

            size_t graph_size = this->adj_matrix.size();
            if(graph_size != g1.adj_matrix.size()){  // sizes validation
                throw std::invalid_argument("Cannot add graphs of different sizes.");
            }

            Graph res;
            std::vector<std::vector<int>> matrix;

            for(size_t i=0; i<graph_size; i++){
                std::vector<int> row;
                for(size_t j=0; j<graph_size; j++){
                    row.push_back(this->adj_matrix[i][j] + g1.adj_matrix[i][j]);
                }
                matrix.push_back(row);
            }

            res.loadGraph(matrix);
            return res;
        }

        Graph& Graph::operator+=(const Graph& g2){

            size_t graph_size = this->adj_matrix.size();
            if(graph_size != g2.adj_matrix.size()){  // sizes validation
                throw std::invalid_argument("Cannot add graphs of different sizes.");
            }
            for(size_t i=0; i<graph_size; i++){
                for(size_t j=0; j<graph_size; j++){
                    this->adj_matrix[i][j] += g2.adj_matrix[i][j];
                }
            }

            return *this;
        }

        Graph Graph::operator+() const{
            return *this; // returning a new copy of the graph.
        }

        Graph Graph::operator-(const Graph& g1) const{

            size_t graph_size = this->adj_matrix.size();
            if(graph_size != g1.adj_matrix.size()){  // sizes validation
                throw std::invalid_argument("Cannot substruct graphs of different sizes.");
            }

            Graph res;
            std::vector<std::vector<int>> matrix;

            for(size_t i=0; i<graph_size; i++){
                std::vector<int> row;
                for(size_t j=0; j<graph_size; j++){
                    row.push_back(this->adj_matrix[i][j] - g1.adj_matrix[i][j]);
                }
                matrix.push_back(row);
            }

            res.loadGraph(matrix);
            return res;
        }

        Graph& Graph::operator-=(const Graph& g2){

            size_t graph_size = this->adj_matrix.size();
            if(graph_size != g2.adj_matrix.size()){  // sizes validation
                throw std::invalid_argument("Cannot substruct graphs of different sizes.");
            }
            for(size_t i=0; i<graph_size; i++){
                for(size_t j=0; j<graph_size; j++){
                    this->adj_matrix[i][j] -= g2.adj_matrix[i][j];
                }
            }

            return *this;
        }

        Graph Graph::operator-() const {

            Graph result = *this; // Create a copy of the current object
            size_t graph_size = result.adj_matrix.size();
            
            // Negate all elements of the adjacency matrix
            for(size_t i = 0; i < graph_size; i++) {
                for(size_t j = 0; j < graph_size; j++) {
                    result.adj_matrix[i][j] = -result.adj_matrix[i][j];
                }
            }
            return result; // Return the negated Graph object
        }

        bool operator<(const Graph& g1, const Graph& g2) {

            // check if this graph is contained in g2:
            size_t size_this = g1.adj_matrix.size();
            size_t size_g2 = g2.adj_matrix.size();
            bool check_contained = false;
            // if this.size > g2.size so obviously this is not contained in g2. else:
            if(size_this <= size_g2){
                check_contained = true;
                for (size_t i = 0; i < size_this; ++i) {
                    for (size_t j = 0; j < size_this; ++j) {
                        if (g1.adj_matrix[i][j] != 0 && g1.adj_matrix[i][j] != g2.adj_matrix[i][j]) {  // contained condition
                            check_contained = false;  // means there is an edge in this that doesnt exist in g2
                        }
                    }
                }
                if(size_this == size_g2 && check_contained == true){  // if the sizes are equal and all components in this exists in g2,
                    check_contained = false;                          // so we need to check for strict contained.
                    for (size_t i = 0; i < size_this; ++i) {          
                        for (size_t j = 0; j < size_this; ++j) {
                            if(g2.adj_matrix[i][j] != 0 && g1.adj_matrix[i][j] == 0){
                                check_contained = true;  // means we found component that exist in g2 but not in this.
                            }
                        }
                    }
                }
            }
            if(check_contained == true) return true;  // first condition accepted.

            // check number of edges:
            size_t edges_g2 = 0;
            size_t edges_this = 0;
            if(size_this == size_g2){  // equal sizes:
                for (size_t i = 0; i < size_g2; ++i) {
                    for (size_t j = 0; j < size_g2; ++j) {
                        if(g1.adj_matrix[i][j] != 0) edges_this++;  //counting this edges
                        if(g2.adj_matrix[i][j] != 0) edges_g2++;  // counting g2 edges
                    }
                }
                if(edges_this < edges_g2) return true;
            }
            else{  // not equal sizes:
                for (size_t i = 0; i < size_this; ++i) {
                    for (size_t j = 0; j < size_this; ++j) {
                        if(g1.adj_matrix[i][j] != 0) edges_this++;  //counting this edges
                    }
                }
                for (size_t i = 0; i < size_g2; ++i) {
                    for (size_t j = 0; j < size_g2; ++j) {
                        if(g2.adj_matrix[i][j] != 0) edges_g2++;  // counting g2 edges
                    }
                }
                if(edges_this < edges_g2) return true;
            }

            return size_this < size_g2;
        }

        bool operator>(const Graph& g1, const Graph& g2) {
            // Check if g2 is strictly contained in this graph or if g2 is not larger than this graph
            return g2 < g1;
        }

        bool operator==(const Graph& g1, const Graph& g2) {
            bool equals = true;
            // Check if the graphs are of the same size and contain the same edges
            if (g1.adj_matrix.size() != g2.adj_matrix.size()) {
                equals = false;
            }
            else{
                for (size_t i = 0; i < g1.adj_matrix.size(); ++i) {
                    for (size_t j = 0; j < g1.adj_matrix[i].size(); ++j) {
                        if (g1.adj_matrix[i][j] != g2.adj_matrix[i][j]) {
                            equals = false;
                        }
                    }
                }
            }
            // cheack if one is bigger than the other:
            if(g1 < g2 || g1 > g2) equals = false;

            return equals;
        }

        bool operator!=(const Graph& g1, const Graph& g2) {
            return !(g1 == g2);
        }

        bool operator<=(const Graph& g1, const Graph& g2) {
            return g1 < g2 || g1 == g2;
        }

        bool operator>=(const Graph& g1, const Graph& g2) {
            return g1 > g2 || g1 == g2;
        }

        /**
         * incrementing ad decrement multiplication and division:
        */
       // Prefix increment
        Graph& Graph::operator++(){
            for (size_t i = 0; i < this->adj_matrix.size(); ++i) {
                for (size_t j = 0; j < this->adj_matrix.size(); ++j) {
                    if (this->adj_matrix[i][j] != 0) {
                        this->adj_matrix[i][j]++;
                    }
                }
            }
            return *this;
        }
        // Postfix increment
        Graph Graph::operator++(int) {
            Graph temp = *this; // Store the current state
            ++(*this);          // Use prefix increment to increment the current object
            return temp;        // Return the stored state (the original value before increment)
        }
        // Prefix decrement
        Graph& Graph::operator--(){
            for (size_t i = 0; i < this->adj_matrix.size(); ++i) {
                for (size_t j = 0; j < this->adj_matrix.size(); ++j) {
                    if (this->adj_matrix[i][j] != 0) {
                        this->adj_matrix[i][j]--;
                    }
                }
            }
            return *this;
        }
        // Postfix decrement
        Graph Graph::operator--(int) {
            Graph temp = *this; // Store the current state
            --(*this);          // Use prefix increment to increment the current object
            return temp;        // Return the stored state (the original value before increment)
        }
        Graph& Graph::operator*=(int val){
            for (size_t i = 0; i < this->adj_matrix.size(); ++i) {
                for (size_t j = 0; j < this->adj_matrix.size(); ++j) {
                        this->adj_matrix[i][j] *= val;
                }
            }
            return *this;
        }
        Graph& Graph::operator/=(int val){
            if(val == 0){
                throw std::runtime_error("Division by zero error");
            }
            for (size_t i = 0; i < this->adj_matrix.size(); ++i) {
                for (size_t j = 0; j < this->adj_matrix.size(); ++j) {
                        this->adj_matrix[i][j] /= val;
                }
            }
            return *this;
        }

        /**
         * multiplication of two graphs:
        */
        Graph Graph::operator*(const Graph& g2) const {

            // Ensure the graphs are of the same size and are square matrices
            size_t size_this = this->adj_matrix.size();
            size_t size_g2 = g2.adj_matrix.size();
            
            if (size_this != size_g2) {
                throw std::invalid_argument("Cannot multiply graphs of different sizes.");
            }
            
            // create and initiate the result graph:
            Graph result;   
            result.adj_matrix.resize(size_this, std::vector<int>(size_this, 0));

            // Matrix multiplication
            for (size_t i = 0; i < size_this; ++i) {
                for (size_t j = 0; j < size_this; ++j) {
                    if (i != j) { // Skip main diagonal
                        for (size_t k = 0; k < size_this; ++k) {
                            if (i != k && k != j) { // Skip elements that would contribute to the main diagonal
                                result.adj_matrix[i][j] += this->adj_matrix[i][k] * g2.adj_matrix[k][j];
                            }
                        }
                    }
                }
            }

            return result;
        }

};
