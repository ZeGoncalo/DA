#include <iostream>
#include "../data_structures/Graph.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../data_structures/Graph.h"
using namespace std;
/****************** DFS ********************/

/*
 * Performs a depth-first search (dfs) in a graph from the source node.
 * Returns a vector with the contents of the vertices by dfs order.
 */
template <class T>
vector<T> dfs(Graph<T> *g, const T & source) {
    vector<int> res;
    for (auto v : g->getVertexSet()) {
        v->setVisited(false);
    }
    Vertex<T>* s = g->findVertex(source);
    if (s == nullptr) {
        return res;
    }
    dfsVisit(s, res);
    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void dfsVisit(Vertex<T> *v, vector<T> & res) {
    v->setVisited(true);
    res.push_back(v->getInfo());
    for (auto e : v->getAdj()) {
        auto w = e->getDest();
        if (!w->isVisited()) {
            dfsVisit(w, res);
        }
    }
}

/****************** BFS ********************/
/*
 * Performs a breadth-first search (bfs) in a graph, starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by bfs order.
 */
template <typename T>
vector<T> bfs(Graph<T> *g, const T & source) {
    vector<int> res;
    for (auto v : g->getVertexSet()) {
        v->setVisited(false);
    }
    Vertex<T>* s = g->findVertex(source);
    if (s == nullptr) return res;
    queue<Vertex<T>*> q;
    q.push(s);
    s->setVisited(true);
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->getInfo());
        for (auto e : v->getAdj()) {
            auto w = e->getDest();
            if (!w->isVisited()) {
                w->setVisited(true);
                q.push(w);
            }
        }
    }
    return res;
}


TEST(TP1_Ex1, test_dfs) {
    // Create a graph
    Graph<int> graph;
    // Create a graph with 7 vertices
    for(unsigned int i = 1; i <= 7; i++) {
        graph.addVertex(i);
    }
    // Add edges
    graph.addEdge(1,2,0);
    graph.addEdge(1,3,0);
    graph.addEdge(1,4,0);
    graph.addEdge(2,5,0);
    graph.addEdge(5,6,0);
    graph.addEdge(5,1,0);
    graph.addEdge(3,6,0);
    graph.addEdge(3,7,0);
    graph.addEdge(6,2,0);

    std::vector<int> vs = dfs(&graph, 1);
    unsigned int ids[] = {1, 2, 5, 6, 3, 7, 4};
    EXPECT_EQ(vs.size(), 7);
    for (unsigned int i = 0; i < vs.size(); i++) {
        EXPECT_EQ(vs[i], ids[i]);
    }
}

TEST(TP1_Ex1, test_bfs) {
    // Create a graph
    Graph<int> graph;
    // Create a graph with 7 vertices
    for(unsigned int i = 1; i <= 7; i++) {
        graph.addVertex(i);
    }
    // Add edges
    graph.addEdge(1,2,0);
    graph.addEdge(1,3,0);
    graph.addEdge(1,4,0);
    graph.addEdge(2,5,0);
    graph.addEdge(5,6,0);
    graph.addEdge(5,1,0);
    graph.addEdge(3,6,0);
    graph.addEdge(3,7,0);
    graph.addEdge(6,2,0);

    std::vector<int> vs = bfs(&graph, 1);
    unsigned int ids[] = {1, 2, 3, 4, 5, 6, 7};
    EXPECT_EQ(vs.size(), 7);
    for (unsigned int i = 0; i < vs.size(); i++) {
        EXPECT_EQ(vs[i], ids[i]);
    }
}

template <typename T>
void expectTopSort(const Graph<T>* graph, std::vector<int> topOrder){
    for(auto u: graph->getVertexSet()) {
        auto itrU = std::find(topOrder.begin(), topOrder.end(), u->getInfo());
        unsigned int indexU = std::distance(topOrder.begin(), itrU);
        for(auto edge: u->getAdj()) {
            auto v = edge->getDest();
            auto itrV = std::find(topOrder.begin(), topOrder.end(), v->getInfo());
            unsigned int indexV = std::distance(topOrder.begin(), itrV);
            EXPECT_LT(indexU,indexV);
        }
    }
}