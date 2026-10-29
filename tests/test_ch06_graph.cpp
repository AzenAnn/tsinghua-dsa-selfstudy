// 第6章 图的测试（D14–D17）。每个用例对邻接矩阵 GraphMatrix 和邻接表 GraphList 各跑一遍。

#include <algorithm>
#include <climits>
#include <functional>
#include <numeric>
#include <tuple>
#include <vector>

#include "dsa/graph_list.h"
#include "dsa/graph_matrix.h"
#include "dsa_test.h"

using namespace dsa;
using dsa_test::randInt;

namespace {

using GM = GraphMatrix<int, int>;
using GL = GraphList<int, int>;
using Mat = std::vector<std::vector<int>>;  // 参考：w[v][u] 是边 (v, u) 的权重，-1 表示没有

// 随机图：n 个顶点，每条可能的边以 p% 的概率出现；undirected 时两个方向同时加入；
// dag 时只加从“拓扑序靠前”指向“靠后”的边
template <typename G>
Mat build(G& g, int n, int p, bool undirected, bool dag = false, int maxW = 20) {
    Mat w(n, std::vector<int>(n, -1));
    std::vector<int> order(n);
    std::iota(order.begin(), order.end(), 0);
    for (int i = n - 1; i > 0; --i) std::swap(order[i], order[randInt(0, i)]);
    std::vector<int> pos(n);
    for (int i = 0; i < n; ++i) pos[order[i]] = i;
    for (int i = 0; i < n; ++i) g.insert(i * 10);
    for (int v = 0; v < n; ++v)
        for (int u = 0; u < n; ++u) {
            if (v == u || w[v][u] != -1 || randInt(0, 99) >= p) continue;
            if (undirected && u < v) continue;
            if (dag && pos[v] > pos[u]) continue;
            int wt = (int)randInt(1, maxW);
            g.insert(v * 100 + u, wt, v, u);
            w[v][u] = wt;
            if (undirected) {
                g.insert(u * 100 + v, wt, u, v);
                w[u][v] = wt;
            }
        }
    return w;
}

std::vector<int> hopDist(const Mat& w, int s) {
    int n = (int)w.size();
    std::vector<int> d(n, -1), q{s};
    d[s] = 0;
    for (std::size_t i = 0; i < q.size(); ++i)
        for (int u = 0; u < n; ++u)
            if (w[q[i]][u] != -1 && d[u] == -1) {
                d[u] = d[q[i]] + 1;
                q.push_back(u);
            }
    return d;
}

// 无向图删掉顶点 skip（-1 表示不删）后的连通域个数
int components(const Mat& w, int skip = -1) {
    int n = (int)w.size(), c = 0;
    std::vector<bool> seen(n, false);
    for (int s = 0; s < n; ++s) {
        if (s == skip || seen[s]) continue;
        ++c;
        std::vector<int> st{s};
        seen[s] = true;
        while (!st.empty()) {
            int v = st.back();
            st.pop_back();
            for (int u = 0; u < n; ++u)
                if (u != skip && w[v][u] != -1 && !seen[u]) {
                    seen[u] = true;
                    st.push_back(u);
                }
        }
    }
    return c;
}

// ---------------- D14：基本操作和参考模型对拍 ----------------
template <typename G>
void checkAgainst(G& g, const std::vector<int>& data, const Mat& w) {
    int n = (int)data.size(), edges = 0;
    REQUIRE_EQ(g.n, n);
    for (int v = 0; v < n; ++v) {
        REQUIRE_EQ(g.vertex(v), data[v]);
        int in = 0, out = 0;
        for (int u = 0; u < n; ++u) {
            in += w[u][v] != -1;
            out += w[v][u] != -1;
            REQUIRE_EQ(g.exists(v, u), w[v][u] != -1);
            if (w[v][u] != -1) {
                REQUIRE_EQ(g.weight(v, u), w[v][u]);
                REQUIRE_EQ(g.edge(v, u), w[v][u] * 1000);
            }
        }
        edges += out;
        REQUIRE_EQ(g.inDegree(v), in);
        REQUIRE_EQ(g.outDegree(v), out);
        std::vector<int> nbr, expect;  // 邻居按编号从大到小枚举
        for (int u = g.firstNbr(v); -1 < u; u = g.nextNbr(v, u)) nbr.push_back(u);
        for (int u = n - 1; u >= 0; --u)
            if (w[v][u] != -1) expect.push_back(u);
        REQUIRE_EQ(nbr, expect);
    }
    REQUIRE_EQ(g.e, edges);
}

template <typename G>
void testBasic() {
    for (int round = 0; round < 30; ++round) {
        G g;
        std::vector<int> data;
        Mat w;
        for (int op = 0; op < 200; ++op) {
            int n = (int)data.size(), kind = (int)randInt(0, 9);
            if (kind < 2 || n < 2) {
                int d = (int)randInt(0, 999);
                REQUIRE_EQ(g.insert(d), n);
                data.push_back(d);
                for (auto& row : w) row.push_back(-1);
                w.push_back(std::vector<int>(n + 1, -1));
            } else if (kind < 7) {
                int v = (int)randInt(0, n - 1), u = (int)randInt(0, n - 1);
                if (v == u) continue;
                int wt = (int)randInt(1, 50);
                g.insert(wt * 1000, wt, v, u);  // 已存在时什么也不做
                if (w[v][u] == -1) w[v][u] = wt;
            } else if (kind < 9) {
                int v = (int)randInt(0, n - 1), u = (int)randInt(0, n - 1);
                if (w[v][u] == -1) continue;
                REQUIRE_EQ(g.remove(v, u), w[v][u] * 1000);
                w[v][u] = -1;
            } else {
                int v = (int)randInt(0, n - 1);
                REQUIRE_EQ(g.remove(v), data[v]);
                data.erase(data.begin() + v);
                w.erase(w.begin() + v);
                for (auto& row : w) row.erase(row.begin() + v);
            }
            checkAgainst(g, data, w);
        }
    }
}

// ---------------- D15：BFS 和 DFS ----------------
template <typename G>
void testBfs() {
    for (int round = 0; round < 200; ++round) {
        G g;
        int n = (int)randInt(1, 25);
        bool undirected = randInt(0, 1);
        Mat w = build(g, n, (int)randInt(5, 40), undirected);
        int s = (int)randInt(0, n - 1);
        g.bfs(s);
        REQUIRE_EQ(g.dTime(s), 0);
        std::vector<int> times;
        int roots = 0;
        for (int v = 0; v < n; ++v) {
            REQUIRE(g.status(v) == VStatus::Visited);
            times.push_back(g.dTime(v));
            int p = g.parent(v);
            if (p == -1) {
                ++roots;
                continue;
            }
            REQUIRE(g.exists(p, v));
            REQUIRE(g.type(p, v) == EType::Tree);
            REQUIRE(g.dTime(p) < g.dTime(v));
        }
        std::sort(times.begin(), times.end());
        for (int i = 0; i < n; ++i) REQUIRE_EQ(times[i], i);  // dTime 恰好是 0..n-1
        for (int v = 0; v < n; ++v)
            for (int u = 0; u < n; ++u)
                if (w[v][u] != -1) REQUIRE(g.type(v, u) == (g.parent(u) == v ? EType::Tree : EType::Cross));
        std::vector<int> d = hopDist(w, s);  // 从 s 可达的顶点：树上的深度就是最短跳数
        for (int v = 0; v < n; ++v) {
            if (d[v] < 0) continue;
            int depth = 0;
            for (int x = v; g.parent(x) != -1; x = g.parent(x)) ++depth;
            REQUIRE_EQ(depth, d[v]);
        }
        (void)roots;
    }
}

template <typename G>
void testDfs() {
    for (int round = 0; round < 200; ++round) {
        G g;
        int n = (int)randInt(1, 25);
        Mat w = build(g, n, (int)randInt(5, 40), randInt(0, 1));
        int s = (int)randInt(0, n - 1);
        g.dfs(s);
        REQUIRE_EQ(g.dTime(s), 1);
        std::vector<int> times;
        auto inside = [&](int a, int b) {  // a 的活跃期包含于 b 的活跃期（b 是 a 的祖先或 a 自己）
            return g.dTime(b) <= g.dTime(a) && g.fTime(a) <= g.fTime(b);
        };
        for (int v = 0; v < n; ++v) {
            REQUIRE(g.status(v) == VStatus::Visited);
            REQUIRE(g.dTime(v) < g.fTime(v));
            times.push_back(g.dTime(v));
            times.push_back(g.fTime(v));
            int p = g.parent(v);
            if (p != -1) {
                REQUIRE(g.exists(p, v));
                REQUIRE(inside(v, p));
            }
        }
        std::sort(times.begin(), times.end());
        for (int i = 0; i < 2 * n; ++i) REQUIRE_EQ(times[i], i + 1);  // 时钟 1..2n 各用一次
        for (int v = 0; v < n; ++v)  // 括号引理：任意两个活跃期要么嵌套，要么不相交
            for (int u = 0; u < n; ++u) {
                bool disjoint = g.fTime(v) < g.dTime(u) || g.fTime(u) < g.dTime(v);
                REQUIRE(disjoint || inside(v, u) || inside(u, v));
            }
        for (int v = 0; v < n; ++v)
            for (int u = 0; u < n; ++u) {
                if (w[v][u] == -1) continue;
                EType t = g.type(v, u);
                if (g.parent(u) == v)
                    REQUIRE(t == EType::Tree);
                else if (inside(v, u))
                    REQUIRE(t == EType::Backward);
                else if (inside(u, v))
                    REQUIRE(t == EType::Forward);
                else {
                    REQUIRE(t == EType::Cross);
                    REQUIRE(g.dTime(u) < g.dTime(v));
                }
            }
    }
}

// ---------------- D16：拓扑排序、双连通域 ----------------
template <typename G>
void testTSort(bool kahn) {
    for (int round = 0; round < 300; ++round) {
        G g;
        int n = (int)randInt(1, 25);
        Mat w = build(g, n, (int)randInt(5, 40), false, true);
        bool cyclic = randInt(0, 1);
        if (cyclic) {  // 找一条边 (a, b)，加上 (b, a) 形成环
            std::vector<std::pair<int, int>> es;
            for (int v = 0; v < n; ++v)
                for (int u = 0; u < n; ++u)
                    if (w[v][u] != -1) es.push_back({v, u});
            if (es.empty()) {
                cyclic = false;
            } else {
                auto [a, b] = es[randInt(0, es.size() - 1)];
                g.insert(0, 1, b, a);
                w[b][a] = 1;
            }
        }
        std::vector<int> order;
        bool ok = kahn ? g.tSortKahn(order) : g.tSort((int)randInt(0, n - 1), order);
        REQUIRE_EQ(ok, !cyclic);
        if (!ok) continue;
        REQUIRE_EQ((int)order.size(), n);
        std::vector<int> pos(n, -1);
        for (int i = 0; i < n; ++i) {
            REQUIRE(0 <= order[i] && order[i] < n && pos[order[i]] == -1);
            pos[order[i]] = i;
        }
        for (int v = 0; v < n; ++v)
            for (int u = 0; u < n; ++u)
                if (w[v][u] != -1) REQUIRE(pos[v] < pos[u]);
    }
}

template <typename G>
void testBcc() {
    for (int round = 0; round < 300; ++round) {
        G g;
        int n = (int)randInt(1, 14);
        Mat w = build(g, n, (int)randInt(10, 40), true);
        std::vector<int> art;
        int count = g.bcc((int)randInt(0, n - 1), art);
        // 参考：v 是关节点 ⇔ v 有邻居，且删掉 v 后连通域变多
        int base = components(w);
        std::vector<int> expectArt;
        int blocks = 0;
        std::vector<bool> compHasEdge(n, false);
        for (int v = 0; v < n; ++v) {
            int deg = 0;
            for (int u = 0; u < n; ++u) deg += w[v][u] != -1;
            if (deg == 0) continue;
            int pieces = components(w, v) - (base - 1);  // v 所在连通域删掉 v 后碎成几块
            if (pieces >= 2) expectArt.push_back(v);
            blocks += pieces - 1;
        }
        // 每个至少有一条边的连通域贡献 1，再加上每个关节点多出的块数
        std::vector<int> comp(n, -1);
        int cid = 0;
        for (int s = 0; s < n; ++s) {
            if (comp[s] != -1) continue;
            std::vector<int> st{s};
            comp[s] = cid;
            bool hasEdge = false;
            while (!st.empty()) {
                int v = st.back();
                st.pop_back();
                for (int u = 0; u < n; ++u)
                    if (w[v][u] != -1) {
                        hasEdge = true;
                        if (comp[u] == -1) {
                            comp[u] = cid;
                            st.push_back(u);
                        }
                    }
            }
            blocks += hasEdge;
            ++cid;
        }
        REQUIRE_EQ(art, expectArt);
        REQUIRE_EQ(count, blocks);
    }
}

// ---------------- D17：Prim 和 Dijkstra ----------------
long long kruskal(const Mat& w) {
    int n = (int)w.size();
    std::vector<std::tuple<int, int, int>> es;
    for (int v = 0; v < n; ++v)
        for (int u = v + 1; u < n; ++u)
            if (w[v][u] != -1) es.push_back({w[v][u], v, u});
    std::sort(es.begin(), es.end());
    std::vector<int> f(n);
    std::iota(f.begin(), f.end(), 0);
    std::function<int(int)> find = [&](int x) { return f[x] == x ? x : f[x] = find(f[x]); };
    long long total = 0;
    for (auto [wt, v, u] : es)
        if (find(v) != find(u)) {
            f[find(v)] = find(u);
            total += wt;
        }
    return total;
}

template <typename G>
void testPrim() {
    for (int round = 0; round < 300; ++round) {
        G g;
        int n = (int)randInt(1, 20);
        Mat w = build(g, n, (int)randInt(10, 60), true);
        g.prim((int)randInt(0, n - 1));
        long long total = 0;
        int treeEdges = 0;
        for (int v = 0; v < n; ++v) {
            int p = g.parent(v);
            if (p == -1) continue;
            REQUIRE(g.exists(p, v));
            REQUIRE(g.type(p, v) == EType::Tree);
            total += g.weight(p, v);
            ++treeEdges;
        }
        REQUIRE_EQ(treeEdges, n - components(w));
        REQUIRE_EQ(total, kruskal(w));
    }
}

template <typename G>
void testDijkstra() {
    for (int round = 0; round < 300; ++round) {
        G g;
        int n = (int)randInt(1, 20);
        Mat w = build(g, n, (int)randInt(10, 50), randInt(0, 1));
        int s = (int)randInt(0, n - 1);
        g.dijkstra(s);
        std::vector<long long> d(n, LLONG_MAX);  // Bellman-Ford
        d[s] = 0;
        for (int it = 0; it < n; ++it)
            for (int v = 0; v < n; ++v)
                for (int u = 0; u < n; ++u)
                    if (w[v][u] != -1 && d[v] != LLONG_MAX) d[u] = std::min(d[u], d[v] + w[v][u]);
        for (int v = 0; v < n; ++v) {
            if (d[v] == LLONG_MAX) continue;
            REQUIRE_EQ((long long)g.priority(v), d[v]);
            if (v != s) {
                int p = g.parent(v);
                REQUIRE(p != -1 && g.exists(p, v));
                REQUIRE_EQ(g.priority(v), g.priority(p) + g.weight(p, v));
            }
        }
    }
}

}  // namespace

TEST("D14 GraphMatrix：插入、删除顶点和边，度数、邻居枚举") { testBasic<GM>(); }
TEST("D14 GraphList：插入、删除顶点和边，度数、邻居枚举") { testBasic<GL>(); }
TEST("D15 bfs（GraphMatrix）") { testBfs<GM>(); }
TEST("D15 bfs（GraphList）") { testBfs<GL>(); }
TEST("D15 dfs（GraphMatrix）：时间标签、括号引理、边分类") { testDfs<GM>(); }
TEST("D15 dfs（GraphList）：时间标签、括号引理、边分类") { testDfs<GL>(); }
TEST("D16 tSort（GraphMatrix）：基于 DFS") { testTSort<GM>(false); }
TEST("D16 tSort（GraphList）：基于 DFS") { testTSort<GL>(false); }
TEST("D16 tSortKahn（GraphMatrix）：零入度算法") { testTSort<GM>(true); }
TEST("D16 tSortKahn（GraphList）：零入度算法") { testTSort<GL>(true); }
TEST("D16 bcc（GraphMatrix）：关节点和双连通域个数") { testBcc<GM>(); }
TEST("D16 bcc（GraphList）：关节点和双连通域个数") { testBcc<GL>(); }
TEST("D17 prim（GraphMatrix）：最小支撑森林的总权重") { testPrim<GM>(); }
TEST("D17 prim（GraphList）：最小支撑森林的总权重") { testPrim<GL>(); }
TEST("D17 dijkstra（GraphMatrix）：最短路径") { testDijkstra<GM>(); }
TEST("D17 dijkstra（GraphList）：最短路径") { testDijkstra<GL>(); }
