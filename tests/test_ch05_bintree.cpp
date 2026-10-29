// 第5章 二叉树的测试（D11–D12）

#include <algorithm>
#include <functional>
#include <memory>
#include <vector>

#include "dsa/bintree.h"
#include "dsa_test.h"

using namespace dsa;
using dsa_test::randInt;

namespace {

using Node = BinNodePosi<int>;

// 参考实现：递归遍历，以及按定义计算的高度和规模
void refPre(Node x, std::vector<int>& v) {
    if (!x) return;
    v.push_back(x->data);
    refPre(x->lc, v);
    refPre(x->rc, v);
}
void refIn(Node x, std::vector<int>& v) {
    if (!x) return;
    refIn(x->lc, v);
    v.push_back(x->data);
    refIn(x->rc, v);
}
void refPost(Node x, std::vector<int>& v) {
    if (!x) return;
    refPost(x->lc, v);
    refPost(x->rc, v);
    v.push_back(x->data);
}
std::vector<int> refLevel(Node x) {
    std::vector<int> v;
    std::vector<Node> q;
    if (x) q.push_back(x);
    for (std::size_t i = 0; i < q.size(); ++i) {
        v.push_back(q[i]->data);
        if (q[i]->lc) q.push_back(q[i]->lc);
        if (q[i]->rc) q.push_back(q[i]->rc);
    }
    return v;
}
int refHeight(Node x) { return x ? 1 + std::max(refHeight(x->lc), refHeight(x->rc)) : -1; }
int refSize(Node x) { return x ? 1 + refSize(x->lc) + refSize(x->rc) : 0; }

// 检查整棵树：父指针、每个节点记录的高度、规模
void checkTree(const BinTree<int>& t) {
    std::function<void(Node)> go = [&](Node x) {
        if (!x) return;
        if (x->lc) REQUIRE(x->lc->parent == x);
        if (x->rc) REQUIRE(x->rc->parent == x);
        REQUIRE_EQ(x->height, refHeight(x));
        go(x->lc);
        go(x->rc);
    };
    if (t.root()) REQUIRE(t.root()->parent == nullptr);
    go(t.root());
    REQUIRE_EQ((int)t.size(), refSize(t.root()));
}

// 随机长出一棵 n 个节点的树，数据是 0..n-1（互不相同），nodes 收集所有节点
void grow(BinTree<int>& t, int n, std::vector<Node>& nodes, int base = 0) {
    if (n == 0) return;
    nodes.push_back(t.insertAsRoot(base));
    for (int k = 1; k < n; ++k) {
        while (true) {
            Node x = nodes[randInt(0, nodes.size() - 1)];
            bool left = randInt(0, 1);
            if (left && !x->lc) {
                nodes.push_back(t.insertAsLC(x, base + k));
                break;
            }
            if (!left && !x->rc) {
                nodes.push_back(t.insertAsRC(x, base + k));
                break;
            }
        }
    }
}

// 随机的真二叉树：每个节点 0 或 2 个孩子，共 2m+1 个节点
void growProper(BinTree<int>& t, int m) {
    std::vector<Node> leaves{t.insertAsRoot(0)};
    int next = 1;
    for (int k = 0; k < m; ++k) {
        int i = (int)randInt(0, leaves.size() - 1);
        Node x = leaves[i];
        leaves.erase(leaves.begin() + i);
        leaves.push_back(t.insertAsLC(x, next++));
        leaves.push_back(t.insertAsRC(x, next++));
    }
}

template <typename F>
std::vector<int> collect(Node root, F trav) {
    std::vector<int> v;
    trav(root, [&](int& e) { v.push_back(e); });
    return v;
}

}  // namespace

// ======================= 第 11 天 =======================

TEST("D11 insertAsRoot / insertAsLC / insertAsRC：规模、高度、父指针") {
    BinTree<int> t;
    CHECK(t.empty());
    Node r = t.insertAsRoot(1);
    CHECK_EQ(r->height, 0);
    Node a = t.insertAsLC(r, 2);
    Node b = t.insertAsRC(a, 3);
    CHECK_EQ(t.size(), 3u);
    CHECK_EQ(r->height, 2);
    CHECK(b->parent == a && a->parent == r);
    checkTree(t);
    for (int round = 0; round < 300; ++round) {
        BinTree<int> u;
        std::vector<Node> nodes;
        grow(u, (int)randInt(1, 60), nodes);
        checkTree(u);
    }
}

TEST("D11 BinNode::size：子树规模") {
    for (int round = 0; round < 300; ++round) {
        BinTree<int> t;
        std::vector<Node> nodes;
        grow(t, (int)randInt(1, 60), nodes);
        for (Node x : nodes) REQUIRE_EQ((int)x->size(), refSize(x));
    }
}

TEST("D11 remove：删除子树，返回删除的节点数，祖先高度随之更新") {
    for (int round = 0; round < 300; ++round) {
        BinTree<int> t;
        std::vector<Node> nodes;
        grow(t, (int)randInt(1, 60), nodes);
        Node x = nodes[randInt(0, nodes.size() - 1)];
        int expect = refSize(x);
        int before = (int)t.size();
        REQUIRE_EQ((int)t.remove(x), expect);
        REQUIRE_EQ((int)t.size(), before - expect);
        checkTree(t);
    }
}

TEST("D11 secede：摘下子树成为新树") {
    for (int round = 0; round < 300; ++round) {
        BinTree<int> t;
        std::vector<Node> nodes;
        grow(t, (int)randInt(1, 60), nodes);
        Node x = nodes[randInt(0, nodes.size() - 1)];
        std::vector<int> sub;
        refPre(x, sub);
        int before = (int)t.size();
        std::unique_ptr<BinTree<int>> s(t.secede(x));
        REQUIRE(s->root() == x);
        REQUIRE_EQ((int)s->size(), (int)sub.size());
        REQUIRE_EQ((int)t.size(), before - (int)sub.size());
        std::vector<int> got;
        refPre(s->root(), got);
        REQUIRE_EQ(got, sub);
        checkTree(t);
        checkTree(*s);
    }
}

TEST("D11 attachAsLC / attachAsRC：接上子树，S 被释放并置空") {
    for (int round = 0; round < 300; ++round) {
        BinTree<int> t;
        std::vector<Node> nodes;
        grow(t, (int)randInt(1, 30), nodes);
        BinTree<int>* s = new BinTree<int>;
        std::vector<Node> sn;
        grow(*s, (int)randInt(0, 30), sn, 1000);
        int ssize = (int)s->size(), tsize = (int)t.size();
        std::vector<Node> slots;  // 还缺左孩子或右孩子的节点
        for (Node x : nodes)
            if (!x->lc || !x->rc) slots.push_back(x);
        Node x = slots[randInt(0, slots.size() - 1)];
        if (!x->lc)
            t.attachAsLC(x, s);
        else
            t.attachAsRC(x, s);
        REQUIRE(s == nullptr);
        REQUIRE_EQ((int)t.size(), tsize + ssize);
        checkTree(t);
    }
}

// ======================= 第 12 天 =======================

static void checkTraversal(int kind) {
    for (int round = 0; round < 300; ++round) {
        BinTree<int> t;
        std::vector<Node> nodes;
        grow(t, (int)randInt(0, 80), nodes);
        std::vector<int> expect, got;
        Node r = t.root();
        auto visit = [&](int& e) { got.push_back(e); };
        switch (kind) {
            case 0: refPre(r, expect), travPreR(r, visit); break;
            case 1: refPre(r, expect), travPreI1(r, visit); break;
            case 2: refPre(r, expect), travPreI2(r, visit); break;
            case 3: refIn(r, expect), travInR(r, visit); break;
            case 4: refIn(r, expect), travInI1(r, visit); break;
            case 5: refIn(r, expect), travInI2(r, visit); break;
            case 6: refIn(r, expect), travInI3(r, visit); break;
            case 7: refPost(r, expect), travPostR(r, visit); break;
            case 8: refPost(r, expect), travPostI(r, visit); break;
            case 9: expect = refLevel(r), travLevel(r, visit); break;
        }
        REQUIRE_EQ(got, expect);
    }
}

TEST("D12 travPreR：先序，递归") { checkTraversal(0); }
TEST("D12 travPreI1：先序，迭代版 1") { checkTraversal(1); }
TEST("D12 travPreI2：先序，迭代版 2") { checkTraversal(2); }
TEST("D12 travInR：中序，递归") { checkTraversal(3); }
TEST("D12 travInI1：中序，迭代版 1") { checkTraversal(4); }
TEST("D12 travInI2：中序，迭代版 2") { checkTraversal(5); }
TEST("D12 travInI3：中序，不用栈") { checkTraversal(6); }
TEST("D12 travPostR：后序，递归") { checkTraversal(7); }
TEST("D12 travPostI：后序，迭代") { checkTraversal(8); }
TEST("D12 travLevel：层次遍历") { checkTraversal(9); }

TEST("D12 遍历时可以通过引用修改节点数据") {
    BinTree<int> t;
    std::vector<Node> nodes;
    grow(t, 20, nodes);
    travInI1(t.root(), [](int& e) { e += 100; });
    std::vector<int> v;
    refPre(t.root(), v);
    for (int e : v) REQUIRE(e >= 100);
}

TEST("D12 succ：中序意义下的直接后继") {
    for (int round = 0; round < 300; ++round) {
        BinTree<int> t;
        std::vector<Node> nodes;
        grow(t, (int)randInt(1, 60), nodes);
        std::vector<int> in;
        refIn(t.root(), in);
        std::vector<Node> byData(nodes.size());
        for (Node x : nodes) byData[x->data] = x;
        for (std::size_t i = 0; i < in.size(); ++i) {
            Node s = byData[in[i]]->succ();
            if (i + 1 < in.size())
                REQUIRE(s == byData[in[i + 1]]);
            else
                REQUIRE(s == nullptr);
        }
    }
}

TEST("D12 rebuildPreIn：由先序和中序重构") {
    for (int round = 0; round < 300; ++round) {
        BinTree<int> t;
        std::vector<Node> nodes;
        grow(t, (int)randInt(0, 60), nodes);
        std::vector<int> pre, in, post;
        refPre(t.root(), pre);
        refIn(t.root(), in);
        refPost(t.root(), post);
        std::unique_ptr<BinTree<int>> r(rebuildPreIn(pre, in));
        std::vector<int> p2, i2, q2;
        refPre(r->root(), p2);
        refIn(r->root(), i2);
        refPost(r->root(), q2);
        REQUIRE_EQ(p2, pre);
        REQUIRE_EQ(i2, in);
        REQUIRE_EQ(q2, post);  // 先序 + 中序唯一确定这棵树
        checkTree(*r);
    }
}

TEST("D12 rebuildPrePost：由先序和后序重构真二叉树") {
    for (int round = 0; round < 300; ++round) {
        BinTree<int> t;
        growProper(t, (int)randInt(0, 30));
        std::vector<int> pre, in, post;
        refPre(t.root(), pre);
        refIn(t.root(), in);
        refPost(t.root(), post);
        std::unique_ptr<BinTree<int>> r(rebuildPrePost(pre, post));
        std::vector<int> p2, i2, q2;
        refPre(r->root(), p2);
        refIn(r->root(), i2);
        refPost(r->root(), q2);
        REQUIRE_EQ(p2, pre);
        REQUIRE_EQ(q2, post);
        REQUIRE_EQ(i2, in);  // 对真二叉树，先序 + 后序唯一确定这棵树
        checkTree(*r);
    }
}
