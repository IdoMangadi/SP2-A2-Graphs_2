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
                throw std::invalid_argument("Cannot add graphs of different sizes.");
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

        Graph& Graph::operator+=(const Graph& g2){

            size_t graph_size = this->adj_matrix.size();
            if(graph_size != g2.adj_matrix.size()){  // sizes validation
                throw std::invalid_argument("Cannot add graphs of different sizes.");
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

};
