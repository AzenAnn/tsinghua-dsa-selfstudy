// 第1章 绪论的测试：每个函数都有边界情况，再和标准库或朴素算法随机对拍

#include <algorithm>
#include <climits>
#include <numeric>
#include <string>
#include <vector>

#include "dsa/ch01_intro.h"
#include "dsa_test.h"

using namespace dsa::ch01;
using dsa_test::randInt;
using dsa_test::randVector;

namespace {

// 按 moves 模拟汉诺塔：每一步都要合法（不能大盘压小盘），最后全部到了 to 柱
bool hanoiValid(int n, char from, char via, char to, const std::vector<std::pair<char, char>>& moves) {
    std::vector<int> peg[3];
    auto id = [&](char c) { return c == from ? 0 : c == via ? 1 : c == to ? 2 : -1; };
    for (int d = n; d >= 1; --d) peg[0].push_back(d);
    for (auto [s, t] : moves) {
        int a = id(s), b = id(t);
        if (a < 0 || b < 0 || a == b || peg[a].empty()) return false;
        if (!peg[b].empty() && peg[b].back() < peg[a].back()) return false;
        peg[b].push_back(peg[a].back());
        peg[a].pop_back();
    }
    return (int)peg[2].size() == n;
}

std::string randString(int len, char maxChar) {
    std::string s(len, 'a');
    for (auto& c : s) c = (char)randInt('a', maxChar);
    return s;
}

int lcsReference(const std::string& a, const std::string& b) {
    std::vector<std::vector<int>> f(a.size() + 1, std::vector<int>(b.size() + 1, 0));
    for (std::size_t i = 1; i <= a.size(); ++i)
        for (std::size_t j = 1; j <= b.size(); ++j)
            f[i][j] = a[i - 1] == b[j - 1] ? f[i - 1][j - 1] + 1 : std::max(f[i - 1][j], f[i][j - 1]);
    return f[a.size()][b.size()];
}

}  // namespace

// ---------------- 第 1 天 ----------------

TEST("D01 bubblesort1A：边界情况") {
    int one[] = {7};
    bubblesort1A(one, 1);
    CHECK_EQ(one[0], 7);
    bubblesort1A(one, 0);  // 空数组什么也不做
    std::vector<int> v = {1, 2, 3, 4};
    bubblesort1A(v.data(), 4);
    CHECK_EQ(v, (std::vector<int>{1, 2, 3, 4}));
    v = {4, 3, 2, 1};
    bubblesort1A(v.data(), 4);
    CHECK_EQ(v, (std::vector<int>{1, 2, 3, 4}));
    v = {2, 1, 2, 1, 2};
    bubblesort1A(v.data(), 5);
    CHECK_EQ(v, (std::vector<int>{1, 1, 2, 2, 2}));
}

TEST("D01 bubblesort1A：和 std::sort 随机对拍") {
    for (int round = 0; round < 2000; ++round) {
        auto v = randVector(randInt(0, 40), -20, 20);
        auto w = v;
        bubblesort1A(v.data(), (int)v.size());
        std::sort(w.begin(), w.end());
        REQUIRE_EQ(v, w);
    }
}

TEST("D01 countOnes：逐位检查") {
    CHECK_EQ(countOnes(0), 0);
    CHECK_EQ(countOnes(1), 1);
    CHECK_EQ(countOnes(0xFFFFFFFFu), 32);
    CHECK_EQ(countOnes(0x80000000u), 1);
    for (int round = 0; round < 10000; ++round) {
        unsigned int n = (unsigned int)randInt(0, 0xFFFFFFFFLL);
        REQUIRE_EQ(countOnes(n), __builtin_popcount(n));
    }
}

TEST("D01 countOnes1：消去最低位的 1") {
    CHECK_EQ(countOnes1(0), 0);
    CHECK_EQ(countOnes1(0xFFFFFFFFu), 32);
    for (int round = 0; round < 10000; ++round) {
        unsigned int n = (unsigned int)randInt(0, 0xFFFFFFFFLL);
        REQUIRE_EQ(countOnes1(n), __builtin_popcount(n));
    }
}

TEST("D01 power2BF：蛮力") {
    for (int n = 0; n <= 62; ++n) REQUIRE_EQ(power2BF(n), 1LL << n);
}

TEST("D01 power2：反复平方") {
    for (int n = 0; n <= 62; ++n) REQUIRE_EQ(power2(n), 1LL << n);
}

TEST("D01 sumI：迭代求和") {
    CHECK_EQ(sumI(nullptr, 0), 0LL);
    for (int round = 0; round < 1000; ++round) {
        auto v = randVector(randInt(0, 100), -1000000000, 1000000000);
        REQUIRE_EQ(sumI(v.data(), (int)v.size()), std::accumulate(v.begin(), v.end(), 0LL));
    }
}

// ---------------- 第 2 天 ----------------

TEST("D02 sumLinear：线性递归求和") {
    CHECK_EQ(sumLinear(nullptr, 0), 0LL);
    for (int round = 0; round < 1000; ++round) {
        auto v = randVector(randInt(0, 100), -1000000000, 1000000000);
        REQUIRE_EQ(sumLinear(v.data(), (int)v.size()), std::accumulate(v.begin(), v.end(), 0LL));
    }
}

TEST("D02 sumBinary：二分递归求和") {
    CHECK_EQ(sumBinary(nullptr, 0, 0), 0LL);
    for (int round = 0; round < 1000; ++round) {
        auto v = randVector(randInt(1, 100), -1000000000, 1000000000);
        int lo = (int)randInt(0, v.size()), hi = (int)randInt(lo, v.size());
        REQUIRE_EQ(sumBinary(v.data(), lo, hi), std::accumulate(v.begin() + lo, v.begin() + hi, 0LL));
    }
}

TEST("D02 reverseR：递归倒置") {
    for (int round = 0; round < 1000; ++round) {
        auto v = randVector(randInt(0, 50), 0, 99);
        int lo = (int)randInt(0, v.size()), hi = (int)randInt(lo, v.size());
        auto w = v;
        reverseR(v.data(), lo, hi);
        std::reverse(w.begin() + lo, w.begin() + hi);
        REQUIRE_EQ(v, w);
    }
}

TEST("D02 reverseI：迭代倒置") {
    for (int round = 0; round < 1000; ++round) {
        auto v = randVector(randInt(0, 50), 0, 99);
        int lo = (int)randInt(0, v.size()), hi = (int)randInt(lo, v.size());
        auto w = v;
        reverseI(v.data(), lo, hi);
        std::reverse(w.begin() + lo, w.begin() + hi);
        REQUIRE_EQ(v, w);
    }
}

// max2 的结果只要求：x1 是某个最大者，x2 是除 x1 以外的某个最大者
static void checkMax2(void (*f)(const int*, int, int, int&, int&)) {
    for (int round = 0; round < 3000; ++round) {
        auto v = randVector(randInt(2, 40), 0, round % 2 ? 5 : 1000);  // 一半的轮次有大量重复
        int lo = (int)randInt(0, v.size() - 2), hi = (int)randInt(lo + 2, v.size());
        int x1 = -1, x2 = -1;
        f(v.data(), lo, hi, x1, x2);
        REQUIRE(lo <= x1 && x1 < hi && lo <= x2 && x2 < hi && x1 != x2);
        int best = *std::max_element(v.begin() + lo, v.begin() + hi);
        int second = INT_MIN;
        for (int i = lo; i < hi; ++i)
            if (i != x1) second = std::max(second, v[i]);
        REQUIRE_EQ(v[x1], best);
        REQUIRE_EQ(v[x2], second);
    }
}
TEST("D02 max2I：迭代找最大的两个") { checkMax2(max2I); }
TEST("D02 max2R：二分递归找最大的两个") { checkMax2(max2R); }

TEST("D02 hanoi：步数为 2^n - 1 且每一步合法") {
    for (int n = 0; n <= 12; ++n) {
        std::vector<std::pair<char, char>> moves;
        hanoi(n, 'A', 'B', 'C', moves);
        REQUIRE_EQ(moves.size(), (std::size_t)((1 << n) - 1));
        REQUIRE(hanoiValid(n, 'A', 'B', 'C', moves));
    }
}

TEST("D02 fibR：二分递归") {
    long long f[31] = {0, 1};
    for (int i = 2; i <= 30; ++i) f[i] = f[i - 1] + f[i - 2];
    for (int n = 0; n <= 30; ++n) REQUIRE_EQ(fibR(n), f[n]);
}

TEST("D02 fibL：线性递归，同时带回前一项") {
    long long f[93] = {0, 1};
    for (int i = 2; i <= 92; ++i) f[i] = f[i - 1] + f[i - 2];
    long long prev = -1;
    CHECK_EQ(fibL(0, prev), 0LL);
    CHECK_EQ(prev, 1LL);  // fib(-1) = 1
    for (int n = 1; n <= 92; ++n) {
        REQUIRE_EQ(fibL(n, prev), f[n]);
        REQUIRE_EQ(prev, f[n - 1]);
    }
}

TEST("D02 fibI：迭代") {
    long long f[93] = {0, 1};
    for (int i = 2; i <= 92; ++i) f[i] = f[i - 1] + f[i - 2];
    for (int n = 0; n <= 92; ++n) REQUIRE_EQ(fibI(n), f[n]);
}

TEST("D02 gcdEuclid：辗转相除") {
    CHECK_EQ(gcdEuclid(1, 1), 1LL);
    CHECK_EQ(gcdEuclid(12, 18), 6LL);
    for (int round = 0; round < 10000; ++round) {
        long long a = randInt(1, 1000000000000LL), b = randInt(1, round % 2 ? 1000 : 1000000000000LL);
        REQUIRE_EQ(gcdEuclid(a, b), std::gcd(a, b));
    }
}

TEST("D02 gcdCN：更相减损") {
    CHECK_EQ(gcdCN(1, 1), 1LL);
    CHECK_EQ(gcdCN(64, 48), 16LL);
    for (int round = 0; round < 10000; ++round) {
        long long a = randInt(1, 1000000000000LL), b = randInt(1, round % 2 ? 1000 : 1000000000000LL);
        REQUIRE_EQ(gcdCN(a, b), std::gcd(a, b));
    }
}

TEST("D02 lcsR：朴素递归") {
    CHECK_EQ(lcsR("", "abc"), 0);
    CHECK_EQ(lcsR("program", "algorithm"), 3);
    for (int round = 0; round < 300; ++round) {
        auto a = randString(randInt(0, 8), 'c'), b = randString(randInt(0, 8), 'c');
        REQUIRE_EQ(lcsR(a, b), lcsReference(a, b));
    }
}

TEST("D02 lcsI：动态规划") {
    CHECK_EQ(lcsI("", ""), 0);
    CHECK_EQ(lcsI("educational", "advantage"), 4);
    for (int round = 0; round < 300; ++round) {
        auto a = randString(randInt(0, 200), round % 2 ? 'b' : 'z');
        auto b = randString(randInt(0, 200), round % 2 ? 'b' : 'z');
        REQUIRE_EQ(lcsI(a, b), lcsReference(a, b));
    }
}
