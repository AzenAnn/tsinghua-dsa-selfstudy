# D34 · 12-02 周三 · 第12章 排序（一）：快速排序

> 教材 §12.1 ｜ 讲义 第12章 ｜ 约 5 小时
> [← D33](../../D33-D40/D33/README.md) ｜ [总计划](../../../../PLAN.md) ｜ [D35 →](../../D33-D40/D35/README.md)

## 今天的目标

实现三种轴点构造（LUG、DUP、LGU）和快速排序的递归版、迭代版。

## 今天要动的文件

| 文件 | 内容 |
|---|---|
| `learn/include/dsa/vector.h` | “第 34 天”那一段：partitionLUG、partitionDUP、partitionLGU、quickSort、quickSortIter |

## 第 1 步：读书（约 1.5 小时）

打开教材 `deng/local-only/dsacpp-3rd-edn.pdf`，读 §12.1；再看讲义 `deng/local-only/DSA-2026F-10up-V.pdf` 的第12章。读的时候想清楚这几个问题，读完能用自己的话回答：

- §12.1.2 轴点构造的 LUG 版：L、G 两个区向中间扩展。
- §12.1.4 大量重复元素时 LUG 为什么退化？DUP 版改了哪里？
- §12.1.5 LGU 版。
- §12.1.3 快排的平均比较次数约 1.386 n log n 的推导。

## 第 2 步：写代码（约 2 小时）

合上书，按下面的顺序写，每写完一个函数就运行一次测试：

1. 三个 partition 开头都先随机选一个元素和 `_elem[lo]` 交换，作为轴点。
2. 写 `partitionLUG`、`partitionDUP`、`partitionLGU`，每写一个运行 `tools/test.sh ch12 partition`。
3. 写 `quickSort`（用 DUP 版）和 `quickSortIter`（用栈代替递归；为了不和第4章的 Stack 互相包含，可以用一个简单的数组当栈）。
4. 运行 `tools/test.sh ch12 D34`。

## 第 3 步：检测与调试

运行：

```bash
tools/test.sh ch12 D34
```

全部完成时，这 5 个用例都显示 `[通过]`，每个测试程序的最后一行是 `通过 …，失败 0，待实现 0`。还没写的函数显示黄色的 `[待实现]`；写错的显示红色的 `[失败]`，下面跟着出错的那行测试代码和两边的实际值。

调试提示：

- “全是相同元素时不能退化”统计了比较次数：quickSort 用 LUG 版就会在这里失败，换成 DUP 版。
- partition 只能动 [lo, hi) 里的元素。

实测复杂度：

- 运行 `tools/bench.sh ch12_sorts`（今天先看 quickSort 和 mergeSort 两行；heapSort 在第 29 天已写好，shellSort 后天写）。

## 第 4 步：对照邓老师的代码

测试通过以后再看，逐处对比你的写法，把差异和自己没想到的地方记进笔记：

- `deng/code/src/vector/vector_partition_LUG.h`、`vector_partition_DUP.h`、`vector_partition_LGU.h`、`vector_quickSort_iterative.h`。

## 第 5 步：练习（约 1 小时）

- 课后习题（每题一个文件，打开后在“我的解答”下面写；编程题的代码写在同目录的同名 `.cpp` 里）：
  - 必做：[[12-1]](../../../exercises/ch12/12-1.md)
  - 选做：无
- OJ 题（在 [learn/problems/README.md](../../../problems/README.md) 里打勾；新建题目用 `python3 tools/new.py problem D34 luogu-P1234 题名`，样例测试用 `tools/run.sh`）：
  - 必做：[力扣 75. 颜色分类](https://leetcode.cn/problems/sort-colors/)（中等，三路划分）
  - 热身（选做）：[力扣 912. 排序数组](https://leetcode.cn/problems/sort-an-array/)（中等，用快排交，注意大量重复）

## 第 6 步：笔记与提交（约 0.5 小时）

在 `learn/notes/ch12-排序.md` 里写：

- 三种 partition 的不变式；快排平均比较次数的推导。

把下面的完成清单打勾，然后：

```bash
python3 tools/progress.py
git add -A
git commit -m "D34: 快速排序"
git push
```

## ✅ 完成清单

- [ ] 读完教材 §12.1 和讲义，能回答上面的问题
- [ ] 写完今天的代码
- [ ] `tools/test.sh ch12 D34` 的结果符合预期
- [ ] 对照了邓老师的代码，差异记进笔记
- [ ] 完成今天的练习
- [ ] 写完笔记，提交并推送
