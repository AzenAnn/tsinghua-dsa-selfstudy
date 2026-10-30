# D07 · 11-05 周四 · 第3章 列表（二）：有序列表与排序

> 教材 §3.4–3.5 ｜ 讲义 第3章 ｜ 约 5 小时
> [← D06](../../D01-D08/D06/README.md) ｜ [总计划](../../../../PLAN.md) ｜ [D08 →](../../D01-D08/D08/README.md)

## 今天的目标

实现有序列表的去重和查找，三种列表排序（插入、选择、归并），以及归并和倒置；第3章收尾。

## 今天要动的文件

| 文件 | 内容 |
|---|---|
| `learn/include/dsa/list.h` | “第 7 天”那一段：uniquify、search、selectMax、insertionSort、selectionSort、merge、mergeSort、sort、reverse |
| `learn/exercises/ch03/` | 第3章课后习题（今天的题号见“练习”一节） |

## 第 1 步：读书（约 1.5 小时）

打开教材 `deng/local-only/dsacpp-3rd-edn.pdf`，读 §3.4–3.5；再看讲义 `deng/local-only/DSA-2026F-10up-V.pdf` 的第3章。读的时候想清楚这几个问题，读完能用自己的话回答：

- §3.5.2 插入排序的比较次数和逆序对数有什么关系？
- §3.5.3 选择排序为什么不受输入影响？selectMax 遇到相等时取最后一个，为什么这样排序才稳定？
- §3.5.4 列表的归并排序和向量的有什么不同？为什么 mergeSort 的参数 p 要传引用？

## 第 2 步：写代码（约 2 小时）

合上书，按下面的顺序写，每写完一个函数就运行一次测试：

1. 写 `uniquify` 和 `search`（在 p 的 n 个真前驱中找最后一个不大于 e 的；都比 e 大时返回再往前的那个节点）。
2. 写 `selectMax`、`insertionSort`（借助 search 找插入位置）、`selectionSort`（每次把最大者移到末尾）。
3. 写受保护的 `merge(p, n, L, q, m)` 和 `mergeSort(p, n)`；`sort` 调用你选的一种。
4. 写 `reverse`（提示：交换每个节点的 pred 和 succ，最后交换 header 和 trailer）。
5. 运行 `DSA_STRICT=1 tools/test.sh ch03`，20 个用例全部通过。

## 第 3 步：检测与调试

运行：

```bash
DSA_STRICT=1 tools/test.sh ch03
```

全部完成时，这 20 个用例都显示 `[通过]`，每个测试程序的最后一行是 `通过 …，失败 0，待实现 0`。还没写的函数显示黄色的 `[待实现]`；写错的显示红色的 `[失败]`，下面跟着出错的那行测试代码和两边的实际值。

调试提示：

- 排序测试只排“从 p 起的 n 个节点”，前后的节点必须原样不动。
- 归并时 L 可以就是 *this（mergeSort 里就是这样调用的），别在 merge 里假设 L 是另一个列表。

## 第 4 步：对照邓老师的代码

测试通过以后再看，逐处对比你的写法，把差异和自己没想到的地方记进笔记：

- `deng/code/src/list/List_search.h`、`List_insertionsort.h`、`List_SelectionSort.h`、`List_merge.h`、`List_mergesort.h`。

## 第 5 步：练习（约 1 小时）

- 课后习题（每题一个文件，打开后在“我的解答”下面写；编程题的代码写在同目录的同名 `.cpp` 里）：
  - 必做：[[3-4]](../../../exercises/ch03/3-4.md)、[[3-5]](../../../exercises/ch03/3-5.md)、[[3-6]](../../../exercises/ch03/3-6.md)、[[3-8]](../../../exercises/ch03/3-8.md)、[[3-9]](../../../exercises/ch03/3-9.md)、[[3-10]](../../../exercises/ch03/3-10.md)、[[3-11]](../../../exercises/ch03/3-11.md)、[[3-13]](../../../exercises/ch03/3-13.md)、[[3-14]](../../../exercises/ch03/3-14.md)、[[3-16]](../../../exercises/ch03/3-16.md)、[[3-17]](../../../exercises/ch03/3-17.md)、[[3-18]](../../../exercises/ch03/3-18.md)、[[3-19]](../../../exercises/ch03/3-19.md)
  - 选做：[[3-7]](../../../exercises/ch03/3-7.md)、[[3-12]](../../../exercises/ch03/3-12.md)、[[3-15]](../../../exercises/ch03/3-15.md)
- 今天是第3章的最后一天：打开 [`learn/exercises/ch03/README.md`](../../../exercises/ch03/README.md)，把本章前几天没做完的必做题补上。
- OJ 题（在 [learn/problems/README.md](../../../problems/README.md) 里打勾；新建题目用 `python3 tools/new.py problem D07 luogu-P1234 题名`，样例测试用 `tools/run.sh`）：
  - 必做：[力扣 148. 排序链表](https://leetcode.cn/problems/sort-list/)（中等，列表归并排序）；[力扣 146. LRU 缓存](https://leetcode.cn/problems/lru-cache/)（中等，哈希 + 双向链表）；[力扣 25. K 个一组翻转链表](https://leetcode.cn/problems/reverse-nodes-in-k-group/)（困难）
  - 挑战（选做）：[力扣 460. LFU 缓存](https://leetcode.cn/problems/lfu-cache/)（困难）；[洛谷 P7912 [CSP-J 2021] 小熊的果篮](https://www.luogu.com.cn/problem/P7912)（普及+/提高，链表维护块）

## 第 6 步：笔记与提交（约 0.5 小时）

在 `learn/notes/ch03-列表.md` 里写：

- 插入排序与逆序对。
- 三种排序的稳定性分析。
- 第3章“易错点”汇总。

把下面的完成清单打勾，然后：

```bash
python3 tools/progress.py
git add -A
git commit -m "D07: 完成第3章，ch03 全部测试通过"
git push
```

## ✅ 完成清单

- [ ] 读完教材 §3.4–3.5 和讲义，能回答上面的问题
- [ ] 写完今天的代码
- [ ] `DSA_STRICT=1 tools/test.sh ch03` 的结果符合预期
- [ ] 对照了邓老师的代码，差异记进笔记
- [ ] 完成今天的练习
- [ ] 写完笔记，提交并推送
