// 第9章：散列表线性试探和平方试探的平均试探次数。
// 先插入 n 个随机关键码，再查找 n 次（一半命中、一半不命中），统计每次操作平均检查了几个桶。
// 运行：tools/bench.sh ch09_probe

#include <random>

#include "bench.h"
#include "dsa/hashtable.h"

static double avgProbes(dsa::Probe mode, int n) {
    std::mt19937 rng(2026);
    dsa::Hashtable<int, int> h(5, mode);
    for (int i = 0; i < n; ++i) h.put((int)(rng() % 1000000000), i);
    long long before = h.probes();
    for (int i = 0; i < n; ++i) bench::keep(h.get((int)(rng() % 1000000000)));
    return (double)(h.probes() - before) / n;
}

int main() {
    bench::Table table("ch09_probe", "n,linear,quadratic");
    for (int n = 1000; n <= 256000; n *= 2) {
        double a = NAN, b = NAN;
        try {
            a = avgProbes(dsa::Probe::Linear, n);
            b = avgProbes(dsa::Probe::Quadratic, n);
        } catch (const dsa::NotImplemented&) {
        }
        table.row(n, a, b);
    }
}
