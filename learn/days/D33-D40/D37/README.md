# D37 · 12-05 周六 · 阶段复习二（第7–12章）

> 教材 第7–12章 ｜ 讲义 第7–12章 ｜ 约 5 小时
> [← D36](../../D33-D40/D36/README.md) ｜ [总计划](../../../../PLAN.md) ｜ [D38 →](../../D33-D40/D38/README.md)

## 今天的目标

限时重写后半本书最难的几个结构，补齐第7–12章的笔记和习题。

## 今天要动的文件

| 文件 | 内容 |
|---|---|
| （新分支 review2） | 重写的代码；复习完以后删掉这个分支 |

## 第 1 步：准备

1. `git switch -c review2`，把要重写的函数体换回 `DSA_TODO();`。

## 第 2 步：读书（约 1.5 小时）

- 翻一遍第7–12章自己的笔记，重点看“易错点”。

## 第 3 步：写代码（约 2 小时）

合上书，按下面的顺序写，每写完一个函数就运行一次测试：

1. 60 分钟：重写 connect34、rotateAt、AVL 的 insert 和 remove，然后 `tools/test.sh ch07`。
2. 90 分钟：重写红黑树的 solveDoubleRed 和 solveDoubleBlack，然后 `tools/test.sh ch08_redblack`。
3. 60 分钟：重写 B-树的 solveOverflow 和 solveUnderflow，然后 `tools/test.sh ch08_btree`。
4. 30 分钟：重写 buildNext、matchKMP、buildBC、matchBMbc，然后 `tools/test.sh ch11`。
5. 20 分钟：重写 partitionDUP、quickSort、quickSelect，然后 `tools/test.sh ch12`。
6. 做完后 `git switch main`，再 `git branch -D review2`。

## 第 4 步：检测与调试

运行：

```bash
tools/test.sh ch07
```

调试提示：

- 卡住超过 10 分钟的地方记下来，回去重读对应小节。

## 第 5 步：练习（约 1 小时）

- 把第7–12章还没做完的课后习题和 OJ 题补上。

## 第 6 步：笔记与提交（约 0.5 小时）

在 对应章节的笔记 里写：

- 把重写时卡住的地方补进对应章节笔记的“易错点”。

把下面的完成清单打勾，然后：

```bash
python3 tools/progress.py
git add -A
git commit -m "D37: 阶段复习二，补齐第7–12章笔记"
git push
```

## ✅ 完成清单

- [ ] 看完要复习的笔记和要求
- [ ] 写完今天的代码
- [ ] 重写的部分用测试检验通过
- [ ] 完成今天的练习
- [ ] 写完笔记，提交并推送
