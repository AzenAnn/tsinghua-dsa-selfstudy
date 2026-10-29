#pragma once
// 第6章 图的邻接矩阵实现（教材 §6.3）—— 第 14 天
//
// 顶点存在 V 里，边存在矩阵 E 里：E[v][u] 指向边 (v, u)，没有这条边时为 nullptr。
// 简单的取值函数已经写好；要实现的是插入、删除和邻居枚举，现在都是 DSA_TODO();。

#include <climits>

#include "dsa/graph.h"
#include "dsa/vector.h"

namespace dsa {

template <typename Tv>
struct Vertex {
    Tv data{};
    int inDegree = 0, outDegree = 0;
    VStatus status = VStatus::Undiscovered;
    int dTime = -1, fTime = -1;
    int parent = -1;
    int priority = INT_MAX;
    Vertex() = default;
    explicit Vertex(Tv const& d) : data(d) {}
};

template <typename Te>
struct Edge {
    Te data{};
    int weight = 0;
    EType type = EType::Undetermined;
    Edge() = default;
    Edge(Te const& d, int w) : data(d), weight(w) {}
};

template <typename Tv, typename Te>
class GraphMatrix : public Graph<Tv, Te> {
private:
    Vector<Vertex<Tv>> V;          // 顶点集
    Vector<Vector<Edge<Te>*>> E;   // 邻接矩阵

public:
    using Graph<Tv, Te>::n;
    using Graph<Tv, Te>::e;

    GraphMatrix() = default;
    ~GraphMatrix() override;       // 释放所有边

    // ---------- 顶点 ----------
    Tv& vertex(int v) override { return V[v].data; }
    int inDegree(int v) override { return V[v].inDegree; }
    int outDegree(int v) override { return V[v].outDegree; }
    VStatus& status(int v) override { return V[v].status; }
    int& dTime(int v) override { return V[v].dTime; }
    int& fTime(int v) override { return V[v].fTime; }
    int& parent(int v) override { return V[v].parent; }
    int& priority(int v) override { return V[v].priority; }
    int firstNbr(int v) override { return nextNbr(v, n); }
    int nextNbr(int v, int u) override;
    int insert(Tv const& vertex) override;
    Tv remove(int v) override;

    // ---------- 边 ----------
    bool exists(int v, int u) override;
    EType& type(int v, int u) override { return E[v][u]->type; }
    Te& edge(int v, int u) override { return E[v][u]->data; }
    int& weight(int v, int u) override { return E[v][u]->weight; }
    void insert(Te const& edge, int w, int v, int u) override;
    Te remove(int v, int u) override;
};

template <typename Tv, typename Te>
GraphMatrix<Tv, Te>::~GraphMatrix() {
    // 待实现
}

template <typename Tv, typename Te>
int GraphMatrix<Tv, Te>::nextNbr(int v, int u) {
    DSA_TODO();
}

template <typename Tv, typename Te>
int GraphMatrix<Tv, Te>::insert(Tv const& vertex) {
    DSA_TODO();
}

template <typename Tv, typename Te>
Tv GraphMatrix<Tv, Te>::remove(int v) {
    DSA_TODO();
}

template <typename Tv, typename Te>
bool GraphMatrix<Tv, Te>::exists(int v, int u) {
    DSA_TODO();
}

template <typename Tv, typename Te>
void GraphMatrix<Tv, Te>::insert(Te const& edge, int w, int v, int u) {
    DSA_TODO();
}

template <typename Tv, typename Te>
Te GraphMatrix<Tv, Te>::remove(int v, int u) {
    DSA_TODO();
}

}  // namespace dsa
