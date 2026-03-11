//
// Created by jorge on 04/02/2025.
//

#include <unordered_map>

#include "MSTTestAux.h"
#include "../data_structures/UFDS.h"

template <typename T>
std::vector<Vertex<T> *> kruskal(Graph<T> *g) {
    auto vertexSet = g->getVertexSet();
    if (vertexSet.empty()) return vertexSet;
    int n = vertexSet.size();
    UFDS ufds(n);
    std::unordered_map<Vertex<T>*, int> index;
    for (int i = 0; i < n; i++) {
        index[vertexSet[i]] = i;
    }
    std::vector<Edge<T>*> edges;
    for (auto v : vertexSet) {
        for (auto e : v->getAdj()) {
            if (e->getOrig()->getInfo() < e->getDest()->getInfo())
                edges.push_back(e);
        }
    }
    sort(edges.begin(), edges.end(), [](Edge<T>* a, Edge<T>* b){
        return a->getWeight() < b->getWeight();
    });
    for (auto e : edges) {
        int u = index[e->getOrig()];
        int v = index[e->getDest()];
        if (!ufds.isSameSet(u, v)) {
            e->setSelected(true);
            e->getReverse()->setSelected(true);
            ufds.linkSets(u, v);
        }
    }
    for (auto v : vertexSet) {
        v->setVisited(false);
        v->setPath(nullptr);
    }
    dfsKruskalPath(vertexSet[0]);
    return vertexSet;
}

template <typename T>
void dfsKruskalPath(Vertex<T> *v) {
    v->setVisited(true);
    for (auto e : v->getAdj()) {
        if (e->isSelected() && !e->getDest()->isVisited()) {
            e->getDest()->setPath(e);
            dfsKruskalPath(e->getDest());
        }
    }
}

/// TESTS ///
#include <gtest/gtest.h>
#include <chrono>

TEST(TP3_Ex6, test_kruskal) {
    Graph<int> graph = createMSTTestGraph<int>();
    std::vector<Vertex<int> *> res = kruskal(&graph);

    std::stringstream ss;
    for(const auto v : res) {
        ss << v->getInfo() << "<-";
        if ( v->getPath() != nullptr ) {
            ss << v->getPath()->getOrig()->getInfo();
        }
        ss << "|";
    }
    std::cout << ss.str() << std::endl;

    EXPECT_TRUE(isSpanningTree(res));
    EXPECT_EQ(spanningTreeCost(res), 11);
}

TEST(TP3_Ex6, test_performance_kruskal) {
    //Change these const parameters as needed
    const int MIN_SIZE = 10;
    const int MAX_SIZE = 30; //Try with 100
    const int STEP_SIZE = 10;
    const int N_REPETITIONS = 50;
    for (int n = MIN_SIZE; n <= MAX_SIZE; n += STEP_SIZE) {
        Graph<int> g;
        generateRandomGridGraph(n, g);
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 1; i <= N_REPETITIONS; i++)
            kruskal(&g);
        auto finish = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
        std::cout << "Processing grid (Kruskal) " << n << " x " << n << " average time (milliseconds)=" << (elapsed / N_REPETITIONS) << std::endl;
    }
}
