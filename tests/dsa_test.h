#pragma once
// 极简测试框架（只有这一个头文件，不依赖第三方库）
//
//   TEST("名字") { ... }        定义一个用例
//   CHECK(cond)                 不成立时记一次失败，继续往下跑
//   CHECK_EQ(a, b)              同上，失败时打印两边的值
//   REQUIRE(cond) / REQUIRE_EQ  不成立时记失败并结束这个用例（随机对拍的循环里用它，免得刷屏）
//
// 被测函数还是 DSA_TODO() 时，这个用例记为“待实现”，不算失败；
// 设环境变量 DSA_STRICT=1 时“待实现”也算失败，用来确认一章已经全部完成。
// 随机数据用 dsa_test::rng()；失败时会打印随机种子，设 DSA_SEED=<种子> 就能复现同一组数据。
// 运行测试程序时可以带一个参数，只跑名字里含这段文字的用例。

#include <unistd.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ostream>
#include <random>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "dsa/common.h"

namespace dsa_test {

struct Case {
    const char* name;
    void (*fn)();
};
inline std::vector<Case>& registry() {
    static std::vector<Case> r;
    return r;
}
struct Registrar {
    Registrar(const char* name, void (*fn)()) { registry().push_back({name, fn}); }
};

struct Abort {};  // REQUIRE 失败时抛出，结束当前用例

inline std::vector<std::string>& messages() {  // 当前用例的失败信息
    static std::vector<std::string> m;
    return m;
}
inline void fail(const char* file, int line, const std::string& msg) {
    std::ostringstream os;
    os << "    " << file << ":" << line << "  " << msg;
    messages().push_back(os.str());
}

// ---------- 把值打印成字符串 ----------
template <class T, class = void>
struct Printable : std::false_type {};
template <class T>
struct Printable<T, std::void_t<decltype(std::declval<std::ostream&>() << std::declval<const T&>())>>
    : std::true_type {};

template <class T>
std::string show(const T& v);
template <class A, class B>
std::string show(const std::pair<A, B>& p) {
    return "(" + show(p.first) + ", " + show(p.second) + ")";
}
template <class T>
std::string show(const std::vector<T>& v) {
    std::string s = "[";
    for (std::size_t i = 0; i < v.size(); ++i) {
        if (i) s += ", ";
        if (i == 20) return s + "...（共 " + std::to_string(v.size()) + " 个）]";
        s += show(v[i]);
    }
    return s + "]";
}
template <class T>
std::string show(const T& v) {
    if constexpr (Printable<T>::value) {
        std::ostringstream os;
        os << v;
        return os.str();
    } else {
        return "（无法打印）";
    }
}

// ---------- 随机数 ----------
inline std::uint64_t seed() {
    static const std::uint64_t s = []() -> std::uint64_t {
        if (const char* e = std::getenv("DSA_SEED")) return std::strtoull(e, nullptr, 10);
        return (std::uint64_t)std::random_device{}() << 32 ^ std::random_device{}();
    }();
    return s;
}
inline std::mt19937_64& rng() {
    static std::mt19937_64 g(seed());
    return g;
}
// [lo, hi] 中的随机整数（闭区间）
inline long long randInt(long long lo, long long hi) {
    return std::uniform_int_distribution<long long>(lo, hi)(rng());
}
// n 个 [lo, hi] 中的随机整数
inline std::vector<int> randVector(std::size_t n, int lo, int hi) {
    std::vector<int> v(n);
    for (auto& x : v) x = (int)randInt(lo, hi);
    return v;
}

}  // namespace dsa_test

#define DSA_TEST_CAT2(a, b) a##b
#define DSA_TEST_CAT(a, b) DSA_TEST_CAT2(a, b)
#define TEST(name)                                                                                \
    static void DSA_TEST_CAT(dsa_test_fn_, __LINE__)();                                           \
    static ::dsa_test::Registrar DSA_TEST_CAT(dsa_test_reg_, __LINE__)(name,                      \
                                                                       &DSA_TEST_CAT(dsa_test_fn_, __LINE__)); \
    static void DSA_TEST_CAT(dsa_test_fn_, __LINE__)()

#define CHECK(cond)                                                                  \
    do {                                                                             \
        if (!(cond)) ::dsa_test::fail(__FILE__, __LINE__, "CHECK(" #cond ") 不成立"); \
    } while (0)

#define CHECK_EQ(a, b)                                                                                \
    do {                                                                                              \
        auto&& dsa_a_ = (a);                                                                          \
        auto&& dsa_b_ = (b);                                                                          \
        if (!(dsa_a_ == dsa_b_))                                                                      \
            ::dsa_test::fail(__FILE__, __LINE__,                                                      \
                             "CHECK_EQ(" #a ", " #b ")：" + ::dsa_test::show(dsa_a_) + " ≠ " +       \
                                 ::dsa_test::show(dsa_b_));                                           \
    } while (0)

#define REQUIRE(cond)                                                                  \
    do {                                                                               \
        if (!(cond)) {                                                                 \
            ::dsa_test::fail(__FILE__, __LINE__, "REQUIRE(" #cond ") 不成立");          \
            throw ::dsa_test::Abort{};                                                 \
        }                                                                              \
    } while (0)

#define REQUIRE_EQ(a, b)                                                                              \
    do {                                                                                              \
        auto&& dsa_a_ = (a);                                                                          \
        auto&& dsa_b_ = (b);                                                                          \
        if (!(dsa_a_ == dsa_b_)) {                                                                    \
            ::dsa_test::fail(__FILE__, __LINE__,                                                      \
                             "REQUIRE_EQ(" #a ", " #b ")：" + ::dsa_test::show(dsa_a_) + " ≠ " +     \
                                 ::dsa_test::show(dsa_b_));                                           \
            throw ::dsa_test::Abort{};                                                                \
        }                                                                                             \
    } while (0)

int main(int argc, char** argv) {
    using namespace dsa_test;
    const char* filter = argc > 1 ? argv[1] : nullptr;
    const char* strictEnv = std::getenv("DSA_STRICT");
    const bool strict = strictEnv && std::strcmp(strictEnv, "1") == 0;
    const bool color = isatty(1);
    auto paint = [&](const char* code, const char* text) {
        return color ? std::string("\033[") + code + "m" + text + "\033[0m" : std::string(text);
    };

    int pass = 0, failed = 0, todo = 0;
    for (const Case& c : registry()) {
        if (filter && !std::strstr(c.name, filter)) continue;
        messages().clear();
        std::string todoWhere;
        try {
            c.fn();
        } catch (const dsa::NotImplemented& e) {
            todoWhere = e.what();
        } catch (const Abort&) {
        } catch (const std::exception& e) {
            messages().push_back(std::string("    抛出了异常：") + e.what());
        } catch (...) {
            messages().push_back("    抛出了未知异常");
        }
        if (!messages().empty()) {
            ++failed;
            std::printf("%s %s\n", paint("31", "[失败]  ").c_str(), c.name);
            for (const auto& m : messages()) std::printf("%s\n", m.c_str());
        } else if (!todoWhere.empty()) {
            ++todo;
            std::printf("%s %s（%s）\n", paint(strict ? "31" : "33", "[待实现]").c_str(), c.name,
                        todoWhere.c_str());
        } else {
            ++pass;
            std::printf("%s %s\n", paint("32", "[通过]  ").c_str(), c.name);
        }
    }
    std::printf("通过 %d，失败 %d，待实现 %d\n", pass, failed, todo);
    if (failed)
        std::printf("这次的随机种子是 %llu，复现：DSA_SEED=%llu tools/test.sh\n",
                    (unsigned long long)seed(), (unsigned long long)seed());
    return (failed || (strict && todo)) ? 1 : 0;
}
