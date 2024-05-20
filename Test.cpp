#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <sstream>

using namespace std;

TEST_CASE("Test 2 graphs addition (g1+g2)")
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

    ariel::Graph g3 = g1 + g2;

    ariel::Graph g4;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    g4.loadGraph(expectedGraph);
    
    std::ostringstream oss;
    oss << g3;
    string g3_str = oss.str();

    // Clear the ostringstream
    oss.str("");  // Clear the contents
    oss.clear();  // Clear the state flags

    oss << g4;
    string g4_str = oss.str();

    CHECK(g3_str == g4_str);

    // Additional tests
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 2, 3},
        {2, 0, 1},
        {3, 1, 0}};
    g5.loadGraph(graph2);

    ariel::Graph g6 = g1 + g5;

    ariel::Graph g7;
    vector<vector<int>> expectedGraph2 = {
        {0, 3, 3},
        {3, 0, 2},
        {3, 2, 0}};
    g7.loadGraph(expectedGraph2);

    oss.str("");  // Clear the contents
    oss.clear();  // Clear the state flags

    oss << g6;
    string g6_str = oss.str();

    oss.str("");  // Clear the contents
    oss.clear();  // Clear the state flags

    oss << g7;
    string g7_str = oss.str();

    CHECK(g6_str == g7_str);
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

    std::ostringstream oss;
    oss << g1;
    string g1_str = oss.str();

    // Clear the ostringstream
    oss.str("");  // Clear the contents
    oss.clear();  // Clear the state flags

    oss << g3;
    string g3_str = oss.str();

    CHECK(g1_str == g3_str);

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

    oss.str("");  // Clear the contents
    oss.clear();  // Clear the state flags

    oss << g1;
    string g1_str2 = oss.str();

    oss.str("");  // Clear the contents
    oss.clear();  // Clear the state flags

    oss << g5;
    string g5_str = oss.str();

    CHECK(g1_str2 == g5_str);
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

    std::ostringstream oss;
    oss << g1;
    string g1_str = oss.str();

    // Clear the ostringstream
    oss.str("");  // Clear the contents
    oss.clear();  // Clear the state flags

    oss << g2;
    string g2_str = oss.str();

    CHECK(g1_str == g2_str);

    // Additional tests
    ariel::Graph g3;
    vector<vector<int>> graph2 = {
        {0, 2, 3},
        {2, 0, 1},
        {3, 1, 0}};
    g3.loadGraph(graph2);

    ariel::Graph g4 = +g3;

    oss.str("");  // Clear the contents
    oss.clear();  // Clear the state flags

    oss << g3;
    string g3_str = oss.str();

    oss.str("");  // Clear the contents
    oss.clear();  // Clear the state flags

    oss << g4;
    string g4_str = oss.str();

    CHECK(g3_str == g4_str);
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

    std::ostringstream oss;
    oss << g3;
    string g3_str = oss.str();

    // Clear the ostringstream
    oss.str("");  // Clear the contents
    oss.clear();  // Clear the state flags

    oss << g4;
    string g4_str = oss.str();

    CHECK(g3_str == g4_str);

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

    oss.str("");  // Clear the contents
    oss.clear();  // Clear the state flags

    oss << g6;
    string g6_str = oss.str();

    oss.str("");  // Clear the contents
    oss.clear();  // Clear the state flags

    oss << g7;
    string g7_str = oss.str();

    CHECK(g6_str == g7_str);
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

    std::ostringstream oss;
    oss << g1;
    string g1_str = oss.str();

    // Clear the ostringstream
    oss.str("");  // Clear the contents
    oss.clear();  // Clear the state flags

    oss << g3;
    string g3_str = oss.str();

    CHECK(g1_str == g3_str);

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

    oss.str("");  // Clear the contents
    oss.clear();  // Clear the state flags

    oss << g1;
    string g1_str2 = oss.str();

    oss.str("");  // Clear the contents
    oss.clear();  // Clear the state flags

    oss << g5;
    string g5_str = oss.str();

    CHECK(g1_str2 == g5_str);
}

TEST_CASE("Test 1 graph onari substraction (-g1)"){

}

TEST_CASE("Test < comparison (g1<g2)"){

}

TEST_CASE("Test <= comparison (g1<=g2)"){

}

TEST_CASE("Test > comparison (g1>g2)"){

}

TEST_CASE("Test >= comparison (g1>=g2)"){

}

TEST_CASE("Test == comparison (g1==g2)"){

}

TEST_CASE("Test != comparison (g1!=g2)"){

}

TEST_CASE("Test incrementing (g1++ and ++g)"){

}

TEST_CASE("Test decrementing (g1-- and --g)"){

}

TEST_CASE("Test multiplication by int (g1*=value)"){

}

TEST_CASE("Test division by int (g1/=vaule)"){

}

TEST_CASE("Test 2 graph multiplication")
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

    ariel::Graph g3 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {0, 0, 2},
        {1, 0, 1},
        {1, 0, 0}};
    
    ariel::Graph g4;
    g4.loadGraph(expectedGraph);

    std::ostringstream oss;
    oss<<g3;
    string g3_str = oss.str();
   
    // Clear the ostringstream
    oss.str("");  // Clear the contents
    oss.clear();  // Clear the state flags

    oss<<g4;
    string g4_str = oss.str();

    CHECK(g3_str == g4_str);
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