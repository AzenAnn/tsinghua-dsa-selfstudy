#pragma once
// 第9章 词典的接口（教材 §9.1）
//
// 跳转表 Skiplist 和散列表 Hashtable 都实现这个接口。
// 和书上略有不同：这里的词典不允许重复的关键码，put 一个已有的关键码时覆盖它的值。

#include "dsa/common.h"

namespace dsa {

template <typename K, typename V>
struct Entry {
    K key{};
    V value{};
    Entry() = default;
    Entry(K const& k, V const& v) : key(k), value(v) {}
};

template <typename K, typename V>
struct Dictionary {
    virtual ~Dictionary() = default;
    virtual Rank size() const = 0;
    virtual bool put(K const& k, V const& v) = 0;  // 插入；关键码已存在时覆盖值并返回 false
    virtual V* get(K const& k) = 0;                // 查找；不存在时返回 nullptr
    virtual bool remove(K const& k) = 0;           // 删除；不存在时返回 false
};

}  // namespace dsa
