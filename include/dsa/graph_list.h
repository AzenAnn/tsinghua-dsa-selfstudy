#pragma once
// 第6章 图的邻接表实现（教材 §6.4）—— 第 14 天
//
// 每个顶点 v 有一张表 adj[v]，记录从 v 出发的所有边 (邻居编号, 边)。
// 下面的成员只是一种可行的设计（用了标准库的 vector 和 list），你可以按自己的想法改。
// 要求和 GraphMatrix 完全一样：nextNbr(v, u) 返回编号小于 u 的最大邻居，删除顶点后后面的编号都减 1。

#include <list>
#include <stdexcept>
#include <utility>
#include <vector>

#include "dsa/graph_matrix.h"  // 用到其中的 Vertex 和 Edge

namespace dsa {

template <typename Tv, typename Te>
class GraphList : public Graph<Tv, Te> {
private:
    std::vector<Vertex<Tv>> V;                                // 顶点集
    std::vector<std::list<std::pair<int, Edge<Te>>>> adj;    // adj[v]：从 v 出发的边

    Edge<Te>& find(int v, int u);  // 边 (v, u)（必须存在）       第 14 天

public:
    using Graph<Tv, Te>::n;
    using Graph<Tv, Te>::e;

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
    EType& type(int v, int u) override { return find(v, u).type; }
    Te& edge(int v, int u) override { return find(v, u).data; }
    int& weight(int v, int u) override { return find(v, u).weight; }
    void insert(Te const& edge, int w, int v, int u) override;
    Te remove(int v, int u) override;
};

template <typename Tv, typename Te>
Edge<Te>& GraphList<Tv, Te>::find(int v, int u) {
    DSA_TODO();
}

template <typename Tv, typename Te>
int GraphList<Tv, Te>::nextNbr(int v, int u) {
    DSA_TODO();
}

template <typename Tv, typename Te>
int GraphList<Tv, Te>::insert(Tv const& vertex) {
    DSA_TODO();
}

template <typename Tv, typename Te>
Tv GraphList<Tv, Te>::remove(int v) {
    DSA_TODO();
}

template <typename Tv, typename Te>
bool GraphList<Tv, Te>::exists(int v, int u) {
    DSA_TODO();
}

template <typename Tv, typename Te>
void GraphList<Tv, Te>::insert(Te const& edge, int w, int v, int u) {
    DSA_TODO();
}

template <typename Tv, typename Te>
Te GraphList<Tv, Te>::remove(int v, int u) {
    DSA_TODO();
}

}  // namespace dsa
