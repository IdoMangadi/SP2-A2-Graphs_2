// ID: 315310250
// EMAIL: IDOIZHAR.Mangadi@msmail.ariel.ac.il
// GMAIL: idomangadi@gmail.com

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <ostream>
#include <vector>
#include <cstddef>

namespace ariel{
    class Graph{
        private:
            std::vector<std::vector<int>> adj_matrix;
        public:
            
            Graph(){}
            /**
             * @brief Retrieve a constant reference to the adjacency matrix of the graph.
             *
             * This function returns a constant reference to the adjacency matrix of the graph.
             * It allows external access to the graph's internal adjacency matrix for reading purposes only.
             * The returned reference is constant, meaning that it cannot be used to modify the internal state of the graph.
             *
             * @return A constant reference to the adjacency matrix of the graph.
            */
            const std::vector<std::vector<int>>& getGraph() const {
                return adj_matrix;
            }
            // methods:
            /**
             * this function gets a matrix represented in 2d vector and copy it into the instance graph.
            */
            void loadGraph(const std::vector<std::vector<int>> &input_matrix);
            /**
             * this function print a brief of the graph.
            */
            void printGraph();
            /**
             * this function returns the size of the square graph.
            */
            size_t size();
            /**
             * Overloading the output operator
            */
            friend std::ostream& operator<<(std::ostream& os, const Graph& g);
            /**
             * Overloading the addition operators
            */
            friend Graph operator+(const Graph& g0, const Graph& g1);
            Graph& operator+=(const Graph& g1);
            Graph operator+() const;
            /**
             * Overloading the subtruction operators
            */
            friend Graph operator-(const Graph& g0, const Graph& g1);
            Graph& operator-=(const Graph& g1);
            Graph operator-() const;
            /**
             * comparison operators:
             * Graph G2 is larger than graph G1 if graph G1 is strictly contained in graph G2.
             *  If no graph is strictly contained in the other and the graphs are not equal,
             *  then graph G2 is larger than graph G1 if the number of edges in G2 is greater than the number of edges in G1.
             *  If, nevertheless, the number of edges is the same,
             *  then graph G2 is larger than graph G1 if the representing matrix of G2 has a higher order than that of G1.
            */
            friend bool operator<(const Graph& g1, const Graph& g2);
            friend bool operator>(const Graph& g1, const Graph& g2);
            friend bool operator==(const Graph& g1, const Graph& g2);
            friend bool operator!=(const Graph& g1, const Graph& g2);
            friend bool operator<=(const Graph& g1, const Graph& g2);
            friend bool operator>=(const Graph& g1, const Graph& g2);

            /**
             * incrementing and decrement multiplication and division by balue:
            */
            /**
             * incrementing every existing edge by one (prefix).
            */
            Graph& operator++();
            /**
             * incrementing every existing edge by one (postfix).
            */
            Graph operator++(int);
            /**
             * decrementing every existing edge by one (prefix)..
            */
            Graph& operator--();
            /**
             * decrementing every existing edge by one (postfix).
            */
            Graph operator--(int);
            /**
             * multypling every value of the graph by given int.
            */
            Graph& operator*=(int val);
            /**
             * dividing every value of the graph by given int.
            */
            Graph& operator/=(int val);

            /**
             * multiplication of two graphs.
            */
            friend Graph operator*(const Graph& g0, const Graph& g1);
    };
}

#endif // GRAPH_HPP
