# D29 · 11-27 周五 · 第10章 优先级队列（一）：完全二叉堆

> 教材 §10.1–10.2 ｜ 讲义 第10章 ｜ 约 5 小时
> [← D28](../D28/README.md) ｜ [总计划](../../PLAN.md) ｜ [D30 →](../D30/README.md)

## 今天的目标

实现堆的上滤、下滤、Floyd 建堆，完全二叉堆 PQ_ComplHeap，以及向量的就地堆排序。

## 今天要动的文件

| 文件 | 内容 |
|---|---|
| `include/dsa/vector.h` | “第 29 天”那一段：percolateDown、percolateUp、heapify、Vector::heapSort |
| `include/dsa/pq.h` | “第 29 天”那一段：PQ_ComplHeap 的构造、insert、getMax、delMax |

## 第 1 步：读书（约 1.5 小时）

打开教材 `deng/local-only/dsacpp-3rd-edn.pdf`，读 §10.1–10.2；再看讲义 `deng/local-only/DSA-2026F-10up-V.pdf` 的第10章。读的时候想清楚这几个问题，读完能用自己的话回答：

- §10.2.2 完全二叉堆用向量存储时，i 的父亲和孩子的秩。
- §10.2.4 Floyd 建堆为什么是 O(n)（所有节点高度之和）？
- §10.2.5 就地堆排序。

## 第 2 步：写代码（约 2 小时）

合上书，按下面的顺序写，每写完一个函数就运行一次测试：

1. 在 `vector.h` 里写 `percolateDown`、`percolateUp`、`heapify`（从最后一个内部节点开始，自下而上逐个下滤）。运行 `tools/test.sh ch10 percolate`。
2. 写 `Vector::heapSort`：先 heapify，再反复把堆顶和末尾交换、堆的规模减一、下滤。
3. 在 `pq.h` 里写 `PQ_ComplHeap`：insert 是末尾插入再上滤；delMax 是末元素移到堆顶再下滤。
4. 运行 `tools/test.sh ch10 D29`，4 个用例全部通过。

## 第 3 步：检测与调试

运行：

```bash
tools/test.sh ch10 D29
```

全部完成时，这 4 个用例都显示 `[通过]`，每个测试程序的最后一行是 `通过 …，失败 0，待实现 0`。还没写的函数显示黄色的 `[待实现]`；写错的显示红色的 `[失败]`，下面跟着出错的那行测试代码和两边的实际值。

调试提示：

- 这里是大顶堆：A[i] 不小于它的孩子。
- PQ_ComplHeap 同时继承了 PQ 和 Vector；调用 Vector 的 insert 要写 `Vector<T>::insert(e)`。

实测复杂度：

- 运行 `tools/bench.sh ch10_heapify`，比较逐个插入建堆和 Floyd 建堆。

## 第 4 步：对照邓老师的代码

测试通过以后再看，逐处对比你的写法，把差异和自己没想到的地方记进笔记：

- `deng/code/src/PQ_ComplHeap/`。

## 第 5 步：练习（约 1 小时）

- 课后习题（每题一个文件，打开后在“我的解答”下面写；编程题的代码写在同目录的同名 `.cpp` 里）：
  - 必做：[[10-1]](../../exercises/ch10/10-1.md)、[[10-2]](../../exercises/ch10/10-2.md)、[[10-3]](../../exercises/ch10/10-3.md)、[[10-4]](../../exercises/ch10/10-4.md)、[[10-8]](../../exercises/ch10/10-8.md)、[[10-9]](../../exercises/ch10/10-9.md)、[[10-11]](../../exercises/ch10/10-11.md)、[[10-14]](../../exercises/ch10/10-14.md)
  - 选做：[[10-5]](../../exercises/ch10/10-5.md)、[[10-6]](../../exercises/ch10/10-6.md)、[[10-7]](../../exercises/ch10/10-7.md)、[[10-10]](../../exercises/ch10/10-10.md)、[[10-12]](../../exercises/ch10/10-12.md)
- OJ 题（在 [problems/README.md](../../problems/README.md) 里打勾；新建题目用 `python3 tools/new.py problem chNN luogu-P1234 题名`，样例测试用 `tools/run.sh`）：
  - 必做：[力扣 215. 数组中的第K个最大元素](https://leetcode.cn/problems/kth-largest-element-in-an-array/)（中等）；[洛谷 P1168 中位数](https://www.luogu.com.cn/problem/P1168)（普及/提高−，对顶堆）；[力扣 295. 数据流的中位数](https://leetcode.cn/problems/find-median-from-data-stream/)（困难，对顶堆）；[洛谷 P1631 序列合并](https://www.luogu.com.cn/problem/P1631)（普及+/提高）；[洛谷 P2085 最小函数值](https://www.luogu.com.cn/problem/P2085)（普及/提高−）
  - 热身（选做）：[洛谷 P3378 【模板】堆](https://www.luogu.com.cn/problem/P3378)（普及/提高−）；[力扣 703. 数据流中的第 K 大元素](https://leetcode.cn/problems/kth-largest-element-in-a-stream/)（简单）；[力扣 1046. 最后一块石头的重量](https://leetcode.cn/problems/last-stone-weight/)（简单）
  - 挑战（选做）：[洛谷 P2827 [NOIP 2016 提高组] 蚯蚓](https://www.luogu.com.cn/problem/P2827)（提高+/省选−，三个单调队列代替堆）；[洛谷 P1484 种树](https://www.luogu.com.cn/problem/P1484)（提高+/省选−，反悔贪心）

## 第 6 步：笔记与提交（约 0.5 小时）

在 `notes/ch10-优先级队列.md` 里写：

- Floyd 建堆 O(n) 的证明。
- 计时结果。

把下面的完成清单打勾，然后：

```bash
python3 tools/progress.py
git add -A
git commit -m "D29: 完全二叉堆与堆排序"
git push
```

## ✅ 完成清单

- [ ] 读完教材 §10.1–10.2 和讲义，能回答上面的问题
- [ ] 写完今天的代码
- [ ] `tools/test.sh ch10 D29` 的结果符合预期
- [ ] 对照了邓老师的代码，差异记进笔记
- [ ] 完成今天的练习
- [ ] 写完笔记，提交并推送
