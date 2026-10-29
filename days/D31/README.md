# D31 · 11-29 周日 · 第11章 串（一）：蛮力匹配与 KMP

> 教材 §11.1–11.3 ｜ 讲义 第11章 ｜ 约 5 小时
> [← D30](../D30/README.md) ｜ [总计划](../../PLAN.md) ｜ [D32 →](../D32/README.md)

## 今天的目标

实现两种蛮力匹配、KMP 的 next 表和 KMP 匹配。

## 今天要动的文件

| 文件 | 内容 |
|---|---|
| `src/string_match.cpp` | “第 31 天”那一段：matchBF1、matchBF2、buildNext、matchKMP |
| `include/dsa/string_match.h` | 只看不改 |

## 第 1 步：读书（约 1.5 小时）

打开教材 `deng/local-only/dsacpp-3rd-edn.pdf`，读 §11.1–11.3；再看讲义 `deng/local-only/DSA-2026F-10up-V.pdf` 的第11章。读的时候想清楚这几个问题，读完能用自己的话回答：

- §11.2 两种蛮力算法的差别；最坏情况。
- §11.3.2 next 表的含义；§11.3.4 递推构造 next 表。
- §11.3.5 KMP 为什么是 O(n + m)（分摊分析）？

## 第 2 步：写代码（约 2 小时）

合上书，按下面的顺序写，每写完一个函数就运行一次测试：

1. 写 `matchBF1`（i、j 两个指针，失配时 i 回退到 i - j + 1）和 `matchBF2`（逐个对齐位置尝试）。
2. 写 `buildNext`：按书上的递推，next[0] = -1。可以先运行 `tools/test.sh ch11 buildNext`，测试里有 "chinchilla" 的标准答案。
3. 写 `matchKMP`：失配时 j = next[j]，j < 0 时 i、j 同时前进。
4. 运行 `tools/test.sh ch11 D31`。

## 第 3 步：检测与调试

运行：

```bash
tools/test.sh ch11 D31
```

全部完成时，这 4 个用例都显示 `[通过]`，每个测试程序的最后一行是 `通过 …，失败 0，待实现 0`。还没写的函数显示黄色的 `[待实现]`；写错的显示红色的 `[失败]`，下面跟着出错的那行测试代码和两边的实际值。

调试提示：

- P 为空串时返回 0；找不到时返回 -1。
- “最坏情况的输入也要能跑完”：蛮力在这里会慢一些，但应在一两秒内结束。

## 第 4 步：对照邓老师的代码

测试通过以后再看，逐处对比你的写法，把差异和自己没想到的地方记进笔记：

- `deng/code/src/string_pm_bf1/`、`string_pm_bf2/`、`string_pm_kmp/`；`python3 tools/deng.py string_pm_kmp` 可以运行。

## 第 5 步：练习（约 1 小时）

- LeetCode 28；洛谷 P3375 KMP 字符串匹配。

## 第 6 步：笔记与提交（约 0.5 小时）

在 `notes/ch11-串.md` 里写：

- next 表的含义和递推；KMP 的分摊分析。

把下面的完成清单打勾，然后：

```bash
python3 tools/progress.py
git add -A
git commit -m "D31: 蛮力匹配与 KMP"
git push
```

## ✅ 完成清单

- [ ] 读完教材 §11.1–11.3 和讲义，能回答上面的问题
- [ ] 写完今天的代码
- [ ] `tools/test.sh ch11 D31` 的结果符合预期
- [ ] 对照了邓老师的代码，差异记进笔记
- [ ] 完成今天的练习
- [ ] 写完笔记，提交并推送
