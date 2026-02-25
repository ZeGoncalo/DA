#include <iostream>
#include "../data_structures/Graph.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../data_structures/Graph.h"
using namespace std;

/****************** isDAG  ********************/
/*
 * Performs a depth-first search in a graph, to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the stack of recursive calls.
 * Returns true if the graph is acyclic, and false otherwise.
 */

template <class T>
bool isDAG(Graph<T> *g) {
    for (auto v : g->getVertexSet()) {
        v->setVisited(false);
        v->setProcessing(false);
    }
    for (auto v : g->getVertexSet()) {
        if (!v->isVisited()) {
            if (!dfsIsDAG(v))
                return false;
        }
    }
    return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template <class T>
bool dfsIsDAG(Vertex<T> *v) {
    v->setVisited(true);
    v->setProcessing(true);
    for (auto e : v->getAdj()) {
        auto w = e->getDest();
        if (w->isProcessing())
            return false;
        if (!w->isVisited()) {
            if (!dfsIsDAG(w))
                return false;
        }
    }
    v->setProcessing(false);
    return true;
}

TEST(TP1_Ex3, test_isDAG) {
    Graph<int> myGraph;

    for( int i = 0; i < 6; i++) {
        myGraph.addVertex(i);
    }

    myGraph.addEdge(1, 2, 0);
    myGraph.addEdge(2, 5, 0);
    myGraph.addEdge(5, 4, 0);
    myGraph.addEdge(3, 1, 0);
    myGraph.addEdge(0, 4, 0);

    EXPECT_EQ(isDAG(&myGraph), true);

    myGraph.addEdge(4, 1, 0);

    EXPECT_EQ(isDAG(&myGraph), false);
}
