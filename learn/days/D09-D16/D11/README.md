# D11 · 11-09 周一 · 第5章 二叉树（一）：节点与树

> 教材 §5.1–5.3 ｜ 讲义 第5章 ｜ 约 5 小时
> [← D10](../../D09-D16/D10/README.md) ｜ [总计划](../../../../PLAN.md) ｜ [D12 →](../../D09-D16/D12/README.md)

## 今天的目标

实现二叉树节点和二叉树的基本操作：插入、接入子树、删除子树、摘下子树、维护高度。

## 今天要动的文件

| 文件 | 内容 |
|---|---|
| `learn/include/dsa/bintree.h` | “第 11 天”那一段：BinNode::size、insertAsLC/RC，BinTree 的 updateHeight、updateHeightAbove、insertAsRoot、insertAsLC/RC、attachAsLC/RC、remove、secede、析构 |

## 第 1 步：读书（约 1.5 小时）

打开教材 `deng/local-only/dsacpp-3rd-edn.pdf`，读 §5.1–5.3；再看讲义 `deng/local-only/DSA-2026F-10up-V.pdf` 的第5章。读的时候想清楚这几个问题，读完能用自己的话回答：

- §5.1 树的长子-兄弟表示法。
- §5.3 updateHeightAbove 为什么只需要沿父亲往上走？什么时候可以提前停止？
- §5.3 attach 和 secede 分别要更新哪些节点的高度和规模？

## 第 2 步：写代码（约 2 小时）

合上书，按下面的顺序写，每写完一个函数就运行一次测试：

1. 写 `BinNode::size`、`insertAsLC`、`insertAsRC`。
2. 写 `updateHeight`（用已经写好的 `stature`：空树高度为 -1）和 `updateHeightAbove`。
3. 写 `insertAsRoot`、`BinTree::insertAsLC/RC`（插入后更新祖先高度、规模加一）。运行 `tools/test.sh ch05_bintree insert`。
4. 写 `remove`（先断开父亲的指针，再递归释放子树；可以自己写一个递归的辅助函数）、`secede`、`attachAsLC/RC`、析构函数。
5. 运行 `tools/test.sh ch05_bintree D11`。

## 第 3 步：检测与调试

运行：

```bash
tools/test.sh ch05_bintree D11
```

全部完成时，这 5 个用例都显示 `[通过]`，每个测试程序的最后一行是 `通过 …，失败 0，待实现 0`。还没写的函数显示黄色的 `[待实现]`；写错的显示红色的 `[失败]`，下面跟着出错的那行测试代码和两边的实际值。

调试提示：

- 测试会逐个检查节点记录的 height 和实际高度是否一致，不一致说明有地方忘了更新高度。
- `fromParentTo(x)` 已经写好：它返回父节点中指向 x 的那个指针（x 是根时就是 `_root`）的引用，删除、摘下时用它最方便。

## 第 4 步：对照邓老师的代码

测试通过以后再看，逐处对比你的写法，把差异和自己没想到的地方记进笔记：

- `deng/code/src/binTree/` 下的 `BinNode.h`、`BinTree.h`、`BinTree_attach.h`、`BinTree_remove.h`、`BinTree_secede.h`、`BinTree_updateheight.h`。

## 第 5 步：练习（约 1 小时）

- 课后习题（每题一个文件，打开后在“我的解答”下面写；编程题的代码写在同目录的同名 `.cpp` 里）：
  - 必做：[[5-1]](../../../exercises/ch05/5-1.md)、[[5-2]](../../../exercises/ch05/5-2.md)、[[5-3]](../../../exercises/ch05/5-3.md)、[[5-4]](../../../exercises/ch05/5-4.md)、[[5-24]](../../../exercises/ch05/5-24.md)、[[5-25]](../../../exercises/ch05/5-25.md)、[[5-26]](../../../exercises/ch05/5-26.md)、[[5-27]](../../../exercises/ch05/5-27.md)
  - 选做：[[5-22]](../../../exercises/ch05/5-22.md)、[[5-23]](../../../exercises/ch05/5-23.md)
- OJ 题（在 [learn/problems/README.md](../../../problems/README.md) 里打勾；新建题目用 `python3 tools/new.py problem D11 luogu-P1234 题名`，样例测试用 `tools/run.sh`）：
  - 必做：[洛谷 P1087 [NOIP 2004 普及组] FBI 树](https://www.luogu.com.cn/problem/P1087)（普及−，递归建树）
  - 热身（选做）：[力扣 104. 二叉树的最大深度](https://leetcode.cn/problems/maximum-depth-of-binary-tree/)（简单）；[力扣 226. 翻转二叉树](https://leetcode.cn/problems/invert-binary-tree/)（简单）；[洛谷 P4913 【深基16.例3】二叉树深度](https://www.luogu.com.cn/problem/P4913)（普及−）；[洛谷 P1305 新二叉树](https://www.luogu.com.cn/problem/P1305)（普及−）

## 第 6 步：笔记与提交（约 0.5 小时）

在 `learn/notes/ch05-二叉树.md` 里写：

- 树的几种表示法。
- 高度、深度、规模的定义与维护。

把下面的完成清单打勾，然后：

```bash
python3 tools/progress.py
git add -A
git commit -m "D11: BinTree 的基本操作"
git push
```

## ✅ 完成清单

- [ ] 读完教材 §5.1–5.3 和讲义，能回答上面的问题
- [ ] 写完今天的代码
- [ ] `tools/test.sh ch05_bintree D11` 的结果符合预期
- [ ] 对照了邓老师的代码，差异记进笔记
- [ ] 完成今天的练习
- [ ] 写完笔记，提交并推送
