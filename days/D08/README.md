# D08 · 11-06 周五 · 第4章 栈与队列（一）：栈

> 教材 §4.1–4.2 ｜ 讲义 第4章 ｜ 约 5 小时
> [← D07](../D07/README.md) ｜ [总计划](../../PLAN.md) ｜ [D09 →](../D09/README.md)

## 今天的目标

基于自己的 Vector 和 List 各实现一种栈；用栈做进制转换，并用栈把汉诺塔的递归改写成迭代。

## 今天要动的文件

| 文件 | 内容 |
|---|---|
| `include/dsa/stack.h` | Stack（基于 Vector）和 ListStack（基于 List）的 push、pop、top |
| `src/stack_apps.cpp` | “第 8 天”那一段：convert、hanoiI |
| `include/dsa/stack_apps.h` | 只看不改：声明和要求 |

## 第 1 步：读书（约 1.5 小时）

打开教材 `deng/local-only/dsacpp-3rd-edn.pdf`，读 §4.1–4.2；再看讲义 `deng/local-only/DSA-2026F-10up-V.pdf` 的第4章。读的时候想清楚这几个问题，读完能用自己的话回答：

- §4.1 栈顶放在向量的哪一端？为什么？
- §4.2.1 函数调用栈里存的是什么？
- §4.2.2 用栈消除递归：一个递归调用怎样变成“压栈一个任务”？

## 第 2 步：写代码（约 2 小时）

合上书，按下面的顺序写，每写完一个函数就运行一次测试：

1. 在 `include/dsa/stack.h` 里写 `Stack` 的 push / pop / top（各一行，调用 Vector 的 insert / remove / operator[]）。
2. 写 `ListStack` 的三个函数（栈顶放在列表末端）。运行 `tools/test.sh ch04_stack Stack`。
3. 在 `src/stack_apps.cpp` 里写 `convert`：反复取余数入栈，最后依次出栈。必须用你自己的 Stack。
4. 写 `hanoiI`：栈里放“任务”（要移动几个盘子、从哪到哪，或者“移动一个盘子”这一步）。结果必须和递归版完全一样，所以入栈顺序要和递归调用的顺序相反。可以在 stack_apps.cpp 里自己定义一个任务结构体。
5. 运行 `tools/test.sh ch04_stack D08`。

## 第 3 步：检测与调试

运行：

```bash
tools/test.sh ch04_stack D08
```

全部完成时，这 4 个用例都显示 `[通过]`，每个测试程序的最后一行是 `通过 …，失败 0，待实现 0`。还没写的函数显示黄色的 `[待实现]`；写错的显示红色的 `[失败]`，下面跟着出错的那行测试代码和两边的实际值。

调试提示：

- `convert(0, 2)` 要返回 "0"。
- hanoiI 的结果和递归版不同：打印前几步对照，一般是三个任务的入栈顺序反了。

## 第 4 步：对照邓老师的代码

测试通过以后再看，逐处对比你的写法，把差异和自己没想到的地方记进笔记：

- `deng/code/src/stack/stack.h`、`stack_list/`；`deng/code/src/conversion/`。

## 第 5 步：练习（约 1 小时）

- LeetCode 155 最小栈。

## 第 6 步：笔记与提交（约 0.5 小时）

在 `notes/ch04-栈与队列.md` 里写：

- 栈帧的内容；用栈消除递归的一般方法。

把下面的完成清单打勾，然后：

```bash
python3 tools/progress.py
git add -A
git commit -m "D08: 栈、进制转换、汉诺塔的迭代版"
git push
```

## ✅ 完成清单

- [ ] 读完教材 §4.1–4.2 和讲义，能回答上面的问题
- [ ] 写完今天的代码
- [ ] `tools/test.sh ch04_stack D08` 的结果符合预期
- [ ] 对照了邓老师的代码，差异记进笔记
- [ ] 完成今天的练习
- [ ] 写完笔记，提交并推送
