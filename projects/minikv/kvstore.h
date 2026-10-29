#pragma once
// 综合项目一：minikv 的存储层 —— 第 38 天
//
// 用你自己的 B-树（include/dsa/btree.h）存键值对。KV 只按 key 比较，所以 B-树里同一个 key 只有一份。
// 这里的函数现在都是 DSA_TODO();。命令行界面 main.cpp 已经写好，它只调用下面这几个函数。

#include <string>
#include <utility>
#include <vector>

#include "dsa/btree.h"

namespace minikv {

struct KV {
    std::string key, value;
    bool operator<(const KV& o) const { return key < o.key; }
    bool operator>(const KV& o) const { return key > o.key; }
    bool operator<=(const KV& o) const { return key <= o.key; }
    bool operator>=(const KV& o) const { return key >= o.key; }
    bool operator==(const KV& o) const { return key == o.key; }
    bool operator!=(const KV& o) const { return key != o.key; }
};

class KVStore {
public:
    explicit KVStore(dsa::Rank order = 16) : tree_(order) {}

    void put(const std::string& key, const std::string& value);  // 插入；key 已存在时覆盖 value
    bool get(const std::string& key, std::string& value);        // 查询；存在时写进 value 并返回 true
    bool del(const std::string& key);                            // 删除；不存在时返回 false
    // 按 key 从小到大返回 [lo, hi) 里的所有键值对；要求 O(log n + 输出个数)，不能遍历整棵树
    std::vector<std::pair<std::string, std::string>> range(const std::string& lo, const std::string& hi);
    dsa::Rank size() const { return tree_.size(); }

private:
    dsa::BTree<KV> tree_;
};

inline void KVStore::put(const std::string& key, const std::string& value) {
    DSA_TODO();
}

inline bool KVStore::get(const std::string& key, std::string& value) {
    DSA_TODO();
}

inline bool KVStore::del(const std::string& key) {
    DSA_TODO();
}


inline std::vector<std::pair<std::string, std::string>> KVStore::range(const std::string& lo,
                                                                       const std::string& hi) {
    DSA_TODO();
}

}  // namespace minikv
