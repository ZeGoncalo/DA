#include "../data_structures/Graph.h"
#include "stack"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../data_structures/Graph.h"
using namespace std;

template <typename T>
vector<vector<T>> sccTarjan(Graph<T>* g) {
    vector<vector<T>> res;
    stack<Vertex<T>*> st;
    int index = 0;
    for (auto v : g->getVertexSet()) {
        v->setNum(-1);
        v->setLow(-1);
        v->setProcessing(false);
    }
    for (auto v : g->getVertexSet()) {
        if (v->getNum() == -1) {
            dfsTarjan(v, index, st, res);
        }
    }
    return res;
}

template <typename T>
void dfsTarjan(Vertex<T>* v, int& index,
               stack<Vertex<T>*>& st,
               vector<vector<T>>& res) {
    v->setNum(index);
    v->setLow(index);
    index++;
    st.push(v);
    v->setProcessing(true);
    for (auto e : v->getAdj()) {
        auto w = e->getDest();
        if (w->getNum() == -1) {
            dfsTarjan(w, index, st, res);
            v->setLow(min(v->getLow(), w->getLow()));
        }
        else if (w->isProcessing()) {
            v->setLow(min(v->getLow(), w->getNum()));
        }
    }
    if (v->getLow() == v->getNum()) {
        vector<T> scc;
        Vertex<T>* w;
        do {
            w = st.top();
            st.pop();
            w->setProcessing(false);
            scc.push_back(w->getInfo());
        } while (w != v);
        res.push_back(scc);
    }
}

TEST(TP1_Ex5, test_SCC_Tarjan) {
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
    vector<vector<int>> sccs_graph0 = sccTarjan(& graph0);
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

    vector<vector<int>> sccs_graph1 = sccTarjan(&graph1);

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

    vector<vector<int>> sccs_graph2 = sccTarjan(&graph2);

    EXPECT_EQ(sccs_graph2.size(), 3);
    EXPECT_THAT(sccs_graph2,  ::testing::UnorderedElementsAre(::testing::UnorderedElementsAre(1,2,3), ::testing::UnorderedElementsAre(4), ::testing::UnorderedElementsAre(5)));

}


