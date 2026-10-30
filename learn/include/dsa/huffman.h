#pragma once
// 第5章 Huffman 编码（教材 §5.2、§5.5）—— 第 13 天；第 30 天把优先级队列换成左式堆
//
// 这里只有声明；实现写在 src/huffman.cpp 里，那边现在都是 DSA_TODO();。

#include <map>
#include <string>

#include "dsa/bintree.h"

namespace dsa {

struct HuffChar {
    char ch = 0;      // 字符（合并出来的内部节点不用它）
    long long weight = 0;  // 频率
};

class HuffmanCoder {
public:
    // 统计 sample 中各字符的出现次数，建 Huffman 树，生成编码表。
    // 建树时需要反复取出权重最小的两棵树：第 13 天先用你的 List 实现（每次扫描找最小），第 30 天换成左式堆。
    // 只有一种字符时，它的编码是 "0"；sample 为空时编码表也为空。
    explicit HuffmanCoder(const std::string& sample);
    ~HuffmanCoder();
    HuffmanCoder(const HuffmanCoder&) = delete;
    HuffmanCoder& operator=(const HuffmanCoder&) = delete;

    const std::map<char, std::string>& table() const { return table_; }  // 编码表：字符 → "0101..."
    std::string encode(const std::string& text) const;  // 编码成 '0'/'1' 组成的串（text 里的字符都在编码表中）
    std::string decode(const std::string& bits) const;  // 解码：从树根出发，0 往左、1 往右，到叶子输出一个字符
    long long wpl() const;                              // 带权路径长度 = Σ 频率 × 编码长度

private:
    BinTree<HuffChar>* tree_ = nullptr;  // Huffman 树
    std::map<char, std::string> table_;  // 编码表
    std::map<char, long long> freq_;     // 各字符的频率
};

}  // namespace dsa
