# 实测复杂度

每个 `bench/<名字>.cpp` 编成一个计时程序，用 Release（-O2，不带 sanitizer）编译：

```bash
tools/bench.sh                     # 列出所有计时程序
tools/bench.sh ch01_fib            # 运行，结果打印成表格，同时写到 bench/results/ch01_fib.csv
python3 tools/plot.py ch01_fib --log   # 画成曲线 bench/results/ch01_fib.png（需要 matplotlib）
```

现有的计时程序：

| 程序 | 对照的理论 | 哪天用 |
|---|---|---|
| `ch01_fib` | Fibonacci 二分递归 O(φⁿ) 与线性 O(n) | D02 |
| `ch02_expand` | 加倍扩容的分摊 O(1) | D03 |
| `ch09_probe` | 线性试探与平方试探的平均试探次数 | D27 |
| `ch10_heapify` | 逐个插入 O(n log n) 与 Floyd 建堆 O(n) | D29 |
| `ch11_match` | 各种串匹配算法在不同字母表下的表现 | D33 |
| `ch12_sorts` | 各种排序，含大量重复元素的情况 | D34、D36 |

写新的计时程序时参考 `ch01_fib.cpp`：

- `bench::timeNs(函数)` 返回单次平均耗时（纳秒）；
- `bench::keep(值)` 防止编译器把结果优化掉；
- `bench::Table` 负责输出表格和 CSV。

每次实测完，在对应章节的笔记里写一句结论：实测曲线和理论复杂度是否吻合，不吻合的话原因是什么（常数、缓存、规模不够大……）。
