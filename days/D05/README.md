# D05 · 11-03 周二 · 第2章 向量（三）：有序向量与排序

> 教材 §2.6–2.8 ｜ 讲义 第2章 ｜ 约 5 小时
> [← D04](../D04/README.md) ｜ [总计划](../../PLAN.md) ｜ [D06 →](../D06/README.md)

## 今天的目标

实现有序向量的去重、三个版本的二分查找、两个版本的 Fibonacci 查找，以及起泡排序和归并排序；第2章收尾。

## 今天要动的文件

| 文件 | 内容 |
|---|---|
| `include/dsa/vector.h` | “第 5 天”那一段：disordered、uniquify、search、binSearchA/B/C、fibSearchA/B、sort、bubbleSort、merge、mergeSort |
| `exercises/ch02/` | 第2章课后习题（今天的题号见“练习”一节） |
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

- 课后习题（每题一个文件，打开后在“我的解答”下面写；编程题的代码写在同目录的同名 `.cpp` 里）：
  - 必做：[[2-13]](../../exercises/ch02/2-13.md)、[[2-15]](../../exercises/ch02/2-15.md)、[[2-17]](../../exercises/ch02/2-17.md)、[[2-18]](../../exercises/ch02/2-18.md)、[[2-21]](../../exercises/ch02/2-21.md)、[[2-24]](../../exercises/ch02/2-24.md)、[[2-26]](../../exercises/ch02/2-26.md)、[[2-28]](../../exercises/ch02/2-28.md)、[[2-30]](../../exercises/ch02/2-30.md)、[[2-31]](../../exercises/ch02/2-31.md)、[[2-34]](../../exercises/ch02/2-34.md)、[[2-37]](../../exercises/ch02/2-37.md)、[[2-41]](../../exercises/ch02/2-41.md)
  - 选做：[[2-14]](../../exercises/ch02/2-14.md)、[[2-16]](../../exercises/ch02/2-16.md)、[[2-19]](../../exercises/ch02/2-19.md)、[[2-20]](../../exercises/ch02/2-20.md)、[[2-22]](../../exercises/ch02/2-22.md)、[[2-23]](../../exercises/ch02/2-23.md)、[[2-25]](../../exercises/ch02/2-25.md)、[[2-27]](../../exercises/ch02/2-27.md)、[[2-29]](../../exercises/ch02/2-29.md)、[[2-32]](../../exercises/ch02/2-32.md)、[[2-33]](../../exercises/ch02/2-33.md)、[[2-35]](../../exercises/ch02/2-35.md)、[[2-36]](../../exercises/ch02/2-36.md)、[[2-38]](../../exercises/ch02/2-38.md)、[[2-39]](../../exercises/ch02/2-39.md)、[[2-40]](../../exercises/ch02/2-40.md)
- 今天是第2章的最后一天：打开 [`exercises/ch02/README.md`](../../exercises/ch02/README.md)，把本章前几天没做完的必做题补上。
- OJ 题（在 [problems/README.md](../../problems/README.md) 里打勾；新建题目用 `python3 tools/new.py problem chNN luogu-P1234 题名`，样例测试用 `tools/run.sh`）：
  - 必做：[力扣 34. 在排序数组中查找元素的第一个和最后一个位置](https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/)（中等，二分的边界）；[洛谷 P2249 【深基13.例1】查找](https://www.luogu.com.cn/problem/P2249)（普及−，二分，返回第一次出现）；[洛谷 P1908 逆序对](https://www.luogu.com.cn/problem/P1908)（普及/提高−，归并时统计）；[洛谷 P1873 [COCI 2011/2012 #5] EKO / 砍树](https://www.luogu.com.cn/problem/P1873)（普及−，二分答案）；[洛谷 P2678 [NOIP 2015 提高组] 跳石头](https://www.luogu.com.cn/problem/P2678)（普及/提高−，二分答案）
  - 热身（选做）：[力扣 704. 二分查找](https://leetcode.cn/problems/binary-search/)（简单）；[力扣 35. 搜索插入位置](https://leetcode.cn/problems/search-insert-position/)（简单，search 的语义）；[力扣 26. 删除有序数组中的重复项](https://leetcode.cn/problems/remove-duplicates-from-sorted-array/)（简单，uniquify）；[力扣 88. 合并两个有序数组](https://leetcode.cn/problems/merge-sorted-array/)（简单，merge）
  - 挑战（选做）：[洛谷 P1083 [NOIP 2012 提高组] 借教室](https://www.luogu.com.cn/problem/P1083)（普及/提高−，二分 + 差分）；[洛谷 P1966 [NOIP 2013 提高组] 火柴排队](https://www.luogu.com.cn/problem/P1966)（提高+/省选−，转化为逆序对）；[洛谷 P1309 [NOIP 2011 普及组] 瑞士轮](https://www.luogu.com.cn/problem/P1309)（普及/提高−，每轮只需归并，不用重排）；[力扣 493. 翻转对](https://leetcode.cn/problems/reverse-pairs/)（困难，归并中统计）；[力扣 315. 计算右侧小于当前元素的个数](https://leetcode.cn/problems/count-of-smaller-numbers-after-self/)（困难，归并中统计）

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
