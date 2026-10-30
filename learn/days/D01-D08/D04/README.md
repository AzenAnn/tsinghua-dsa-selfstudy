# D04 · 11-02 周一 · 第2章 向量（二）：无序向量

> 教材 §2.5 ｜ 讲义 第2章 ｜ 约 5 小时
> [← D03](../../D01-D08/D03/README.md) ｜ [总计划](../../../../PLAN.md) ｜ [D05 →](../../D01-D08/D05/README.md)

## 今天的目标

实现无序向量的置乱、查找、插入、删除、去重、遍历。

## 今天要动的文件

| 文件 | 内容 |
|---|---|
| `learn/include/dsa/vector.h` | “第 4 天”那一段：unsort、permute、find、insert、remove（区间和单个）、dedup、两个 traverse |

## 第 1 步：读书（约 1.5 小时）

打开教材 `deng/local-only/dsacpp-3rd-edn.pdf`，读 §2.5；再看讲义 `deng/local-only/DSA-2026F-10up-V.pdf` 的第2章。读的时候想清楚这几个问题，读完能用自己的话回答：

- §2.5.5–2.5.6 为什么要先实现“区间删除”，再用它实现“单元素删除”？反过来有什么问题？
- §2.5.4 find 为什么从后往前找？失败时为什么返回 lo - 1？
- §2.5.7 dedup 的不变式是什么？复杂度是多少？

## 第 2 步：写代码（约 2 小时）

合上书，按下面的顺序写，每写完一个函数就运行一次测试：

1. 写 `unsort` 和 `permute`（从后往前，每次和前面随机一个位置交换）。
2. 写 `find(e, lo, hi)`：从 hi 往前找第一个等于 e 的；找不到返回 lo - 1。注意 Rank 是无符号数，`lo - 1` 在 lo = 0 时会回绕成 Rank(-1)，这正是约定的返回值。
3. 写 `insert(r, e)`：先 `expand()`，再把 [r, size) 整体后移一位。运行 `tools/test.sh ch02 insert`。
4. 写区间删除 `remove(lo, hi)`：把 [hi, size) 整体前移，更新规模，最后 `shrink()`；再用它写单元素删除 `remove(r)`。
5. 写 `dedup`：对每个元素，在它前面查找有没有相同的，有就删掉它。
6. 写两个 `traverse`：对每个元素调用 visit。
7. 运行 `tools/test.sh ch02 D04`，7 个用例都应通过；再运行 `tools/test.sh ch02` 确认 D03 的用例没有被改坏。

## 第 3 步：检测与调试

运行：

```bash
tools/test.sh ch02 D04
```

全部完成时，这 7 个用例都显示 `[通过]`，每个测试程序的最后一行是 `通过 …，失败 0，待实现 0`。还没写的函数显示黄色的 `[待实现]`；写错的显示红色的 `[失败]`，下面跟着出错的那行测试代码和两边的实际值。

调试提示：

- 随机操作对拍失败时，会显示是第几步、哪个操作结果不一致；用 `DSA_SEED` 重现后，在你的函数里打印中间状态。
- `insert` 后移元素要从后往前挪，否则会覆盖。
- 无符号 Rank 的循环 `for (Rank i = n - 1; i >= 0; i--)` 永远不会结束（i >= 0 恒成立），这是常见的坑。

## 第 4 步：对照邓老师的代码

测试通过以后再看，逐处对比你的写法，把差异和自己没想到的地方记进笔记：

- `deng/code/src/vector/Vector_insert.h`、`vector_remove.h`、`vector_removeInterval.h`、`vector_find.h`、`Vector_deduplicate.h`、`vector_traverse.h`。

## 第 5 步：练习（约 1 小时）

- 课后习题（每题一个文件，打开后在“我的解答”下面写；编程题的代码写在同目录的同名 `.cpp` 里）：
  - 必做：[[2-4]](../../../exercises/ch02/2-4.md)、[[2-5]](../../../exercises/ch02/2-5.md)、[[2-6]](../../../exercises/ch02/2-6.md)、[[2-9]](../../../exercises/ch02/2-9.md)、[[2-11]](../../../exercises/ch02/2-11.md)、[[2-12]](../../../exercises/ch02/2-12.md)
  - 选做：[[2-7]](../../../exercises/ch02/2-7.md)、[[2-8]](../../../exercises/ch02/2-8.md)、[[2-10]](../../../exercises/ch02/2-10.md)
- OJ 题（在 [learn/problems/README.md](../../../problems/README.md) 里打勾；新建题目用 `python3 tools/new.py problem D04 luogu-P1234 题名`，样例测试用 `tools/run.sh`）：
  - 必做：[力扣 283. 移动零](https://leetcode.cn/problems/move-zeroes/)（简单，就地、一趟）；[力扣 189. 轮转数组](https://leetcode.cn/problems/rotate-array/)（中等，三次倒置）
  - 热身（选做）：[力扣 27. 移除元素](https://leetcode.cn/problems/remove-element/)（简单，区间删除的思路）

## 第 6 步：笔记与提交（约 0.5 小时）

在 `learn/notes/ch02-向量.md` 里写：

- 区间删除和逐个删除的复杂度对比。
- dedup 的不变式和正确性。

把下面的完成清单打勾，然后：

```bash
python3 tools/progress.py
git add -A
git commit -m "D04: Vector 无序向量的操作"
git push
```

## ✅ 完成清单

- [ ] 读完教材 §2.5 和讲义，能回答上面的问题
- [ ] 写完今天的代码
- [ ] `tools/test.sh ch02 D04` 的结果符合预期
- [ ] 对照了邓老师的代码，差异记进笔记
- [ ] 完成今天的练习
- [ ] 写完笔记，提交并推送
