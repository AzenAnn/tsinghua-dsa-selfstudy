# D14 · 11-12 周四 · 第6章 图（一）：邻接矩阵与邻接表

> 教材 §6.1–6.4 ｜ 讲义 第6章 ｜ 约 5 小时
> [← D13](../D13/README.md) ｜ [总计划](../../PLAN.md) ｜ [D15 →](../D15/README.md)

## 今天的目标

读懂图的抽象接口 Graph，实现邻接矩阵 GraphMatrix 和邻接表 GraphList 两种表示。

## 今天要动的文件

| 文件 | 内容 |
|---|---|
| `include/dsa/graph.h` | 只读：Graph 的接口（纯虚函数）和算法的位置（后几天写） |
| `include/dsa/graph_matrix.h` | GraphMatrix 的析构、nextNbr、插入/删除顶点、exists、插入/删除边 |
| `include/dsa/graph_list.h` | GraphList 的 find、nextNbr、插入/删除顶点、exists、插入/删除边 |

## 第 1 步：读书（约 1.5 小时）

打开教材 `deng/local-only/dsacpp-3rd-edn.pdf`，读 §6.1–6.4；再看讲义 `deng/local-only/DSA-2026F-10up-V.pdf` 的第6章。读的时候想清楚这几个问题，读完能用自己的话回答：

- §6.2 图的 ADT：为什么顶点和边的“状态、时间标签、父亲、优先级”都放在图里？
- §6.3–6.4 两种表示在各操作上的复杂度。
- nextNbr(v, u) 返回“编号小于 u 的最大邻居”，firstNbr(v) = nextNbr(v, n)：邻居是从大到小枚举的。

## 第 2 步：写代码（约 2 小时）

合上书，按下面的顺序写，每写完一个函数就运行一次测试：

1. 先通读 `include/dsa/graph.h` 的接口部分。
2. 写 `GraphMatrix`：插入顶点时每一行末尾加一个空指针，再加一个新行；删除顶点时删掉那一行和每一行里那一列，并更新相关顶点的度数和边数。运行 `tools/test.sh ch06 GraphMatrix`。
3. 写 `GraphList`：成员已经给了一种设计（`std::vector` 存顶点，每个顶点一条 `std::list`），删除顶点后要把所有大于 v 的邻居编号减 1。运行 `tools/test.sh ch06 GraphList`。
4. 运行 `tools/test.sh ch06 D14`，两个用例都通过。

## 第 3 步：检测与调试

运行：

```bash
tools/test.sh ch06 D14
```

全部完成时，这 2 个用例都显示 `[通过]`，每个测试程序的最后一行是 `通过 …，失败 0，待实现 0`。还没写的函数显示黄色的 `[待实现]`；写错的显示红色的 `[失败]`，下面跟着出错的那行测试代码和两边的实际值。

调试提示：

- 测试会在每一步之后把度数、边数、每条边的权重和数据、邻居的枚举顺序都和参考模型比一遍，报错信息会指出是哪一项。
- 插入已经存在的边时什么也不做（边数不能加）。

## 第 4 步：对照邓老师的代码

测试通过以后再看，逐处对比你的写法，把差异和自己没想到的地方记进笔记：

- `deng/code/src/graph/Graph.h`、`deng/code/src/graphmatrix/GraphMatrix.h`。

## 第 5 步：练习（约 1 小时）

- 课后习题（每题一个文件，打开后在“我的解答”下面写；编程题的代码写在同目录的同名 `.cpp` 里）：
  - 必做：[[6-1]](../../exercises/ch06/6-1.md)、[[6-3]](../../exercises/ch06/6-3.md)、[[6-5]](../../exercises/ch06/6-5.md)、[[6-6]](../../exercises/ch06/6-6.md)、[[6-7]](../../exercises/ch06/6-7.md)、[[6-8]](../../exercises/ch06/6-8.md)、[[6-10]](../../exercises/ch06/6-10.md)
  - 选做：[[6-2]](../../exercises/ch06/6-2.md)、[[6-4]](../../exercises/ch06/6-4.md)、[[6-9]](../../exercises/ch06/6-9.md)
- OJ 题（在 [problems/README.md](../../problems/README.md) 里打勾；新建题目用 `python3 tools/new.py problem chNN luogu-P1234 题名`，样例测试用 `tools/run.sh`）：
  - 热身（选做）：[力扣 997. 找到小镇的法官](https://leetcode.cn/problems/find-the-town-judge/)（简单，入度、出度）

## 第 6 步：笔记与提交（约 0.5 小时）

在 `notes/ch06-图.md` 里写：

- 两种表示的复杂度对比表（插入/删除顶点、插入/删除边、判断边、枚举邻居、空间）。

把下面的完成清单打勾，然后：

```bash
python3 tools/progress.py
git add -A
git commit -m "D14: 图的邻接矩阵和邻接表"
git push
```

## ✅ 完成清单

- [ ] 读完教材 §6.1–6.4 和讲义，能回答上面的问题
- [ ] 写完今天的代码
- [ ] `tools/test.sh ch06 D14` 的结果符合预期
- [ ] 对照了邓老师的代码，差异记进笔记
- [ ] 完成今天的练习
- [ ] 写完笔记，提交并推送
