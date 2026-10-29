// 第8章 伸展树的测试（D21）

#include <algorithm>
#include <functional>
#include <set>
#include <vector>

#include "dsa/splay.h"
#include "dsa_test.h"

using namespace dsa;
using dsa_test::randInt;

namespace {

using Node = BinNodePosi<int>;
int realHeight(Node x) { return x ? 1 + std::max(realHeight(x->lc), realHeight(x->rc)) : -1; }

void checkTree(Splay<int>& t, const std::set<int>& ref) {
    std::vector<int> in;
    std::function<void(Node)> go = [&](Node x) {
        if (!x) return;
        if (x->lc) REQUIRE(x->lc->parent == x);
        if (x->rc) REQUIRE(x->rc->parent == x);
        REQUIRE_EQ(x->height, realHeight(x));
        go(x->lc);
        in.push_back(x->data);
        go(x->rc);
    };
    if (t.root()) REQUIRE(t.root()->parent == nullptr);
    go(t.root());
    REQUIRE_EQ(in, std::vector<int>(ref.begin(), ref.end()));
    REQUIRE_EQ((std::size_t)t.size(), ref.size());
}

}  // namespace

TEST("D21 Splay：随机插入、删除、查找，和 std::set 对拍") {
    for (int round = 0; round < 100; ++round) {
        Splay<int> t;
        std::set<int> ref;
        for (int op = 0; op < 300; ++op) {
            int e = (int)randInt(0, 60), kind = (int)randInt(0, 2);
            if (kind == 0) {
                Node x = t.insert(e);
                ref.insert(e);
                REQUIRE(x && x->data == e);
                REQUIRE(t.root() == x);  // 插入的节点成为树根
            } else if (kind == 1) {
                REQUIRE_EQ(t.remove(e), ref.erase(e) == 1);
            } else {
                Node r = t.search(e);
                REQUIRE(r == t.root());
                if (ref.count(e)) {
                    REQUIRE(r && r->data == e);  // 命中的节点被伸展到根
                } else if (!ref.empty()) {
                    // 失败时伸展到根的是 e 的前驱或后继
                    auto it = ref.lower_bound(e);
                    bool ok = (it != ref.end() && r->data == *it) || (it != ref.begin() && r->data == *std::prev(it));
                    REQUIRE(ok);
                }
            }
            checkTree(t, ref);
        }
    }
}

TEST("D21 Splay：顺序访问的分摊效率（双层伸展）") {
    // 先顺序插入 1..n（会得到一条链），再顺序访问一遍：双层伸展把总代价压到 O(n)，树高很快减半
    Splay<int> t;
    const int n = 2000;
    for (int i = 1; i <= n; ++i) t.insert(i);
    t.search(1);  // 访问链底的最深节点后，树高应大约减半
    CHECK(t.root()->data == 1);
    CHECK(t.root()->height <= n / 2 + 2);
    std::set<int> ref;
    for (int i = 1; i <= n; ++i) ref.insert(i);
    for (int i = 1; i <= n; ++i) REQUIRE(t.search(i)->data == i);
    checkTree(t, ref);
}
