# D15 · 11-13 周五 · 第6章 图（二）：BFS 与 DFS

> 教材 §6.5–6.7 ｜ 讲义 第6章 ｜ 约 5 小时
> [← D14](../D14/README.md) ｜ [总计划](../../PLAN.md) ｜ [D16 →](../D16/README.md)

## 今天的目标

实现广度优先搜索和深度优先搜索，正确设置时间标签和边的类型。

## 今天要动的文件

| 文件 | 内容 |
|---|---|
| `include/dsa/graph.h` | “第 15 天”那一段：BFS、bfs、DFS、dfs |

## 第 1 步：读书（约 1.5 小时）

打开教材 `deng/local-only/dsacpp-3rd-edn.pdf`，读 §6.5–6.7；再看讲义 `deng/local-only/DSA-2026F-10up-V.pdf` 的第6章。读的时候想清楚这几个问题，读完能用自己的话回答：

- §6.6 BFS 的树边和跨边；为什么 BFS 树给出最短跳数？
- §6.7 DFS 的 dTime、fTime；边的四种类型 Tree、Backward、Forward、Cross 怎么判断？
- 括号引理：任意两个顶点的活跃期要么嵌套、要么不相交。

## 第 2 步：写代码（约 2 小时）

合上书，按下面的顺序写，每写完一个函数就运行一次测试：

1. 写 `BFS(v, clock)`：用你的 Queue；发现顶点时 `dTime = clock++`，设好 parent，边标为 Tree；遇到已发现的顶点，边标为 Cross。
2. 写 `bfs(s)`：`reset()` 后从 s 开始，按 s, s+1, ...（循环）对每个未发现的顶点调用 BFS，覆盖全图。
3. 写 `DFS(v, clock)`（递归）：发现时 `dTime = ++clock`，结束时 `fTime = ++clock`；邻居是 Discovered 时边为 Backward，是 Visited 时根据 dTime 判断 Forward 还是 Cross。
4. 写 `dfs(s)`。运行 `tools/test.sh ch06 D15`：同一份算法对两种表示各测一次，共 4 个用例。

## 第 3 步：检测与调试

运行：

```bash
tools/test.sh ch06 D15
```

全部完成时，这 4 个用例都显示 `[通过]`，每个测试程序的最后一行是 `通过 …，失败 0，待实现 0`。还没写的函数显示黄色的 `[待实现]`；写错的显示红色的 `[失败]`，下面跟着出错的那行测试代码和两边的实际值。

调试提示：

- dTime 的约定：bfs 从 0 开始、每发现一个加 1；dfs 用 ++clock，所以从 1 开始，1..2n 每个时刻用一次。
- 边分类不对：测试是按活跃期的包含关系检查的，把出错的那条边两端顶点的 dTime、fTime 打印出来对照。

## 第 4 步：对照邓老师的代码

测试通过以后再看，逐处对比你的写法，把差异和自己没想到的地方记进笔记：

- `deng/code/src/graph/Graph_bfs.h`、`Graph_dfs.h`。

## 第 5 步：练习（约 1 小时）

- 课后习题（每题一个文件，打开后在“我的解答”下面写；编程题的代码写在同目录的同名 `.cpp` 里）：
  - 必做：[[6-12]](../../exercises/ch06/6-12.md)、[[6-13]](../../exercises/ch06/6-13.md)、[[6-14]](../../exercises/ch06/6-14.md)
  - 选做：[[6-11]](../../exercises/ch06/6-11.md)、[[6-15]](../../exercises/ch06/6-15.md)、[[6-16]](../../exercises/ch06/6-16.md)
- OJ 题（在 [problems/README.md](../../problems/README.md) 里打勾；新建题目用 `python3 tools/new.py problem chNN luogu-P1234 题名`，样例测试用 `tools/run.sh`）：
  - 必做：[洛谷 P5318 【深基18.例3】查找文献](https://www.luogu.com.cn/problem/P5318)（普及−，BFS、DFS）；[洛谷 P3916 图的遍历](https://www.luogu.com.cn/problem/P3916)（普及/提高−，反向建图）；[力扣 200. 岛屿数量](https://leetcode.cn/problems/number-of-islands/)（中等）；[力扣 994. 腐烂的橘子](https://leetcode.cn/problems/rotting-oranges/)（中等，多源 BFS）；[洛谷 P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)（普及/提高−，BFS）
  - 挑战（选做）：[洛谷 P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)（普及+/提高，BFS 计数）

## 第 6 步：笔记与提交（约 0.5 小时）

在 `notes/ch06-图.md` 里写：

- 边分类的判定规则；括号引理的证明。

把下面的完成清单打勾，然后：

```bash
python3 tools/progress.py
git add -A
git commit -m "D15: BFS 与 DFS"
git push
```

## ✅ 完成清单

- [ ] 读完教材 §6.5–6.7 和讲义，能回答上面的问题
- [ ] 写完今天的代码
- [ ] `tools/test.sh ch06 D15` 的结果符合预期
- [ ] 对照了邓老师的代码，差异记进笔记
- [ ] 完成今天的练习
- [ ] 写完笔记，提交并推送
