// 第2章 向量的测试（D03–D05）。堆排序、快速排序、希尔排序的测试在第10、12章。

#include <algorithm>
#include <numeric>
#include <vector>

#include "dsa/vector.h"
#include "dsa_test.h"

using dsa::Rank;
using dsa::Vector;
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

// 统计赋值次数的元素类型，用来检查扩容的分摊复杂度
struct Counted {
    static long long assigns;
    int v = 0;
    Counted() = default;
    Counted(int x) : v(x) {}
    Counted(const Counted& o) : v(o.v) { ++assigns; }
    Counted& operator=(const Counted& o) {
        v = o.v;
        ++assigns;
        return *this;
    }
};
long long Counted::assigns = 0;

// 只用来测试第 3 天的 expand / shrink：借派生类调用受保护的成员
template <typename T>
struct Probe : Vector<T> {
    explicit Probe(Rank c = dsa::DEFAULT_CAPACITY) : Vector<T>(c) {}
    void push(const T& e) {
        this->expand();
        this->_elem[this->_size++] = e;
    }
    void pop() {
        this->_size--;
        this->shrink();
    }
};

// 稳定性测试用：只按 key 比较，id 记录原来的顺序
struct Item {
    int key = 0, id = 0;
    bool operator<(const Item& o) const { return key < o.key; }
    bool operator>(const Item& o) const { return key > o.key; }
    bool operator<=(const Item& o) const { return key <= o.key; }
    bool operator>=(const Item& o) const { return key >= o.key; }
    bool operator==(const Item& o) const { return key == o.key; }
    bool operator!=(const Item& o) const { return key != o.key; }
};

std::vector<int> sortedRandom(std::size_t n, int lo, int hi) {
    auto v = randVector(n, lo, hi);
    std::sort(v.begin(), v.end());
    return v;
}

}  // namespace

// ======================= 第 3 天：构造、析构、动态空间 =======================

TEST("D03 构造：默认构造、(c, s, v)、数组、数组区间") {
    Vector<int> a;
    CHECK_EQ(a.size(), 0u);
    CHECK(a.empty());
    Vector<int> b(10, 4, 7);
    CHECK_EQ(toStd(b), (std::vector<int>{7, 7, 7, 7}));
    CHECK(b.capacity() >= b.size());
    int A[] = {5, 1, 4, 2, 3};
    Vector<int> c(A, 5);
    CHECK_EQ(toStd(c), (std::vector<int>{5, 1, 4, 2, 3}));
    Vector<int> d(A, 1, 4);
    CHECK_EQ(toStd(d), (std::vector<int>{1, 4, 2}));
    Vector<int> e(A, 2, 2);
    CHECK_EQ(e.size(), 0u);
}

TEST("D03 构造：复制整个向量和向量区间（深复制）") {
    int A[] = {1, 2, 3, 4, 5, 6};
    Vector<int> v(A, 6);
    Vector<int> w(v);
    CHECK_EQ(toStd(w), toStd(v));
    w[0] = 100;  // 改副本不能影响原向量
    CHECK_EQ(v[0], 1);
    Vector<int> x(v, 2, 5);
    CHECK_EQ(toStd(x), (std::vector<int>{3, 4, 5}));
}

TEST("D03 operator[] 可读可写，operator= 是深复制且能自赋值") {
    int A[] = {1, 2, 3};
    Vector<int> v(A, 3);
    v[1] = 20;
    const Vector<int>& cv = v;
    CHECK_EQ(cv[1], 20);
    Vector<int> w;
    w = v;
    CHECK_EQ(toStd(w), (std::vector<int>{1, 20, 3}));
    w[2] = 30;
    CHECK_EQ(v[2], 3);
    w = w;  // 自赋值
    CHECK_EQ(toStd(w), (std::vector<int>{1, 20, 30}));
    Vector<int> big(100, 100, 9);
    w = big;  // 从小变大
    CHECK_EQ(w.size(), 100u);
    CHECK_EQ(w[99], 9);
}

TEST("D03 expand：容量加倍，n 次追加的总复制次数是 O(n)") {
    Probe<Counted> p;
    const int n = 20000;
    Counted::assigns = 0;
    for (int i = 0; i < n; ++i) {
        p.push(Counted(i));
        REQUIRE(p.capacity() >= p.size());
    }
    // 加倍扩容时总复制次数约 2n；每次只加一个常数的话会是 O(n^2)，远超这个上限
    CHECK(Counted::assigns <= 4LL * n);
    CHECK(p.capacity() < 2 * (Rank)n + 2 * dsa::DEFAULT_CAPACITY);
    for (int i = 0; i < n; ++i) REQUIRE_EQ(p[i].v, i);
}

TEST("D03 expand：初始容量为 0 也能正常扩容") {
    Probe<int> p(0);
    for (int i = 0; i < 100; ++i) p.push(i);
    CHECK_EQ(p.size(), 100u);
    CHECK_EQ(p[99], 99);
}

TEST("D03 shrink：装填因子低于 25% 时缩容，但不低于 2 倍默认容量") {
    Probe<int> p;
    for (int i = 0; i < 1000; ++i) p.push(i);
    Rank big = p.capacity();
    while (p.size() > 10) p.pop();
    CHECK(p.capacity() < big);
    CHECK(p.capacity() <= 64);
    CHECK(p.capacity() >= p.size());
    while (p.size() > 0) p.pop();
    CHECK(p.capacity() >= dsa::DEFAULT_CAPACITY);
    for (int i = 0; i < 10; ++i) p.push(i);  // 缩容后还能正常扩容
    for (int i = 0; i < 10; ++i) REQUIRE_EQ(p[i], i);
}

// ======================= 第 4 天：无序向量 =======================

TEST("D04 insert：插到开头、中间、末尾，返回插入的秩") {
    Vector<int> v;
    CHECK_EQ(v.insert(0, 2), 0u);
    CHECK_EQ(v.insert(0, 1), 0u);
    CHECK_EQ(v.insert(2, 4), 2u);
    CHECK_EQ(v.insert(2, 3), 2u);
    CHECK_EQ(v.insert(5), 4u);
    CHECK_EQ(toStd(v), (std::vector<int>{1, 2, 3, 4, 5}));
}

TEST("D04 remove：单个元素和区间") {
    int A[] = {0, 1, 2, 3, 4, 5, 6, 7};
    Vector<int> v(A, 8);
    CHECK_EQ(v.remove(0), 0);
    CHECK_EQ(v.remove(2, 5), 3u);
    CHECK_EQ(toStd(v), (std::vector<int>{1, 2, 6, 7}));
    CHECK_EQ(v.remove(1, 1), 0u);
    CHECK_EQ(v.remove(3), 7);
    CHECK_EQ(toStd(v), (std::vector<int>{1, 2, 6}));
}

TEST("D04 insert / remove：随机操作序列和 std::vector 对拍") {
    for (int round = 0; round < 50; ++round) {
        Vector<int> v;
        std::vector<int> w;
        for (int op = 0; op < 2000; ++op) {
            int kind = (int)randInt(0, 9);
            if (kind < 5 || w.empty()) {
                Rank r = (Rank)randInt(0, w.size());
                int e = (int)randInt(-1000, 1000);
                REQUIRE_EQ(v.insert(r, e), r);
                w.insert(w.begin() + r, e);
            } else if (kind < 8) {
                Rank r = (Rank)randInt(0, w.size() - 1);
                REQUIRE_EQ(v.remove(r), w[r]);
                w.erase(w.begin() + r);
            } else {
                Rank lo = (Rank)randInt(0, w.size()), hi = (Rank)randInt(lo, std::min(w.size(), (std::size_t)lo + 20));
                REQUIRE_EQ(v.remove(lo, hi), hi - lo);
                w.erase(w.begin() + lo, w.begin() + hi);
            }
            REQUIRE_EQ(v.size(), (Rank)w.size());
            REQUIRE(v.capacity() >= v.size());
        }
        REQUIRE_EQ(toStd(v), w);
    }
}

TEST("D04 find：返回区间里最后一个等于 e 的秩，失败返回 lo - 1") {
    int A[] = {3, 1, 4, 1, 5, 9, 2, 6};
    Vector<int> v(A, 8);
    CHECK_EQ(v.find(1), 3u);
    CHECK_EQ(v.find(3), 0u);
    CHECK_EQ(v.find(7), Rank(-1));
    CHECK_EQ(v.find(1, 0, 3), 1u);
    CHECK_EQ(v.find(9, 2, 5), 1u);  // 失败：lo - 1 = 1
    Vector<int> empty;
    CHECK_EQ(empty.find(1), Rank(-1));
    for (int round = 0; round < 2000; ++round) {
        auto w = randVector(randInt(0, 30), 0, 9);
        Vector<int> u = fromStd(w);
        int e = (int)randInt(0, 10);
        Rank lo = (Rank)randInt(0, w.size()), hi = (Rank)randInt(lo, w.size());
        Rank expect = lo - 1;
        for (Rank i = lo; i < hi; ++i)
            if (w[i] == e) expect = i;
        REQUIRE_EQ(u.find(e, lo, hi), expect);
    }
}

TEST("D04 dedup：每个值只保留第一次出现的，返回删除的个数") {
    for (int round = 0; round < 1000; ++round) {
        auto w = randVector(randInt(0, 60), 0, round % 2 ? 5 : 100);
        Vector<int> v = fromStd(w);
        std::vector<int> expect;
        for (int x : w)
            if (std::find(expect.begin(), expect.end(), x) == expect.end()) expect.push_back(x);
        REQUIRE_EQ(v.dedup(), (Rank)(w.size() - expect.size()));
        REQUIRE_EQ(toStd(v), expect);
    }
}

TEST("D04 unsort / permute：结果是原来元素的一个排列，而且确实被打乱了") {
    std::vector<int> w(200);
    std::iota(w.begin(), w.end(), 0);
    Vector<int> v = fromStd(w);
    v.unsort();
    auto got = toStd(v);
    CHECK(got != w);
    std::sort(got.begin(), got.end());
    CHECK_EQ(got, w);

    Vector<int> u = fromStd(w);
    u.unsort(50, 150);  // 只打乱中间一段
    auto g2 = toStd(u);
    CHECK(std::equal(g2.begin(), g2.begin() + 50, w.begin()));
    CHECK(std::equal(g2.begin() + 150, g2.end(), w.begin() + 150));
    std::sort(g2.begin() + 50, g2.begin() + 150);
    CHECK_EQ(g2, w);

    Vector<int> p = fromStd(w);
    dsa::permute(p);
    auto g3 = toStd(p);
    CHECK(g3 != w);
    std::sort(g3.begin(), g3.end());
    CHECK_EQ(g3, w);
}

static void doubleIt(int& x) { x *= 2; }

TEST("D04 traverse：函数指针和 lambda 两种") {
    int A[] = {1, 2, 3, 4};
    Vector<int> v(A, 4);
    v.traverse(doubleIt);
    CHECK_EQ(toStd(v), (std::vector<int>{2, 4, 6, 8}));
    int sum = 0;
    v.traverse([&](int& x) { sum += x; });
    CHECK_EQ(sum, 20);
    v.traverse([](int& x) { x += 1; });
    CHECK_EQ(toStd(v), (std::vector<int>{3, 5, 7, 9}));
}

// ======================= 第 5 天：有序向量与排序 =======================

TEST("D05 disordered：相邻逆序对的个数") {
    int A[] = {1, 3, 2, 5, 4, 4, 0};
    CHECK_EQ(Vector<int>(A, 7).disordered(), 3u);
    CHECK_EQ(Vector<int>(A, 2).disordered(), 0u);
    CHECK_EQ(Vector<int>().disordered(), 0u);
    int B[] = {2, 1};
    CHECK_EQ(Vector<int>(B, 2).disordered(), 1u);
    for (int round = 0; round < 1000; ++round) {
        auto w = randVector(randInt(0, 30), 0, 9);
        Rank expect = 0;
        for (std::size_t i = 1; i < w.size(); ++i) expect += w[i - 1] > w[i];
        REQUIRE_EQ(fromStd(w).disordered(), expect);
    }
}

TEST("D05 uniquify：有序去重，和 std::unique 对拍") {
    for (int round = 0; round < 1000; ++round) {
        auto w = sortedRandom(randInt(0, 80), 0, round % 2 ? 5 : 1000);
        Vector<int> v = fromStd(w);
        auto expect = w;
        expect.erase(std::unique(expect.begin(), expect.end()), expect.end());
        REQUIRE_EQ(v.uniquify(), (Rank)(w.size() - expect.size()));
        REQUIRE_EQ(toStd(v), expect);
    }
}

// A、B 版和 fibSearchA：找到时 V[r] == e，找不到返回 Rank(-1)
static void checkHitOrMiss(Rank (Vector<int>::*f)(const int&, Rank, Rank) const) {
    for (int round = 0; round < 3000; ++round) {
        auto w = sortedRandom(randInt(0, 40), 0, 30);
        Vector<int> v = fromStd(w);
        Rank lo = (Rank)randInt(0, w.size()), hi = (Rank)randInt(lo, w.size());
        int e = (int)randInt(-1, 31);
        Rank r = (v.*f)(e, lo, hi);
        bool present = std::binary_search(w.begin() + lo, w.begin() + hi, e);
        if (present) {
            REQUIRE(lo <= r && r < hi);
            REQUIRE_EQ(w[r], e);
        } else {
            REQUIRE_EQ(r, Rank(-1));
        }
    }
}

// C 版、fibSearchB、search：返回不大于 e 的最后一个元素的秩（都比 e 大时返回 lo - 1）
static void checkNotGreater(Rank (Vector<int>::*f)(const int&, Rank, Rank) const) {
    for (int round = 0; round < 3000; ++round) {
        auto w = sortedRandom(randInt(0, 40), 0, 30);
        Vector<int> v = fromStd(w);
        Rank lo = (Rank)randInt(0, w.size()), hi = (Rank)randInt(lo, w.size());
        int e = (int)randInt(-1, 31);
        Rank expect = (Rank)(std::upper_bound(w.begin() + lo, w.begin() + hi, e) - w.begin()) - 1;
        REQUIRE_EQ((v.*f)(e, lo, hi), expect);
    }
}

TEST("D05 binSearchA") { checkHitOrMiss(&Vector<int>::binSearchA); }
TEST("D05 binSearchB") { checkHitOrMiss(&Vector<int>::binSearchB); }
TEST("D05 fibSearchA") { checkHitOrMiss(&Vector<int>::fibSearchA); }
TEST("D05 binSearchC：返回不大于 e 的最后一个") { checkNotGreater(&Vector<int>::binSearchC); }
TEST("D05 fibSearchB：返回不大于 e 的最后一个") { checkNotGreater(&Vector<int>::fibSearchB); }
TEST("D05 search：统一入口，语义和 C 版相同") {
    checkNotGreater(&Vector<int>::search);
    Vector<int> v;
    for (int round = 0; round < 500; ++round) {  // 用 insert(search(e) + 1, e) 维持有序
        int e = (int)randInt(0, 50);
        v.insert(v.search(e) + 1, e);
        REQUIRE_EQ(v.disordered(), 0u);
    }
}

static void checkSort(void (Vector<int>::*sortFn)(Rank, Rank)) {
    for (int round = 0; round < 500; ++round) {
        auto w = randVector(randInt(0, 200), -50, round % 2 ? 50 : 1000000);
        Vector<int> v = fromStd(w);
        Rank lo = (Rank)randInt(0, w.size()), hi = (Rank)randInt(lo, w.size());
        (v.*sortFn)(lo, hi);
        std::sort(w.begin() + lo, w.begin() + hi);
        REQUIRE_EQ(toStd(v), w);
    }
}

static void checkStable(void (Vector<Item>::*sortFn)(Rank, Rank)) {
    for (int round = 0; round < 300; ++round) {
        std::vector<Item> w(randInt(0, 100));
        for (std::size_t i = 0; i < w.size(); ++i) w[i] = Item{(int)randInt(0, 5), (int)i};
        Vector<Item> v(w.data(), (Rank)w.size());
        (v.*sortFn)(0, v.size());
        std::stable_sort(w.begin(), w.end());
        for (std::size_t i = 0; i < w.size(); ++i) {
            REQUIRE_EQ(v[(Rank)i].key, w[i].key);
            REQUIRE_EQ(v[(Rank)i].id, w[i].id);  // 相等元素保持原来的先后
        }
    }
}

TEST("D05 bubbleSort：和 std::sort 对拍，只排指定区间") { checkSort(&Vector<int>::bubbleSort); }
TEST("D05 bubbleSort：稳定") { checkStable(&Vector<Item>::bubbleSort); }
TEST("D05 mergeSort：和 std::sort 对拍，只排指定区间") { checkSort(&Vector<int>::mergeSort); }
TEST("D05 mergeSort：稳定") { checkStable(&Vector<Item>::mergeSort); }
TEST("D05 sort：统一入口") {
    checkSort(&Vector<int>::sort);
    auto w = randVector(1000, 0, 100);
    Vector<int> v = fromStd(w);
    v.sort();
    CHECK_EQ(v.disordered(), 0u);
}
