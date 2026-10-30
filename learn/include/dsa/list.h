#pragma once
// 第3章 列表（教材 §3.1–3.5）
//
// 双向链表，带头哨兵 header 和尾哨兵 trailer。模板类，声明和实现都在这个文件里：
// 先是 ListNode 和 List 的定义，后面按天分段给出每个函数的实现位置，现在都是 DSA_TODO();。
// “p 的 n 个真前驱”指 p 前面紧挨着的 n 个节点（不含 p 本身）。

#include <utility>

#include "dsa/common.h"

namespace dsa {

template <typename T>
struct ListNode;
template <typename T>
using ListNodePosi = ListNode<T>*;  // 列表节点的位置

template <typename T>
struct ListNode {
    T data;
    ListNodePosi<T> pred = nullptr;  // 前驱
    ListNodePosi<T> succ = nullptr;  // 后继

    ListNode() = default;  // 给 header 和 trailer 用
    ListNode(T const& e, ListNodePosi<T> p = nullptr, ListNodePosi<T> s = nullptr) : data(e), pred(p), succ(s) {}

    ListNodePosi<T> insertAsPred(T const& e);  // 紧靠当前节点之前插入新节点，返回它   第 6 天
    ListNodePosi<T> insertAsSucc(T const& e);  // 紧靠当前节点之后插入新节点，返回它   第 6 天
};

template <typename T>
class List {
private:
    Rank _size;
    ListNodePosi<T> header;   // 头哨兵
    ListNodePosi<T> trailer;  // 尾哨兵

protected:
    void init();                                  // 创建空列表（只有两个哨兵）           第 6 天
    Rank clear();                                 // 删除所有节点，返回删除的个数         第 6 天
    void copyNodes(ListNodePosi<T> p, Rank n);    // 在末尾复制从 p 起的 n 个节点         第 6 天
    // 把 L 中从 q 起的 m 个节点归并到本列表从 p 起的 n 个节点里（两段都有序），返回归并后的首节点   第 7 天
    ListNodePosi<T> merge(ListNodePosi<T> p, Rank n, List<T>& L, ListNodePosi<T> q, Rank m);

public:
    // ---------- 构造与析构（第 6 天） ----------
    List() { init(); }
    List(List<T> const& L);                       // 复制整个列表
    List(List<T> const& L, Rank r, Rank n);       // 复制 L 中从秩 r 起的 n 个节点
    List(ListNodePosi<T> p, Rank n);              // 复制从节点 p 起的 n 个节点
    ~List();                                      // 释放所有节点（包括哨兵）
    List<T>& operator=(List<T> const&) = delete;  // 不需要赋值

    // ---------- 只读访问 ----------
    Rank size() const { return _size; }
    bool empty() const { return _size <= 0; }
    ListNodePosi<T> first() const { return header->succ; }  // 首节点（空列表时就是 trailer）
    ListNodePosi<T> last() const { return trailer->pred; }  // 末节点（空列表时就是 header）
    bool valid(ListNodePosi<T> p) const { return p && (trailer != p) && (header != p); }
    T& operator[](Rank r) const;                  // 按秩访问，O(r)                       第 6 天
    // 无序查找：在 p 的 n 个真前驱中，找最后一个（离 p 最近的）等于 e 的节点，找不到返回 nullptr   第 6 天
    ListNodePosi<T> find(T const& e, Rank n, ListNodePosi<T> p) const;
    ListNodePosi<T> find(T const& e) const { return find(e, _size, trailer); }
    // 有序查找：在 p 的 n 个真前驱中，找最后一个不大于 e 的节点；
    // 都比 e 大时，返回这 n 个前驱再往前的那个节点（可能是 header）                    第 7 天
    ListNodePosi<T> search(T const& e, Rank n, ListNodePosi<T> p) const;
    ListNodePosi<T> search(T const& e) const { return search(e, _size, trailer); }
    // 从 p 起的 n 个节点中最大者；有多个时返回最后一个（这样选择排序才稳定）           第 7 天
    ListNodePosi<T> selectMax(ListNodePosi<T> p, Rank n) const;
    ListNodePosi<T> selectMax() const { return selectMax(header->succ, _size); }

    // ---------- 可写访问 ----------
    ListNodePosi<T> insertAsFirst(T const& e);                // 第 6 天
    ListNodePosi<T> insertAsLast(T const& e);                 // 第 6 天
    ListNodePosi<T> insert(ListNodePosi<T> p, T const& e);    // 作为 p 的后继插入        第 6 天
    ListNodePosi<T> insert(T const& e, ListNodePosi<T> p);    // 作为 p 的前驱插入        第 6 天
    T remove(ListNodePosi<T> p);                              // 删除合法节点 p，返回其数据   第 6 天
    // 无序去重：和书上一样，遇到重复时删掉前面那个，所以每个值保留的是最后一次出现的；返回删除的个数   第 6 天
    Rank dedup();
    Rank uniquify();                                          // 有序去重，返回删除的个数   第 7 天
    void merge(List<T>& L) { merge(header->succ, _size, L, L.header->succ, L._size); }  // 归并有序列表 L，L 变空
    void reverse();                                           // 前后倒置                 第 7 天

    // ---------- 排序（第 7 天）：对从 p 起的 n 个节点排序 ----------
    void insertionSort(ListNodePosi<T> p, Rank n);
    void selectionSort(ListNodePosi<T> p, Rank n);
    void mergeSort(ListNodePosi<T>& p, Rank n);   // 排完后 p 指向这段新的首节点
    void sort(ListNodePosi<T> p, Rank n);         // 统一入口，用你写好的任何一种
    void sort() { sort(first(), _size); }

    // ---------- 遍历（第 6 天） ----------
    void traverse(void (*visit)(T&));
    template <typename VST>
    void traverse(VST&& visit);
};

// ======================================================================
// 第 6 天：列表（§3.1–3.3）
// ======================================================================

template <typename T>
ListNodePosi<T> ListNode<T>::insertAsPred(T const& e) {
    DSA_TODO();
}

template <typename T>
ListNodePosi<T> ListNode<T>::insertAsSucc(T const& e) {
    DSA_TODO();
}

template <typename T>
void List<T>::init() {
    DSA_TODO();
}

template <typename T>
Rank List<T>::clear() {
    DSA_TODO();
}

template <typename T>
void List<T>::copyNodes(ListNodePosi<T> p, Rank n) {
    DSA_TODO();
}

template <typename T>
List<T>::List(List<T> const& L) {
    DSA_TODO();
}

template <typename T>
List<T>::List(List<T> const& L, Rank r, Rank n) {
    DSA_TODO();
}

template <typename T>
List<T>::List(ListNodePosi<T> p, Rank n) {
    DSA_TODO();
}

template <typename T>
List<T>::~List() {
    // 待实现
}

template <typename T>
T& List<T>::operator[](Rank r) const {
    DSA_TODO();
}

template <typename T>
ListNodePosi<T> List<T>::find(T const& e, Rank n, ListNodePosi<T> p) const {
    DSA_TODO();
}

template <typename T>
ListNodePosi<T> List<T>::insertAsFirst(T const& e) {
    DSA_TODO();
}

template <typename T>
ListNodePosi<T> List<T>::insertAsLast(T const& e) {
    DSA_TODO();
}

template <typename T>
ListNodePosi<T> List<T>::insert(ListNodePosi<T> p, T const& e) {
    DSA_TODO();
}

template <typename T>
ListNodePosi<T> List<T>::insert(T const& e, ListNodePosi<T> p) {
    DSA_TODO();
}

template <typename T>
T List<T>::remove(ListNodePosi<T> p) {
    DSA_TODO();
}

template <typename T>
Rank List<T>::dedup() {
    DSA_TODO();
}

template <typename T>
void List<T>::traverse(void (*visit)(T&)) {
    DSA_TODO();
}

template <typename T>
template <typename VST>
void List<T>::traverse(VST&& visit) {
    DSA_TODO();
}

// ======================================================================
// 第 7 天：有序列表与排序（§3.4–3.5）
// ======================================================================

template <typename T>
Rank List<T>::uniquify() {
    DSA_TODO();
}

template <typename T>
ListNodePosi<T> List<T>::search(T const& e, Rank n, ListNodePosi<T> p) const {
    DSA_TODO();
}

template <typename T>
ListNodePosi<T> List<T>::selectMax(ListNodePosi<T> p, Rank n) const {
    DSA_TODO();
}

template <typename T>
void List<T>::insertionSort(ListNodePosi<T> p, Rank n) {
    DSA_TODO();
}

template <typename T>
void List<T>::selectionSort(ListNodePosi<T> p, Rank n) {
    DSA_TODO();
}

template <typename T>
ListNodePosi<T> List<T>::merge(ListNodePosi<T> p, Rank n, List<T>& L, ListNodePosi<T> q, Rank m) {
    DSA_TODO();
}

template <typename T>
void List<T>::mergeSort(ListNodePosi<T>& p, Rank n) {
    DSA_TODO();
}

template <typename T>
void List<T>::sort(ListNodePosi<T> p, Rank n) {
    DSA_TODO();
}

template <typename T>
void List<T>::reverse() {
    DSA_TODO();
}

}  // namespace dsa
