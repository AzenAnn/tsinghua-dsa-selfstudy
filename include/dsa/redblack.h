#pragma once
// 第8章 红黑树（教材 §8.3）—— 第 24 天（插入）、第 25 天（删除）
//
// 节点的 height 字段在红黑树里表示“黑高度”：
//   空节点（外部节点）的黑高度为 -1（即 stature(nullptr)），
//   x 的黑高度 = max(stature(x->lc), stature(x->rc)) + (x 是黑色 ? 1 : 0)。

#include "dsa/bst.h"

namespace dsa {

// ---------- 颜色的小工具（已经写好了）：空节点视为黑色 ----------
template <typename T> bool isBlack(BinNodePosi<T> p) { return !p || p->color == RBColor::Black; }
template <typename T> bool isRed(BinNodePosi<T> p) { return !isBlack(p); }
// x 的黑高度是否不需要更新
template <typename T>
bool blackHeightUpdated(BinNodePosi<T> x) {
    return stature(x->lc) == stature(x->rc) && x->height == (isRed(x) ? stature(x->lc) : stature(x->lc) + 1);
}

template <typename T>
class RedBlack : public BST<T> {
protected:
    void solveDoubleRed(BinNodePosi<T> x);    // 双红修正：RR-1（叔叔黑）、RR-2（叔叔红）   第 24 天
    void solveDoubleBlack(BinNodePosi<T> r);  // 双黑修正：BB-1、BB-2R、BB-2B、BB-3          第 25 天
    int updateHeight(BinNodePosi<T> x) override;  // 更新黑高度                             第 24 天

public:
    BinNodePosi<T> insert(const T& e) override;  // 第 24 天
    bool remove(const T& e) override;            // 第 25 天
};

// ======================================================================
// 第 24 天：插入
// ======================================================================

template <typename T>
int RedBlack<T>::updateHeight(BinNodePosi<T> x) {
    DSA_TODO();
}

template <typename T>
BinNodePosi<T> RedBlack<T>::insert(const T& e) {
    DSA_TODO();
}

template <typename T>
void RedBlack<T>::solveDoubleRed(BinNodePosi<T> x) {
    DSA_TODO();
}

// ======================================================================
// 第 25 天：删除
// ======================================================================

template <typename T>
bool RedBlack<T>::remove(const T& e) {
    DSA_TODO();
}

template <typename T>
void RedBlack<T>::solveDoubleBlack(BinNodePosi<T> r) {
    DSA_TODO();
}

}  // namespace dsa
