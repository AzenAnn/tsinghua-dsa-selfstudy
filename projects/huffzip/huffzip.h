#pragma once
// 综合项目二：huffzip，Huffman 文件压缩 —— 第 39 天
//
// 数据按字节处理（std::string 当字节数组用，里面可以有任意字节，包括 '\0'）。
// 压缩结果自己设计格式：至少要存下各字节的频率（或编码表）、原文长度、编码后的比特流（8 个比特装一个字节）。
// 建议用上自己写的 Huffman 树（第5章）、左式堆（第10章），实现写在 huffzip.cpp 里，现在都是 DSA_TODO();。
// 命令行界面 main.cpp 已经写好。

#include <string>

namespace huffzip {

std::string compress(const std::string& data);
std::string decompress(const std::string& packed);  // decompress(compress(x)) 必须等于 x

}  // namespace huffzip
