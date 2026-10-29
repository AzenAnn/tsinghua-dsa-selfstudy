// 第8章 B-树的测试（D22–D23）

#include <algorithm>
#include <functional>
#include <set>
#include <vector>

#include "dsa/btree.h"
#include "dsa_test.h"

using namespace dsa;
using dsa_test::randInt;

namespace {

// 检查 B-树的全部性质，并返回中序遍历的关键码
void checkBTree(BTree<int>& t, const std::set<int>& ref) {
    Rank m = t.order();
    Rank minKeys = (m + 1) / 2 - 1;
    std::vector<int> keys;
    int leafDepth = -1;
    std::function<void(BTNodePosi<int>, int)> go = [&](BTNodePosi<int> v, int depth) {
        REQUIRE_EQ(v->child.size(), v->key.size() + 1);
        REQUIRE(v->key.size() <= m - 1);
        if (v != t.root()) REQUIRE(v->key.size() >= minKeys);
        bool leaf = v->child[0] == nullptr;
        for (Rank i = 0; i < v->child.size(); ++i) {
            REQUIRE_EQ(v->child[i] == nullptr, leaf);  // 叶子的孩子全空，内部节点的孩子全不空
            if (v->child[i]) REQUIRE(v->child[i]->parent == v);
        }
        if (leaf) {
            if (leafDepth == -1) leafDepth = depth;
            REQUIRE_EQ(depth, leafDepth);  // 所有叶子同深
        }
        for (Rank i = 0; i < v->key.size(); ++i) {
            if (!leaf) go(v->child[i], depth + 1);
            keys.push_back(v->key[i]);
        }
        if (!leaf) go(v->child[v->key.size()], depth + 1);
    };
    REQUIRE(t.root() != nullptr);
    REQUIRE(t.root()->parent == nullptr);
    go(t.root(), 0);
    REQUIRE_EQ(keys, std::vector<int>(ref.begin(), ref.end()));
    REQUIRE_EQ((std::size_t)t.size(), ref.size());
}

}  // namespace

// ======================= 第 22 天：查找与插入 =======================

TEST("D22 BTree：空树，只有一个没有关键码的根") {
    BTree<int> t(4);
    CHECK_EQ(t.order(), 4u);
    CHECK(t.empty());
    CHECK(t.root() != nullptr);
    CHECK_EQ(t.root()->key.size(), 0u);
    CHECK(t.search(1) == nullptr);
}

TEST("D22 BTree::insert：顺序插入引起连续分裂，树高增长") {
    BTree<int> t(3);
    std::set<int> ref;
    for (int i = 1; i <= 100; ++i) {
        CHECK(t.insert(i));
        ref.insert(i);
        checkBTree(t, ref);
    }
    CHECK(!t.insert(50));  // 重复
    CHECK(t.root()->child[0] != nullptr);
}

TEST("D22 BTree：各种阶数下随机插入、查找，和 std::set 对拍") {
    for (int round = 0; round < 120; ++round) {
        Rank m = (Rank)randInt(3, 8);
        BTree<int> t(m);
        std::set<int> ref;
        for (int op = 0; op < 300; ++op) {
            int e = (int)randInt(0, 500);
            if (randInt(0, 2)) {
                REQUIRE_EQ(t.insert(e), ref.insert(e).second);
                checkBTree(t, ref);
            } else {
                BTNodePosi<int> v = t.search(e);
                REQUIRE_EQ(v != nullptr, ref.count(e) == 1);
                if (v) {
                    bool has = false;
                    for (Rank i = 0; i < v->key.size(); ++i) has |= v->key[i] == e;
                    REQUIRE(has);
                }
            }
        }
    }
}

// ======================= 第 23 天：删除 =======================

TEST("D23 BTree::remove：随机插入、删除交替进行，每一步都检查 B-树性质") {
    for (int round = 0; round < 120; ++round) {
        Rank m = (Rank)randInt(3, 8);
        BTree<int> t(m);
        std::set<int> ref;
        for (int op = 0; op < 400; ++op) {
            int e = (int)randInt(0, 200);
            if (randInt(0, 1))
                REQUIRE_EQ(t.insert(e), ref.insert(e).second);
            else
                REQUIRE_EQ(t.remove(e), ref.erase(e) == 1);
            checkBTree(t, ref);
        }
    }
}

TEST("D23 BTree::remove：全部删光后树高降回 0") {
    BTree<int> t(3);
    std::set<int> ref;
    for (int i = 0; i < 200; ++i) {
        t.insert(i);
        ref.insert(i);
    }
    std::vector<int> order(ref.begin(), ref.end());
    for (int i = (int)order.size() - 1; i > 0; --i) std::swap(order[i], order[randInt(0, i)]);
    for (int x : order) {
        REQUIRE(t.remove(x));
        ref.erase(x);
        checkBTree(t, ref);
    }
    CHECK(t.empty());
    CHECK(t.root()->child[0] == nullptr);
}
