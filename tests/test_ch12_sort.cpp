// 第12章 排序的测试（D34–D36）：快速排序、选取与中位数、希尔排序

#include <algorithm>
#include <vector>

#include "dsa/select.h"
#include "dsa/vector.h"
#include "dsa_test.h"

using namespace dsa;
using dsa_test::randInt;
using dsa_test::randVector;

namespace {

template <typename T>
std::vector<T> toStd(const Vector<T>& V) {
    std::vector<T> v;
    for (Rank i = 0; i < V.size(); ++i) v.push_back(V[i]);
    return v;
}

Vector<int> fromStd(const std::vector<int>& v) { return Vector<int>(v.data(), (Rank)v.size()); }

// 轴点构造的约定：返回 p，[lo, p) 都 <= A[p] <= (p, hi)，且区间里还是原来那些元素，区间外不动
void checkPartition(Rank (Vector<int>::*part)(Rank, Rank)) {
    for (int round = 0; round < 3000; ++round) {
        auto w = randVector(randInt(1, 60), 0, round % 3 == 0 ? 2 : 100);  // 三分之一的轮次几乎全是重复元素
        Vector<int> v = fromStd(w);
        Rank lo = (Rank)randInt(0, w.size() - 1), hi = (Rank)randInt(lo + 1, w.size());
        Rank p = (v.*part)(lo, hi);
        auto got = toStd(v);
        REQUIRE(lo <= p && p < hi);
        for (Rank i = lo; i < p; ++i) REQUIRE(got[i] <= got[p]);
        for (Rank i = p + 1; i < hi; ++i) REQUIRE(got[p] <= got[i]);
        for (Rank i = 0; i < lo; ++i) REQUIRE_EQ(got[i], w[i]);
        for (Rank i = hi; i < w.size(); ++i) REQUIRE_EQ(got[i], w[i]);
        std::sort(got.begin() + lo, got.begin() + hi);
        std::sort(w.begin() + lo, w.begin() + hi);
        REQUIRE_EQ(got, w);
    }
}

void checkSort(void (*sortFn)(Vector<int>&, Rank, Rank)) {
    for (int round = 0; round < 500; ++round) {
        auto w = randVector(randInt(0, 300), 0, round % 3 == 0 ? 3 : 1000000);
        Vector<int> v = fromStd(w);
        Rank lo = (Rank)randInt(0, w.size()), hi = (Rank)randInt(lo, w.size());
        sortFn(v, lo, hi);
        std::sort(w.begin() + lo, w.begin() + hi);
        REQUIRE_EQ(toStd(v), w);
    }
}

// 统计比较次数的元素类型
struct Cmp {
    static long long count;
    int v = 0;
    bool operator<(const Cmp& o) const { return ++count, v < o.v; }
    bool operator<=(const Cmp& o) const { return ++count, v <= o.v; }
    bool operator>(const Cmp& o) const { return ++count, v > o.v; }
    bool operator>=(const Cmp& o) const { return ++count, v >= o.v; }
    bool operator==(const Cmp& o) const { return ++count, v == o.v; }
    bool operator!=(const Cmp& o) const { return ++count, v != o.v; }
};
long long Cmp::count = 0;

// 全是相同元素时不能退化成 O(n^2)：n = 5000 时 O(n log n) 约十几万次比较，O(n^2) 要上千万次
void checkNoDegenerate(void (*sortFn)(Vector<Cmp>&, Rank, Rank)) {
    const Rank n = 5000;
    Vector<Cmp> same(n, n, Cmp{7});
    Cmp::count = 0;
    sortFn(same, 0, n);
    CHECK(Cmp::count < 2000000);  // 不通过说明退化了：轴点构造要用 DUP 版
}

}  // namespace

// ======================= 第 34 天：快速排序 =======================

TEST("D34 partitionLUG：轴点构造") { checkPartition(&Vector<int>::partitionLUG); }
TEST("D34 partitionDUP：轴点构造（应对重复元素）") { checkPartition(&Vector<int>::partitionDUP); }
TEST("D34 partitionLGU：轴点构造") { checkPartition(&Vector<int>::partitionLGU); }
TEST("D34 quickSort：递归版") {
    checkSort([](Vector<int>& v, Rank lo, Rank hi) { v.quickSort(lo, hi); });
    checkNoDegenerate([](Vector<Cmp>& v, Rank lo, Rank hi) { v.quickSort(lo, hi); });
}
TEST("D34 quickSortIter：迭代版") {
    checkSort([](Vector<int>& v, Rank lo, Rank hi) { v.quickSortIter(lo, hi); });
    checkNoDegenerate([](Vector<Cmp>& v, Rank lo, Rank hi) { v.quickSortIter(lo, hi); });
}

// ======================= 第 35 天：选取与中位数 =======================

TEST("D35 majority：众数") {
    int a1[] = {3, 1, 3, 2, 3};
    int got = 0;
    CHECK(majority(Vector<int>(a1, 5), got));
    CHECK_EQ(got, 3);
    int a2[] = {1, 2, 1, 2};
    CHECK(!majority(Vector<int>(a2, 4), got));
    CHECK(!majority(Vector<int>(), got));
    for (int round = 0; round < 3000; ++round) {
        auto w = randVector(randInt(1, 40), 0, round % 2 ? 1 : 4);
        int expect = -1;
        for (int x : w)
            if (2 * std::count(w.begin(), w.end(), x) > (long)w.size()) expect = x;
        int m = -100;
        bool ok = majority(fromStd(w), m);
        REQUIRE_EQ(ok, expect != -1);
        if (ok) REQUIRE_EQ(m, expect);
    }
}

TEST("D35 median：两个有序向量的中位数") {
    for (int round = 0; round < 3000; ++round) {
        auto a = randVector(randInt(0, 30), 0, 50), b = randVector(randInt(a.empty() ? 1 : 0, 30), 0, 50);
        std::sort(a.begin(), a.end());
        std::sort(b.begin(), b.end());
        std::vector<int> all = a;
        all.insert(all.end(), b.begin(), b.end());
        std::sort(all.begin(), all.end());
        REQUIRE_EQ(median(fromStd(a), fromStd(b)), all[all.size() / 2]);
    }
}

TEST("D35 quickSelect：A[k] 就位，前面的都不大于它，后面的都不小于它") {
    for (int round = 0; round < 3000; ++round) {
        auto w = randVector(randInt(1, 60), 0, round % 3 == 0 ? 2 : 100);
        Vector<int> v = fromStd(w);
        Rank k = (Rank)randInt(0, w.size() - 1);
        quickSelect(v, k);
        auto got = toStd(v);
        std::sort(w.begin(), w.end());
        REQUIRE_EQ(got[k], w[k]);
        for (Rank i = 0; i < k; ++i) REQUIRE(got[i] <= got[k]);
        for (Rank i = k + 1; i < got.size(); ++i) REQUIRE(got[k] <= got[i]);
        std::sort(got.begin(), got.end());
        REQUIRE_EQ(got, w);
    }
}

TEST("D35 linearSelect：第 k 小的元素") {
    for (int round = 0; round < 2000; ++round) {
        auto w = randVector(randInt(1, 200), 0, round % 3 == 0 ? 2 : 1000);
        Vector<int> v = fromStd(w);
        Rank k = (Rank)randInt(0, w.size() - 1);
        int got = linearSelect(v, k);
        std::sort(w.begin(), w.end());
        REQUIRE_EQ(got, w[k]);
    }
}

// ======================= 第 36 天：希尔排序 =======================

TEST("D36 shellSort：四种增量序列") {
    for (ShellSeq seq : {ShellSeq::Shell, ShellSeq::PS, ShellSeq::Pratt, ShellSeq::Sedgewick}) {
        for (int round = 0; round < 300; ++round) {
            auto w = randVector(randInt(0, 300), 0, round % 3 == 0 ? 3 : 1000000);
            Vector<int> v = fromStd(w);
            Rank lo = (Rank)randInt(0, w.size()), hi = (Rank)randInt(lo, w.size());
            v.shellSort(lo, hi, seq);
            std::sort(w.begin() + lo, w.begin() + hi);
            REQUIRE_EQ(toStd(v), w);
        }
    }
}
