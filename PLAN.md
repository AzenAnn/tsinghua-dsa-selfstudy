# 40 天学习计划

从 2026-10-30（周五）到 2026-12-08（周二），每天约 5 小时。**每天具体怎么做写在 `learn/days/DNN/README.md` 里**，点下表第一列就能打开。

## 每天的流程

每份每日指南都按同样的顺序写：

1. **读书**：读教材和讲义的哪几节，带着哪几个问题读。
2. **写代码**：打开哪个文件，按什么顺序把 `DSA_TODO();` 换成实现，写完一个就运行哪条命令。
3. **检测与调试**：运行哪条测试命令，正确时的输出是什么样，常见的错误怎么查。
4. **对照邓老师的代码**：看 `deng/code/src/` 下的哪几个文件。
5. **练习**：课后习题和 OJ 题。
6. **笔记与提交**：笔记写什么，最后在指南末尾的“完成清单”里打勾，运行 `python3 tools/progress.py`，再 commit、push。

## 几条规矩

- **进度怎么算**：进度只看每份指南末尾“完成清单”的勾，一天的框全打勾才算完成；README 上的进度条和徽章由 `python3 tools/progress.py` 生成。
- **拖了就往后挤**：某一章拖了，先占用后面的复习日（D18、D37），不压缩第8章。
- **课后习题**：教材全部 292 道习题已经一题一个文件放在 `learn/exercises/chNN/`，并按内容安排到了具体某一天（见每天指南的“练习”一节）。原书没有用 \* 标出难题，这里的规则是：**编程题和证明题必做（184 道），分析、举例类选做**。当天做不完的必做题，留到本章最后一天或复习日补。
- **OJ 题**：题单见 [learn/problems/README.md](learn/problems/README.md)。
- **一章完成的标准**：`DSA_STRICT=1 tools/test.sh chNN` 全部通过，笔记写完，本章必做习题和 OJ 题做完。
- **文件怎么分**：
  - 模板类（Vector、List、BinTree、各种树、图、堆……）的声明和实现都在 `learn/include/dsa/*.h` 里；
  - 普通函数（第1章、栈的应用、Huffman、kd-树、散列码、线性排序、串匹配）的声明在 `.h`，实现在 `src/*.cpp`；
  - 每个要写的函数现在都是 `DSA_TODO();`，文件里按天分好了段。

## 总览

| 天 | 日期 | 主题 | 要写的文件 | 检测命令 |
|---|---|---|---|---|
| [D01](learn/days/D01-D08/D01/README.md) | 10-30 周五 | 搭环境 ＋ 第1章 绪论（上） | `src/ch01_intro.cpp` | `tools/test.sh ch01 D01` |
| [D02](learn/days/D01-D08/D02/README.md) | 10-31 周六 | 第1章 绪论（下）：递归 | `src/ch01_intro.cpp` | `DSA_STRICT=1 tools/test.sh ch01` |
| [D03](learn/days/D01-D08/D03/README.md) | 11-01 周日 | 第2章 向量（一）：构造与动态空间管理 | `learn/include/dsa/vector.h` | `tools/test.sh ch02 D03` |
| [D04](learn/days/D01-D08/D04/README.md) | 11-02 周一 | 第2章 向量（二）：无序向量 | `learn/include/dsa/vector.h` | `tools/test.sh ch02 D04` |
| [D05](learn/days/D01-D08/D05/README.md) | 11-03 周二 | 第2章 向量（三）：有序向量与排序 | `learn/include/dsa/vector.h` | `DSA_STRICT=1 tools/test.sh ch02` |
| [D06](learn/days/D01-D08/D06/README.md) | 11-04 周三 | 第3章 列表（一） | `learn/include/dsa/list.h` | `tools/test.sh ch03 D06` |
| [D07](learn/days/D01-D08/D07/README.md) | 11-05 周四 | 第3章 列表（二）：有序列表与排序 | `learn/include/dsa/list.h` | `DSA_STRICT=1 tools/test.sh ch03` |
| [D08](learn/days/D01-D08/D08/README.md) | 11-06 周五 | 第4章 栈与队列（一）：栈 | `learn/include/dsa/stack.h`、`src/stack_apps.cpp` | `tools/test.sh ch04_stack D08` |
| [D09](learn/days/D09-D16/D09/README.md) | 11-07 周六 | 第4章 栈与队列（二）：栈的典型应用 | `src/stack_apps.cpp` | `tools/test.sh ch04_stack D09` |
| [D10](learn/days/D09-D16/D10/README.md) | 11-08 周日 | 第4章 栈与队列（三）：回溯与队列 | `learn/include/dsa/queue.h`、`src/stack_apps.cpp` | `DSA_STRICT=1 tools/test.sh ch04` |
| [D11](learn/days/D09-D16/D11/README.md) | 11-09 周一 | 第5章 二叉树（一）：节点与树 | `learn/include/dsa/bintree.h` | `tools/test.sh ch05_bintree D11` |
| [D12](learn/days/D09-D16/D12/README.md) | 11-10 周二 | 第5章 二叉树（二）：遍历 | `learn/include/dsa/bintree.h` | `DSA_STRICT=1 tools/test.sh ch05_bintree` |
| [D13](learn/days/D09-D16/D13/README.md) | 11-11 周三 | 第5章 二叉树（三）：编码树与 Huffman | `src/huffman.cpp` | `DSA_STRICT=1 tools/test.sh ch05` |
| [D14](learn/days/D09-D16/D14/README.md) | 11-12 周四 | 第6章 图（一）：邻接矩阵与邻接表 | `learn/include/dsa/graph_matrix.h`、`learn/include/dsa/graph_list.h` | `tools/test.sh ch06 D14` |
| [D15](learn/days/D09-D16/D15/README.md) | 11-13 周五 | 第6章 图（二）：BFS 与 DFS | `learn/include/dsa/graph.h` | `tools/test.sh ch06 D15` |
| [D16](learn/days/D09-D16/D16/README.md) | 11-14 周六 | 第6章 图（三）：拓扑排序与双连通域 | `learn/include/dsa/graph.h` | `tools/test.sh ch06 D16` |
| [D17](learn/days/D17-D24/D17/README.md) | 11-15 周日 | 第6章 图（四）：优先级搜索、Prim、Dijkstra | `learn/include/dsa/graph.h` | `DSA_STRICT=1 tools/test.sh ch06` |
| [D18](learn/days/D17-D24/D18/README.md) | 11-16 周一 | 阶段复习一（第1–6章） | — | `tools/test.sh ch02` |
| [D19](learn/days/D17-D24/D19/README.md) | 11-17 周二 | 第7章 搜索树（一）：二叉搜索树 | `learn/include/dsa/bst.h` | `tools/test.sh ch07 D19` |
| [D20](learn/days/D17-D24/D20/README.md) | 11-18 周三 | 第7章 搜索树（二）：AVL 树 | `learn/include/dsa/bst.h`、`learn/include/dsa/avl.h` | `DSA_STRICT=1 tools/test.sh ch07` |
| [D21](learn/days/D17-D24/D21/README.md) | 11-19 周四 | 第8章 高级搜索树（一）：伸展树 | `learn/include/dsa/splay.h` | `tools/test.sh ch08_splay` |
| [D22](learn/days/D17-D24/D22/README.md) | 11-20 周五 | 第8章 高级搜索树（二）：B-树的查找与插入 | `learn/include/dsa/btree.h` | `tools/test.sh ch08_btree D22` |
| [D23](learn/days/D17-D24/D23/README.md) | 11-21 周六 | 第8章 高级搜索树（三）：B-树的删除 | `learn/include/dsa/btree.h` | `DSA_STRICT=1 tools/test.sh ch08_btree` |
| [D24](learn/days/D17-D24/D24/README.md) | 11-22 周日 | 第8章 高级搜索树（四）：红黑树的插入 | `learn/include/dsa/redblack.h` | `tools/test.sh ch08_redblack D24` |
| [D25](learn/days/D25-D32/D25/README.md) | 11-23 周一 | 第8章 高级搜索树（五）：红黑树的删除 ＋ kd-树 | `learn/include/dsa/redblack.h`、`src/kdtree.cpp` | `DSA_STRICT=1 tools/test.sh ch08` |
| [D26](learn/days/D25-D32/D26/README.md) | 11-24 周二 | 第9章 词典（一）：跳转表 | `learn/include/dsa/skiplist.h` | `tools/test.sh ch09 D26` |
| [D27](learn/days/D25-D32/D27/README.md) | 11-25 周三 | 第9章 词典（二）：散列表 | `src/hashtable.cpp`、`learn/include/dsa/hashtable.h` | `tools/test.sh ch09 D27` |
| [D28](learn/days/D25-D32/D28/README.md) | 11-26 周四 | 第9章 词典（三）：散列的应用——线性排序 | `src/sort_linear.cpp` | `DSA_STRICT=1 tools/test.sh ch09` |
| [D29](learn/days/D25-D32/D29/README.md) | 11-27 周五 | 第10章 优先级队列（一）：完全二叉堆 | `learn/include/dsa/vector.h`、`learn/include/dsa/pq.h` | `tools/test.sh ch10 D29` |
| [D30](learn/days/D25-D32/D30/README.md) | 11-28 周六 | 第10章 优先级队列（二）：左式堆 | `learn/include/dsa/pq.h`、`src/huffman.cpp` | `DSA_STRICT=1 tools/test.sh ch10` |
| [D31](learn/days/D25-D32/D31/README.md) | 11-29 周日 | 第11章 串（一）：蛮力匹配与 KMP | `src/string_match.cpp` | `tools/test.sh ch11 D31` |
| [D32](learn/days/D25-D32/D32/README.md) | 11-30 周一 | 第11章 串（二）：改进的 KMP 与 BM 坏字符 | `src/string_match.cpp` | `tools/test.sh ch11 D32` |
| [D33](learn/days/D33-D40/D33/README.md) | 12-01 周二 | 第11章 串（三）：BM 好后缀与 Karp-Rabin | `src/string_match.cpp` | `DSA_STRICT=1 tools/test.sh ch11` |
| [D34](learn/days/D33-D40/D34/README.md) | 12-02 周三 | 第12章 排序（一）：快速排序 | `learn/include/dsa/vector.h` | `tools/test.sh ch12 D34` |
| [D35](learn/days/D33-D40/D35/README.md) | 12-03 周四 | 第12章 排序（二）：选取与中位数 | `learn/include/dsa/select.h` | `tools/test.sh ch12 D35` |
| [D36](learn/days/D33-D40/D36/README.md) | 12-04 周五 | 第12章 排序（三）：希尔排序与总结 | `learn/include/dsa/vector.h` | `DSA_STRICT=1 tools/test.sh ch12` |
| [D37](learn/days/D33-D40/D37/README.md) | 12-05 周六 | 阶段复习二（第7–12章） | — | `tools/test.sh ch07` |
| [D38](learn/days/D33-D40/D38/README.md) | 12-06 周日 | 综合项目一：minikv 键值库 | `learn/projects/minikv/kvstore.h`、`learn/projects/minikv/test_minikv.cpp` | `tools/test.sh proj_minikv` |
| [D39](learn/days/D33-D40/D39/README.md) | 12-07 周一 | 综合项目二：huffzip 文件压缩 | `learn/projects/huffzip/huffzip.cpp`、`learn/projects/huffzip/main.cpp`、`learn/projects/huffzip/test_huffzip.cpp` | `tools/test.sh proj_huffzip` |
| [D40](learn/days/D33-D40/D40/README.md) | 12-08 周二 | 总复习与发布 | `README.md` | `DSA_STRICT=1 tools/test.sh` |
