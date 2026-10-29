#pragma once
// 第2章 向量（教材 §2.1–2.8），另有第10章的堆排序、第12章的快速排序和希尔排序
//
// Vector 是模板类，模板的实现必须写在头文件里，所以声明和实现都在这个文件中：
// 先是类的定义（只有声明），后面按天分段给出每个函数的实现位置，现在都是 DSA_TODO();。
// 区间一律左闭右开 [lo, hi)。查找失败时返回 lo - 1；lo = 0 时就是 Rank(-1)（无符号数回绕），
// 这正是邓老师的设计：insert(search(e) + 1, e) 在任何情况下都把 e 插到正确位置。

#include <algorithm>
#include <cstdlib>
#include <utility>
#include <vector>

#include "dsa/common.h"

namespace dsa {

constexpr Rank DEFAULT_CAPACITY = 3;  // 默认的初始容量（实际应用中可以更大）

// Fibonacci 数列的游标（Fibonacci 查找要用），已经写好了
class Fib {
public:
    explicit Fib(Rank n) : f(1), g(0) {  // 初始化为不小于 n 的最小 Fibonacci 项
        while (g < n) next();
    }
    Rank get() const { return g; }
    Rank next() {  // 转到下一项
        g += f;
        f = g - f;
        return g;
    }
    Rank prev() {  // 转到上一项
        f = g - f;
        g -= f;
        return g;
    }

private:
    Rank f, g;  // f = fib(k - 1)，g = fib(k)
};

// 希尔排序的增量序列（第 36 天）
enum class ShellSeq { Shell, PS, Pratt, Sedgewick };

template <typename T>
class Vector {
protected:
    Rank _size;      // 规模
    Rank _capacity;  // 容量
    T* _elem;        // 数据区

    void copyFrom(T const* A, Rank lo, Rank hi);  // 复制数组区间 A[lo, hi)          第 3 天
    void expand();                                // 空间不足时扩容                   第 3 天
    void shrink();                                // 装填因子过小时缩容               第 3 天
    void merge(Rank lo, Rank mi, Rank hi);        // 归并 [lo, mi) 和 [mi, hi)        第 5 天

public:
    // ---------- 构造与析构（第 3 天） ----------
    explicit Vector(Rank c = DEFAULT_CAPACITY);   // 容量为 c 的空向量
    Vector(Rank c, Rank s, T const& v);           // 容量为 c、规模为 s、所有元素都是 v（s <= c）
    Vector(T const* A, Rank n);                   // 复制数组 A[0, n)
    Vector(T const* A, Rank lo, Rank hi);         // 复制数组区间 A[lo, hi)
    Vector(Vector<T> const& V);                   // 复制整个向量
    Vector(Vector<T> const& V, Rank lo, Rank hi); // 复制向量区间 V[lo, hi)
    ~Vector();                                    // 释放数据区

    // ---------- 只读访问 ----------
    Rank size() const { return _size; }
    bool empty() const { return !_size; }
    Rank capacity() const { return _capacity; }   // 测试用：检查扩容和缩容
    Rank disordered() const;                      // 相邻逆序对的个数                 第 5 天
    Rank find(T const& e) const { return find(e, 0, _size); }
    Rank find(T const& e, Rank lo, Rank hi) const;  // 无序查找：最后一个等于 e 的元素的秩，失败返回 lo - 1   第 4 天
    Rank search(T const& e) const { return (0 >= _size) ? Rank(-1) : search(e, 0, _size); }
    Rank search(T const& e, Rank lo, Rank hi) const;  // 有序查找：不大于 e 的最后一个元素的秩   第 5 天

    // 有序向量的几种查找（第 5 天）
    // A、B 版和 fibSearchA：找到 e 时返回它的秩（有多个时返回任意一个），找不到返回 Rank(-1)
    // C 版和 fibSearchB：返回不大于 e 的最后一个元素的秩，和 search 的语义相同
    Rank binSearchA(T const& e, Rank lo, Rank hi) const;
    Rank binSearchB(T const& e, Rank lo, Rank hi) const;
    Rank binSearchC(T const& e, Rank lo, Rank hi) const;
    Rank fibSearchA(T const& e, Rank lo, Rank hi) const;
    Rank fibSearchB(T const& e, Rank lo, Rank hi) const;

    // ---------- 可写访问 ----------
    T& operator[](Rank r);                         // 第 3 天
    const T& operator[](Rank r) const;             // 第 3 天
    Vector<T>& operator=(Vector<T> const& V);      // 第 3 天
    T remove(Rank r);                              // 删除秩为 r 的元素，返回它       第 4 天
    Rank remove(Rank lo, Rank hi);                 // 删除区间 [lo, hi)，返回删除的个数   第 4 天
    Rank insert(Rank r, T const& e);               // 把 e 插到秩 r（0 <= r <= size），返回 r   第 4 天
    Rank insert(T const& e) { return insert(_size, e); }  // 默认插在末尾
    void unsort(Rank lo, Rank hi);                 // 随机置乱区间 [lo, hi)            第 4 天
    void unsort() { unsort(0, _size); }
    Rank dedup();                                  // 无序去重：每个值只保留第一次出现的，返回删除的个数   第 4 天
    Rank uniquify();                               // 有序去重，O(n)，返回删除的个数   第 5 天

    // ---------- 排序 ----------
    void sort(Rank lo, Rank hi);                   // 统一入口，用你写好的任何一种排序   第 5 天
    void sort() { sort(0, _size); }
    void bubbleSort(Rank lo, Rank hi);             // 起泡排序（改进版：记录最后一次交换的位置）   第 5 天
    void mergeSort(Rank lo, Rank hi);              // 归并排序                         第 5 天
    void heapSort(Rank lo, Rank hi);               // 堆排序（就地）                   第 29 天
    Rank partitionLUG(Rank lo, Rank hi);           // 快速排序的轴点构造：LUG 版       第 34 天
    Rank partitionDUP(Rank lo, Rank hi);           // DUP 版（应对大量重复元素）       第 34 天
    Rank partitionLGU(Rank lo, Rank hi);           // LGU 版                           第 34 天
    void quickSort(Rank lo, Rank hi);              // 快速排序（递归，轴点构造用任一版本）   第 34 天
    void quickSortIter(Rank lo, Rank hi);          // 快速排序（迭代，用栈）           第 34 天
    void shellSort(Rank lo, Rank hi, ShellSeq seq = ShellSeq::Sedgewick);  // 希尔排序   第 36 天

    // ---------- 遍历（第 4 天） ----------
    void traverse(void (*visit)(T&));              // 用函数指针
    template <typename VST>
    void traverse(VST&& visit);                    // 用函数对象（包括 lambda）
};

// 随机置乱整个向量（第 4 天）
template <typename T>
void permute(Vector<T>& V);

// 堆的基本操作，作用在数组 A 上（第 29 天）：A[0, n) 看作一棵完全二叉树，i 的孩子是 2i+1、2i+2
template <typename T>
Rank percolateDown(T* A, Rank n, Rank i);  // 下滤 A[i]，返回它最终的位置
template <typename T>
Rank percolateUp(T* A, Rank i);            // 上滤 A[i]，返回它最终的位置
template <typename T>
void heapify(T* A, Rank n);                // Floyd 建堆，O(n)

// ======================================================================
// 第 3 天：构造、析构、动态空间管理（§2.3–2.4）
// ======================================================================

template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {
    DSA_TODO();
}

template <typename T>
Vector<T>::Vector(Rank c) {
    DSA_TODO();
}

template <typename T>
Vector<T>::Vector(Rank c, Rank s, T const& v) {
    DSA_TODO();
}

template <typename T>
Vector<T>::Vector(T const* A, Rank n) {
    DSA_TODO();
}

template <typename T>
Vector<T>::Vector(T const* A, Rank lo, Rank hi) {
    DSA_TODO();
}

template <typename T>
Vector<T>::Vector(Vector<T> const& V) {
    DSA_TODO();
}

template <typename T>
Vector<T>::Vector(Vector<T> const& V, Rank lo, Rank hi) {
    DSA_TODO();
}

template <typename T>
Vector<T>::~Vector() {
    // 待实现
}

template <typename T>
void Vector<T>::expand() {
    DSA_TODO();
}

template <typename T>
void Vector<T>::shrink() {
    DSA_TODO();
}

template <typename T>
T& Vector<T>::operator[](Rank r) {
    DSA_TODO();
}

template <typename T>
const T& Vector<T>::operator[](Rank r) const {
    DSA_TODO();
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& V) {
    DSA_TODO();
}

// ======================================================================
// 第 4 天：无序向量（§2.5）
// ======================================================================

template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
    DSA_TODO();
}

template <typename T>
void permute(Vector<T>& V) {
    DSA_TODO();
}

template <typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const {
    DSA_TODO();
}

template <typename T>
Rank Vector<T>::insert(Rank r, T const& e) {
    DSA_TODO();
}

template <typename T>
Rank Vector<T>::remove(Rank lo, Rank hi) {
    DSA_TODO();
}

template <typename T>
T Vector<T>::remove(Rank r) {
    DSA_TODO();
}

template <typename T>
Rank Vector<T>::dedup() {
    DSA_TODO();
}

template <typename T>
void Vector<T>::traverse(void (*visit)(T&)) {
    DSA_TODO();
}

template <typename T>
template <typename VST>
void Vector<T>::traverse(VST&& visit) {
    DSA_TODO();
}

// ======================================================================
// 第 5 天：有序向量与排序（§2.6–2.8）
// ======================================================================

template <typename T>
Rank Vector<T>::disordered() const {
    DSA_TODO();
}

template <typename T>
Rank Vector<T>::uniquify() {
    DSA_TODO();
}

template <typename T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const {
    DSA_TODO();
}

template <typename T>
Rank Vector<T>::binSearchA(T const& e, Rank lo, Rank hi) const {
    DSA_TODO();
}

template <typename T>
Rank Vector<T>::binSearchB(T const& e, Rank lo, Rank hi) const {
    DSA_TODO();
}

template <typename T>
Rank Vector<T>::binSearchC(T const& e, Rank lo, Rank hi) const {
    DSA_TODO();
}

template <typename T>
Rank Vector<T>::fibSearchA(T const& e, Rank lo, Rank hi) const {
    DSA_TODO();
}

template <typename T>
Rank Vector<T>::fibSearchB(T const& e, Rank lo, Rank hi) const {
    DSA_TODO();
}

template <typename T>
void Vector<T>::sort(Rank lo, Rank hi) {
    DSA_TODO();
}

template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) {
    DSA_TODO();
}

template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
    DSA_TODO();
}

template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
    DSA_TODO();
}

// ======================================================================
// 第 29 天：堆排序（§10.2.5），以及堆的基本操作
// ======================================================================

template <typename T>
Rank percolateDown(T* A, Rank n, Rank i) {
    DSA_TODO();
}

template <typename T>
Rank percolateUp(T* A, Rank i) {
    DSA_TODO();
}

template <typename T>
void heapify(T* A, Rank n) {
    DSA_TODO();
}

template <typename T>
void Vector<T>::heapSort(Rank lo, Rank hi) {
    DSA_TODO();
}

// ======================================================================
// 第 34 天：快速排序（§12.1）
// 三个 partition 都要先随机选一个元素做轴点，返回轴点最终的秩 p，
// 并保证 [lo, p) 的元素都 <= 轴点 <= (p, hi) 的元素。
// ======================================================================

template <typename T>
Rank Vector<T>::partitionLUG(Rank lo, Rank hi) {
    DSA_TODO();
}

template <typename T>
Rank Vector<T>::partitionDUP(Rank lo, Rank hi) {
    DSA_TODO();
}

template <typename T>
Rank Vector<T>::partitionLGU(Rank lo, Rank hi) {
    DSA_TODO();
}

template <typename T>
void Vector<T>::quickSort(Rank lo, Rank hi) {
    DSA_TODO();
}

template <typename T>
void Vector<T>::quickSortIter(Rank lo, Rank hi) {
    DSA_TODO();
}

// ======================================================================
// 第 36 天：希尔排序（§12.3）
// ======================================================================

template <typename T>
void Vector<T>::shellSort(Rank lo, Rank hi, ShellSeq seq) {
    DSA_TODO();
}

}  // namespace dsa
