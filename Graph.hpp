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
        public:
            std::vector<std::vector<int>> adj_matrix;
            Graph(){}
            // methods:
            /**
             * this function gets a matrix represented in 2d vector and copy it into the instance graph.
            */
            void loadGraph(const std::vector<std::vector<int>> &input_matrix);
            /**
             * this function print all the values of the graph.
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
            Graph operator+(const Graph& g1) const;
            Graph& operator+=(const Graph& g1);
            Graph operator+() const;
            /**
             * Overloading the substruction operators
            */
            Graph operator-(const Graph& g1) const;
            Graph& operator-=(const Graph& g1);
            Graph operator-() const;
    };
}

#endif // GRAPH_HPP
