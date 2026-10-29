# tsinghua-dsa-selfstudy

用 40 天学完邓俊辉《数据结构（C++语言版）》第 3 版（清华大学出版社），配合清华大学 2026 年秋季学期的课程讲义。

学习方式：每个数据结构和算法都**合上书从零自己实现**，再用单元测试和标准库随机对拍验证。然后和邓老师的实现逐处对照，每章写笔记（不变式、复杂度证明、易错点），并完成课后习题和 OJ 题。

## 进度

<!-- progress:start -->
`□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□`

| 项目 | 进度 |
|---|---|
| 天数 | 0 / 40 |
| 计划里的任务 | 0 / 187 |
| 下一步 | D01 · 10-30 周五 · 搭环境 ＋ 第1章 绪论（上） |
| OJ 题（problems/） | 0 道 |
| 课后习题（exercises/） | 0 道 |

■ 完成　◧ 做了一部分　□ 还没开始。这一块由 `python3 tools/progress.py` 生成，不要手改。
<!-- progress:end -->

## 学习路线

| 阶段 | 天数 | 章节 |
|---|---|---|
| 一 · 线性结构 | D01–D10 | 第1章 绪论 · 第2章 向量 · 第3章 列表 · 第4章 栈与队列 |
| 二 · 树与图 | D11–D17 | 第5章 二叉树 · 第6章 图 |
| 复习 | D18 | 第1–6章：不看书限时重写 |
| 三 · 搜索树 | D19–D25 | 第7章 搜索树 · 第8章 高级搜索树（伸展树、B-树、红黑树、kd-树） |
| 四 · 词典、堆、串、排序 | D26–D36 | 第9章 词典 · 第10章 优先级队列 · 第11章 串 · 第12章 排序 |
| 复习 | D37 | 第7–12章：不看书限时重写 |
| 综合项目 | D38–D39 | minikv 键值库 · Huffman 文件压缩 |
| 收尾 | D40 | 全书总复习、发布 v1.0 |

每天的具体任务见 [PLAN.md](PLAN.md)。

## 目录结构

```text
├── PLAN.md                 40 天计划，每天打卡
├── include/dsa/            自己实现的数据结构和算法（只有头文件）
├── tests/                  单元测试 + 和 std 随机对拍（dsa_test.h 是自带的小测试框架）
├── bench/                  实测耗时，和理论复杂度对照
├── notes/                  每章笔记
├── exercises/              教材课后习题
├── problems/               OJ 题（清华 PA、洛谷、LeetCode）
├── projects/               综合项目
├── tools/                  安装、测试、计时、做题、对拍、进度统计、编译邓老师代码的脚本
└── deng/                   邓老师的原版资料（原样保留，不修改），说明见 deng/README.md
```

## 环境要求

| 工具 | 版本 | 用途 |
|---|---|---|
| g++ 或 clang++ | 支持 C++17 | 编译 |
| make | | 编译 |
| cmake | ≥ 3.16 | 组织编译和测试 |
| ninja | 可选 | 编译更快，没有时自动改用 make |
| python3 | ≥ 3.10 | `tools/` 下的脚本（只用标准库） |
| git | | 版本管理 |
| matplotlib | 可选 | `tools/plot.py` 画复杂度曲线 |

在 Ubuntu / Debian 或 macOS（Homebrew）上一键安装：

```bash
bash tools/install_deps.sh          # 必需的
bash tools/install_deps.sh --plot   # 另外装 matplotlib
```

## 快速开始

```bash
git clone https://github.com/AzenAnn/tsinghua-dsa-selfstudy.git
cd tsinghua-dsa-selfstudy
bash tools/install_deps.sh

tools/test.sh                     # 编译并运行全部测试
tools/test.sh ch01                # 只跑第1章
DSA_STRICT=1 tools/test.sh ch01   # “待实现”也算失败，确认这一章全部完成
tools/bench.sh ch01_fib           # 运行计时程序，结果在 bench/results/
python3 tools/plot.py ch01_fib --log
python3 tools/deng.py list        # 邓老师代码包里的示例
python3 tools/deng.py fibonacci -- 20
python3 tools/progress.py         # 按 PLAN.md 的打勾情况更新上面的进度
```

## 每天怎么学

| 时间 | 做什么 |
|---|---|
| 1.5 小时 | 看讲义，读教材对应的小节 |
| 2 小时 | 合上书实现 → `tools/test.sh` 通过 → 和邓老师的实现对照，差异记进笔记 |
| 1 小时 | 课后习题或 OJ 题 |
| 0.5 小时 | 写笔记，在 PLAN.md 里打勾，`python3 tools/progress.py`，commit 并 push |

一章算完成的标准：

1. `DSA_STRICT=1 tools/test.sh chNN` 全部通过；
2. 笔记写完；
3. 课后习题里带 \* 的题和编程题做完；
4. 这一章的 OJ 题做完。

## 约定

- **区间**一律左闭右开 `[lo, hi)`，秩的类型是 `dsa::Rank`（`unsigned int`），和邓老师的代码一致，方便对照。
- **待实现**：还没写的函数体是 `DSA_TODO();`。测试遇到它记为“待实现”，不算失败，所以 CI 一直能保持绿色。
- **测试文件**命名为 `tests/test_chNN_<名字>.cpp`，新加的文件会被自动编译。每个结构至少要有边界情况测试，以及和 `std` 的随机对拍。测试失败时会打印随机种子，用 `DSA_SEED=<种子>` 复现。
- **每章开始时**，先在 `include/dsa/` 里写好接口（函数体都是 `DSA_TODO();`），在 `tests/` 里写好测试，然后再逐个实现。
- **commit 信息**以天数开头，例如 `D03: Vector 构造、扩容与分摊分析`。
- **做题**：`python3 tools/new.py problem ch02 luogu-P1908 逆序对` 新建题目，`tools/run.sh <题目目录>` 跑样例，`tools/duipai.sh <题目目录>` 对拍。

## 资料来源与版权

- 教材、讲义、示例代码和勘误均来自邓俊辉老师的课程主页 <https://dsa.cs.tsinghua.edu.cn/~deng/ds/dsacpp/>，版权归原作者所有。详见 [deng/README.md](deng/README.md)。
- 教材和讲义的 PDF 体积较大，不放在仓库里，请从课程主页下载。
- 除 `deng/` 以外，本仓库的代码和笔记是我自己写的，采用 [MIT 许可](LICENSE)。
