#pragma once
// 第12章 选取与中位数（教材 §12.2）—— 第 35 天
//
// 快速排序（第 34 天）和希尔排序（第 36 天）是 Vector 的成员函数，在 vector.h 里。

#include <algorithm>
#include <vector>

#include "dsa/vector.h"

namespace dsa {

// 众数：出现次数超过一半的元素。存在时写进 maj 并返回 true。O(n) 时间、O(1) 额外空间（摩尔投票 + 验证）
template <typename T>
bool majority(const Vector<T>& A, T& maj);

// 两个有序向量合并后秩为 ⌊(n1+n2)/2⌋ 的元素（秩从 0 算起；总数为偶数时就是两个中间数里较大的那个）
// A、B 至少有一个非空；要求 O(log(n1+n2))，不能真的合并
template <typename T>
T median(const Vector<T>& A, const Vector<T>& B);

// 快速选取：调整 A，使 A[k] 恰好是第 k 小的元素（k 从 0 算起），它前面的都不大于它、后面的都不小于它
template <typename T>
void quickSelect(Vector<T>& A, Rank k);

// 线性选取：返回第 k 小的元素（k 从 0 算起），最坏情况也是 O(n)（5 个一组取中位数的中位数）；可以改动 A
template <typename T>
T linearSelect(Vector<T>& A, Rank k);

template <typename T>
bool majority(const Vector<T>& A, T& maj) {
    DSA_TODO();
}


template <typename T>
T median(const Vector<T>& A, const Vector<T>& B) {
    DSA_TODO();
}

template <typename T>
void quickSelect(Vector<T>& A, Rank k) {
    DSA_TODO();
}


template <typename T>
T linearSelect(Vector<T>& A, Rank k) {
    DSA_TODO();
}

}  // namespace dsa
