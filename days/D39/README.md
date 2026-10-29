# D39 · 12-07 周一 · 综合项目二：huffzip 文件压缩

> 约 5 小时
> [← D38](../D38/README.md) ｜ [总计划](../../PLAN.md) ｜ [D40 →](../D40/README.md)

## 今天的目标

用自己的 Huffman 树和堆做一个文件压缩工具。

## 今天要动的文件

| 文件 | 内容 |
|---|---|
| `projects/huffzip/huffzip.cpp` | compress、decompress |
| `projects/huffzip/main.cpp` | 已写好的命令行界面 |
| `projects/huffzip/test_huffzip.cpp` | 已写好的测试 |

## 第 1 步：读书（约 1.5 小时）

- 读 `projects/README.md` 里 huffzip 的要求。
- 设计压缩文件的格式：原文长度、各字节的频率、比特流。解压时要能用同样的频率建出同一棵树。

## 第 2 步：写代码（约 2 小时）

合上书，按下面的顺序写，每写完一个函数就运行一次测试：

1. 在 `huffzip.cpp` 里写 `compress`：统计 256 种字节的频率，建 Huffman 树（用你的堆），生成编码表，把比特流每 8 位装成一个字节；文件头写原文长度和频率表。
2. 写 `decompress`：读文件头，用同样的方法建树，按比特从根走到叶子还原。
3. 运行 `tools/test.sh proj_huffzip`。
4. 试用：`build/debug/projects/huffzip/huffzip c README.md /tmp/r.hz` 再 `... d /tmp/r.hz /tmp/r.md`，用 `cmp README.md /tmp/r.md` 确认一致。

## 第 3 步：检测与调试

运行：

```bash
tools/test.sh proj_huffzip
```

全部完成时，这 2 个用例都显示 `[通过]`，每个测试程序的最后一行是 `通过 …，失败 0，待实现 0`。还没写的函数显示黄色的 `[待实现]`；写错的显示红色的 `[失败]`，下面跟着出错的那行测试代码和两边的实际值。

调试提示：

- 压缩和解压建树时，权重相同的树谁先取出必须一致，否则树不一样，解压出乱码。
- 空文件、只有一种字节的文件要单独处理。

## 第 4 步：练习（约 1 小时）

- 用几类文件（文本、代码、图片）测压缩率，并和 `gzip` 对比。

## 第 5 步：笔记与提交（约 0.5 小时）

在 对应章节的笔记 里写：

- 在 `projects/huffzip/README.md` 写格式设计和压缩率表格。

把下面的完成清单打勾，然后：

```bash
python3 tools/progress.py
git add -A
git commit -m "D39: huffzip 文件压缩"
git push
```

## ✅ 完成清单

- [ ] 看完要复习的笔记和要求
- [ ] 写完今天的代码
- [ ] `tools/test.sh proj_huffzip` 的结果符合预期
- [ ] 完成今天的练习
- [ ] 写完笔记，提交并推送
