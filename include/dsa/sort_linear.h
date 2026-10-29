#pragma once
// 第9章 散列的应用：线性时间的排序（教材 §9.4）—— 第 28 天
//
// 这里只有声明；实现写在 src/sort_linear.cpp 里，那边现在都是 DSA_TODO();。
// 它们都不基于比较，所以不受 Ω(n log n) 下界的限制。

#include <vector>

#include "dsa/common.h"

namespace dsa {

// 计数排序：A 中元素都在 [0, maxValue] 内，O(n + maxValue)，要求稳定
void countingSort(std::vector<int>& A, int maxValue);

// 基数排序（LSD）：以 8 位为一位，从低位到高位做 4 趟稳定的计数排序
void radixSort(std::vector<unsigned int>& A);

// 桶排序：A 中元素都在 [0, 1) 内，分成 n 个桶，每个桶内再排序；均匀分布时期望 O(n)
void bucketSort(std::vector<double>& A);

// 最大间隙：A 排序后相邻两数之差的最大值（元素少于 2 个时返回 0），要求 O(n)，不能排序
// 提示：n 个数放进 n+1 个等宽的桶，必有空桶，最大间隙一定跨越桶的边界
long long maxGap(const std::vector<int>& A);

}  // namespace dsa
