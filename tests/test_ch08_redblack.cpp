// 第8章 红黑树的测试（D24–D25）

#include <algorithm>
#include <cmath>
#include <functional>
#include <set>
#include <vector>

#include "dsa/redblack.h"
#include "dsa_test.h"

using namespace dsa;
using dsa_test::randInt;

namespace {

using Node = BinNodePosi<int>;

// 检查红黑树的全部性质，以及 height 字段确实是黑高度
void checkRB(RedBlack<int>& t, const std::set<int>& ref) {
    std::vector<int> in;
    // 返回 x 的黑高度（空节点为 -1）
    std::function<int(Node)> go = [&](Node x) -> int {
        if (!x) return -1;
        if (x->lc) REQUIRE(x->lc->parent == x);
        if (x->rc) REQUIRE(x->rc->parent == x);
        if (isRed(x)) REQUIRE(isBlack(x->lc) && isBlack(x->rc));  // 红节点的孩子都是黑的
        int hl = go(x->lc);
        in.push_back(x->data);
        int hr = go(x->rc);
        REQUIRE_EQ(hl, hr);  // 各条路径上的黑节点数相同
        int bh = hl + (isBlack(x) ? 1 : 0);
        REQUIRE_EQ(x->height, bh);
        return bh;
    };
    if (t.root()) {
        REQUIRE(t.root()->parent == nullptr);
        REQUIRE(isBlack(t.root()));  // 树根是黑的
    }
    go(t.root());
    REQUIRE_EQ(in, std::vector<int>(ref.begin(), ref.end()));
    REQUIRE_EQ((std::size_t)t.size(), ref.size());
}

int realHeight(Node x) { return x ? 1 + std::max(realHeight(x->lc), realHeight(x->rc)) : -1; }

}  // namespace

// ======================= 第 24 天：插入 =======================

TEST("D24 RedBlack::insert：随机插入，每一步都检查红黑性质") {
    for (int round = 0; round < 150; ++round) {
        RedBlack<int> t;
        std::set<int> ref;
        for (int op = 0; op < 300; ++op) {
            int e = (int)randInt(0, 400);
            Node x = t.insert(e);
            REQUIRE(x && x->data == e);
            ref.insert(e);
            checkRB(t, ref);
        }
    }
}

TEST("D24 RedBlack::insert：顺序插入，树高不超过 2 log2(n+1)") {
    RedBlack<int> t;
    std::set<int> ref;
    const int n = 5000;
    for (int i = 0; i < n; ++i) {
        t.insert(i);
        ref.insert(i);
    }
    checkRB(t, ref);
    CHECK(realHeight(t.root()) <= 2 * std::log2(n + 1));
}

// ======================= 第 25 天：删除 =======================

TEST("D25 RedBlack::remove：随机插入、删除交替进行，每一步都检查红黑性质") {
    for (int round = 0; round < 150; ++round) {
        RedBlack<int> t;
        std::set<int> ref;
        for (int op = 0; op < 400; ++op) {
            int e = (int)randInt(0, 150);
            if (randInt(0, 1)) {
                t.insert(e);
                ref.insert(e);
            } else {
                REQUIRE_EQ(t.remove(e), ref.erase(e) == 1);
            }
            checkRB(t, ref);
        }
    }
}

TEST("D25 RedBlack::remove：全部删光") {
    RedBlack<int> t;
    std::set<int> ref;
    for (int i = 0; i < 500; ++i) {
        t.insert(i * 7 % 500);
        ref.insert(i * 7 % 500);
    }
    for (int i = 0; i < 500; ++i) {
        REQUIRE(t.remove(i * 13 % 500));
        ref.erase(i * 13 % 500);
        checkRB(t, ref);
    }
    CHECK(t.root() == nullptr);
}
