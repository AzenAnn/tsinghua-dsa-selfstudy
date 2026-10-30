#pragma once
// 第7章 AVL 树（教材 §7.4）—— 第 20 天

#include "dsa/bst.h"

namespace dsa {

// ---------- 平衡相关的小工具（已经写好了） ----------
template <typename T> int balFac(BinNodePosi<T> x) { return stature(x->lc) - stature(x->rc); }  // 平衡因子
template <typename T> bool avlBalanced(BinNodePosi<T> x) { return -2 < balFac(x) && balFac(x) < 2; }
// 更高的孩子；一样高时取与父亲同侧的那个（这样单旋就够了）
template <typename T>
BinNodePosi<T> tallerChild(BinNodePosi<T> x) {
    if (stature(x->lc) > stature(x->rc)) return x->lc;
    if (stature(x->lc) < stature(x->rc)) return x->rc;
    return isLChild(x) ? x->lc : x->rc;
}

template <typename T>
class AVL : public BST<T> {
public:
    BinNodePosi<T> insert(const T& e) override;  // 插入后自下而上找第一个失衡的祖先，一次调整就恢复平衡
    bool remove(const T& e) override;            // 删除后可能要一路向上调整多次
};

template <typename T>
BinNodePosi<T> AVL<T>::insert(const T& e) {
    DSA_TODO();
}

template <typename T>
bool AVL<T>::remove(const T& e) {
    DSA_TODO();
}

}  // namespace dsa
