// 第7章 二叉搜索树和 AVL 树的测试（D19–D20）

#include <algorithm>
#include <cmath>
#include <functional>
#include <set>
#include <vector>

#include "dsa/avl.h"
#include "dsa/bst.h"
#include "dsa_test.h"

using namespace dsa;
using dsa_test::randInt;

namespace {

using Node = BinNodePosi<int>;

int realHeight(Node x) { return x ? 1 + std::max(realHeight(x->lc), realHeight(x->rc)) : -1; }

// 检查：中序遍历和 std::set 一致（因而有序）、父指针正确、记录的高度正确、规模正确；avl 时还检查平衡
template <typename Tree>
void checkTree(Tree& t, const std::set<int>& ref, bool avl) {
    std::vector<int> in;
    std::function<void(Node)> go = [&](Node x) {
        if (!x) return;
        if (x->lc) REQUIRE(x->lc->parent == x);
        if (x->rc) REQUIRE(x->rc->parent == x);
        REQUIRE_EQ(x->height, realHeight(x));
        if (avl) REQUIRE(std::abs(realHeight(x->lc) - realHeight(x->rc)) <= 1);
        go(x->lc);
        in.push_back(x->data);
        go(x->rc);
    };
    if (t.root()) REQUIRE(t.root()->parent == nullptr);
    go(t.root());
    REQUIRE_EQ(in, std::vector<int>(ref.begin(), ref.end()));
    REQUIRE_EQ((std::size_t)t.size(), ref.size());
}

template <typename Tree>
void randomOps(bool avl, int rounds, int ops, int range) {
    for (int round = 0; round < rounds; ++round) {
        Tree t;
        std::set<int> ref;
        for (int op = 0; op < ops; ++op) {
            int e = (int)randInt(0, range);
            int kind = (int)randInt(0, 2);
            if (kind == 0) {
                Node x = t.insert(e);
                REQUIRE(x != nullptr);
                REQUIRE_EQ(x->data, e);
                ref.insert(e);
            } else if (kind == 1) {
                REQUIRE_EQ(t.remove(e), ref.erase(e) == 1);
            } else {
                Node x = t.search(e);
                REQUIRE_EQ(x != nullptr, ref.count(e) == 1);
                if (x) REQUIRE_EQ(x->data, e);
            }
            checkTree(t, ref, avl);
        }
    }
}

}  // namespace

// ======================= 第 19 天：BST =======================

TEST("D19 BST::search：命中时返回该节点，_hot 是它的父亲；失败时 _hot 是假想新节点的父亲") {
    BST<int> t;
    CHECK(t.search(5) == nullptr);
    CHECK(t.hot() == nullptr);
    for (int e : {50, 30, 70, 20, 40, 60, 80}) t.insert(e);
    Node x = t.search(40);
    CHECK(x && x->data == 40);
    CHECK(t.hot() && t.hot()->data == 30);
    CHECK(t.search(50) == t.root());
    CHECK(t.hot() == nullptr);
    CHECK(t.search(65) == nullptr);
    CHECK(t.hot() && t.hot()->data == 60);
    for (int round = 0; round < 300; ++round) {
        BST<int> u;
        std::set<int> ref;
        for (int i = 0; i < 40; ++i) ref.insert((int)u.insert((int)randInt(0, 100))->data);
        int e = (int)randInt(-1, 101);
        Node r = u.search(e);
        Node h = u.hot();
        if (ref.count(e)) {
            REQUIRE(r && r->data == e && r->parent == h);
        } else {
            REQUIRE(r == nullptr);
            REQUIRE(h != nullptr);
            REQUIRE(e < h->data ? h->lc == nullptr : h->rc == nullptr);
        }
    }
}

TEST("D19 BST::insert：插入已有的元素时什么也不做") {
    BST<int> t;
    Node a = t.insert(5);
    Node b = t.insert(5);
    CHECK(a == b);
    CHECK_EQ(t.size(), 1u);
}

TEST("D19 BST：随机插入、删除、查找，和 std::set 对拍") { randomOps<BST<int>>(false, 100, 300, 60); }

TEST("D19 BST::remove：删除有两个孩子的节点（用直接后继替代）") {
    BST<int> t;
    std::set<int> ref;
    for (int e : {50, 30, 70, 20, 40, 60, 80, 35, 45, 65}) {
        t.insert(e);
        ref.insert(e);
    }
    for (int e : {30, 50, 70}) {
        CHECK(t.remove(e));
        ref.erase(e);
        checkTree(t, ref, false);
    }
    CHECK(!t.remove(999));
}

// ======================= 第 20 天：AVL =======================

TEST("D20 AVL：随机插入、删除、查找，每一步都保持平衡") { randomOps<AVL<int>>(true, 100, 300, 60); }

TEST("D20 AVL：顺序插入 1..n，高度仍是 O(log n)") {
    AVL<int> t;
    std::set<int> ref;
    const int n = 4095;
    for (int i = 1; i <= n; ++i) {
        t.insert(i);
        ref.insert(i);
    }
    checkTree(t, ref, true);
    CHECK(t.root()->height <= (int)(1.44 * std::log2(n + 2)));
    for (int i = 1; i <= n; i += 2) {  // 删掉一半
        t.remove(i);
        ref.erase(i);
    }
    checkTree(t, ref, true);
}

TEST("D20 AVL：插入后的四种失衡（zig-zig、zig-zag、zag-zig、zag-zag）") {
    for (auto seq : std::vector<std::vector<int>>{{3, 2, 1}, {3, 1, 2}, {1, 3, 2}, {1, 2, 3}}) {
        AVL<int> t;
        std::set<int> ref;
        for (int e : seq) {
            t.insert(e);
            ref.insert(e);
        }
        checkTree(t, ref, true);
        CHECK_EQ(t.root()->data, 2);
    }
}
