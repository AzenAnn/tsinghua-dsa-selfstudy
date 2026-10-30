#pragma once
// 第1章 绪论（教材 §1.1–1.4）
//
// 这里只有声明；实现写在 src/ch01_intro.cpp 里，那边每个函数现在都是 DSA_TODO();
// 写完一个函数就运行 tools/test.sh ch01，对应的用例会从“待实现”变成“通过”或“失败”。
// 区间一律左闭右开 [lo, hi)，和邓老师的代码一致。

#include <string>
#include <utility>
#include <vector>

#include "dsa/common.h"

namespace dsa::ch01 {

// ---------------- 第 1 天：§1.1–1.3 ----------------

// §1.1.3 起泡排序：反复扫描 A[0, n)，交换相邻的逆序对，直到某一趟没有发生交换
void bubblesort1A(int A[], int n);

// §1.3.2 n 的二进制展开中 1 的个数
int countOnes(unsigned int n);   // 逐位检查，O(log n)
int countOnes1(unsigned int n);  // 每次消去最低位的 1（n &= n - 1），O(1 的个数)

// §1.3.4 2 的 n 次幂，0 <= n <= 62
long long power2BF(int n);  // 蛮力：连乘 n 次，O(n)
long long power2(int n);    // 反复平方，O(log n)

// §1.3.3 数组求和（迭代版），n = 0 时返回 0
long long sumI(const int A[], int n);

// ---------------- 第 2 天：§1.4 递归 ----------------

// §1.4.1 线性递归求和：sum(A, n) = sum(A, n - 1) + A[n - 1]；n = 0 时返回 0
long long sumLinear(const int A[], int n);
// §1.4.5 二分递归求和：A[lo, hi) 从中点均分，两半分别递归；空区间返回 0
long long sumBinary(const int A[], int lo, int hi);

// §1.4.3 倒置 A[lo, hi)
void reverseR(int A[], int lo, int hi);  // 递归版
void reverseI(int A[], int lo, int hi);  // 迭代版（§1.4.4 递归消除）

// §1.4.5 找出 A[lo, hi) 中最大的两个元素（hi - lo >= 2）：
// x1 是最大者的秩，x2 是除 x1 以外最大者的秩。
// 迭代版的比较次数不超过 2n - 3；二分递归版不超过 5n/3 - 2。
void max2I(const int A[], int lo, int hi, int& x1, int& x2);
void max2R(const int A[], int lo, int hi, int& x1, int& x2);

// 汉诺塔：把 n 个盘子从柱 from 借助柱 via 移到柱 to，每一步的 (起点, 终点) 依次记入 moves
void hanoi(int n, char from, char via, char to, std::vector<std::pair<char, char>>& moves);

// Fibonacci 数：fib(0) = 0，fib(1) = 1，约定 fib(-1) = 1；n <= 92 时不溢出
long long fibR(int n);                   // 二分递归，O(phi^n)，测试只用 n <= 30
long long fibL(int n, long long& prev);  // 线性递归：返回 fib(n)，prev 带回 fib(n - 1)
long long fibI(int n);                   // 迭代（动态规划），O(n) 时间、O(1) 空间

// 最大公约数，a, b > 0
long long gcdEuclid(long long a, long long b);  // §1.1.2 欧几里得算法（辗转相除）
long long gcdCN(long long a, long long b);      // 中华更相减损术（只用减法和移位）

// 最长公共子序列的长度
int lcsR(const std::string& a, const std::string& b);  // 朴素递归，测试只用很短的串
int lcsI(const std::string& a, const std::string& b);  // 动态规划，O(nm) 时间、O(min(n, m)) 空间

}  // namespace dsa::ch01
