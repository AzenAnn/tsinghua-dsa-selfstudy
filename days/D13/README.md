# D13 · 11-11 周三 · 第5章 二叉树（三）：编码树与 Huffman

> 教材 §5.2、§5.5 ｜ 讲义 第5章 ｜ 约 5 小时
> [← D12](../D12/README.md) ｜ [总计划](../../PLAN.md) ｜ [D14 →](../D14/README.md)

## 今天的目标

用你的 BinTree 和 List 实现 Huffman 编码：建树、生成编码表、编码、解码；第5章收尾。

## 今天要动的文件

| 文件 | 内容 |
|---|---|
| `src/huffman.cpp` | HuffmanCoder 的构造函数、析构函数、encode、decode、wpl |
| `include/dsa/huffman.h` | 只看不改（私有成员可以按需要改） |
| `exercises/ch05/` | 第5章课后习题（今天的题号见“练习”一节） |

## 第 1 步：读书（约 1.5 小时）

打开教材 `deng/local-only/dsacpp-3rd-edn.pdf`，读 §5.2、§5.5；再看讲义 `deng/local-only/DSA-2026F-10up-V.pdf` 的第5章。读的时候想清楚这几个问题，读完能用自己的话回答：

- §5.2 前缀无歧义编码（PFC）为什么对应一棵编码树？
- §5.5 Huffman 算法为什么最优（双子性、层次性、交换论证）？

## 第 2 步：写代码（约 2 小时）

合上书，按下面的顺序写，每写完一个函数就运行一次测试：

1. 构造函数：先统计频率到 `freq_`；每个字符建一棵只有根的 `BinTree<HuffChar>`，放进一个 `List<BinTree<HuffChar>*>`（森林）。
2. 反复从森林里取出权重最小的两棵（扫描一遍列表），新建一个根，用 `attachAsLC/RC` 把两棵接上去，再放回森林；直到只剩一棵，存进 `tree_`。
3. 从根出发遍历，左 0 右 1，生成编码表 `table_`；只有一种字符时编码是 "0"。
4. 写 `encode`、`decode`、`wpl` 和析构函数（释放 tree_）。
5. 运行 `tools/test.sh ch05_huffman`，3 个用例全部通过；再运行 `DSA_STRICT=1 tools/test.sh ch05` 确认整章通过。

## 第 3 步：检测与调试

运行：

```bash
DSA_STRICT=1 tools/test.sh ch05
```

全部完成时，这 22 个用例都显示 `[通过]`，每个测试程序的最后一行是 `通过 …，失败 0，待实现 0`。还没写的函数显示黄色的 `[待实现]`；写错的显示红色的 `[失败]`，下面跟着出错的那行测试代码和两边的实际值。

调试提示：

- wpl 不是最优：检查每次是否真的取出了最小的两棵。
- 解码只有一种字符的情况要单独处理（树只有根）。
- attachAsLC 之后传进去的 BinTree 指针会被置为 nullptr，别再用它。

## 第 4 步：对照邓老师的代码

测试通过以后再看，逐处对比你的写法，把差异和自己没想到的地方记进笔记：

- `deng/code/src/huffman/`、`Huffman_PQ_List/`。

## 第 5 步：练习（约 1 小时）

- 课后习题（每题一个文件，打开后在“我的解答”下面写；编程题的代码写在同目录的同名 `.cpp` 里）：
  - 必做：[[5-19]](../../exercises/ch05/5-19.md)、[[5-20]](../../exercises/ch05/5-20.md)、[[5-21]](../../exercises/ch05/5-21.md)、[[5-28]](../../exercises/ch05/5-28.md)、[[5-29]](../../exercises/ch05/5-29.md)、[[5-30]](../../exercises/ch05/5-30.md)
  - 选做：无
- 今天是第5章的最后一天：打开 [`exercises/ch05/README.md`](../../exercises/ch05/README.md)，把本章前几天没做完的必做题补上。
- 洛谷 P1090 合并果子（就是 Huffman 的 wpl）。

## 第 6 步：笔记与提交（约 0.5 小时）

在 `notes/ch05-二叉树.md` 里写：

- Huffman 最优性的证明。
- 第5章“易错点”汇总。

把下面的完成清单打勾，然后：

```bash
python3 tools/progress.py
git add -A
git commit -m "D13: 完成第5章，Huffman 编码"
git push
```

## ✅ 完成清单

- [ ] 读完教材 §5.2、§5.5 和讲义，能回答上面的问题
- [ ] 写完今天的代码
- [ ] `DSA_STRICT=1 tools/test.sh ch05` 的结果符合预期
- [ ] 对照了邓老师的代码，差异记进笔记
- [ ] 完成今天的练习
- [ ] 写完笔记，提交并推送
