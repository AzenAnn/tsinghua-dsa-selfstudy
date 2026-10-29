# D32 · 11-30 周一 · 第11章 串（二）：改进的 KMP 与 BM 坏字符

> 教材 §11.3.7、§11.4 ｜ 讲义 第11章 ｜ 约 5 小时
> [← D31](../D31/README.md) ｜ [总计划](../../PLAN.md) ｜ [D33 →](../D33/README.md)

## 今天的目标

实现改进的 next 表，以及只用坏字符策略的 BM 算法。

## 今天要动的文件

| 文件 | 内容 |
|---|---|
| `src/string_match.cpp` | “第 32 天”那一段：buildNextImproved、matchKMPImproved、buildBC、matchBMbc |

## 第 1 步：读书（约 1.5 小时）

打开教材 `deng/local-only/dsacpp-3rd-edn.pdf`，读 §11.3.7、§11.4；再看讲义 `deng/local-only/DSA-2026F-10up-V.pdf` 的第11章。读的时候想清楚这几个问题，读完能用自己的话回答：

- §11.3.7 原来的 next 表在什么情况下会做无用的比较？改进在哪里？
- §11.4.2 坏字符策略：bc 表的含义；为什么右移量至少为 1？

## 第 2 步：写代码（约 2 小时）

合上书，按下面的顺序写，每写完一个函数就运行一次测试：

1. 写 `buildNextImproved`：在 buildNext 的基础上，P[j] == P[t] 时取 next[t]。测试里有 "aaaab" 的标准答案。
2. 写 `matchKMPImproved`。
3. 写 `buildBC`（长度 256，字符按 unsigned char 取下标）和 `matchBMbc`（从模式串末尾往前比；失配时按坏字符表右移，至少移 1）。
4. 运行 `tools/test.sh ch11 D32`。

## 第 3 步：检测与调试

运行：

```bash
tools/test.sh ch11 D32
```

全部完成时，这 4 个用例都显示 `[通过]`，每个测试程序的最后一行是 `通过 …，失败 0，待实现 0`。还没写的函数显示黄色的 `[待实现]`；写错的显示红色的 `[失败]`，下面跟着出错的那行测试代码和两边的实际值。

调试提示：

- 字符要转成 `unsigned char` 再当下标，否则遇到值大于 127 的字节会越界。

## 第 4 步：对照邓老师的代码

测试通过以后再看，逐处对比你的写法，把差异和自己没想到的地方记进笔记：

- `deng/code/src/string_pm_kmp_improved/`、`string_pm_bm_bc/`。

## 第 5 步：练习（约 1 小时）

- 洛谷 P4391 无线传输（next 表的应用）。

## 第 6 步：笔记与提交（约 0.5 小时）

在 `notes/ch11-串.md` 里写：

- 改进 next 表修正了什么问题；bc 表的最坏情况。

把下面的完成清单打勾，然后：

```bash
python3 tools/progress.py
git add -A
git commit -m "D32: 改进的 KMP 与 BM 坏字符"
git push
```

## ✅ 完成清单

- [ ] 读完教材 §11.3.7、§11.4 和讲义，能回答上面的问题
- [ ] 写完今天的代码
- [ ] `tools/test.sh ch11 D32` 的结果符合预期
- [ ] 对照了邓老师的代码，差异记进笔记
- [ ] 完成今天的练习
- [ ] 写完笔记，提交并推送
