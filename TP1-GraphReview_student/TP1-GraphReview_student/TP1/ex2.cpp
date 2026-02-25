#include <iostream>
#include "../data_structures/Graph.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace std;

/*
 * Performs a topological sorting of the vertices of a graph.
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
*/
template <typename T>
vector<T> topsort(Graph<T> *g) {
    vector<int> res;
    queue<Vertex<T>*> q;
    for (auto v : g->getVertexSet()) {
        v->setIndegree(0);
    }
    for (auto v : g->getVertexSet()) {
        for (auto e : v->getAdj()) {
            auto w = e->getDest();
            w->setIndegree(w->getIndegree() + 1);
        }
    }
    for (auto v : g->getVertexSet()) {
        if (v->getIndegree() == 0) {
            q.push(v);
        }
    }
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->getInfo());
        for (auto e : v->getAdj()) {
            auto w = e->getDest();
            w->setIndegree(w->getIndegree() - 1);
            if (w->getIndegree() == 0) {
                q.push(w);
            }
        }
    }
    if (res.size() != g->getNumVertex()) {
        return {};
    }
    return res;
}
template <typename T>
void expectTopSort(const Graph<T>* graph, std::vector<int> topOrder) {
    for (auto u: graph->getVertexSet()) {
        auto itrU = std::find(topOrder.begin(), topOrder.end(), u->getInfo());
        unsigned int indexU = std::distance(topOrder.begin(), itrU);
        for (auto edge: u->getAdj()) {
            auto v = edge->getDest();
            auto itrV = std::find(topOrder.begin(), topOrder.end(), v->getInfo());
            unsigned int indexV = std::distance(topOrder.begin(), itrV);
            EXPECT_LT(indexU, indexV);
        }
    }

}
TEST(TP1_Ex2, test_topsort) {
    Graph<int> myGraph;
    myGraph.addVertex(1); myGraph.addVertex(2); myGraph.addVertex(3); myGraph.addVertex(4);
    myGraph.addVertex(5); myGraph.addVertex(6); myGraph.addVertex(7);

    myGraph.addEdge(1, 2, 0);
    myGraph.addEdge(1, 4, 0);
    myGraph.addEdge(1, 3, 0);
    myGraph.addEdge(2, 5, 0);
    myGraph.addEdge(2, 4, 0);
    myGraph.addEdge(3, 6, 0);
    myGraph.addEdge(4, 3, 0);
    myGraph.addEdge(4, 6, 0);
    myGraph.addEdge(4, 7, 0);
    myGraph.addEdge(5, 4, 0);
    myGraph.addEdge(5, 7, 0);
    myGraph.addEdge(7, 6, 0);

    std::vector<int> topOrder = topsort(&myGraph);
    EXPECT_EQ(topOrder.size(), 7);
    expectTopSort(&myGraph, topOrder); // example of two valid topsorts: "1 2 5 4 3 7 6" and "1 2 5 4 7 3 6"

    // to test including a cycle in the graph
    myGraph.addEdge(3, 1, 0);

    topOrder = topsort(&myGraph);
    EXPECT_EQ(topOrder.size(), 0);
}
