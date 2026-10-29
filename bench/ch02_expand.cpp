// 第2章：向量扩容的分摊复杂度。逐个 insert 到末尾，测每次插入的平均耗时（纳秒）。
// 加倍扩容时这一列应该基本是常数；把 expand() 临时改成“容量 + 固定常数”再跑一次，会看到它随 n 线性增长。
// 运行：tools/bench.sh ch02_expand

#include "bench.h"
#include "dsa/vector.h"

int main() {
    bench::Table table("ch02_expand", "n,insert_ns");
    for (int n = 1000; n <= 1024000; n *= 2) {
        double t = bench::timeNs([&] {
            dsa::Vector<int> v;
            for (int i = 0; i < n; ++i) v.insert(i);
            bench::keep(v.size());
        });
        table.row(n, t / n);
    }
}
