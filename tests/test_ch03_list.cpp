// 第3章 列表的测试（D06–D07）

#include <algorithm>
#include <list>
#include <vector>

#include "dsa/list.h"
#include "dsa_test.h"

using dsa::List;
using dsa::ListNodePosi;
using dsa::Rank;
using dsa_test::randInt;
using dsa_test::randVector;

namespace {

// 从首节点顺着 succ 走一遍，同时检查 pred 指针是否一致、节点数是否等于 size()
template <typename T>
std::vector<T> toStd(const List<T>& L) {
    std::vector<T> v;
    ListNodePosi<T> p = L.first();
    for (Rank i = 0; i < L.size(); ++i) {
        REQUIRE(L.valid(p));
        REQUIRE(p->succ->pred == p);
        v.push_back(p->data);
        p = p->succ;
    }
    REQUIRE(!L.valid(p));  // 走完 size() 个节点后应该正好到 trailer
    return v;
}

template <typename T>
void fill(List<T>& L, const std::vector<T>& v) {
    for (const T& x : v) L.insertAsLast(x);
}

template <typename T>
ListNodePosi<T> nodeAt(const List<T>& L, Rank r) {
    ListNodePosi<T> p = L.first();
    while (r--) p = p->succ;
    return p;
}

struct Item {
    int key = 0, id = 0;
    bool operator<(const Item& o) const { return key < o.key; }
    bool operator>(const Item& o) const { return key > o.key; }
    bool operator<=(const Item& o) const { return key <= o.key; }
    bool operator>=(const Item& o) const { return key >= o.key; }
    bool operator==(const Item& o) const { return key == o.key; }
    bool operator!=(const Item& o) const { return key != o.key; }
};

}  // namespace

// ======================= 第 6 天：列表 =======================

TEST("D06 空列表：只有两个哨兵") {
    List<int> L;
    CHECK_EQ(L.size(), 0u);
    CHECK(L.empty());
    CHECK(!L.valid(L.first()));
    CHECK(!L.valid(L.last()));
    CHECK(L.first()->pred == L.last());  // first() 是 trailer，last() 是 header
}

TEST("D06 insertAsFirst / insertAsLast / insert 前驱后继") {
    List<int> L;
    auto p2 = L.insertAsLast(2);
    L.insertAsFirst(1);
    L.insertAsLast(4);
    CHECK_EQ(L.insert(p2, 3)->data, 3);   // 作为 p2 的后继
    CHECK_EQ(L.insert(0, L.first())->data, 0);  // 作为首节点的前驱
    CHECK_EQ(toStd(L), (std::vector<int>{0, 1, 2, 3, 4}));
    CHECK_EQ(L.size(), 5u);
    CHECK_EQ(L[0], 0);
    CHECK_EQ(L[4], 4);
    L[2] = 20;
    CHECK_EQ(L[2], 20);
}

TEST("D06 remove 和随机操作序列：和 std::list 对拍") {
    for (int round = 0; round < 50; ++round) {
        List<int> L;
        std::vector<int> w;  // 用 vector 当参考，按秩操作
        for (int op = 0; op < 1500; ++op) {
            int kind = (int)randInt(0, 9);
            if (kind < 6 || w.empty()) {
                int e = (int)randInt(-100, 100);
                Rank r = (Rank)randInt(0, w.size());
                if (r == w.size())
                    L.insertAsLast(e);
                else if (randInt(0, 1))
                    L.insert(e, nodeAt(L, r));
                else if (r == 0)
                    L.insertAsFirst(e);
                else
                    L.insert(nodeAt(L, r - 1), e);
                w.insert(w.begin() + r, e);
            } else {
                Rank r = (Rank)randInt(0, w.size() - 1);
                REQUIRE_EQ(L.remove(nodeAt(L, r)), w[r]);
                w.erase(w.begin() + r);
            }
            REQUIRE_EQ(L.size(), (Rank)w.size());
        }
        REQUIRE_EQ(toStd(L), w);
    }
}

TEST("D06 复制构造：整个列表、从秩 r 起的 n 个、从节点 p 起的 n 个（深复制）") {
    List<int> L;
    fill(L, {1, 2, 3, 4, 5, 6});
    List<int> A(L);
    CHECK_EQ(toStd(A), (std::vector<int>{1, 2, 3, 4, 5, 6}));
    A.first()->data = 100;
    CHECK_EQ(L[0], 1);
    List<int> B(L, 2, 3);
    CHECK_EQ(toStd(B), (std::vector<int>{3, 4, 5}));
    List<int> C(nodeAt(L, 4), 2);
    CHECK_EQ(toStd(C), (std::vector<int>{5, 6}));
    List<int> D(L, 6, 0);
    CHECK_EQ(D.size(), 0u);
}

TEST("D06 find：在 p 的 n 个真前驱中找最后一个等于 e 的") {
    List<int> L;
    fill(L, {3, 1, 4, 1, 5, 9, 2, 6});
    CHECK(L.find(1) == nodeAt(L, 3));
    CHECK(L.find(7) == nullptr);
    CHECK(L.find(1, 3, nodeAt(L, 3)) == nodeAt(L, 1));  // 只看 3 1 4
    CHECK(L.find(9, 2, nodeAt(L, 5)) == nullptr);       // 只看 1 5
    for (int round = 0; round < 1000; ++round) {
        auto w = randVector(randInt(1, 30), 0, 9);
        List<int> M;
        fill(M, w);
        Rank pr = (Rank)randInt(0, w.size());  // p 的秩，等于 size 时 p 是 trailer
        Rank n = (Rank)randInt(0, pr);
        ListNodePosi<int> p = pr == w.size() ? M.last()->succ : nodeAt(M, pr);
        int e = (int)randInt(0, 10);
        ListNodePosi<int> expect = nullptr;
        for (Rank i = pr - n; i < pr; ++i)
            if (w[i] == e) expect = nodeAt(M, i);
        REQUIRE(M.find(e, n, p) == expect);
    }
}

TEST("D06 dedup：删掉前面的重复，保留每个值最后一次出现的") {
    for (int round = 0; round < 1000; ++round) {
        auto w = randVector(randInt(0, 50), 0, round % 2 ? 5 : 100);
        List<int> L;
        fill(L, w);
        std::vector<int> expect;
        for (std::size_t i = 0; i < w.size(); ++i)
            if (std::find(w.begin() + i + 1, w.end(), w[i]) == w.end()) expect.push_back(w[i]);
        REQUIRE_EQ(L.dedup(), (Rank)(w.size() - expect.size()));
        REQUIRE_EQ(toStd(L), expect);
    }
}

static void tripleIt(int& x) { x *= 3; }

TEST("D06 traverse：函数指针和 lambda") {
    List<int> L;
    fill(L, {1, 2, 3});
    L.traverse(tripleIt);
    CHECK_EQ(toStd(L), (std::vector<int>{3, 6, 9}));
    int sum = 0;
    L.traverse([&](int& x) { sum += x; });
    CHECK_EQ(sum, 18);
}

// ======================= 第 7 天：有序列表与排序 =======================

TEST("D07 uniquify：有序去重") {
    for (int round = 0; round < 1000; ++round) {
        auto w = randVector(randInt(0, 60), 0, round % 2 ? 5 : 1000);
        std::sort(w.begin(), w.end());
        List<int> L;
        fill(L, w);
        auto expect = w;
        expect.erase(std::unique(expect.begin(), expect.end()), expect.end());
        REQUIRE_EQ(L.uniquify(), (Rank)(w.size() - expect.size()));
        REQUIRE_EQ(toStd(L), expect);
    }
}

TEST("D07 search：在 p 的 n 个真前驱中找最后一个不大于 e 的") {
    for (int round = 0; round < 2000; ++round) {
        auto w = randVector(randInt(0, 30), 0, 20);
        std::sort(w.begin(), w.end());
        List<int> L;
        fill(L, w);
        Rank pr = (Rank)randInt(0, w.size());
        Rank n = (Rank)randInt(0, pr);
        ListNodePosi<int> p = pr == w.size() ? L.last()->succ : nodeAt(L, pr);
        int e = (int)randInt(-1, 21);
        // 期望：区间 [pr - n, pr) 里最后一个 <= e 的；都比 e 大时是区间前面那个节点
        long long idx = (long long)pr - n - 1;
        for (Rank i = pr - n; i < pr; ++i)
            if (w[i] <= e) idx = i;
        ListNodePosi<int> expect = idx < 0 ? L.first()->pred : nodeAt(L, (Rank)idx);
        REQUIRE(L.search(e, n, p) == expect);
    }
}

TEST("D07 selectMax：最大者有多个时返回最后一个") {
    List<int> L;
    fill(L, {3, 7, 1, 7, 2});
    CHECK(L.selectMax() == nodeAt(L, 3));
    CHECK(L.selectMax(L.first(), 2) == nodeAt(L, 1));
    CHECK(L.selectMax(nodeAt(L, 4), 1) == nodeAt(L, 4));
}

static void checkListSort(int which) {
    for (int round = 0; round < 400; ++round) {
        auto w = randVector(randInt(0, 120), -50, round % 2 ? 50 : 100000);
        List<int> L;
        fill(L, w);
        Rank r = (Rank)randInt(0, w.size()), n = (Rank)randInt(0, w.size() - r);
        ListNodePosi<int> p = r == w.size() ? L.last()->succ : nodeAt(L, r);
        if (which == 0) L.insertionSort(p, n);
        if (which == 1) L.selectionSort(p, n);
        if (which == 2) L.mergeSort(p, n);
        if (which == 3) L.sort(p, n);
        std::sort(w.begin() + r, w.begin() + r + n);
        REQUIRE_EQ(toStd(L), w);
    }
}

static void checkListStable(int which) {
    for (int round = 0; round < 300; ++round) {
        std::vector<Item> w(randInt(0, 80));
        for (std::size_t i = 0; i < w.size(); ++i) w[i] = Item{(int)randInt(0, 4), (int)i};
        List<Item> L;
        fill(L, w);
        ListNodePosi<Item> p = L.first();
        if (which == 0) L.insertionSort(p, L.size());
        if (which == 1) L.selectionSort(p, L.size());
        if (which == 2) L.mergeSort(p, L.size());
        std::stable_sort(w.begin(), w.end());
        auto got = toStd(L);
        for (std::size_t i = 0; i < w.size(); ++i) REQUIRE_EQ(got[i].id, w[i].id);
    }
}

TEST("D07 insertionSort：对拍、只排指定的一段") { checkListSort(0); }
TEST("D07 insertionSort：稳定") { checkListStable(0); }
TEST("D07 selectionSort：对拍、只排指定的一段") { checkListSort(1); }
TEST("D07 selectionSort：稳定") { checkListStable(1); }
TEST("D07 mergeSort：对拍、只排指定的一段") { checkListSort(2); }
TEST("D07 mergeSort：稳定") { checkListStable(2); }
TEST("D07 sort：统一入口") { checkListSort(3); }

TEST("D07 mergeSort：p 被更新为这一段新的首节点") {
    List<int> L;
    fill(L, {9, 5, 7, 1, 3});
    ListNodePosi<int> p = nodeAt(L, 1);
    L.mergeSort(p, 3);
    CHECK_EQ(p->data, 1);
    CHECK_EQ(toStd(L), (std::vector<int>{9, 1, 5, 7, 3}));
}

TEST("D07 merge：归并两个有序列表，L 变空") {
    for (int round = 0; round < 500; ++round) {
        auto a = randVector(randInt(0, 40), 0, 50), b = randVector(randInt(0, 40), 0, 50);
        std::sort(a.begin(), a.end());
        std::sort(b.begin(), b.end());
        List<int> A, B;
        fill(A, a);
        fill(B, b);
        A.merge(B);
        std::vector<int> expect;
        std::merge(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(expect));
        REQUIRE_EQ(toStd(A), expect);
        REQUIRE_EQ(B.size(), 0u);
        REQUIRE(B.empty());
    }
}

TEST("D07 reverse：前后倒置") {
    for (int round = 0; round < 300; ++round) {
        auto w = randVector(randInt(0, 30), 0, 99);
        List<int> L;
        fill(L, w);
        L.reverse();
        std::reverse(w.begin(), w.end());
        REQUIRE_EQ(toStd(L), w);
        L.insertAsFirst(-1);  // 倒置后还能正常插入
        L.insertAsLast(-2);
        REQUIRE_EQ(L.size(), (Rank)w.size() + 2);
    }
}
