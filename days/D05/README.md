# D05 · 11-03 周二 · 第2章 向量（三）：有序向量与排序

> 教材 §2.6–2.8 ｜ 讲义 第2章 ｜ 约 5 小时
> [← D04](../D04/README.md) ｜ [总计划](../../PLAN.md) ｜ [D06 →](../D06/README.md)

## 今天的目标

实现有序向量的去重、三个版本的二分查找、两个版本的 Fibonacci 查找，以及起泡排序和归并排序；第2章收尾。

## 今天要动的文件

| 文件 | 内容 |
|---|---|
| `include/dsa/vector.h` | “第 5 天”那一段：disordered、uniquify、search、binSearchA/B/C、fibSearchA/B、sort、bubbleSort、merge、mergeSort |
| `exercises/ch02/` | 第2章课后习题 |
| `problems/ch02/` | 第2章的 OJ 题 |

## 第 1 步：读书（约 1.5 小时）

打开教材 `deng/local-only/dsacpp-3rd-edn.pdf`，读 §2.6–2.8；再看讲义 `deng/local-only/DSA-2026F-10up-V.pdf` 的第2章。读的时候想清楚这几个问题，读完能用自己的话回答：

- §2.6.5–2.6.8 三个版本的二分查找各自的不变式是什么？C 版为什么能返回“不大于 e 的最后一个”？
- §2.6.6 Fibonacci 查找为什么平均查找长度比二分查找短？
- §2.7 比较树与 Ω(n log n) 下界。
- §2.8 归并排序为什么稳定？merge 里哪一个比较符号决定了稳定性？

## 第 2 步：写代码（约 2 小时）

合上书，按下面的顺序写，每写完一个函数就运行一次测试：

1. 写 `disordered` 和 `uniquify`（双指针，O(n)）。
2. 写 `binSearchA`（三分支）、`binSearchB`（两分支，最后再判断一次相等）、`binSearchC`（两分支，返回 lo - 1）。每写一个就运行 `tools/test.sh ch02 binSearch`。
3. 写 `fibSearchA`、`fibSearchB`。`Fib` 类已经写好，用 `Fib fib(hi - lo)` 得到不小于区间长度的 Fibonacci 数，`fib.prev()` 往回走。
4. 写 `search`：调用你认为最好的那个版本（语义必须和 C 版一样）。
5. 写改进版的 `bubbleSort`（记录最后一次交换的位置，下一趟只扫到那里）。
6. 写 `merge` 和 `mergeSort`；`sort` 调用 mergeSort。
7. 运行 `DSA_STRICT=1 tools/test.sh ch02`：第2章的 26 个用例全部通过（第 29、34、36 天的堆排序、快排、希尔排序在其他测试文件里，不影响这里）。

## 第 3 步：检测与调试

运行：

```bash
DSA_STRICT=1 tools/test.sh ch02
```

全部完成时，这 26 个用例都显示 `[通过]`，每个测试程序的最后一行是 `通过 …，失败 0，待实现 0`。还没写的函数显示黄色的 `[待实现]`；写错的显示红色的 `[失败]`，下面跟着出错的那行测试代码和两边的实际值。

调试提示：

- 查找的测试都在子区间 [lo, hi) 上做，别默认整个向量。
- “稳定”的用例不通过：merge 里遇到相等元素时，应该先取前半段的。
- binSearchB 在空区间上要直接返回 Rank(-1)，否则会访问 `_elem[lo]` 越界。

## 第 4 步：对照邓老师的代码

测试通过以后再看，逐处对比你的写法，把差异和自己没想到的地方记进笔记：

- `deng/code/src/vector/Vector_search_binary_A.h`、`Vector_search_binary_B.h`、`Vector_search_binary_C.h`、`Vector_search_fibonaccian_A.h`、`Vector_search_fibonaccian_B.h`、`Vector_uniquify.h`、`vector_bubblesort_A.h`、`vector_bubblesort_B.h`、`vector_bubblesort_C.h`、`Vector_merge.h`。

## 第 5 步：练习（约 1 小时）

- 第2章课后习题：带 * 的题和编程题。
- OJ：LeetCode 26、704、35、88，洛谷 P1908 逆序对（在归并时顺便统计逆序对）。

## 第 6 步：笔记与提交（约 0.5 小时）

在 `notes/ch02-向量.md` 里写：

- 三个二分查找版本的不变式和返回值。
- Fibonacci 查找的平均查找长度。
- 比较排序 Ω(n log n) 下界的比较树证明。
- 第2章“易错点”汇总。

把下面的完成清单打勾，然后：

```bash
python3 tools/progress.py
git add -A
git commit -m "D05: 完成第2章，ch02 全部测试通过"
git push
```

## ✅ 完成清单

- [ ] 读完教材 §2.6–2.8 和讲义，能回答上面的问题
- [ ] 写完今天的代码
- [ ] `DSA_STRICT=1 tools/test.sh ch02` 的结果符合预期
- [ ] 对照了邓老师的代码，差异记进笔记
- [ ] 完成今天的练习
- [ ] 写完笔记，提交并推送
