# D01 · 10-30 周五 · 搭环境 ＋ 第1章 绪论（上）

> 教材 §1.1–1.3 ｜ 讲义 第1章前半 ｜ 约 5 小时
> [总计划](../../../../PLAN.md) ｜ [D02 →](../../D01-D08/D02/README.md)

## 今天的目标

把环境跑通，熟悉“写一个函数 → 跑测试 → 看结果”的循环；实现第1章前 6 个函数。

## 今天要动的文件

| 文件 | 内容 |
|---|---|
| `src/ch01_intro.cpp` | 第 1 天的 6 个函数：bubblesort1A、countOnes、countOnes1、power2BF、power2、sumI |
| `learn/include/dsa/ch01_intro.h` | 只看不改：每个函数的声明和要求写在这里 |
| `learn/notes/ch01-绪论.md` | 今天的笔记 |

## 第 1 步：准备

1. 在 VS Code 里打开 `清华大学dengjunhui` 这个文件夹，再打开终端（Ctrl+`）。
2. 运行 `tools/test.sh ch01`。第一次会先配置 CMake，再编译，大约半分钟。最后应看到 21 行 `[待实现]` 和一行 `通过 0，失败 0，待实现 21`，说明环境没问题。
3. 运行 `python3 tools/deng.py fibonacci -- 20`，看到邓老师示例打印的 Fibonacci 数，说明他的代码也能在 Linux 上跑。
4. 打开 `learn/include/dsa/ch01_intro.h` 通读一遍，了解第1章所有函数的要求；再打开 `src/ch01_intro.cpp`，你要写的就是这里。

## 第 2 步：读书（约 1.5 小时）

打开教材 `deng/local-only/dsacpp-3rd-edn.pdf`，读 §1.1–1.3；再看讲义 `deng/local-only/DSA-2026F-10up-V.pdf` 的第1章前半。读的时候想清楚这几个问题，读完能用自己的话回答：

- §1.1 起泡排序为什么一定会结束？每一趟扫描之后，什么性质一定成立（不变式）？
- §1.2 大 O、大 Ω、大 Θ 的定义，三者有什么区别？
- §1.3 countOnes 为什么是 O(log n)？“输入规模”应该用 n 还是 n 的二进制位数？

## 第 3 步：写代码（约 2 小时）

合上书，按下面的顺序写，每写完一个函数就运行一次测试：

1. 打开 `src/ch01_intro.cpp`，找到 `bubblesort1A`，把 `DSA_TODO();` 换成你的实现（照书上的思路：用一个 `sorted` 标志，反复扫描交换相邻逆序对）。
2. 保存后运行 `tools/test.sh ch01 D01`，`bubblesort1A` 的两个用例应变成 `[通过]`。
3. 依次实现 `countOnes`（逐位检查）、`countOnes1`（`n &= n - 1` 每次消去最低位的 1）、`power2BF`（连乘）、`power2`（反复平方，奇偶分开处理）、`sumI`（迭代求和）。每写完一个就重新运行一次上面的命令。

## 第 4 步：检测与调试

运行：

```bash
tools/test.sh ch01 D01
```

全部完成时，这 7 个用例都显示 `[通过]`，每个测试程序的最后一行是 `通过 …，失败 0，待实现 0`。还没写的函数显示黄色的 `[待实现]`；写错的显示红色的 `[失败]`，下面跟着出错的那行测试代码和两边的实际值。

调试提示：

- 编译报错时，先看第一条 `error:`，它会写出文件名和行号。
- `[失败]` 下面会打印出错的那一行测试和两边的值，比如 `CHECK_EQ(v, ...)：[2, 3, 4, 1] ≠ [1, 2, 3, 4]`，对照着找原因。
- 随机对拍失败时，最后会打印随机种子；用 `DSA_SEED=<种子> tools/test.sh ch01 D01` 可以重现同一组数据，方便加 `printf` 调试。
- 看到 `AddressSanitizer: heap-buffer-overflow` 之类的报告，说明数组越界了，报告里第一个 `#0 ... src/ch01_intro.cpp:行号` 就是出错的位置。

## 第 5 步：对照邓老师的代码

测试通过以后再看，逐处对比你的写法，把差异和自己没想到的地方记进笔记：

- `deng/code/src/bubblesort/bubble1A.cpp`：和你的起泡排序比一比。可以运行 `python3 tools/deng.py bubblesort` 看它每一趟的过程。
- `deng/code/src/countOnes/`、`deng/code/src/power/`：看看他用了哪几种写法。

## 第 6 步：练习（约 1 小时）

- 课后习题（每题一个文件，打开后在“我的解答”下面写；编程题的代码写在同目录的同名 `.cpp` 里）：
  - 必做：[[1-1]](../../../exercises/ch01/1-1.md)、[[1-2]](../../../exercises/ch01/1-2.md)、[[1-8]](../../../exercises/ch01/1-8.md)、[[1-9]](../../../exercises/ch01/1-9.md)、[[1-10]](../../../exercises/ch01/1-10.md)、[[1-13]](../../../exercises/ch01/1-13.md)
  - 选做：[[1-3]](../../../exercises/ch01/1-3.md)、[[1-4]](../../../exercises/ch01/1-4.md)、[[1-5]](../../../exercises/ch01/1-5.md)、[[1-6]](../../../exercises/ch01/1-6.md)、[[1-7]](../../../exercises/ch01/1-7.md)、[[1-11]](../../../exercises/ch01/1-11.md)、[[1-12]](../../../exercises/ch01/1-12.md)
- OJ 题（在 [learn/problems/README.md](../../../problems/README.md) 里打勾；新建题目用 `python3 tools/new.py problem D01 luogu-P1234 题名`，样例测试用 `tools/run.sh`）：
  - 必做：[洛谷 P1226 【模板】快速幂](https://www.luogu.com.cn/problem/P1226)（普及−，反复平方）；[力扣 50. Pow(x, n)](https://leetcode.cn/problems/powx-n/)（中等，快速幂，注意负指数）
  - 热身（选做）：[力扣 191. 位1的个数](https://leetcode.cn/problems/number-of-1-bits/)（简单，countOnes）
  - 挑战（选做）：[洛谷 P1045 [NOIP 2003 普及组] 麦森数](https://www.luogu.com.cn/problem/P1045)（普及/提高−，快速幂 + 高精度）

## 第 7 步：笔记与提交（约 0.5 小时）

在 `learn/notes/ch01-绪论.md` 里写：

- 大 O、大 Ω、大 Θ 的定义（用自己的话写一遍）。
- 起泡排序的不变式，以及“为什么会结束、为什么结果正确”的证明。
- countOnes 两种写法的复杂度。

把下面的完成清单打勾，然后：

```bash
python3 tools/progress.py
git add -A
git commit -m "D01: 搭好环境，完成第1章前 6 个函数"
git push
```

## ✅ 完成清单

- [x] 读完教材 §1.1–1.3 和讲义，能回答上面的问题
- [x] 写完今天的代码
- [x] `tools/test.sh ch01 D01` 的结果符合预期
- [ ] 对照了邓老师的代码，差异记进笔记
- [ ] 完成今天的练习
- [ ] 写完笔记，提交并推送
