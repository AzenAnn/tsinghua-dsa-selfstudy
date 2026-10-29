// 第1章：Fibonacci 三种算法的实测耗时（纳秒）。
// fibR 是二分递归，耗时按 phi^n（约 1.618^n）增长；fibL、fibI 都是线性的。
// 运行：tools/bench.sh ch01_fib

#include "bench.h"
#include "dsa/ch01_intro.h"

using namespace dsa::ch01;

int main() {
    bench::Table table("ch01_fib", "n,fibR_ns,fibL_ns,fibI_ns");
    for (int n = 5; n <= 35; n += 5) {
        double r = bench::timeNs([&] { bench::keep(fibR(n)); });
        double l = bench::timeNs([&] {
            long long prev;
            bench::keep(fibL(n, prev));
        });
        double i = bench::timeNs([&] { bench::keep(fibI(n)); });
        table.row(n, r, l, i);
    }
}
