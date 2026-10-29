#pragma once
// 计时小工具：测一段代码的平均耗时，结果同时打印成表格并写成 CSV，方便和理论复杂度对照。
// CSV 写在 bench/results/<名字>.csv；装了 matplotlib 可以用 tools/plot.py 画成曲线。

#include <chrono>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <functional>
#include <sstream>
#include <string>
#include <type_traits>

#include "dsa/common.h"

namespace bench {

// 反复运行 f，直到累计至少 minMs 毫秒，返回单次平均耗时（纳秒）。
// f 里调用了还没实现的函数时返回 NaN，表格里显示“待实现”。
inline double timeNs(const std::function<void()>& f, double minMs = 30) {
    using Clock = std::chrono::steady_clock;
    long long reps = 0;
    double elapsedMs = 0;
    const auto start = Clock::now();
    try {
        do {
            f();
            ++reps;
            elapsedMs = std::chrono::duration<double, std::milli>(Clock::now() - start).count();
        } while (elapsedMs < minMs);
    } catch (const dsa::NotImplemented&) {
        return NAN;
    }
    return elapsedMs * 1e6 / reps;
}

// 防止编译器把没被用到的计算结果优化掉
template <class T>
inline void keep(const T& value) {
    asm volatile("" : : "g"(&value) : "memory");
}

// 一张结果表：表头用逗号分隔，每一行的值依次给出
class Table {
public:
    Table(const std::string& name, const std::string& header)
        : out_(std::string(DSA_BENCH_DIR) + "/" + name + ".csv") {
        out_ << header << "\n";
        std::stringstream ss(header);
        for (std::string col; std::getline(ss, col, ',');) std::printf("%16s", col.c_str());
        std::printf("\n");
        path_ = std::string(DSA_BENCH_DIR) + "/" + name + ".csv";
    }
    ~Table() { std::printf("结果已写入 %s\n", path_.c_str()); }

    template <class... Ts>
    void row(const Ts&... values) {
        bool first = true;
        ((put(values, first), first = false), ...);
        out_ << "\n";
        std::printf("\n");
        out_.flush();
        std::fflush(stdout);
    }

private:
    template <class T>
    void put(const T& v, bool first) {
        if (!first) out_ << ",";
        if constexpr (std::is_floating_point_v<T>) {
            if (std::isnan(v)) {
                std::printf("%16s", "待实现");
                return;  // CSV 里留空
            }
            out_ << v;
            std::printf("%16.1f", (double)v);
        } else {
            out_ << v;
            std::printf("%16lld", (long long)v);
        }
    }

    std::ofstream out_;
    std::string path_;
};

}  // namespace bench
