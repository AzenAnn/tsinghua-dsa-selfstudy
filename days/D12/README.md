# D12 · 11-10 周二 · 第5章 二叉树（二）：遍历

> 教材 §5.4 ｜ 讲义 第5章 ｜ 约 5 小时
> [← D11](../D11/README.md) ｜ [总计划](../../PLAN.md) ｜ [D13 →](../D13/README.md)

## 今天的目标

实现先序、中序、后序、层次遍历的递归版和迭代版，中序后继，以及由遍历序列重构二叉树。

## 今天要动的文件

| 文件 | 内容 |
|---|---|
| `include/dsa/bintree.h` | “第 12 天”那一段：succ、travPreR/I1/I2、travInR/I1/I2/I3、travPostR/I、travLevel、rebuildPreIn、rebuildPrePost |

## 第 1 步：读书（约 1.5 小时）

打开教材 `deng/local-only/dsacpp-3rd-edn.pdf`，读 §5.4；再看讲义 `deng/local-only/DSA-2026F-10up-V.pdf` 的第5章。读的时候想清楚这几个问题，读完能用自己的话回答：

- §5.4.2 先序迭代版 2：“沿左侧藤访问，右孩子入栈”。
- §5.4.3 中序迭代：“沿左侧藤入栈”；版本 3 怎样只靠 succ() 和回溯标志、不用栈？
- §5.4.4 后序迭代：为什么要“找到最高的叶子”？
- §5.4.5 为什么先序+中序能唯一确定二叉树，先序+后序只对真二叉树成立？

## 第 2 步：写代码（约 2 小时）

合上书，按下面的顺序写，每写完一个函数就运行一次测试：

1. 先写 4 个递归版（各 3 行）。运行 `tools/test.sh ch05_bintree R：`，确认递归版都对。
2. 写 `succ`（有右孩子：右子树最左；否则一直往上，直到自己是父亲的左孩子）。
3. 写先序 I1、I2，中序 I1、I2、I3，后序 I，层次遍历。迭代版必须用你自己的 Stack 和 Queue。每写一个就运行一次 `tools/test.sh ch05_bintree D12`。
4. 写 `rebuildPreIn`、`rebuildPrePost`：用已写好的 `insertAsRoot/LC/RC` 建树；可以自己写一个递归的辅助函数，参数是两个序列各自的起点和长度。
5. 运行 `DSA_STRICT=1 tools/test.sh ch05_bintree`，19 个用例全部通过。

## 第 3 步：检测与调试

运行：

```bash
DSA_STRICT=1 tools/test.sh ch05_bintree
```

全部完成时，这 19 个用例都显示 `[通过]`，每个测试程序的最后一行是 `通过 …，失败 0，待实现 0`。还没写的函数显示黄色的 `[待实现]`；写错的显示红色的 `[失败]`，下面跟着出错的那行测试代码和两边的实际值。

调试提示：

- 遍历的测试会打印期望序列和你的序列；对一棵小树（3–5 个节点）手动模拟栈的变化，最容易找到错。
- travInI3 写成死循环时，用 Ctrl+C 中断，再在循环里打印当前节点。

## 第 4 步：对照邓老师的代码

测试通过以后再看，逐处对比你的写法，把差异和自己没想到的地方记进笔记：

- `deng/code/src/binTree/` 下的 `BinNode_TravPreorder_I1.h`、`_I2.h`、`BinNode_TravInorder_I1.h`…`_I4.h`、`BinNode_TravPostorder_I.h`、`BinNode_TravLevel.h`、`BinNode_succ.h`。

## 第 5 步：练习（约 1 小时）

- 课后习题（每题一个文件，打开后在“我的解答”下面写；编程题的代码写在同目录的同名 `.cpp` 里）：
  - 必做：[[5-6]](../../exercises/ch05/5-6.md)、[[5-8]](../../exercises/ch05/5-8.md)、[[5-9]](../../exercises/ch05/5-9.md)、[[5-10]](../../exercises/ch05/5-10.md)、[[5-11]](../../exercises/ch05/5-11.md)、[[5-12]](../../exercises/ch05/5-12.md)、[[5-14]](../../exercises/ch05/5-14.md)、[[5-15]](../../exercises/ch05/5-15.md)、[[5-16]](../../exercises/ch05/5-16.md)、[[5-18]](../../exercises/ch05/5-18.md)
  - 选做：[[5-5]](../../exercises/ch05/5-5.md)、[[5-7]](../../exercises/ch05/5-7.md)、[[5-13]](../../exercises/ch05/5-13.md)、[[5-17]](../../exercises/ch05/5-17.md)
- OJ 题（在 [problems/README.md](../../problems/README.md) 里打勾；新建题目用 `python3 tools/new.py problem chNN luogu-P1234 题名`，样例测试用 `tools/run.sh`）：
  - 必做：[力扣 105. 从前序与中序遍历序列构造二叉树](https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)（中等）；[力扣 106. 从中序与后序遍历序列构造二叉树](https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal/)（中等）；[力扣 889. 根据前序和后序遍历构造二叉树](https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-postorder-traversal/)（中等，真二叉树）；[洛谷 P1030 [NOIP 2001 普及组] 求先序排列](https://www.luogu.com.cn/problem/P1030)（普及−）；[洛谷 P1827 [USACO3.4] 美国血统 American Heritage](https://www.luogu.com.cn/problem/P1827)（普及−）；[洛谷 P1229 遍历问题](https://www.luogu.com.cn/problem/P1229)（普及/提高−，先序 + 后序时的可能数）
  - 热身（选做）：[力扣 144. 二叉树的前序遍历](https://leetcode.cn/problems/binary-tree-preorder-traversal/)（简单，用迭代写）；[力扣 94. 二叉树的中序遍历](https://leetcode.cn/problems/binary-tree-inorder-traversal/)（简单，用迭代写）；[力扣 145. 二叉树的后序遍历](https://leetcode.cn/problems/binary-tree-postorder-traversal/)（简单，用迭代写）；[力扣 102. 二叉树的层序遍历](https://leetcode.cn/problems/binary-tree-level-order-traversal/)（中等）
  - 挑战（选做）：[力扣 297. 二叉树的序列化与反序列化](https://leetcode.cn/problems/serialize-and-deserialize-binary-tree/)（困难）；[力扣 124. 二叉树中的最大路径和](https://leetcode.cn/problems/binary-tree-maximum-path-sum/)（困难）

## 第 6 步：笔记与提交（约 0.5 小时）

在 `notes/ch05-二叉树.md` 里写：

- 每种迭代遍历的思路（画出“藤缠树”）。
- 重构二叉树的唯一性。

把下面的完成清单打勾，然后：

```bash
python3 tools/progress.py
git add -A
git commit -m "D12: 二叉树的遍历与重构"
git push
```

## ✅ 完成清单

- [ ] 读完教材 §5.4 和讲义，能回答上面的问题
- [ ] 写完今天的代码
- [ ] `DSA_STRICT=1 tools/test.sh ch05_bintree` 的结果符合预期
- [ ] 对照了邓老师的代码，差异记进笔记
- [ ] 完成今天的练习
- [ ] 写完笔记，提交并推送
