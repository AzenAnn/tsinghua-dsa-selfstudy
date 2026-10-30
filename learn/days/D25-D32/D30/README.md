# D30 · 11-28 周六 · 第10章 优先级队列（二）：左式堆

> 教材 §10.3 ｜ 讲义 第10章 ｜ 约 5 小时
> [← D29](../../D25-D32/D29/README.md) ｜ [总计划](../../../../PLAN.md) ｜ [D31 →](../../D25-D32/D31/README.md)

## 今天的目标

实现左式堆及其合并；把 Huffman 编码里的“取最小两棵树”换成堆；第10章收尾。

## 今天要动的文件

| 文件 | 内容 |
|---|---|
| `learn/include/dsa/pq.h` | “第 30 天”那一段：merge、PQ_LeftHeap 的 insert、getMax、delMax、merge |
| `src/huffman.cpp` | （选做）把森林从 List 换成堆 |
| `learn/exercises/ch10/` | 第10章课后习题（今天的题号见“练习”一节） |

## 第 1 步：读书（约 1.5 小时）

打开教材 `deng/local-only/dsacpp-3rd-edn.pdf`，读 §10.3；再看讲义 `deng/local-only/DSA-2026F-10up-V.pdf` 的第10章。读的时候想清楚这几个问题，读完能用自己的话回答：

- §10.3.1 为什么完全二叉堆不好合并？
- §10.3.2 npl 的定义；左倾性；右侧链长度为什么是 O(log n)？
- §10.3.4 合并算法：把堆顶大的那个作为根，递归合并它的右子堆和另一个堆，必要时交换左右孩子。

## 第 2 步：写代码（约 2 小时）

合上书，按下面的顺序写，每写完一个函数就运行一次测试：

1. 写自由函数 `merge(a, b)`（递归），维护 npl 和 parent。
2. 写 `PQ_LeftHeap` 的 insert（新节点单独成堆再合并）、getMax、delMax（摘掉根，合并左右子堆）、merge（把另一个堆并进来，它变空）。注意类里的 merge 会遮住同名的自由函数，调用自由函数要写 `dsa::merge(...)`。
3. 运行 `DSA_STRICT=1 tools/test.sh ch10`，6 个用例全部通过。
4. （选做）打开 `src/huffman.cpp`，把每次扫描列表取最小两棵树，改成用你的堆（存树指针，按根的权重比较，需要自己写一个比较用的小结构体），再运行 `tools/test.sh ch05_huffman` 确认结果不变。

## 第 3 步：检测与调试

运行：

```bash
DSA_STRICT=1 tools/test.sh ch10
```

全部完成时，这 6 个用例都显示 `[通过]`，每个测试程序的最后一行是 `通过 …，失败 0，待实现 0`。还没写的函数显示黄色的 `[待实现]`；写错的显示红色的 `[失败]`，下面跟着出错的那行测试代码和两边的实际值。

调试提示：

- 测试会检查每个节点的 npl 和左倾性；merge 回来后别忘了比较左右孩子的 npl。

## 第 4 步：对照邓老师的代码

测试通过以后再看，逐处对比你的写法，把差异和自己没想到的地方记进笔记：

- `deng/code/src/PQ_leftheap/`。

## 第 5 步：练习（约 1 小时）

- 课后习题（每题一个文件，打开后在“我的解答”下面写；编程题的代码写在同目录的同名 `.cpp` 里）：
  - 必做：[[10-13]](../../../exercises/ch10/10-13.md)、[[10-15]](../../../exercises/ch10/10-15.md)、[[10-16]](../../../exercises/ch10/10-16.md)、[[10-17]](../../../exercises/ch10/10-17.md)、[[10-18]](../../../exercises/ch10/10-18.md)
  - 选做：[[10-19]](../../../exercises/ch10/10-19.md)、[[10-20]](../../../exercises/ch10/10-20.md)、[[10-21]](../../../exercises/ch10/10-21.md)、[[10-22]](../../../exercises/ch10/10-22.md)
- 今天是第10章的最后一天：打开 [`learn/exercises/ch10/README.md`](../../../exercises/ch10/README.md)，把本章前几天没做完的必做题补上。
- OJ 题（在 [learn/problems/README.md](../../../problems/README.md) 里打勾；新建题目用 `python3 tools/new.py problem D30 luogu-P1234 题名`，样例测试用 `tools/run.sh`）：
  - 必做：[力扣 23. 合并 K 个升序链表](https://leetcode.cn/problems/merge-k-sorted-lists/)（困难）；[洛谷 P3377 【模板】可并堆 1](https://www.luogu.com.cn/problem/P3377)（提高+/省选−）；[洛谷 P1456 Monkey King](https://www.luogu.com.cn/problem/P1456)（提高+/省选−，左式堆）
  - 挑战（选做）：[洛谷 P4331 [BalticOI 2004] Sequence (Day1)](https://www.luogu.com.cn/problem/P4331)（NOI/NOI+/CTSC，左式堆）

## 第 6 步：笔记与提交（约 0.5 小时）

在 `learn/notes/ch10-优先级队列.md` 里写：

- 右侧链长度 O(log n) 的证明。
- 第10章“易错点”汇总。

把下面的完成清单打勾，然后：

```bash
python3 tools/progress.py
git add -A
git commit -m "D30: 完成第10章，左式堆"
git push
```

## ✅ 完成清单

- [ ] 读完教材 §10.3 和讲义，能回答上面的问题
- [ ] 写完今天的代码
- [ ] `DSA_STRICT=1 tools/test.sh ch10` 的结果符合预期
- [ ] 对照了邓老师的代码，差异记进笔记
- [ ] 完成今天的练习
- [ ] 写完笔记，提交并推送
