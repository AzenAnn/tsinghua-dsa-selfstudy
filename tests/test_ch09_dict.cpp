// 第9章 词典的测试（D26–D28）

#include <algorithm>
#include <cmath>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "dsa/hashtable.h"
#include "dsa/skiplist.h"
#include "dsa/sort_linear.h"
#include "dsa_test.h"

using namespace dsa;
using dsa_test::randInt;

namespace {

bool isPrime(Rank n) {
    if (n < 2) return false;
    for (Rank d = 2; (unsigned long long)d * d <= n; ++d)
        if (n % d == 0) return false;
    return true;
}

std::string randKey() {
    std::string s(randInt(0, 6), 'a');
    for (auto& c : s) c = (char)randInt('a', 'e');
    return s;
}

// 词典的随机操作和 std::map 对拍
template <typename Dict, typename K, typename Gen>
void dictOps(Dict& d, Gen gen, int ops) {
    std::map<K, int> ref;
    for (int op = 0; op < ops; ++op) {
        K k = gen();
        int kind = (int)randInt(0, 2);
        if (kind == 0) {
            int v = (int)randInt(0, 1000000);
            REQUIRE_EQ(d.put(k, v), ref.count(k) == 0);
            ref[k] = v;
        } else if (kind == 1) {
            REQUIRE_EQ(d.remove(k), ref.erase(k) == 1);
        } else {
            int* v = d.get(k);
            auto it = ref.find(k);
            REQUIRE_EQ(v != nullptr, it != ref.end());
            if (v) REQUIRE_EQ(*v, it->second);
        }
        REQUIRE_EQ((std::size_t)d.size(), ref.size());
    }
    for (auto& [k, v] : ref) {
        int* got = d.get(k);
        REQUIRE(got && *got == v);
    }
}

}  // namespace

// ======================= 第 26 天：跳转表 =======================

TEST("D26 Skiplist：随机 put / get / remove，和 std::map 对拍") {
    for (int round = 0; round < 50; ++round) {
        Skiplist<int, int> s;
        dictOps<Skiplist<int, int>, int>(s, [] { return (int)randInt(0, 300); }, 2000);
    }
    Skiplist<std::string, int> t;
    dictOps<Skiplist<std::string, int>, std::string>(t, randKey, 3000);
}

TEST("D26 Skiplist：层数是 O(log n)，删光后只剩一层") {
    Skiplist<int, int> s;
    CHECK_EQ(s.level(), 1u);
    const int n = 4096;
    for (int i = 0; i < n; ++i) s.put(i, i);
    double lg = std::log2(n);
    CHECK(s.level() >= lg / 2);
    CHECK(s.level() <= 2 * lg + 4);
    for (int i = 0; i < n; ++i) REQUIRE(s.remove(i));
    CHECK_EQ(s.size(), 0u);
    CHECK_EQ(s.level(), 1u);
}

// ======================= 第 27 天：散列表 =======================

TEST("D27 hashCode(string)：不同的串一般散列到不同的值") {
    CHECK(hashCode(std::string("abc")) != hashCode(std::string("acb")));
    CHECK(hashCode(std::string("")) == hashCode(std::string("")));
    std::map<std::size_t, int> seen;
    int collisions = 0;
    for (int i = 0; i < 10000; ++i) collisions += seen[hashCode("key" + std::to_string(i))]++ > 0;
    CHECK(collisions == 0);
}

TEST("D27 Hashtable（线性试探）：和 std::map 对拍，表长是素数，装填因子不超过 1/2") {
    for (int round = 0; round < 50; ++round) {
        Hashtable<int, int> h(5, Probe::Linear);
        dictOps<Hashtable<int, int>, int>(h, [] { return (int)randInt(-500, 500); }, 2000);
        REQUIRE(isPrime(h.capacity()));
        REQUIRE(h.size() * 2 <= h.capacity());
    }
    Hashtable<std::string, int> t(5, Probe::Linear);
    dictOps<Hashtable<std::string, int>, std::string>(t, randKey, 3000);
}

TEST("D27 Hashtable（平方试探）：和 std::map 对拍，表长是素数，装填因子不超过 1/2") {
    for (int round = 0; round < 50; ++round) {
        Hashtable<int, int> h(5, Probe::Quadratic);
        dictOps<Hashtable<int, int>, int>(h, [] { return (int)randInt(-500, 500); }, 2000);
        REQUIRE(isPrime(h.capacity()));
        REQUIRE(h.size() * 2 <= h.capacity());
    }
    Hashtable<std::string, int> t(5, Probe::Quadratic);
    dictOps<Hashtable<std::string, int>, std::string>(t, randKey, 3000);
}

TEST("D27 Hashtable：重散列的分摊代价是 O(1)（总试探次数是 O(n)）") {
    for (Probe mode : {Probe::Linear, Probe::Quadratic}) {
        Hashtable<int, int> h(5, mode);
        const int n = 20000;
        for (int i = 0; i < n; ++i) h.put(i * 7919, i);
        REQUIRE_EQ(h.size(), (Rank)n);
        CHECK(h.probes() > 0);         // probes_ 要维护
        CHECK(h.probes() < 30LL * n);  // 每次重散列都只扩大一点点的话，总代价会是 O(n^2)
    }
}

TEST("D27 Hashtable：懒惰删除不能切断查找链") {
    for (Probe mode : {Probe::Linear, Probe::Quadratic}) {
        Hashtable<int, int> h(101, mode);
        // 101 的倍数散列到同一个桶，形成一条长查找链
        for (int i = 0; i < 20; ++i) h.put(i * 101, i);
        for (int i = 0; i < 20; i += 2) REQUIRE(h.remove(i * 101));
        for (int i = 1; i < 20; i += 2) REQUIRE(h.get(i * 101) && *h.get(i * 101) == i);
        for (int i = 0; i < 20; i += 2) REQUIRE(h.get(i * 101) == nullptr);
    }
}

// ======================= 第 28 天：线性时间的排序 =======================

TEST("D28 countingSort") {
    for (int round = 0; round < 500; ++round) {
        int maxV = (int)randInt(0, round % 2 ? 10 : 10000);
        std::vector<int> a(randInt(0, 300));
        for (auto& x : a) x = (int)randInt(0, maxV);
        auto b = a;
        countingSort(a, maxV);
        std::sort(b.begin(), b.end());
        REQUIRE_EQ(a, b);
    }
}

TEST("D28 radixSort") {
    for (int round = 0; round < 300; ++round) {
        std::vector<unsigned int> a(randInt(0, 500));
        for (auto& x : a) x = (unsigned int)randInt(0, round % 2 ? 1000 : 0xFFFFFFFFLL);
        auto b = a;
        radixSort(a);
        std::sort(b.begin(), b.end());
        REQUIRE(a == b);
    }
}

TEST("D28 bucketSort") {
    for (int round = 0; round < 300; ++round) {
        std::vector<double> a(randInt(0, 500));
        for (auto& x : a) x = (double)randInt(0, 999999) / 1000000.0;
        auto b = a;
        bucketSort(a);
        std::sort(b.begin(), b.end());
        REQUIRE(a == b);
    }
}

TEST("D28 maxGap：和“排序后逐个比较”对拍") {
    CHECK_EQ(maxGap({}), 0LL);
    CHECK_EQ(maxGap({5}), 0LL);
    CHECK_EQ(maxGap({3, 6, 9, 1}), 3LL);
    CHECK_EQ(maxGap({7, 7, 7}), 0LL);
    CHECK_EQ(maxGap({-2147483647 - 1, 2147483647}), 4294967295LL);
    for (int round = 0; round < 1000; ++round) {
        std::vector<int> a(randInt(0, 200));
        for (auto& x : a) x = (int)randInt(round % 2 ? -100 : -2000000000, round % 2 ? 100 : 2000000000);
        auto b = a;
        std::sort(b.begin(), b.end());
        long long expect = 0;
        for (std::size_t i = 1; i < b.size(); ++i) expect = std::max(expect, (long long)b[i] - b[i - 1]);
        REQUIRE_EQ(maxGap(a), expect);
    }
}
