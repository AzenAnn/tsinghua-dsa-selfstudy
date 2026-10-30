#pragma once
// 第10章 优先级队列（教材 §10.1–10.3）
//
// PQ_ComplHeap：完全二叉堆，用你的 Vector 存（第 29 天）；
// PQ_LeftHeap：左式堆，用你的 BinTree 存（第 30 天）。
// 都是大顶堆：getMax 取最大元素。堆的基本操作 percolateDown / percolateUp / heapify 在 vector.h 里。

#include "dsa/bintree.h"
#include "dsa/vector.h"

namespace dsa {

template <typename T>
struct PQ {
    virtual ~PQ() = default;
    virtual void insert(T const& e) = 0;
    virtual T getMax() = 0;  // 取最大元素（非空）
    virtual T delMax() = 0;  // 删除并返回最大元素（非空）
};

// ======================================================================
// 第 29 天：完全二叉堆（§10.2）
// ======================================================================

template <typename T>
class PQ_ComplHeap : public PQ<T>, public Vector<T> {
public:
    PQ_ComplHeap() = default;
    PQ_ComplHeap(T const* A, Rank n);  // 用 Floyd 算法批量建堆，O(n)
    void insert(T const& e) override;  // 插到末尾再上滤
    T getMax() override;
    T delMax() override;               // 末元素移到堆顶再下滤
};

template <typename T>
PQ_ComplHeap<T>::PQ_ComplHeap(T const* A, Rank n) : Vector<T>(A, n) {
    DSA_TODO();
}

template <typename T>
void PQ_ComplHeap<T>::insert(T const& e) {
    DSA_TODO();
}

template <typename T>
T PQ_ComplHeap<T>::getMax() {
    DSA_TODO();
}

template <typename T>
T PQ_ComplHeap<T>::delMax() {
    DSA_TODO();
}

// ======================================================================
// 第 30 天：左式堆（§10.3）
// ======================================================================

// 合并以 a、b 为根的两个左式堆，返回合并后的根（节点的 npl 字段要维护好）
template <typename T>
BinNodePosi<T> merge(BinNodePosi<T> a, BinNodePosi<T> b);

template <typename T>
class PQ_LeftHeap : public PQ<T>, public BinTree<T> {
public:
    PQ_LeftHeap() = default;
    void insert(T const& e) override;  // 新节点单独成堆，再合并
    T getMax() override;
    T delMax() override;               // 摘掉根，合并左右子堆
    void merge(PQ_LeftHeap<T>& other);  // 把 other 的全部元素并进来，other 变空；O(log n)
};

template <typename T>
BinNodePosi<T> merge(BinNodePosi<T> a, BinNodePosi<T> b) {
    DSA_TODO();
}

template <typename T>
void PQ_LeftHeap<T>::insert(T const& e) {
    DSA_TODO();
}

template <typename T>
T PQ_LeftHeap<T>::getMax() {
    DSA_TODO();
}

template <typename T>
T PQ_LeftHeap<T>::delMax() {
    DSA_TODO();
}

template <typename T>
void PQ_LeftHeap<T>::merge(PQ_LeftHeap<T>& other) {
    DSA_TODO();
}

}  // namespace dsa
