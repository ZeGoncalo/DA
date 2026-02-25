#include "../data_structures/Graph.h"
#include "stack"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../data_structures/Graph.h"
using namespace std;

// Kosaraju-Sharir algorithm
template <typename T>
vector<vector<T>> SCCkosaraju(Graph<T>* g) {
    vector<vector<T>> sccs;
    stack<Vertex<T>*> st;
    for (auto v : g->getVertexSet()) {
        v->setVisited(false);
    }
    for (auto v : g->getVertexSet()) {
        if (!v->isVisited()) {
            dfsFillStack(v, st);
        }
    }
    for (auto v : g->getVertexSet()) {
        v->setVisited(false);
    }
    while (!st.empty()) {
        auto v = st.top();
        st.pop();
        if (!v->isVisited()) {
            vector<T> scc;
            dfsTranspose(v, scc);
            sccs.push_back(scc);
        }
    }
    return sccs;
}

template <typename T>
void dfsFillStack(Vertex<T>* v, stack<Vertex<T>*>& st) {
    v->setVisited(true);
    for (auto e : v->getAdj()) {
        auto w = e->getDest();
        if (!w->isVisited()) {
            dfsFillStack(w, st);
        }
    }
    st.push(v);
}

template <typename T>
void dfsTranspose(Vertex<T>* v, vector<T>& scc) {
    v->setVisited(true);
    scc.push_back(v->getInfo());
    for (auto e : v->getIncoming()) {
        auto w = e->getOrig();
        if (!w->isVisited()) {
            dfsTranspose(w, scc);
        }
    }
}


TEST(TP1_Ex4, test_SCC_kosaraju) {
    Graph<int> graph0;
    for( int i = 0; i <= 7; i++) {
        graph0.addVertex(i);
    }
    graph0.addEdge(0,1,0);
    graph0.addEdge(1,2,0);
    graph0.addEdge(2,0,0);
    graph0.addEdge(2,3,0);
    graph0.addEdge(3,4,0);
    graph0.addEdge(4,7,0);
    graph0.addEdge(4,5,0);
    graph0.addEdge(5,6,0);
    graph0.addEdge(6,7,0);
    graph0.addEdge(6,4,0);
    vector<vector<int>> sccs_graph0 = SCCkosaraju(& graph0);
    EXPECT_EQ(sccs_graph0.size(), 4);

    Graph<int> graph1;
    for(unsigned int i = 1; i <= 7; i++) {
        graph1.addVertex(i);
    }
    graph1.addEdge(1,2,0);
    graph1.addEdge(1,3,0);
    graph1.addEdge(1,4,0);
    graph1.addEdge(2,5,0);
    graph1.addEdge(5,6,0);
    graph1.addEdge(5,1,0);
    graph1.addEdge(3,6,0);
    graph1.addEdge(3,7,0);
    graph1.addEdge(6,2,0);
    vector<vector<int>> sccs_graph1 = SCCkosaraju(&graph1);

    EXPECT_EQ(sccs_graph1.size(), 3);
    EXPECT_THAT(sccs_graph1,  ::testing::UnorderedElementsAre(::testing::UnorderedElementsAre(1,2,3,5,6), ::testing::UnorderedElementsAre(4), ::testing::UnorderedElementsAre(7)));

    Graph<int> graph2;
    for(unsigned int i = 1; i <= 5; i++) {
        graph2.addVertex(i);
    }
    graph2.addEdge(1,3,0);
    graph2.addEdge(1,4,0);
    graph2.addEdge(2,1,0);
    graph2.addEdge(3,2,0);
    graph2.addEdge(4,5,0);
    vector<vector<int>> sccs_graph2 = SCCkosaraju(&graph2);

    EXPECT_EQ(sccs_graph2.size(), 3);
    EXPECT_THAT(sccs_graph2,  ::testing::UnorderedElementsAre(::testing::UnorderedElementsAre(1,2,3), ::testing::UnorderedElementsAre(4), ::testing::UnorderedElementsAre(5)));

}
