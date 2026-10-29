#pragma once
// 第8章 B-树（教材 §8.2）—— 第 22 天（查找、插入）、第 23 天（删除）
//
// m 阶 B-树：每个节点最多 m-1 个关键码、m 个孩子；除根以外至少 ⌈m/2⌉-1 个关键码；所有叶子同深。
// 节点里关键码 key 和孩子 child 都用你自己的 Vector 存，child.size() 总是 key.size() + 1，
// 叶子的孩子都是 nullptr。树为空时 _root 也存在，是一个没有关键码的节点。

#include "dsa/vector.h"

namespace dsa {

template <typename T>
struct BTNode;
template <typename T>
using BTNodePosi = BTNode<T>*;

template <typename T>
struct BTNode {
    BTNodePosi<T> parent = nullptr;
    Vector<T> key;
    Vector<BTNodePosi<T>> child;
    BTNode() { child.insert(nullptr); }  // 只有一个空孩子
    BTNode(T const& e, BTNodePosi<T> lc = nullptr, BTNodePosi<T> rc = nullptr) {
        key.insert(e);
        child.insert(lc);
        child.insert(rc);
        if (lc) lc->parent = this;
        if (rc) rc->parent = this;
    }
};

template <typename T>
class BTree {
protected:
    Rank _size = 0;                 // 关键码总数
    Rank _m;                        // 阶数
    BTNodePosi<T> _root = nullptr;
    BTNodePosi<T> _hot = nullptr;   // search 最后访问的非空节点

    void solveOverflow(BTNodePosi<T> v);   // 节点上溢：分裂            第 22 天
    void solveUnderflow(BTNodePosi<T> v);  // 节点下溢：旋转或合并      第 23 天

public:
    explicit BTree(Rank m = 3);  // 创建一棵空的 m 阶 B-树（m >= 3）     第 22 天
    ~BTree();                    // 释放所有节点                         第 22 天
    BTree(const BTree&) = delete;
    BTree& operator=(const BTree&) = delete;

    Rank order() const { return _m; }
    Rank size() const { return _size; }
    BTNodePosi<T> root() const { return _root; }
    bool empty() const { return !_size; }

    BTNodePosi<T> search(const T& e);  // 返回含 e 的节点，找不到返回 nullptr   第 22 天
    bool insert(const T& e);           // 已存在时返回 false                    第 22 天
    bool remove(const T& e);           // 不存在时返回 false                    第 23 天
};

// ======================================================================
// 第 22 天：查找与插入
// ======================================================================

template <typename T>
BTree<T>::BTree(Rank m) : _m(m) {
    DSA_TODO();
}


template <typename T>
BTree<T>::~BTree() {
    // 待实现
}

template <typename T>
BTNodePosi<T> BTree<T>::search(const T& e) {
    DSA_TODO();
}

template <typename T>
bool BTree<T>::insert(const T& e) {
    DSA_TODO();
}

template <typename T>
void BTree<T>::solveOverflow(BTNodePosi<T> v) {
    DSA_TODO();
}

// ======================================================================
// 第 23 天：删除
// ======================================================================

template <typename T>
bool BTree<T>::remove(const T& e) {
    DSA_TODO();
}

template <typename T>
void BTree<T>::solveUnderflow(BTNodePosi<T> v) {
    DSA_TODO();
}

}  // namespace dsa
