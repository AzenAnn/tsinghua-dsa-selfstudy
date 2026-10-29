// 第5章 Huffman 编码的测试（D13）

#include <functional>
#include <map>
#include <queue>
#include <string>
#include <vector>

#include "dsa/huffman.h"
#include "dsa_test.h"

using namespace dsa;
using dsa_test::randInt;

namespace {

std::string randText(int len, int alphabet) {
    std::string s(len, 'a');
    for (auto& c : s) {
        int k = (int)randInt(0, alphabet - 1);
        // 让频率不均匀：越靠前的字符越常见
        k = (int)randInt(0, k);
        c = (char)('a' + k);
    }
    return s;
}

// 最优带权路径长度：每次合并最小的两个，合并代价之和
long long optimalWpl(const std::string& s) {
    std::map<char, long long> f;
    for (char c : s) f[c]++;
    if (f.size() == 1) return (long long)s.size();  // 只有一种字符时编码长度为 1
    std::priority_queue<long long, std::vector<long long>, std::greater<>> pq;
    for (auto& kv : f) pq.push(kv.second);
    long long total = 0;
    while (pq.size() > 1) {
        long long a = pq.top();
        pq.pop();
        long long b = pq.top();
        pq.pop();
        total += a + b;
        pq.push(a + b);
    }
    return total;
}

bool prefixFree(const std::map<char, std::string>& t) {
    for (auto& [c1, a] : t)
        for (auto& [c2, b] : t)
            if (c1 != c2 && b.compare(0, a.size(), a) == 0) return false;
    return true;
}

}  // namespace

TEST("D13 Huffman：固定的例子") {
    HuffmanCoder h("aaaabbc");
    CHECK_EQ(h.table().size(), 3u);
    CHECK_EQ(h.table().at('a').size(), 1u);
    CHECK_EQ(h.table().at('b').size(), 2u);
    CHECK_EQ(h.table().at('c').size(), 2u);
    CHECK_EQ(h.wpl(), 10LL);
    CHECK_EQ(h.decode(h.encode("abcab")), std::string("abcab"));
}

TEST("D13 Huffman：只有一种字符、空串") {
    HuffmanCoder one("zzzz");
    CHECK_EQ(one.table().at('z'), std::string("0"));
    CHECK_EQ(one.encode("zz"), std::string("00"));
    CHECK_EQ(one.decode("000"), std::string("zzz"));
    HuffmanCoder empty("");
    CHECK(empty.table().empty());
}

TEST("D13 Huffman：编码表是前缀码，带权路径长度最优，编码后能解码回原文") {
    for (int round = 0; round < 300; ++round) {
        std::string sample = randText((int)randInt(1, 400), (int)randInt(1, 26));
        HuffmanCoder h(sample);
        auto& t = h.table();
        for (auto& [c, code] : t) {
            REQUIRE(!code.empty());
            REQUIRE(code.find_first_not_of("01") == std::string::npos);
        }
        REQUIRE(prefixFree(t));
        REQUIRE_EQ(h.wpl(), optimalWpl(sample));
        REQUIRE_EQ((long long)h.encode(sample).size(), h.wpl());
        REQUIRE_EQ(h.decode(h.encode(sample)), sample);
        // 换一段只用样本里出现过的字符的文本
        std::string other;
        for (int i = 0; i < 100; ++i) other += sample[randInt(0, sample.size() - 1)];
        REQUIRE_EQ(h.decode(h.encode(other)), other);
    }
}
