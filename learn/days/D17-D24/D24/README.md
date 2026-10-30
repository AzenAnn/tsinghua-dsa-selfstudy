# D24 · 11-22 周日 · 第8章 高级搜索树（四）：红黑树的插入

> 教材 §8.3 ｜ 讲义 第8章 ｜ 约 5 小时
> [← D23](../../D17-D24/D23/README.md) ｜ [总计划](../../../../PLAN.md) ｜ [D25 →](../../D25-D32/D25/README.md)

## 今天的目标

实现红黑树的黑高度维护和插入（双红修正）。

## 今天要动的文件

| 文件 | 内容 |
|---|---|
| `learn/include/dsa/redblack.h` | “第 24 天”那一段：updateHeight、insert、solveDoubleRed |

## 第 1 步：读书（约 1.5 小时）

打开教材 `deng/local-only/dsacpp-3rd-edn.pdf`，读 §8.3；再看讲义 `deng/local-only/DSA-2026F-10up-V.pdf` 的第8章。读的时候想清楚这几个问题，读完能用自己的话回答：

- §8.3.1 红黑树的四条规则；和 (2,4)-树的对应关系（“提升”红节点）。
- §8.3.3 双红修正：RR-1（叔叔是黑的，一次 3+4 重构 + 染色）、RR-2（叔叔是红的，只染色，问题可能上移）。
- 这里 height 字段存的是黑高度：空节点为 -1。

## 第 2 步：写代码（约 2 小时）

合上书，按下面的顺序写，每写完一个函数就运行一次测试：

1. 写 `updateHeight`：取左右孩子黑高度的较大者，自己是黑色再加 1。
2. 写 `insert`：search 失败后新建红节点（黑高度 -1），然后 `solveDoubleRed`。
3. 写 `solveDoubleRed(x)`：x 是根就染黑并加高；父亲是黑的就结束；叔叔是黑的走 RR-1，是红的走 RR-2 并对祖父递归。`rotateAt`、`fromParentTo`、`uncle`、`isRed/isBlack` 都已经有了。
4. 运行 `tools/test.sh ch08_redblack D24`。

## 第 3 步：检测与调试

运行：

```bash
tools/test.sh ch08_redblack D24
```

全部完成时，这 2 个用例都显示 `[通过]`，每个测试程序的最后一行是 `通过 …，失败 0，待实现 0`。还没写的函数显示黄色的 `[待实现]`；写错的显示红色的 `[失败]`，下面跟着出错的那行测试代码和两边的实际值。

调试提示：

- 测试每步检查：根是黑的、红节点的孩子都是黑的、各路径黑节点数相同、height 字段等于黑高度。
- RR-1 的染色：p、x 同侧时 p 变黑，异侧时 x 变黑；祖父变红。

## 第 4 步：对照邓老师的代码

测试通过以后再看，逐处对比你的写法，把差异和自己没想到的地方记进笔记：

- `deng/code/src/redBlack/RedBlack.h`、`RedBlack_Insert.h`、`RedBlack_solveDoubleRed.h`。

## 第 5 步：练习（约 1 小时）

- OJ 题（在 [learn/problems/README.md](../../../problems/README.md) 里打勾；新建题目用 `python3 tools/new.py problem D24 luogu-P1234 题名`，样例测试用 `tools/run.sh`）：
  - 必做：[洛谷 P2286 [HNOI2004] 宠物收养场](https://www.luogu.com.cn/problem/P2286)（普及/提高−，平衡树前驱后继）

## 第 6 步：笔记与提交（约 0.5 小时）

在 `learn/notes/ch08-高级搜索树.md` 里写：

- 红黑树与 4 阶 B-树的对应关系。
- 插入两种情况各需几次旋转、几次染色。

把下面的完成清单打勾，然后：

```bash
python3 tools/progress.py
git add -A
git commit -m "D24: 红黑树的插入"
git push
```

## ✅ 完成清单

- [ ] 读完教材 §8.3 和讲义，能回答上面的问题
- [ ] 写完今天的代码
- [ ] `tools/test.sh ch08_redblack D24` 的结果符合预期
- [ ] 对照了邓老师的代码，差异记进笔记
- [ ] 完成今天的练习
- [ ] 写完笔记，提交并推送
