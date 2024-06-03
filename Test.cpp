#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <sstream>

using namespace std;

TEST_CASE("Test 2 graphs addition (g1+g2)")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(graph2);

    ariel::Graph g3 = g1 + g2;

    ariel::Graph g4;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    g4.loadGraph(expectedGraph);

    CHECK(g3.getGraph() == g4.getGraph());  // g3 should be equal to g4

    ariel::Graph g5;
    vector<vector<int>> graph5 = {
        {0, 2, 3},
        {2, 0, 1},
        {3, 1, 0}};
    g5.loadGraph(graph5);

    ariel::Graph g6 = g1 + g5;

    ariel::Graph g7;
    vector<vector<int>> expectedGraph2 = {
        {0, 3, 3},
        {3, 0, 2},
        {3, 2, 0}};
    g7.loadGraph(expectedGraph2);

    CHECK(g6.getGraph() == g7.getGraph());  // g6 should be equal to g7

    // invalid operation: g1 and g2 have different dimensions
    ariel::Graph g8;
    vector<vector<int>> graph6 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g8.loadGraph(graph6);
    CHECK_THROWS(g1 + g8);  // invalid operation

    // adding 2 graphs of size 0:
    ariel::Graph g9;
    ariel::Graph g10;
    ariel::Graph g11;
    CHECK_THROWS(g11 = g9 + g10);  // invalid operation (both graphs are empty)
}

TEST_CASE("Test appending (g1+=g2)")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);

    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);

    g1 += g2;

    ariel::Graph g3;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    g3.loadGraph(expectedGraph);

    CHECK(g1.getGraph() == g3.getGraph());  // g1 should be equal to g3

    // Additional tests
    ariel::Graph g4;
    vector<vector<int>> graph2 = {
        {0, 2, 3},
        {2, 0, 1},
        {3, 1, 0}};
    g4.loadGraph(graph2);

    g1 += g4;

    ariel::Graph g5;
    vector<vector<int>> expectedGraph2 = {
        {0, 4, 4},
        {4, 0, 4},
        {4, 4, 0}};
    g5.loadGraph(expectedGraph2);

    CHECK(g1.getGraph() == g5.getGraph());

    // invalid operation: g1 and g2 have different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    // g1 and g6 have different dimensions
    CHECK_THROWS(g1 += g6);  // invalid operation
}

TEST_CASE("Test 1 graph unary addition (+g1)")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);

    ariel::Graph g2 = +g1;

    CHECK(g1.getGraph() == g2.getGraph());

    // Additional tests
    ariel::Graph g3;
    vector<vector<int>> graph2 = {
        {0, 2, 3},
        {2, 0, 1},
        {3, 1, 0}};
    g3.loadGraph(graph2);

    ariel::Graph g4 = +g3;

    CHECK(g3.getGraph() == g4.getGraph());
}

TEST_CASE("Test 2 graph subtraction (g1-g2)")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 3, 0},
        {3, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);

    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);

    ariel::Graph g3 = g1 - g2;

    ariel::Graph g4;
    vector<vector<int>> expectedGraph = {
        {0, 2, -1},
        {2, 0, -1},
        {-1, -1, 0}};
    g4.loadGraph(expectedGraph);

    CHECK(g3.getGraph() == g4.getGraph());

    // Additional tests
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 4, 3},
        {4, 0, 2},
        {3, 2, 0}};
    g5.loadGraph(graph2);

    ariel::Graph g6 = g1 - g5;

    ariel::Graph g7;
    vector<vector<int>> expectedGraph2 = {
        {0, -1, -3},
        {-1, 0, -1},
        {-3, -1, 0}};
    g7.loadGraph(expectedGraph2);

    CHECK(g6.getGraph() == g7.getGraph());

    // invalid operation: g1 and g2 have different dimensions
    ariel::Graph g8;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g8.loadGraph(graph3);
    // g1 and g8 have different dimensions
    CHECK_THROWS(g1 - g8);  // invalid operation
}

TEST_CASE("Test subtraction (g1-=g2)")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 3, 0},
        {3, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);

    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);

    g1 -= g2;

    ariel::Graph g3;
    vector<vector<int>> expectedGraph = {
        {0, 2, -1},
        {2, 0, -1},
        {-1, -1, 0}};
    g3.loadGraph(expectedGraph);

    CHECK(g1.getGraph() == g3.getGraph());

    // Additional tests
    ariel::Graph g4;
    vector<vector<int>> graph2 = {
        {0, 4, 3},
        {4, 0, 2},
        {3, 2, 0}};
    g4.loadGraph(graph2);

    g1 -= g4;

    ariel::Graph g5;
    vector<vector<int>> expectedGraph2 = {
        {0, -2, -4},
        {-2, 0, -3},
        {-4, -3, 0}};
    g5.loadGraph(expectedGraph2);

    CHECK(g1.getGraph() == g5.getGraph());

    // invalid operation: g1 and g2 have different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    // g1 and g6 have different dimensions
    CHECK_THROWS(g1 -= g6);  // invalid operation
}

TEST_CASE("Test 1 graph unary subtraction (-g1)") {
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 2, -1},
        {2, 0, 3},
        {-1, 3, 0}};
    g1.loadGraph(graph);

    ariel::Graph g2 = -g1;

    ariel::Graph g3;
    vector<vector<int>> expectedGraph = {
        {0, -2, 1},
        {-2, 0, -3},
        {1, -3, 0}};
    g3.loadGraph(expectedGraph);

    CHECK(g2.getGraph() == g3.getGraph());

    // Additional tests
    ariel::Graph g4;
    vector<vector<int>> graph2 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g4.loadGraph(graph2);

    ariel::Graph g5 = -g4;

    ariel::Graph g6;
    vector<vector<int>> expectedGraph2 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g6.loadGraph(expectedGraph2);
    
    CHECK(g5.getGraph() == g6.getGraph());
}


TEST_CASE("Test < comparison (g1<g2)") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 < g2);  // g1 is strictly contained within g2

    ariel::Graph g3;
    vector<vector<int>> graph3 = {
        {0, 1},
        {1, 0}};
    g3.loadGraph(graph3);

    CHECK(g3 < g1);  // g3 has fewer edges and is smaller in size than g1

    ariel::Graph g4;
    vector<vector<int>> graph4 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g4.loadGraph(graph4);

    CHECK(!(g1 < g4));  // g1 is equal to g4, so g1 is not less than g4

    ariel::Graph g5;
    vector<vector<int>> graph5 = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}};
    g5.loadGraph(graph5);

    CHECK(g1 < g5);  // g1 has fewer edges and is smaller in size than g5
}


TEST_CASE("Test <= comparison (g1<=g2)") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 <= g2);  // g1 is strictly contained within g2

    ariel::Graph g3;
    vector<vector<int>> graph3 = {
        {0, 1},
        {1, 0}};
    g3.loadGraph(graph3);

    CHECK(g3 <= g1);  // g3 has fewer edges and is smaller in size than g1

    ariel::Graph g4;
    vector<vector<int>> graph4 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g4.loadGraph(graph4);

    CHECK(g1 <= g4);  // g1 is equal to g4

    ariel::Graph g5;
    vector<vector<int>> graph5 = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}};
    g5.loadGraph(graph5);

    CHECK(g1 <= g5);  // g1 has fewer edges and is smaller in size than g5
}


TEST_CASE("Test > comparison (g1>g2)") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g2.loadGraph(graph2);

    CHECK(g2 > g1);  // g2 has more edges than g1

    ariel::Graph g3;
    vector<vector<int>> graph3 = {
        {0, 1},
        {1, 0}};
    g3.loadGraph(graph3);

    CHECK(g1 > g3);  // g1 has more edges and a larger size than g3

    ariel::Graph g4;
    vector<vector<int>> graph4 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g4.loadGraph(graph4);

    CHECK_FALSE(g1 > g4);  // g1 is equal to g4, so the comparison should return false

    ariel::Graph g5;
    vector<vector<int>> graph5 = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}};
    g5.loadGraph(graph5);

    CHECK(g5 > g1);  // g5 has more edges and a larger size than g1
}


TEST_CASE("Test >= comparison (g1>=g2)") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g2.loadGraph(graph2);

    CHECK(g2 >= g1);  // g2 has more edges than g1

    ariel::Graph g3;
    vector<vector<int>> graph3 = {
        {0, 1},
        {1, 0}};
    g3.loadGraph(graph3);

    CHECK(g1 >= g3);  // g1 has more edges and a larger size than g3

    ariel::Graph g4;
    vector<vector<int>> graph4 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g4.loadGraph(graph4);

    CHECK(g1 >= g4);  // g1 is equal to g4, so the comparison should return true

    ariel::Graph g5;
    vector<vector<int>> graph5 = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}};
    g5.loadGraph(graph5);

    CHECK(g5 >= g1);  // g5 has more edges and a larger size than g1
}


TEST_CASE("Test == comparison (g1==g2)") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 == g2);  // g1 and g2 are identical

    ariel::Graph g3;
    vector<vector<int>> graph3 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g3.loadGraph(graph3);

    CHECK_FALSE(g1 == g3);  // g1 and g3 are not identical

    ariel::Graph g4;
    vector<vector<int>> graph4 = {
        {0, 1},
        {1, 0}};
    g4.loadGraph(graph4);

    CHECK_FALSE(g1 == g4);  // g1 and g4 have different sizes

    // in this test:
    // no graph is bigger then the other.
    // they are not identical as well.
    // but still equals.
    ariel::Graph g5;
    vector<vector<int>> graph5 = {
        {0, 1, 1},
        {1, 0, 1},
        {0, 1, 0}};
    g5.loadGraph(graph5);

    ariel::Graph g6;
    vector<vector<int>> graph6 = {
        {0, 1, 0},
        {1, 0, 1},
        {1, 1, 0}};
    g6.loadGraph(graph6);

    CHECK(g5 == g6);
}


TEST_CASE("Test != comparison (g1!=g2)") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g2.loadGraph(graph2);

    CHECK_FALSE(g1 != g2);  // g1 and g2 are identical

    ariel::Graph g3;
    vector<vector<int>> graph3 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g3.loadGraph(graph3);

    CHECK(g1 != g3);  // g1 and g3 are not equal

    ariel::Graph g4;
    vector<vector<int>> graph4 = {
        {0, 1},
        {1, 0}};
    g4.loadGraph(graph4);

    CHECK(g1 != g4);  // g1 and g4 have different sizes
}


TEST_CASE("Test incrementing (g1++ and ++g1)") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    // Expected graph after incrementing (incrementing adds 1 to all existing edges)
    vector<vector<int>> expectedGraph = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}};

    // Test postfix increment
    ariel::Graph g2 = g1++;
    CHECK(g1.getGraph() == expectedGraph);
    CHECK(g2.getGraph() == graph1);  // g2 should be the state before incrementing

    // Reset g1 to original state for next test
    g1.loadGraph(graph1);

    // Test prefix increment
    ariel::Graph g3 = ++g1;
    CHECK(g1.getGraph() == expectedGraph);
    CHECK(g3.getGraph() == expectedGraph);  // g3 should be the state after incrementing
}


TEST_CASE("Test decrementing (g1-- and --g1)") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 2, 1},
        {2, 0, 2},
        {1, 2, 0}};
    g1.loadGraph(graph1);

    // Expected graph after decrementing (decrementing subtracts 1 from all existing edges)
    vector<vector<int>> expectedGraph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};

    // Test postfix decrement
    ariel::Graph g2 = g1--;
    CHECK(g1.getGraph() == expectedGraph);
    CHECK(g2.getGraph() == graph1);  // g2 should be the state before decrementing

    // Reset g1 to original state for next test
    g1.loadGraph(graph1);

    // Test prefix decrement
    ariel::Graph g3 = --g1;
    CHECK(g1.getGraph() == expectedGraph);
    CHECK(g3.getGraph() == expectedGraph);  // g3 should be the state after decrementing
}


TEST_CASE("Test multiplication by int (g1 *= value)") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 2, 3},
        {4, 0, 6},
        {7, 8, 0}};
    g1.loadGraph(graph1);

    int value = 2;
    vector<vector<int>> expectedGraph = {
        {0, 4, 6},
        {8, 0, 12},
        {14, 16, 0}};

    g1 *= value;
    CHECK(g1.getGraph() == expectedGraph);

    // test multiplication by 0
    value = 0;
    vector<vector<int>> expectedGraph2 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g1 *= value;
    CHECK(g1.getGraph() == expectedGraph2);
}


TEST_CASE("Test division by int (g1 /= value)") {
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 4, 6},
        {8, 0, 12},
        {14, 16, 0}};
    g1.loadGraph(graph1);

    int value = 2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 3},
        {4, 0, 6},
        {7, 8, 0}};

    g1 /= value;
    CHECK(g1.getGraph() == expectedGraph);

    value = 0;
    CHECK_THROWS(g1/=value);
}


TEST_CASE("Test 2 graph multiplication")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 0},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(graph2);

    CHECK_THROWS(g1 * g2);  // invalid operation graph with self loop created

    ariel::Graph g3;
    vector<vector<int>> graph3 = {
        {0, 0, 3},
        {0, 0, 0},
        {1, 1, 0}};
    g3.loadGraph(graph3);

    vector<vector<int>> graph_g1_g3 = {
        {0, 0, 0},
        {0, 0, 3},
        {0, 0, 0}};
    ariel::Graph res_g1_g3;
    res_g1_g3.loadGraph(graph_g1_g3);

    ariel::Graph g5 = g1*g3;

    CHECK(g5.getGraph() == res_g1_g3.getGraph());

    ariel::Graph g10, g20;
    vector<vector<int>> graph10 = {
        {0, 2},
        {3, 0}};
    vector<vector<int>> graph20 = {
        {0, 0},
        {0, 0}};
    g10.loadGraph(graph10);
    g20.loadGraph(graph20);

    // Expected result of matrix multiplication of graph1 and graph2
    vector<vector<int>> expectedGraph2 = {
        {0, 0},
        {0, 0}};

    ariel::Graph g30 = g10 * g20;
    CHECK(g30.getGraph() == expectedGraph2);

    // invalid operation: g1 and g10 have different dimensions
    CHECK_THROWS(g1 * g10);  // invalid operation


}


TEST_CASE("Invalid operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);

    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1}};
    
    CHECK_THROWS(g2.loadGraph(weightedGraph));

    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g5 * g1);
    CHECK_THROWS(g1 * g2);

    // Addition of two graphs with different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    CHECK_THROWS(g1 + g6);
}