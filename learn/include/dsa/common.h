#pragma once
// 全仓库共用的基本定义

#include <stdexcept>
#include <string>

namespace dsa {

using Rank = unsigned int;  // 秩，和邓老师的代码保持一致，方便对照

// 还没实现的函数先写 DSA_TODO();
// 测试遇到它会记为“待实现”而不是“失败”，所以一章没写完时 CI 照样是绿的。
struct NotImplemented : std::logic_error {
    explicit NotImplemented(const std::string& where) : std::logic_error("待实现：" + where) {}
};

}  // namespace dsa

#define DSA_TODO() throw ::dsa::NotImplemented(__func__)
