# D20 · 11-18 周三 · 第7章 搜索树（二）：AVL 树

> 教材 §7.3–7.4 ｜ 讲义 第7章 ｜ 约 5 小时
> [← D19](../D19/README.md) ｜ [总计划](../../PLAN.md) ｜ [D21 →](../D21/README.md)

## 今天的目标

实现“3+4 重构”和 AVL 树的插入、删除；第7章收尾。

## 今天要动的文件

| 文件 | 内容 |
|---|---|
| `include/dsa/bst.h` | “第 20 天”那一段：connect34、rotateAt |
| `include/dsa/avl.h` | AVL 的 insert、remove |
| `exercises/ch07/` | 第7章课后习题 |

## 第 1 步：读书（约 1.5 小时）

打开教材 `deng/local-only/dsacpp-3rd-edn.pdf`，读 §7.3–7.4；再看讲义 `deng/local-only/DSA-2026F-10up-V.pdf` 的第7章。读的时候想清楚这几个问题，读完能用自己的话回答：

- §7.3 等价变换：zig、zag。
- §7.4.3 插入后为什么只需要一次调整？删除后为什么可能要调整 O(log n) 次？
- §7.4.4 “3+4 重构”：把三个节点、四棵子树按中序排好，统一处理四种情况。

## 第 2 步：写代码（约 2 小时）

合上书，按下面的顺序写，每写完一个函数就运行一次测试：

1. 写 `connect34`：按中序 T0 a T1 b T2 c T3 组装，b 为根；更新 a、c、b 的高度（按这个顺序）。
2. 写 `rotateAt(v)`：根据 v、父亲 p、祖父 g 的左右关系分四种情况，调用 connect34；最后把新子树根的 parent 设为原来 g 的父亲。
3. 写 `AVL::insert`：插入后从 _hot 往上找第一个失衡的祖先 g，用 `rotateAt(tallerChild(tallerChild(g)))` 调整一次即可（`tallerChild`、`avlBalanced` 已经写好）。
4. 写 `AVL::remove`：删除后从 _hot 一路往上，每个失衡的祖先都要调整。
5. 运行 `DSA_STRICT=1 tools/test.sh ch07`，7 个用例全部通过。

## 第 3 步：检测与调试

运行：

```bash
DSA_STRICT=1 tools/test.sh ch07
```

全部完成时，这 7 个用例都显示 `[通过]`，每个测试程序的最后一行是 `通过 …，失败 0，待实现 0`。还没写的函数显示黄色的 `[待实现]`；写错的显示红色的 `[失败]`，下面跟着出错的那行测试代码和两边的实际值。

调试提示：

- 旋转之后要把父节点指向新子树根：`fromParentTo(g)` 要在 rotateAt 之前取，因为 rotateAt 会改 g 的父指针。
- 四种失衡的用例（zig-zig 等）各插 3 个数，失败时最容易手算。

## 第 4 步：对照邓老师的代码

测试通过以后再看，逐处对比你的写法，把差异和自己没想到的地方记进笔记：

- `deng/code/src/BST/BST_connect34.h`、`BST_RotateAt.h`、`deng/code/src/AVL/AVL_Insert.h`、`AVL_remove.h`。

## 第 5 步：练习（约 1 小时）

- 第7章课后习题：带 * 的题和编程题。
- LeetCode 110；洛谷 P3369 普通平衡树（用你的 AVL）。

## 第 6 步：笔记与提交（约 0.5 小时）

在 `notes/ch07-搜索树.md` 里写：

- 四种旋转如何统一为 3+4 重构（画图）。
- AVL 插入、删除的调整次数分析。
- 第7章“易错点”汇总。

把下面的完成清单打勾，然后：

```bash
python3 tools/progress.py
git add -A
git commit -m "D20: 完成第7章，AVL 树"
git push
```

## ✅ 完成清单

- [ ] 读完教材 §7.3–7.4 和讲义，能回答上面的问题
- [ ] 写完今天的代码
- [ ] `DSA_STRICT=1 tools/test.sh ch07` 的结果符合预期
- [ ] 对照了邓老师的代码，差异记进笔记
- [ ] 完成今天的练习
- [ ] 写完笔记，提交并推送
