#pragma once
// 第8章 伸展树（教材 §8.1）—— 第 21 天

#include "dsa/bst.h"

namespace dsa {

template <typename T>
class Splay : public BST<T> {
protected:
    BinNodePosi<T> splay(BinNodePosi<T> v);  // 把 v 双层伸展到树根，返回 v（v 为空时返回 nullptr）

public:
    // 查找 e，并把最后访问的节点（命中的节点，或查找失败处的 _hot）伸展到树根；返回树根的引用
    BinNodePosi<T>& search(const T& e) override;
    BinNodePosi<T> insert(const T& e) override;  // 插入后新节点成为树根；已存在时把它伸展到根并返回
    bool remove(const T& e) override;
};


template <typename T>
BinNodePosi<T> Splay<T>::splay(BinNodePosi<T> v) {
    DSA_TODO();
}

template <typename T>
BinNodePosi<T>& Splay<T>::search(const T& e) {
    DSA_TODO();
}

template <typename T>
BinNodePosi<T> Splay<T>::insert(const T& e) {
    DSA_TODO();
}

template <typename T>
bool Splay<T>::remove(const T& e) {
    DSA_TODO();
}

}  // namespace dsa
