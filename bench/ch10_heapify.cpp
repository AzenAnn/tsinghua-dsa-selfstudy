// 第10章：两种建堆方法的耗时（纳秒）。逐个插入是 O(n log n)，Floyd 批量建堆是 O(n)。
// 运行：tools/bench.sh ch10_heapify

#include <random>
#include <vector>

#include "bench.h"
#include "dsa/pq.h"

int main() {
    bench::Table table("ch10_heapify", "n,insert_one_by_one,floyd");
    std::mt19937 rng(2026);
    for (int n = 1000; n <= 512000; n *= 2) {
        std::vector<int> a(n);
        for (auto& x : a) x = (int)rng();
        double t1 = bench::timeNs([&] {
            dsa::PQ_ComplHeap<int> h;
            for (int x : a) h.insert(x);
            bench::keep(h.size());
        });
        double t2 = bench::timeNs([&] {
            dsa::PQ_ComplHeap<int> h(a.data(), (dsa::Rank)a.size());
            bench::keep(h.size());
        });
        table.row(n, t1, t2);
    }
}
