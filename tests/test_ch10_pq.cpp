// 第10章 优先级队列的测试（D29–D30），以及向量的堆排序

#include <algorithm>
#include <functional>
#include <queue>
#include <vector>

#include "dsa/pq.h"
#include "dsa/vector.h"
#include "dsa_test.h"

using namespace dsa;
using dsa_test::randInt;
using dsa_test::randVector;

namespace {

template <typename T>
bool isHeap(const T* A, Rank n) {
    for (Rank i = 1; i < n; ++i)
        if (A[(i - 1) / 2] < A[i]) return false;
    return true;
}

// 左式堆的性质：堆序、npl 正确、左孩子的 npl 不小于右孩子
int checkLeftist(BinNodePosi<int> x) {
    if (!x) return 0;
    int l = checkLeftist(x->lc), r = checkLeftist(x->rc);
    if (x->lc) REQUIRE(x->lc->parent == x && !(x->data < x->lc->data));
    if (x->rc) REQUIRE(x->rc->parent == x && !(x->data < x->rc->data));
    REQUIRE(l >= r);
    REQUIRE_EQ(x->npl, r + 1);
    return r + 1;
}

}  // namespace

// ======================= 第 29 天：完全二叉堆 =======================

TEST("D29 percolateUp / percolateDown / heapify：作用在数组上") {
    for (int round = 0; round < 1000; ++round) {
        auto v = randVector(randInt(0, 100), 0, round % 2 ? 10 : 100000);
        heapify(v.data(), (Rank)v.size());
        REQUIRE(isHeap(v.data(), (Rank)v.size()));
        if (v.empty()) continue;
        Rank i = (Rank)randInt(0, v.size() - 1);  // 改大一个元素再上滤
        v[i] += 1000000;
        Rank pos = percolateUp(v.data(), i);
        REQUIRE(isHeap(v.data(), (Rank)v.size()));
        REQUIRE(v[pos] >= 1000000);
        v[0] = -1;  // 改小堆顶再下滤
        pos = percolateDown(v.data(), (Rank)v.size(), 0);
        REQUIRE(isHeap(v.data(), (Rank)v.size()));
        REQUIRE_EQ(v[pos], -1);
    }
}

TEST("D29 PQ_ComplHeap：随机插入、删除，和 std::priority_queue 对拍") {
    for (int round = 0; round < 100; ++round) {
        PQ_ComplHeap<int> H;
        std::priority_queue<int> ref;
        for (int op = 0; op < 1000; ++op) {
            if (ref.empty() || randInt(0, 2)) {
                int e = (int)randInt(0, 500);
                H.insert(e);
                ref.push(e);
            } else {
                REQUIRE_EQ(H.getMax(), ref.top());
                REQUIRE_EQ(H.delMax(), ref.top());
                ref.pop();
            }
            REQUIRE_EQ((std::size_t)H.size(), ref.size());
        }
    }
}

TEST("D29 PQ_ComplHeap：批量建堆后依次 delMax 得到降序序列") {
    for (int round = 0; round < 300; ++round) {
        auto v = randVector(randInt(1, 300), 0, 1000);
        PQ_ComplHeap<int> H(v.data(), (Rank)v.size());
        std::sort(v.begin(), v.end(), std::greater<>());
        for (int x : v) REQUIRE_EQ(H.delMax(), x);
        REQUIRE(H.empty());
    }
}

TEST("D29 Vector::heapSort：就地堆排序，只排指定区间") {
    for (int round = 0; round < 500; ++round) {
        auto w = randVector(randInt(0, 200), -50, round % 2 ? 50 : 1000000);
        Vector<int> v(w.data(), (Rank)w.size());
        Rank lo = (Rank)randInt(0, w.size()), hi = (Rank)randInt(lo, w.size());
        v.heapSort(lo, hi);
        std::sort(w.begin() + lo, w.begin() + hi);
        for (Rank i = 0; i < v.size(); ++i) REQUIRE_EQ(v[i], w[i]);
    }
}

// ======================= 第 30 天：左式堆 =======================

TEST("D30 PQ_LeftHeap：随机插入、删除，和 std::priority_queue 对拍，每步检查左式性质") {
    for (int round = 0; round < 100; ++round) {
        PQ_LeftHeap<int> H;
        std::priority_queue<int> ref;
        for (int op = 0; op < 600; ++op) {
            if (ref.empty() || randInt(0, 2)) {
                int e = (int)randInt(0, 500);
                H.insert(e);
                ref.push(e);
            } else {
                REQUIRE_EQ(H.getMax(), ref.top());
                REQUIRE_EQ(H.delMax(), ref.top());
                ref.pop();
            }
            REQUIRE_EQ((std::size_t)H.size(), ref.size());
            if (H.root()) REQUIRE(H.root()->parent == nullptr);
            checkLeftist(H.root());
        }
    }
}

TEST("D30 PQ_LeftHeap::merge：合并两个堆") {
    for (int round = 0; round < 300; ++round) {
        PQ_LeftHeap<int> A, B;
        std::vector<int> all;
        for (int i = (int)randInt(0, 100); i > 0; --i) {
            int e = (int)randInt(0, 1000);
            A.insert(e);
            all.push_back(e);
        }
        for (int i = (int)randInt(0, 100); i > 0; --i) {
            int e = (int)randInt(0, 1000);
            B.insert(e);
            all.push_back(e);
        }
        A.merge(B);
        REQUIRE(B.empty());
        REQUIRE_EQ(B.size(), 0u);
        REQUIRE_EQ((std::size_t)A.size(), all.size());
        checkLeftist(A.root());
        std::sort(all.begin(), all.end(), std::greater<>());
        for (int x : all) REQUIRE_EQ(A.delMax(), x);
    }
}
