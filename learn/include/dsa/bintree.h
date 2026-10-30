#pragma once
// 第5章 二叉树（教材 §5.1–5.4）
//
// BinNode 是节点，BinTree 是树。模板类，声明和实现都在这个文件里，按天分段，现在都是 DSA_TODO();。
// 第7、8章的搜索树（BST、AVL、伸展树、红黑树）都从 BinTree 派生，所以这里的节点带着
// npl（左式堆用）和 color（红黑树用）两个字段，现在用不到。
// 树的高度约定：空树（nullptr）高度为 -1，只有一个节点的树高度为 0。

#include <vector>

#include "dsa/queue.h"
#include "dsa/stack.h"

namespace dsa {

enum class RBColor { Red, Black };

template <typename T>
struct BinNode;
template <typename T>
using BinNodePosi = BinNode<T>*;

template <typename T>
struct BinNode {
    T data;
    BinNodePosi<T> parent = nullptr, lc = nullptr, rc = nullptr;
    int height = 0;               // 高度
    int npl = 1;                  // 左式堆用：Null Path Length
    RBColor color = RBColor::Red;  // 红黑树用

    BinNode() = default;
    BinNode(T const& e, BinNodePosi<T> p = nullptr) : data(e), parent(p) {}

    Rank size();                             // 以本节点为根的子树的规模             第 11 天
    BinNodePosi<T> insertAsLC(T const& e);   // 作为左孩子插入（原来没有左孩子）     第 11 天
    BinNodePosi<T> insertAsRC(T const& e);   // 作为右孩子插入（原来没有右孩子）     第 11 天
    BinNodePosi<T> succ();                   // 中序遍历意义下的直接后继，没有则返回 nullptr   第 12 天
};

// ---------- 节点关系的小工具（已经写好了） ----------
template <typename T> int stature(BinNodePosi<T> p) { return p ? p->height : -1; }  // 空树高度为 -1
template <typename T> bool isRoot(BinNodePosi<T> x) { return !x->parent; }
template <typename T> bool isLChild(BinNodePosi<T> x) { return !isRoot(x) && x == x->parent->lc; }
template <typename T> bool isRChild(BinNodePosi<T> x) { return !isRoot(x) && x == x->parent->rc; }
template <typename T> bool hasLChild(BinNodePosi<T> x) { return x->lc; }
template <typename T> bool hasRChild(BinNodePosi<T> x) { return x->rc; }
template <typename T> bool hasChild(BinNodePosi<T> x) { return x->lc || x->rc; }
template <typename T> bool hasBothChild(BinNodePosi<T> x) { return x->lc && x->rc; }
template <typename T> bool isLeaf(BinNodePosi<T> x) { return !hasChild(x); }
template <typename T> BinNodePosi<T> sibling(BinNodePosi<T> x) { return isLChild(x) ? x->parent->rc : x->parent->lc; }
template <typename T> BinNodePosi<T> uncle(BinNodePosi<T> x) { return sibling(x->parent); }

template <typename T>
class BinTree {
protected:
    Rank _size = 0;
    BinNodePosi<T> _root = nullptr;

    virtual int updateHeight(BinNodePosi<T> x);  // 更新 x 的高度并返回（AVL、红黑树会改写它）   第 11 天
    void updateHeightAbove(BinNodePosi<T> x);    // 更新 x 及其所有祖先的高度                    第 11 天
    // 父节点中指向 x 的那个指针（x 是根时就是 _root），已经写好了
    BinNodePosi<T>& fromParentTo(BinNodePosi<T> x) { return isRoot(x) ? _root : (isLChild(x) ? x->parent->lc : x->parent->rc); }

public:
    BinTree() = default;
    virtual ~BinTree();                          // 释放所有节点                        第 11 天
    BinTree(const BinTree&) = delete;
    BinTree& operator=(const BinTree&) = delete;

    Rank size() const { return _size; }
    bool empty() const { return !_root; }
    BinNodePosi<T> root() const { return _root; }

    // ---------- 第 11 天：§5.3 ----------
    BinNodePosi<T> insertAsRoot(T const& e);                    // 在空树中插入根
    BinNodePosi<T> insertAsLC(BinNodePosi<T> x, T const& e);    // e 作为 x 的左孩子（原来没有）
    BinNodePosi<T> insertAsRC(BinNodePosi<T> x, T const& e);    // e 作为 x 的右孩子（原来没有）
    // 把树 S 接成 x 的左（右）子树（x 原来没有左/右孩子）；之后 S 被释放并置为 nullptr，返回 x
    BinNodePosi<T> attachAsLC(BinNodePosi<T> x, BinTree<T>*& S);
    BinNodePosi<T> attachAsRC(BinNodePosi<T> x, BinTree<T>*& S);
    Rank remove(BinNodePosi<T> x);               // 删除以 x 为根的子树，返回删除的节点数
    BinTree<T>* secede(BinNodePosi<T> x);        // 把以 x 为根的子树摘下来，作为一棵新树返回
};

// ---------- 第 12 天：§5.4 遍历 ----------
// visit 是函数对象（可以是 lambda），对每个节点的 data 调用 visit(x->data)。
// 迭代版必须用你自己的 Stack / Queue，不要用递归。
template <typename T, typename VST> void travPreR(BinNodePosi<T> x, VST&& visit);   // 先序，递归
template <typename T, typename VST> void travPreI1(BinNodePosi<T> x, VST&& visit);  // 先序，迭代版 1：右孩子先入栈、左孩子后入栈
template <typename T, typename VST> void travPreI2(BinNodePosi<T> x, VST&& visit);  // 先序，迭代版 2：沿左侧藤访问，右孩子入栈
template <typename T, typename VST> void travInR(BinNodePosi<T> x, VST&& visit);    // 中序，递归
template <typename T, typename VST> void travInI1(BinNodePosi<T> x, VST&& visit);   // 中序，迭代版 1：沿左侧藤入栈
template <typename T, typename VST> void travInI2(BinNodePosi<T> x, VST&& visit);   // 中序，迭代版 2：版本 1 的等价写法
template <typename T, typename VST> void travInI3(BinNodePosi<T> x, VST&& visit);   // 中序，迭代版 3：不用栈，借助 succ() 和回溯标志
template <typename T, typename VST> void travPostR(BinNodePosi<T> x, VST&& visit);  // 后序，递归
template <typename T, typename VST> void travPostI(BinNodePosi<T> x, VST&& visit);  // 后序，迭代
template <typename T, typename VST> void travLevel(BinNodePosi<T> x, VST&& visit);  // 层次遍历，用队列

// 由先序和中序序列重构二叉树（元素互不相同），返回新建的树（用完要 delete）
template <typename T>
BinTree<T>* rebuildPreIn(const std::vector<T>& pre, const std::vector<T>& in);
// 由先序和后序序列重构真二叉树（每个节点的孩子数是 0 或 2，元素互不相同），返回新建的树
template <typename T>
BinTree<T>* rebuildPrePost(const std::vector<T>& pre, const std::vector<T>& post);

// ======================================================================
// 第 11 天：节点与树的基本操作（§5.3）
// ======================================================================

template <typename T>
Rank BinNode<T>::size() {
    DSA_TODO();
}

template <typename T>
BinNodePosi<T> BinNode<T>::insertAsLC(T const& e) {
    DSA_TODO();
}

template <typename T>
BinNodePosi<T> BinNode<T>::insertAsRC(T const& e) {
    DSA_TODO();
}

template <typename T>
int BinTree<T>::updateHeight(BinNodePosi<T> x) {
    DSA_TODO();
}

template <typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi<T> x) {
    DSA_TODO();
}

template <typename T>
BinNodePosi<T> BinTree<T>::insertAsRoot(T const& e) {
    DSA_TODO();
}

template <typename T>
BinNodePosi<T> BinTree<T>::insertAsLC(BinNodePosi<T> x, T const& e) {
    DSA_TODO();
}

template <typename T>
BinNodePosi<T> BinTree<T>::insertAsRC(BinNodePosi<T> x, T const& e) {
    DSA_TODO();
}

template <typename T>
BinNodePosi<T> BinTree<T>::attachAsLC(BinNodePosi<T> x, BinTree<T>*& S) {
    DSA_TODO();
}

template <typename T>
BinNodePosi<T> BinTree<T>::attachAsRC(BinNodePosi<T> x, BinTree<T>*& S) {
    DSA_TODO();
}


template <typename T>
Rank BinTree<T>::remove(BinNodePosi<T> x) {
    DSA_TODO();
}

template <typename T>
BinTree<T>* BinTree<T>::secede(BinNodePosi<T> x) {
    DSA_TODO();
}

template <typename T>
BinTree<T>::~BinTree() {
    // 待实现
}

// ======================================================================
// 第 12 天：遍历（§5.4）
// ======================================================================

template <typename T>
BinNodePosi<T> BinNode<T>::succ() {
    DSA_TODO();
}

template <typename T, typename VST>
void travPreR(BinNodePosi<T> x, VST&& visit) {
    DSA_TODO();
}

template <typename T, typename VST>
void travPreI1(BinNodePosi<T> x, VST&& visit) {
    DSA_TODO();
}

template <typename T, typename VST>
void travPreI2(BinNodePosi<T> x, VST&& visit) {
    DSA_TODO();
}

template <typename T, typename VST>
void travInR(BinNodePosi<T> x, VST&& visit) {
    DSA_TODO();
}

template <typename T, typename VST>
void travInI1(BinNodePosi<T> x, VST&& visit) {
    DSA_TODO();
}

template <typename T, typename VST>
void travInI2(BinNodePosi<T> x, VST&& visit) {
    DSA_TODO();
}

template <typename T, typename VST>
void travInI3(BinNodePosi<T> x, VST&& visit) {
    DSA_TODO();
}

template <typename T, typename VST>
void travPostR(BinNodePosi<T> x, VST&& visit) {
    DSA_TODO();
}

template <typename T, typename VST>
void travPostI(BinNodePosi<T> x, VST&& visit) {
    DSA_TODO();
}

template <typename T, typename VST>
void travLevel(BinNodePosi<T> x, VST&& visit) {
    DSA_TODO();
}


template <typename T>
BinTree<T>* rebuildPreIn(const std::vector<T>& pre, const std::vector<T>& in) {
    DSA_TODO();
}

template <typename T>
BinTree<T>* rebuildPrePost(const std::vector<T>& pre, const std::vector<T>& post) {
    DSA_TODO();
}

}  // namespace dsa
