# D02 · 10-31 周六 · 第1章 绪论（下）：递归

> 教材 §1.4–1.5 ｜ 讲义 第1章后半 ｜ 约 5 小时
> [← D01](../D01/README.md) ｜ [总计划](../../PLAN.md) ｜ [D03 →](../D03/README.md)

## 今天的目标

实现第1章剩下的 15 个函数，体会递归、递归分析与递归消除；第一次运行计时程序。

## 今天要动的文件

| 文件 | 内容 |
|---|---|
| `src/ch01_intro.cpp` | sumLinear、sumBinary、reverseR/I、max2I/R、hanoi、fibR/L/I、gcdEuclid、gcdCN、lcsR、lcsI |
| `notes/ch01-绪论.md` | 补完第1章笔记 |
| `exercises/ch01/` | 第1章课后习题 |

## 第 1 步：读书（约 1.5 小时）

打开教材 `deng/local-only/dsacpp-3rd-edn.pdf`，读 §1.4–1.5；再看讲义 `deng/local-only/DSA-2026F-10up-V.pdf` 的第1章后半。读的时候想清楚这几个问题，读完能用自己的话回答：

- §1.4.2 递归跟踪和递推方程，这两种分析方法各适合什么情况？
- §1.4.4 尾递归为什么容易改写成迭代？reverse 的递归版和迭代版是怎样对应的？
- §1.4.5 max2 的二分递归为什么比较次数是 5n/3 - 2？fib 的二分递归为什么是指数级？

## 第 2 步：写代码（约 2 小时）

合上书，按下面的顺序写，每写完一个函数就运行一次测试：

1. 先写线性递归和二分递归求和 `sumLinear`、`sumBinary`，注意空区间返回 0。运行 `tools/test.sh ch01 sum` 只看求和的用例。
2. 写 `reverseR`（递归），再把它改写成 `reverseI`（迭代）。写的时候对照一下：递归调用的参数变化，在迭代版里对应哪个变量的变化。
3. 写 `max2I`、`max2R`。递归版的递归基要分区间长度为 2 和 3 两种情况。
4. 写 `hanoi`：先把上面 n-1 个盘子移到中转柱，再移最大的盘子，最后把 n-1 个盘子移回来。
5. 写 `fibR`、`fibL`、`fibI`。`fibL` 要通过引用参数 `prev` 带回前一项，`fib(-1) = 1`。
6. 写 `gcdEuclid`、`gcdCN`（更相减损：先同时除掉公共的 2 的幂，再反复相减）。
7. 写 `lcsR`（朴素递归）和 `lcsI`（滚动数组的动态规划）。
8. 全部写完后，运行 `DSA_STRICT=1 tools/test.sh ch01`：“待实现”也算失败，全部通过才说明第1章写完了。

## 第 3 步：检测与调试

运行：

```bash
DSA_STRICT=1 tools/test.sh ch01
```

全部完成时，这 21 个用例都显示 `[通过]`，每个测试程序的最后一行是 `通过 …，失败 0，待实现 0`。还没写的函数显示黄色的 `[待实现]`；写错的显示红色的 `[失败]`，下面跟着出错的那行测试代码和两边的实际值。

调试提示：

- `fibR` 的测试只到 n = 30；如果这个用例特别慢，检查是不是在递归里重复做了不必要的事。
- 递归太深导致 `stack-overflow`：检查递归基是否正确，区间是否每次都在缩小。
- `gcdCN` 出错时，先用小数手算一遍，比如 gcd(64, 48)。

实测复杂度：

- 运行 `tools/bench.sh ch01_fib`，再运行 `python3 tools/plot.py ch01_fib --log`，打开生成的 `bench/results/ch01_fib.png`：fibR 在对数坐标下是一条直线（指数增长），fibL、fibI 几乎是平的。把这个观察写进笔记。

## 第 4 步：对照邓老师的代码

测试通过以后再看，逐处对比你的写法，把差异和自己没想到的地方记进笔记：

- `deng/code/src/sum/`、`reverse/`、`max/`、`fibonacci/`、`gcd/`、`hanoi/`、`lcs/`：逐个对照。
- `python3 tools/deng.py lcs`、`python3 tools/deng.py gcd -- 12 18` 可以直接运行。

## 第 5 步：练习（约 1 小时）

- 第1章课后习题：带 * 的题和编程题必做。每道题用 `python3 tools/new.py exercise ch01 1-3` 这样建文件（题号换成实际的）。
- OJ：problems/README.md 里第1章的 4 道题，用 `python3 tools/new.py problem ch01 leetcode-509 斐波那契数` 建目录，样例存成 `1.in`/`1.out`，再用 `tools/run.sh problems/ch01/leetcode-509-斐波那契数` 测。

## 第 6 步：笔记与提交（约 0.5 小时）

在 `notes/ch01-绪论.md` 里写：

- 递归跟踪和递推方程两种分析方法，各举一个例子。
- 尾递归消除的一般方法。
- max2 两种做法的比较次数推导。
- fib 实测曲线和理论复杂度是否吻合。

把下面的完成清单打勾，然后：

```bash
python3 tools/progress.py
git add -A
git commit -m "D02: 完成第1章，ch01 全部测试通过"
git push
```

## ✅ 完成清单

- [ ] 读完教材 §1.4–1.5 和讲义，能回答上面的问题
- [ ] 写完今天的代码
- [ ] `DSA_STRICT=1 tools/test.sh ch01` 的结果符合预期
- [ ] 对照了邓老师的代码，差异记进笔记
- [ ] 完成今天的练习
- [ ] 写完笔记，提交并推送
