#pragma once
// 第7章 二叉搜索树（教材 §7.1–7.3）—— 第 19 天；“3+4 重构”在第 20 天
//
// BST 从 BinTree 派生，元素互不相同（插入已有的元素时什么也不做）。
// AVL、伸展树、红黑树又从 BST 派生，改写 search / insert / remove。

#include <utility>

#include "dsa/bintree.h"

namespace dsa {

template <typename T>
class BST : public BinTree<T> {
protected:
    BinNodePosi<T> _hot = nullptr;  // 最近一次 search 命中节点的父亲；查找失败时是“假想的新节点”的父亲

    // “3+4 重构”：按中序 T0 a T1 b T2 c T3 把三个节点、四棵子树重新组装成以 b 为根的平衡子树，返回 b   第 20 天
    BinNodePosi<T> connect34(BinNodePosi<T> a, BinNodePosi<T> b, BinNodePosi<T> c, BinNodePosi<T> T0,
                             BinNodePosi<T> T1, BinNodePosi<T> T2, BinNodePosi<T> T3);
    // 对节点 v、它的父亲 p、祖父 g 做统一的旋转调整，返回调整后子树的根（其 parent 已正确设好）   第 20 天
    BinNodePosi<T> rotateAt(BinNodePosi<T> v);

public:
    BinNodePosi<T> hot() const { return _hot; }  // 测试用

    // 查找 e：返回指向目标节点的那个指针（父节点的 lc 或 rc，或 _root）的引用；
    // 找不到时这个指针是 nullptr，同时 _hot 指向它应有的父亲                       第 19 天
    virtual BinNodePosi<T>& search(const T& e);
    virtual BinNodePosi<T> insert(const T& e);  // 插入 e；已存在时直接返回那个节点        第 19 天
    virtual bool remove(const T& e);            // 删除 e；不存在时返回 false             第 19 天
};

// 删除 x 所指的节点（x 是 search 返回的那个引用），返回接替者；hot 被设为实际被删节点的父亲   第 19 天
template <typename T>
BinNodePosi<T> removeAt(BinNodePosi<T>& x, BinNodePosi<T>& hot);

// ======================================================================
// 第 19 天：二叉搜索树（§7.2）
// ======================================================================

template <typename T>
BinNodePosi<T>& BST<T>::search(const T& e) {
    DSA_TODO();
}

template <typename T>
BinNodePosi<T> BST<T>::insert(const T& e) {
    DSA_TODO();
}

template <typename T>
BinNodePosi<T> removeAt(BinNodePosi<T>& x, BinNodePosi<T>& hot) {
    DSA_TODO();
}

template <typename T>
bool BST<T>::remove(const T& e) {
    DSA_TODO();
}

// ======================================================================
// 第 20 天：3+4 重构（§7.4.4）
// ======================================================================

template <typename T>
BinNodePosi<T> BST<T>::connect34(BinNodePosi<T> a, BinNodePosi<T> b, BinNodePosi<T> c, BinNodePosi<T> T0,
                                 BinNodePosi<T> T1, BinNodePosi<T> T2, BinNodePosi<T> T3) {
    DSA_TODO();
}

template <typename T>
BinNodePosi<T> BST<T>::rotateAt(BinNodePosi<T> v) {
    DSA_TODO();
}

}  // namespace dsa
