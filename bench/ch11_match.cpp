// 第11章：各种串匹配算法的耗时（微秒）。文本 100 万字符，模式串 20 字符，放在文本末尾。
// 分别用 2 个字符（a、b）和 26 个字符的字母表：小字母表时 KMP 稳定，大字母表时 BM 跳得远。
// 运行：tools/bench.sh ch11_match

#include <random>
#include <string>

#include "bench.h"
#include "dsa/string_match.h"

int main() {
    bench::Table table("ch11_match", "alphabet,BF,KMP,BMbc,BM,KR");
    std::mt19937 rng(2026);
    for (int sigma : {2, 4, 26}) {
        std::string T(1000000, 'a');
        for (auto& c : T) c = (char)('a' + rng() % sigma);
        std::string P = T.substr(T.size() - 20);
        auto us = [&](int (*f)(const std::string&, const std::string&)) {
            return bench::timeNs([&] { bench::keep(f(P, T)); }) / 1000;
        };
        table.row(sigma, us(dsa::matchBF2), us(dsa::matchKMP), us(dsa::matchBMbc), us(dsa::matchBM), us(dsa::matchKR));
    }
}
