#pragma once
// 第6章 图（教材 §6.1–6.12）：图的抽象基类和图算法
//
// Graph 只规定接口（纯虚函数），邻接矩阵 GraphMatrix 在 graph_matrix.h、邻接表 GraphList 在 graph_list.h。
// 图算法只通过这些接口访问图，所以同一份算法对两种表示都适用。
// 顶点编号用 int（0 .. n-1），“没有”用 -1 表示。无向图用两条方向相反的有向边表示。
// 算法的实现现在都是 DSA_TODO();，可以按需要在类里添加自己的辅助函数。

#include <climits>
#include <vector>

#include "dsa/queue.h"
#include "dsa/stack.h"

namespace dsa {

enum class VStatus { Undiscovered, Discovered, Visited };
enum class EType { Undetermined, Tree, Cross, Forward, Backward };

template <typename Tv, typename Te>
class Graph {
protected:
    // 所有顶点和边的辅助信息复位（已经写好了）
    void reset() {
        for (int i = 0; i < n; i++) {
            status(i) = VStatus::Undiscovered;
            dTime(i) = fTime(i) = -1;
            parent(i) = -1;
            priority(i) = INT_MAX;
            for (int j = 0; j < n; j++)
                if (exists(i, j)) type(i, j) = EType::Undetermined;
        }
    }
    void BFS(int v, int& clock);  // 从 v 出发，广度优先遍历 v 所在的连通域     第 15 天
    void DFS(int v, int& clock);  // 从 v 出发，深度优先遍历                    第 15 天
    template <typename PU>
    void PFS(int s, PU prioUpdater);  // 从 s 出发的优先级搜索（一个连通域）   第 17 天

public:
    int n = 0;  // 顶点数
    int e = 0;  // 边数（有向边的条数）
    virtual ~Graph() = default;

    // ---------- 顶点 ----------
    virtual int insert(Tv const& vertex) = 0;  // 插入顶点，返回它的编号（= 插入前的 n）
    virtual Tv remove(int v) = 0;              // 删除顶点 v 及其关联的边；编号比 v 大的顶点，编号都减 1
    virtual Tv& vertex(int v) = 0;             // 顶点 v 的数据
    virtual int inDegree(int v) = 0;
    virtual int outDegree(int v) = 0;
    virtual int firstNbr(int v) = 0;           // v 的第一个邻居 = nextNbr(v, n)
    virtual int nextNbr(int v, int u) = 0;     // v 的邻居中编号小于 u 的最大的那个；没有则返回 -1
    virtual VStatus& status(int v) = 0;
    virtual int& dTime(int v) = 0;             // 被发现的时刻
    virtual int& fTime(int v) = 0;             // 访问完毕的时刻
    virtual int& parent(int v) = 0;            // 在遍历树中的父亲，没有则为 -1
    virtual int& priority(int v) = 0;          // 在优先级搜索中的优先级（数值越小越优先）

    // ---------- 边：(v, u) 是从 v 指向 u 的有向边 ----------
    virtual bool exists(int v, int u) = 0;
    virtual void insert(Te const& edge, int w, int v, int u) = 0;  // 插入边 (v, u)，权重 w；已经有这条边时什么也不做
    virtual Te remove(int v, int u) = 0;                           // 删除边 (v, u)，返回它的数据
    virtual EType& type(int v, int u) = 0;
    virtual Te& edge(int v, int u) = 0;
    virtual int& weight(int v, int u) = 0;

    // ---------- 算法 ----------
    // 第 15 天：§6.6–6.7。从 s 开始，然后按编号 s+1, s+2, ...（循环）处理其余还没发现的顶点，覆盖全图。
    // bfs：dTime(v) 是 v 被发现的次序（0, 1, 2, ...）；遍历树中的边标为 Tree，其余标为 Cross。
    // dfs：时钟从 0 开始，发现 v 时 dTime(v) = ++clock，访问完毕时 fTime(v) = ++clock；
    //      边按书上的规则分为 Tree、Backward、Forward、Cross。
    void bfs(int s);
    void dfs(int s);
    // 第 16 天：§6.8–6.9
    bool tSort(int s, std::vector<int>& order);  // 基于 DFS 的拓扑排序：有环返回 false；否则 order 是一个拓扑序
    bool tSortKahn(std::vector<int>& order);     // 零入度算法（不断删去入度为 0 的顶点），约定同上
    // 双连通域分解（无向图）：返回双连通域的个数（孤立顶点不算），关节点按编号从小到大放进 articulation
    int bcc(int s, std::vector<int>& articulation);
    // 第 17 天：§6.10–6.12。pfs 和 bfs 一样覆盖全图，每个连通域从它的第一个顶点开始。
    template <typename PU>
    void pfs(int s, PU prioUpdater);
    void prim(int s);      // 最小支撑树（森林）：结束后 parent 指出树边，树边的 type 为 Tree
    void dijkstra(int s);  // 最短路径：结束后 priority(v) 是从 s 到 v 的距离（v 与 s 连通时）
};

// 优先级更新器（第 17 天）：在优先级搜索中，v 刚被访问，对它的邻居 u 调用 pu(g, v, u)
struct PrimPU {
    template <typename Tv, typename Te>
    void operator()(Graph<Tv, Te>* g, int v, int u);
};
struct DijkPU {
    template <typename Tv, typename Te>
    void operator()(Graph<Tv, Te>* g, int v, int u);
};

// ======================================================================
// 第 15 天：BFS 与 DFS（§6.5–6.7）
// ======================================================================

template <typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int v, int& clock) {
    DSA_TODO();
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s) {
    DSA_TODO();
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int& clock) {
    DSA_TODO();
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int s) {
    DSA_TODO();
}

// ======================================================================
// 第 16 天：拓扑排序与双连通域分解（§6.8–6.9）
// ======================================================================


template <typename Tv, typename Te>
bool Graph<Tv, Te>::tSort(int s, std::vector<int>& order) {
    DSA_TODO();
}

template <typename Tv, typename Te>
bool Graph<Tv, Te>::tSortKahn(std::vector<int>& order) {
    DSA_TODO();
}

template <typename Tv, typename Te>
int Graph<Tv, Te>::bcc(int s, std::vector<int>& articulation) {
    DSA_TODO();
}

// ======================================================================
// 第 17 天：优先级搜索、Prim、Dijkstra（§6.10–6.12）
// ======================================================================

template <typename Tv, typename Te>
template <typename PU>
void Graph<Tv, Te>::PFS(int s, PU prioUpdater) {
    DSA_TODO();
}

template <typename Tv, typename Te>
template <typename PU>
void Graph<Tv, Te>::pfs(int s, PU prioUpdater) {
    DSA_TODO();
}

template <typename Tv, typename Te>
void PrimPU::operator()(Graph<Tv, Te>* g, int v, int u) {
    DSA_TODO();
}

template <typename Tv, typename Te>
void DijkPU::operator()(Graph<Tv, Te>* g, int v, int u) {
    DSA_TODO();
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::prim(int s) {
    DSA_TODO();
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::dijkstra(int s) {
    DSA_TODO();
}

}  // namespace dsa
