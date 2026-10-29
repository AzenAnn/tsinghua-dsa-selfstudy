#pragma once
// 第9章 散列表（教材 §9.3）—— 第 27 天
//
// 开放定址 + 懒惰删除：桶数组 ht 的每个桶要么为空，要么存一个词条；
// 删除时不把桶清空，而是标记为“懒惰删除”，这样查找链不会断。
// 两种试探方式：线性试探 h, h+1, h+2, ...；平方试探 h, h+1², h+2², ...（都对 M 取模）。
// 表长 M 取素数；（有效词条数 + 懒惰删除数）× 2 > M 时重散列，新表长取不小于 4N 的素数。
// 这样装填因子始终不超过 1/2（平方试探一定能找到空桶），重散列的总代价分摊下来是 O(1)。

#include <string>
#include <vector>

#include "dsa/dictionary.h"

namespace dsa {

enum class Probe { Linear, Quadratic };

// 散列码：把关键码变成一个整数（已经写好了整数的，字符串的要自己写）
inline std::size_t hashCode(int k) { return (std::size_t)(unsigned int)k; }
inline std::size_t hashCode(long long k) { return (std::size_t)((k >> 32) + (int)k); }
std::size_t hashCode(const std::string& s);  // 多项式散列码，实现在 src/hashtable.cpp    第 27 天

// 不小于 c 的最小素数（已经写好了）
inline Rank primeNLT(Rank c) {
    if (c < 2) c = 2;
    for (;; c++) {
        bool prime = true;
        for (Rank d = 2; (unsigned long long)d * d <= c; d++)
            if (c % d == 0) {
                prime = false;
                break;
            }
        if (prime) return c;
    }
}

template <typename K, typename V>
class Hashtable : public Dictionary<K, V> {
private:
    std::vector<Entry<K, V>*> ht;  // 桶数组，空桶为 nullptr
    std::vector<bool> removed;     // 懒惰删除标记
    Rank M;                        // 表长（素数）
    Rank N = 0;                    // 有效词条数
    Rank L = 0;                    // 懒惰删除的桶数
    Probe mode;
    long long probes_ = 0;         // 累计试探次数：每检查一个桶加 1（重散列时重新插入也算），测试和计时程序用

    Rank probe4Hit(K const& k);    // 沿查找链找关键码为 k 的桶；找不到时返回最后到达的空桶
    Rank probe4Free(K const& k);   // 沿查找链找第一个可以放新词条的桶（空桶或懒惰删除的桶）
    void rehash();                 // 重散列

public:
    explicit Hashtable(Rank c = 5, Probe mode = Probe::Linear);  // 表长取不小于 c 的素数
    ~Hashtable();
    Hashtable(const Hashtable&) = delete;
    Hashtable& operator=(const Hashtable&) = delete;

    Rank size() const override { return N; }
    Rank capacity() const { return M; }
    long long probes() const { return probes_; }
    bool put(K const& k, V const& v) override;
    V* get(K const& k) override;
    bool remove(K const& k) override;
};

template <typename K, typename V>
Hashtable<K, V>::Hashtable(Rank c, Probe mode) : mode(mode) {
    DSA_TODO();
}

template <typename K, typename V>
Hashtable<K, V>::~Hashtable() {
    // 待实现
}

template <typename K, typename V>
Rank Hashtable<K, V>::probe4Hit(K const& k) {
    DSA_TODO();
}

template <typename K, typename V>
Rank Hashtable<K, V>::probe4Free(K const& k) {
    DSA_TODO();
}

template <typename K, typename V>
void Hashtable<K, V>::rehash() {
    DSA_TODO();
}

template <typename K, typename V>
bool Hashtable<K, V>::put(K const& k, V const& v) {
    DSA_TODO();
}

template <typename K, typename V>
V* Hashtable<K, V>::get(K const& k) {
    DSA_TODO();
}

template <typename K, typename V>
bool Hashtable<K, V>::remove(K const& k) {
    DSA_TODO();
}

}  // namespace dsa
