#pragma once
// 第9章 跳转表（教材 §9.2）—— 第 26 天
//
// 由若干层四联表组成，第 0 层（最底层）含有全部词条；每个词条插入时，
// 以 1/2 的概率向上再长一层（用 std::rand()），直到某次“抛硬币”失败。
// 每一层两端各有一个哨兵：head_[i] 和 tail_[i]，哨兵上下相连。
// 下面私有部分的设计可以按自己的想法改，但 level() 要返回层数。

#include <cstdlib>
#include <vector>

#include "dsa/dictionary.h"

namespace dsa {

template <typename T>
struct QNode;
template <typename T>
using QNodePosi = QNode<T>*;

template <typename T>
struct QNode {  // 四联表的节点：前驱、后继、上邻、下邻
    T entry{};
    QNodePosi<T> pred = nullptr, succ = nullptr, above = nullptr, below = nullptr;
    QNode() = default;
    QNode(T const& e, QNodePosi<T> p = nullptr, QNodePosi<T> s = nullptr, QNodePosi<T> a = nullptr,
          QNodePosi<T> b = nullptr)
        : entry(e), pred(p), succ(s), above(a), below(b) {}
};

template <typename K, typename V>
class Skiplist : public Dictionary<K, V> {
    using E = Entry<K, V>;

private:
    Rank size_ = 0;
    std::vector<QNodePosi<E>> head_, tail_;  // 各层的头、尾哨兵，下标 0 是最底层

    // 从最高层开始查找 k：命中时返回该词条所在塔的最顶上那个节点；
    // 否则返回底层中不大于 k 的最后一个节点（可能是底层的头哨兵）
    QNodePosi<E> skipSearch(K const& k);
    void addLevel();  // 在最上面加一层空的四联表

public:
    Skiplist();                  // 只有一层空的四联表          第 26 天
    ~Skiplist();                 // 释放所有节点                第 26 天
    Skiplist(const Skiplist&) = delete;
    Skiplist& operator=(const Skiplist&) = delete;

    Rank size() const override { return size_; }
    Rank level() const { return (Rank)head_.size(); }  // 层数
    bool put(K const& k, V const& v) override;          // 第 26 天
    V* get(K const& k) override;                        // 第 26 天
    bool remove(K const& k) override;                   // 第 26 天
};

template <typename K, typename V>
void Skiplist<K, V>::addLevel() {
    DSA_TODO();
}

template <typename K, typename V>
Skiplist<K, V>::Skiplist() {
    DSA_TODO();
}

template <typename K, typename V>
Skiplist<K, V>::~Skiplist() {
    // 待实现
}

template <typename K, typename V>
QNodePosi<Entry<K, V>> Skiplist<K, V>::skipSearch(K const& k) {
    DSA_TODO();
}

template <typename K, typename V>
V* Skiplist<K, V>::get(K const& k) {
    DSA_TODO();
}

template <typename K, typename V>
bool Skiplist<K, V>::put(K const& k, V const& v) {
    DSA_TODO();
}

template <typename K, typename V>
bool Skiplist<K, V>::remove(K const& k) {
    DSA_TODO();
}

}  // namespace dsa
