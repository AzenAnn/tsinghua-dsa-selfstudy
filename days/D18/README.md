# D18 · 11-16 周一 · 阶段复习一（第1–6章）

> 教材 第1–6章 ｜ 讲义 第1–6章 ｜ 约 5 小时
> [← D17](../D17/README.md) ｜ [总计划](../../PLAN.md) ｜ [D19 →](../D19/README.md)

## 今天的目标

不看书、不看自己的代码，限时重写最核心的几个结构，用原来的测试检验；补齐第1–6章的笔记和习题。

## 今天要动的文件

| 文件 | 内容 |
|---|---|
| （新分支 review1） | 重写的代码；复习完以后删掉这个分支，不影响 main |

## 第 1 步：准备

1. 新建一个复习用的分支：`git switch -c review1`。在这个分支上，把要重写的函数体删掉、换回 `DSA_TODO();`，然后限时重写。

## 第 2 步：读书（约 1.5 小时）

- 翻一遍第1–6章自己的笔记，重点看“易错点”。

## 第 3 步：写代码（约 2 小时）

合上书，按下面的顺序写，每写完一个函数就运行一次测试：

1. 60 分钟：重写 Vector 的 expand、insert、remove（区间）、binSearchC、merge、mergeSort，然后 `tools/test.sh ch02`。
2. 45 分钟：重写 List 的 init、insertAsPred/Succ、remove、insertionSort，然后 `tools/test.sh ch03`。
3. 30 分钟：重写 travInI1 和 travPostI，然后 `tools/test.sh ch05_bintree`。
4. 45 分钟：重写 BFS、DFS、tSort，然后 `tools/test.sh ch06`。
5. 做完后 `git switch main`，再 `git branch -D review1` 删掉复习分支。

## 第 4 步：检测与调试

运行：

```bash
tools/test.sh ch02
```

调试提示：

- 卡住超过 10 分钟的地方，记下来：这就是没真正掌握的点，回去重读对应小节。

## 第 5 步：练习（约 1 小时）

- 把前 6 章还没做完的课后习题和 OJ 题补上。

## 第 6 步：笔记与提交（约 0.5 小时）

在 对应章节的笔记 里写：

- 把重写时卡住的地方补进对应章节笔记的“易错点”。

把下面的完成清单打勾，然后：

```bash
python3 tools/progress.py
git add -A
git commit -m "D18: 阶段复习一，补齐第1–6章笔记"
git push
```

## ✅ 完成清单

- [ ] 看完要复习的笔记和要求
- [ ] 写完今天的代码
- [ ] 重写的部分用测试检验通过
- [ ] 完成今天的练习
- [ ] 写完笔记，提交并推送
