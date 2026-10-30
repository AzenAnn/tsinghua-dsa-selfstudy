# D19 · 11-17 周二 · 第7章 搜索树（一）：二叉搜索树

> 教材 §7.1–7.2 ｜ 讲义 第7章 ｜ 约 5 小时
> [← D18](../D18/README.md) ｜ [总计划](../../PLAN.md) ｜ [D20 →](../D20/README.md)

## 今天的目标

实现二叉搜索树的查找、插入、删除，理解 _hot 的作用。

## 今天要动的文件

| 文件 | 内容 |
|---|---|
| `include/dsa/bst.h` | “第 19 天”那一段：search、insert、removeAt、remove |

## 第 1 步：读书（约 1.5 小时）

打开教材 `deng/local-only/dsacpp-3rd-edn.pdf`，读 §7.1–7.2；再看讲义 `deng/local-only/DSA-2026F-10up-V.pdf` 的第7章。读的时候想清楚这几个问题，读完能用自己的话回答：

- §7.2.2 search 为什么返回“指针的引用”？_hot 在查找成功、失败时分别指向谁？
- §7.2.4 删除有两个孩子的节点：为什么和直接后继交换？
- 随机生成和随机组成的 BST 平均高度。

## 第 2 步：写代码（约 2 小时）

合上书，按下面的顺序写，每写完一个函数就运行一次测试：

1. 写 `search`：从根往下走，同时维护 `_hot`；返回指向目标的那个指针的引用（可能是 `_root`，也可能是某个节点的 lc 或 rc）。
2. 写 `insert`：`search` 返回空指针时，就在那个位置新建节点（父亲是 `_hot`），然后更新规模和祖先高度。
3. 写 `removeAt(x, hot)`：只有一个孩子或没有孩子时，用孩子顶替；有两个孩子时，和直接后继交换数据，再删后继。最后 hot 指向实际被删节点的父亲。
4. 写 `remove`。运行 `tools/test.sh ch07 D19`。

## 第 3 步：检测与调试

运行：

```bash
tools/test.sh ch07 D19
```

全部完成时，这 4 个用例都显示 `[通过]`，每个测试程序的最后一行是 `通过 …，失败 0，待实现 0`。还没写的函数显示黄色的 `[待实现]`；写错的显示红色的 `[失败]`，下面跟着出错的那行测试代码和两边的实际值。

调试提示：

- BST 继承了 BinTree：访问 `_root`、`_size` 时要写 `this->_root`（模板基类的成员，编译器要求这样写）。
- 测试每一步都会检查中序有序、父指针、高度；删除后忘了 `updateHeightAbove(_hot)` 会在“高度”上报错。

## 第 4 步：对照邓老师的代码

测试通过以后再看，逐处对比你的写法，把差异和自己没想到的地方记进笔记：

- `deng/code/src/BST/BST_search.h`、`bst_insert.h`、`bst_remove.h`、`bst_removeAt.h`。

## 第 5 步：练习（约 1 小时）

- 课后习题（每题一个文件，打开后在“我的解答”下面写；编程题的代码写在同目录的同名 `.cpp` 里）：
  - 必做：[[7-1]](../../exercises/ch07/7-1.md)、[[7-2]](../../exercises/ch07/7-2.md)、[[7-3]](../../exercises/ch07/7-3.md)、[[7-4]](../../exercises/ch07/7-4.md)、[[7-5]](../../exercises/ch07/7-5.md)、[[7-11]](../../exercises/ch07/7-11.md)、[[7-12]](../../exercises/ch07/7-12.md)、[[7-13]](../../exercises/ch07/7-13.md)
  - 选做：[[7-10]](../../exercises/ch07/7-10.md)
- OJ 题（在 [problems/README.md](../../problems/README.md) 里打勾；新建题目用 `python3 tools/new.py problem chNN luogu-P1234 题名`，样例测试用 `tools/run.sh`）：
  - 必做：[力扣 450. 删除二叉搜索树中的节点](https://leetcode.cn/problems/delete-node-in-a-bst/)（中等，removeAt）；[力扣 230. 二叉搜索树中第 K 小的元素](https://leetcode.cn/problems/kth-smallest-element-in-a-bst/)（中等）；[力扣 235. 二叉搜索树的最近公共祖先](https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-search-tree/)（中等）；[洛谷 P5076 【深基16.例7】普通二叉树（简化版）](https://www.luogu.com.cn/problem/P5076)（普及+/提高）
  - 热身（选做）：[力扣 700. 二叉搜索树中的搜索](https://leetcode.cn/problems/search-in-a-binary-search-tree/)（简单）；[力扣 701. 二叉搜索树中的插入操作](https://leetcode.cn/problems/insert-into-a-binary-search-tree/)（中等）；[力扣 98. 验证二叉搜索树](https://leetcode.cn/problems/validate-binary-search-tree/)（中等）

## 第 6 步：笔记与提交（约 0.5 小时）

在 `notes/ch07-搜索树.md` 里写：

- _hot 的语义；删除的三种情况（画图）。

把下面的完成清单打勾，然后：

```bash
python3 tools/progress.py
git add -A
git commit -m "D19: 二叉搜索树"
git push
```

## ✅ 完成清单

- [ ] 读完教材 §7.1–7.2 和讲义，能回答上面的问题
- [ ] 写完今天的代码
- [ ] `tools/test.sh ch07 D19` 的结果符合预期
- [ ] 对照了邓老师的代码，差异记进笔记
- [ ] 完成今天的练习
- [ ] 写完笔记，提交并推送
