// 第11章 串匹配的测试（D31–D33）。各种表都按定义直接暴力计算来对拍。

#include <string>
#include <vector>

#include "dsa/string_match.h"
#include "dsa_test.h"

using namespace dsa;
using dsa_test::randInt;

namespace {

std::string randStr(int len, char maxc) {
    std::string s(len, 'a');
    for (auto& c : s) c = (char)randInt('a', maxc);
    return s;
}

int refFind(const std::string& P, const std::string& T) {
    auto r = T.find(P);
    return r == std::string::npos ? -1 : (int)r;
}

std::vector<int> refNext(const std::string& P, bool improved) {
    int m = (int)P.size();
    std::vector<int> N(m, -1);
    for (int j = 1; j < m; ++j)
        for (int t = j - 1; t >= 0; --t)
            if (P.compare(0, t, P, j - t, t) == 0 && (!improved || P[t] != P[j])) {
                N[j] = t;
                break;
            }
    if (improved && m > 0) N[0] = -1;
    return N;
}

std::vector<int> refSS(const std::string& P) {
    int m = (int)P.size();
    std::vector<int> ss(m);
    for (int j = 0; j < m; ++j) {
        int s = 0;
        while (s <= j && P[j - s] == P[m - 1 - s]) ++s;
        ss[j] = s;
    }
    return ss;
}

std::vector<int> refGS(const std::string& P) {
    int m = (int)P.size();
    std::vector<int> gs(m);
    for (int j = 0; j < m; ++j)
        for (int s = 1; s <= m; ++s) {
            bool ok = true;
            for (int k = j + 1; k < m && ok; ++k)
                if (k - s >= 0 && P[k - s] != P[k]) ok = false;
            if (ok && j - s >= 0 && P[j - s] == P[j]) ok = false;
            if (ok) {
                gs[j] = s;
                break;
            }
        }
    return gs;
}

// 随机文本 + 模式串（一半取自文本本身，保证能匹配上）
void checkMatcher(int (*match)(const std::string&, const std::string&)) {
    CHECK_EQ(match("", "abc"), 0);
    CHECK_EQ(match("", ""), 0);
    CHECK_EQ(match("a", ""), -1);
    CHECK_EQ(match("abc", "ab"), -1);
    CHECK_EQ(match("aab", "aaab"), 1);
    CHECK_EQ(match("abab", "abacababab"), 4);
    for (int round = 0; round < 5000; ++round) {
        char maxc = round % 3 == 0 ? 'b' : round % 3 == 1 ? 'd' : 'z';
        std::string T = randStr((int)randInt(0, 60), maxc);
        std::string P;
        if (!T.empty() && randInt(0, 1)) {
            int i = (int)randInt(0, T.size() - 1);
            P = T.substr(i, randInt(1, T.size() - i));
        } else {
            P = randStr((int)randInt(1, 6), maxc);
        }
        REQUIRE_EQ(match(P, T), refFind(P, T));
    }
    std::string big(20000, 'a');  // 最坏情况的输入也要能跑完
    CHECK_EQ(match(std::string(500, 'a') + "b", big), -1);
}

}  // namespace

// ======================= 第 31 天 =======================

TEST("D31 matchBF1") { checkMatcher(matchBF1); }
TEST("D31 matchBF2") { checkMatcher(matchBF2); }
TEST("D31 buildNext：按定义对拍") {
    CHECK_EQ(buildNext("chinchilla"), (std::vector<int>{-1, 0, 0, 0, 0, 1, 2, 3, 0, 0}));
    for (int round = 0; round < 3000; ++round) {
        std::string P = randStr((int)randInt(1, 30), round % 2 ? 'b' : 'c');
        REQUIRE_EQ(buildNext(P), refNext(P, false));
    }
}
TEST("D31 matchKMP") { checkMatcher(matchKMP); }

// ======================= 第 32 天 =======================

TEST("D32 buildNextImproved：按定义对拍") {
    CHECK_EQ(buildNextImproved("aaaab"), (std::vector<int>{-1, -1, -1, -1, 3}));
    for (int round = 0; round < 3000; ++round) {
        std::string P = randStr((int)randInt(1, 30), round % 2 ? 'b' : 'c');
        REQUIRE_EQ(buildNextImproved(P), refNext(P, true));
    }
}
TEST("D32 matchKMPImproved") { checkMatcher(matchKMPImproved); }
TEST("D32 buildBC：每个字符最后一次出现的位置") {
    auto bc = buildBC("DATASTRUCTURE");
    CHECK_EQ((int)bc.size(), 256);
    CHECK_EQ(bc['D'], 0);
    CHECK_EQ(bc['T'], 9);
    CHECK_EQ(bc['E'], 12);
    CHECK_EQ(bc['X'], -1);
    auto bc2 = buildBC(std::string("\xff\x01", 2));
    CHECK_EQ(bc2[255], 0);
    CHECK_EQ(bc2[1], 1);
}
TEST("D32 matchBMbc") { checkMatcher(matchBMbc); }

// ======================= 第 33 天 =======================

TEST("D33 buildSS：按定义对拍") {
    for (int round = 0; round < 3000; ++round) {
        std::string P = randStr((int)randInt(1, 30), round % 2 ? 'b' : 'c');
        REQUIRE_EQ(buildSS(P), refSS(P));
    }
}
TEST("D33 buildGS：按定义对拍") {
    CHECK_EQ(buildGS("ICED RICE PRICE"), (std::vector<int>{12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 6, 12, 15, 15, 1}));
    for (int round = 0; round < 3000; ++round) {
        std::string P = randStr((int)randInt(1, 30), round % 2 ? 'b' : 'c');
        REQUIRE_EQ(buildGS(P), refGS(P));
    }
}
TEST("D33 matchBM：坏字符 + 好后缀") { checkMatcher(matchBM); }
TEST("D33 matchKR：Karp-Rabin") { checkMatcher(matchKR); }
