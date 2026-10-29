// 第12章：各种排序的耗时（毫秒），n = 20 万。dup 列是只有 10 种不同取值的数据（大量重复）。
// 运行：tools/bench.sh ch12_sorts

#include <random>
#include <vector>

#include "bench.h"
#include "dsa/vector.h"

using dsa::ShellSeq;
using dsa::Vector;

int main() {
    const int n = 200000;
    std::mt19937 rng(2026);
    std::vector<int> random(n), dup(n);
    for (auto& x : random) x = (int)rng();
    for (auto& x : dup) x = (int)(rng() % 10);
    bench::Table table("ch12_sorts", "algorithm,random_ms,dup_ms");
    // 第一列用编号：0 mergeSort  1 heapSort  2 quickSort  3 quickSortIter  4-7 shellSort(Shell, PS, Pratt, Sedgewick)
    for (int alg = 0; alg < 8; ++alg) {
        auto ms = [&](const std::vector<int>& data) {
            return bench::timeNs([&] {
                Vector<int> v(data.data(), (dsa::Rank)data.size());
                switch (alg) {
                    case 0: v.mergeSort(0, n); break;
                    case 1: v.heapSort(0, n); break;
                    case 2: v.quickSort(0, n); break;
                    case 3: v.quickSortIter(0, n); break;
                    case 4: v.shellSort(0, n, ShellSeq::Shell); break;
                    case 5: v.shellSort(0, n, ShellSeq::PS); break;
                    case 6: v.shellSort(0, n, ShellSeq::Pratt); break;
                    case 7: v.shellSort(0, n, ShellSeq::Sedgewick); break;
                }
                bench::keep(v[0]);
            }, 100) / 1e6;
        };
        table.row(alg, ms(random), ms(dup));
    }
}
