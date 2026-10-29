# D06 · 11-04 周三 · 第3章 列表（一）

> 教材 §3.1–3.3 ｜ 讲义 第3章 ｜ 约 5 小时
> [← D05](../D05/README.md) ｜ [总计划](../../PLAN.md) ｜ [D07 →](../D07/README.md)

## 今天的目标

实现带头尾哨兵的双向链表：节点插入、列表的构造与析构、按秩访问、查找、插入、删除、去重、遍历。

## 今天要动的文件

| 文件 | 内容 |
|---|---|
| `include/dsa/list.h` | “第 6 天”那一段：insertAsPred、insertAsSucc、init、clear、copyNodes、3 个复制构造函数、析构、operator[]、find、4 个插入、remove、dedup、traverse |

## 第 1 步：读书（约 1.5 小时）

打开教材 `deng/local-only/dsacpp-3rd-edn.pdf`，读 §3.1–3.3；再看讲义 `deng/local-only/DSA-2026F-10up-V.pdf` 的第3章。读的时候想清楚这几个问题，读完能用自己的话回答：

- §3.2 头尾哨兵有什么好处？没有哨兵的话，insert 和 remove 要多处理哪些边界？
- §3.3 为什么列表的按秩访问是 O(r)？
- §3.3 dedup：书上的做法遇到重复时删掉的是前面那个，所以每个值留下的是最后一次出现的。

## 第 2 步：写代码（约 2 小时）

合上书，按下面的顺序写，每写完一个函数就运行一次测试：

1. 先写节点的 `insertAsPred`、`insertAsSucc`：新建节点，改 4 个指针。
2. 写 `init`（创建两个哨兵，互相连上）、`insertAsFirst/Last`、两个 `insert`、`remove`。运行 `tools/test.sh ch03 insert`。
3. 写 `clear`、析构函数（删除全部节点和两个哨兵）、`copyNodes` 和 3 个复制构造函数。
4. 写 `operator[]`、`find`（在 p 的 n 个真前驱中从后往前找）、`dedup`、`traverse`。
5. 运行 `tools/test.sh ch03 D06`。

## 第 3 步：检测与调试

运行：

```bash
tools/test.sh ch03 D06
```

全部完成时，这 7 个用例都显示 `[通过]`，每个测试程序的最后一行是 `通过 …，失败 0，待实现 0`。还没写的函数显示黄色的 `[待实现]`；写错的显示红色的 `[失败]`，下面跟着出错的那行测试代码和两边的实际值。

调试提示：

- 测试里的 `toStd` 会顺着 succ 走一遍并检查 `p->succ->pred == p`，指针没接好会在这里报错。
- `memory leaks`：析构函数里忘了删哨兵。
- `find` 找不到时返回 `nullptr`。

## 第 4 步：对照邓老师的代码

测试通过以后再看，逐处对比你的写法，把差异和自己没想到的地方记进笔记：

- `deng/code/src/list/listNode_insertAsPred.h`、`listNode_insertAsSucc.h`、`list_initialize.h`、`List_insert.h`、`list_remove.h`、`list_copyNodes.h`、`List_find.h`、`List_deduplicate.h`。

## 第 5 步：练习（约 1 小时）

- LeetCode 206 反转链表、21 合并两个有序链表、141 环形链表。

## 第 6 步：笔记与提交（约 0.5 小时）

在 `notes/ch03-列表.md` 里写：

- 哨兵为什么能消除边界判断（画图）。
- 向量和列表在各操作上的复杂度对比表。

把下面的完成清单打勾，然后：

```bash
python3 tools/progress.py
git add -A
git commit -m "D06: List 的基本操作"
git push
```

## ✅ 完成清单

- [ ] 读完教材 §3.1–3.3 和讲义，能回答上面的问题
- [ ] 写完今天的代码
- [ ] `tools/test.sh ch03 D06` 的结果符合预期
- [ ] 对照了邓老师的代码，差异记进笔记
- [ ] 完成今天的练习
- [ ] 写完笔记，提交并推送
