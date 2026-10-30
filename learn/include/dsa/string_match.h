#pragma once
// 第11章 串匹配（教材 §11.1–11.5）
//
// 这里只有声明；实现写在 src/string_match.cpp 里，那边现在都是 DSA_TODO();。
// 所有 match 函数：返回模式串 P 在文本串 T 中第一次出现的位置，没有出现时返回 -1；P 为空串时返回 0。
// 字符按 unsigned char 处理（0..255）。

#include <string>
#include <vector>

#include "dsa/common.h"

namespace dsa {

// ---------------- 第 31 天：§11.2–11.3 ----------------
int matchBF1(const std::string& P, const std::string& T);  // 蛮力版本 1：i、j 两个指针，失配时 i 回退
int matchBF2(const std::string& P, const std::string& T);  // 蛮力版本 2：对齐位置 i 逐个尝试
// next 表：next[0] = -1；j > 0 时，next[j] 是使 P[0, t) == P[j-t, j) 成立的最大的 t（t < j）
std::vector<int> buildNext(const std::string& P);
int matchKMP(const std::string& P, const std::string& T);

// ---------------- 第 32 天：§11.3.7、§11.4 ----------------
// 改进的 next 表：在上面的定义中再要求 P[t] != P[j]；满足条件的 t 不存在时为 -1
std::vector<int> buildNextImproved(const std::string& P);
int matchKMPImproved(const std::string& P, const std::string& T);
// 坏字符表：bc[c] 是字符 c 在 P 中最后一次出现的位置，没有出现时为 -1（长度 256）
std::vector<int> buildBC(const std::string& P);
int matchBMbc(const std::string& P, const std::string& T);  // 只用坏字符策略的 BM

// ---------------- 第 33 天：§11.4–11.5 ----------------
// ss 表：ss[j] 是使 P(j-s, j] == P[m-s, m) 成立的最大的 s（P 的以 j 结尾的子串与 P 的后缀的最长匹配）
std::vector<int> buildSS(const std::string& P);
// gs 表（好后缀）：在 P[j] 失配、P(j, m) 已经匹配时，P 可以右移的最小距离 gs[j]
// 即最小的 s >= 1，使得对所有 j < k < m 有 k-s < 0 或 P[k-s] == P[k]，并且 j-s < 0 或 P[j-s] != P[j]
std::vector<int> buildGS(const std::string& P);
int matchBM(const std::string& P, const std::string& T);  // 坏字符 + 好后缀，每次取两者中较大的位移
int matchKR(const std::string& P, const std::string& T);  // Karp-Rabin：滚动散列做指纹，指纹相同时再逐字核对

}  // namespace dsa
