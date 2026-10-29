# D38 · 12-06 周日 · 综合项目一：minikv 键值库

> 约 5 小时
> [← D37](../D37/README.md) ｜ [总计划](../../PLAN.md) ｜ [D39 →](../D39/README.md)

## 今天的目标

用自己的 B-树做一个命令行键值库，支持 put、get、del、range、size。

## 今天要动的文件

| 文件 | 内容 |
|---|---|
| `projects/minikv/kvstore.h` | KVStore 的 put、get、del、range |
| `projects/minikv/main.cpp` | 已写好的命令行界面，只看不改 |
| `projects/minikv/test_minikv.cpp` | 已写好的测试 |

## 第 1 步：读书（约 1.5 小时）

- 读 `projects/README.md` 里 minikv 的要求。
- 想清楚：range(lo, hi) 怎样在 B-树里只访问必要的节点，做到 O(log n + 输出个数)？

## 第 2 步：写代码（约 2 小时）

合上书，按下面的顺序写，每写完一个函数就运行一次测试：

1. 打开 `projects/minikv/kvstore.h`：KV 只按 key 比较，所以可以直接放进 `BTree<KV>`。
2. 写 `put`：先 search，找到就改那个关键码的 value，找不到就 insert。写 `get`、`del`。
3. 写 `range`：从根开始中序遍历，跳过不可能有 [lo, hi) 中关键码的子树。可以写一个递归的辅助函数。
4. 运行 `tools/test.sh proj_minikv`。
5. 试用命令行：`printf 'put a 1\nput b 2\nrange a z\n' | build/debug/projects/minikv/minikv`。

## 第 3 步：检测与调试

运行：

```bash
tools/test.sh proj_minikv
```

全部完成时，这 1 个用例都显示 `[通过]`，每个测试程序的最后一行是 `通过 …，失败 0，待实现 0`。还没写的函数显示黄色的 `[待实现]`；写错的显示红色的 `[失败]`，下面跟着出错的那行测试代码和两边的实际值。

调试提示：

- 测试用随机命令和 std::map 对拍，B-树的阶数也是随机的。

## 第 4 步：练习（约 1 小时）

- （选做）加 save / load 命令，把数据存到文件。

## 第 5 步：笔记与提交（约 0.5 小时）

在 对应章节的笔记 里写：

- 在 `projects/minikv/README.md` 写设计、用法、各操作的复杂度。

把下面的完成清单打勾，然后：

```bash
python3 tools/progress.py
git add -A
git commit -m "D38: minikv 键值库"
git push
```

## ✅ 完成清单

- [ ] 看完要复习的笔记和要求
- [ ] 写完今天的代码
- [ ] `tools/test.sh proj_minikv` 的结果符合预期
- [ ] 完成今天的练习
- [ ] 写完笔记，提交并推送
