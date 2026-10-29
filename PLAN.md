# 40 天学习计划

从 2026-10-30（周五）开始，到 2026-12-08（周二）结束，每天约 5 小时。

每天的任务做完一项就把 `[ ]` 改成 `[x]`，一天的框全打勾才算这一天完成。然后运行 `python3 tools/progress.py`，把进度更新到 README。

几条规矩：

- **拖了就往后挤**：某一章拖了，先占用后面的复习日，不压缩第8章。
- **习题怎么做**：每章带 \* 的题和编程题必做，其余的挑一半左右。
- **题目在哪**：题号对应的题目列在 [problems/README.md](problems/README.md)。
- **每章先搭接口**：第1章的接口和测试已经写好了。从第2章起，每章第一天先在 `include/dsa/` 写接口，在 `tests/` 写测试，再开始实现。

---

## 阶段一 · 线性结构（D01–D10）

### D01 · 10-30 周五 · 搭环境 ＋ 第1章 绪论（上）
- [ ] 读 README；`tools/test.sh` 能跑，第1章 21 个用例全是“待实现”；`python3 tools/deng.py fibonacci -- 20` 能跑
- [ ] 学：教材 §1.1–1.3（计算机与算法、复杂度度量、复杂度分析），看讲义第1章前半
- [ ] 写：`include/dsa/ch01_intro.h` 里第 1 天的 6 个函数（bubblesort1A、countOnes、countOnes1、power2BF、power2、sumI）
- [ ] 测：`tools/test.sh ch01` 这 6 个函数的用例全部通过
- [ ] 记：`notes/ch01-绪论.md` 写大 O、Ω、Θ 的定义，以及起泡排序的不变式和正确性证明；commit

### D02 · 10-31 周六 · 第1章 绪论（下）· 递归
- [ ] 学：教材 §1.4–1.5（线性递归、递归分析、递归模式、递归消除、二分递归、ADT），看讲义第1章后半
- [ ] 写：ch01 剩下的函数（sumLinear、sumBinary、reverseR/I、max2I/R、hanoi、fibR/L/I、gcdEuclid、gcdCN、lcsR、lcsI）
- [ ] 测：`DSA_STRICT=1 tools/test.sh ch01` 全部通过；`tools/bench.sh ch01_fib` 再用 `tools/plot.py ch01_fib --log` 画图，看指数和线性的差距
- [ ] 题：第1章课后习题；problems 第1章的题
- [ ] 记：递归跟踪与递推方程两种分析方法、尾递归消除、max2 两种做法的比较次数；commit

### D03 · 11-01 周日 · 第2章 向量（一）· 构造与动态空间管理
- [ ] 学：教材 §2.1–2.4（从数组到向量、接口、构造与析构、动态空间管理），讲义第2章
- [ ] 写：`include/dsa/vector.h` 和 `tests/test_ch02_vector.cpp` 的接口与测试；实现构造、析构、copyFrom、expand、shrink、`operator[]`、`operator=`
- [ ] 测：`tools/test.sh ch02` 通过；写 `bench/ch02_expand.cpp` 比较两种扩容：容量加倍与每次固定加一个常数
- [ ] 记：加倍扩容的分摊 O(1) 证明、固定增量为什么是分摊 O(n)、装填因子与缩容的抖动问题；commit

### D04 · 11-02 周一 · 第2章 向量（二）· 无序向量
- [ ] 学：教材 §2.5（元素访问、置乱器、判等器与比较器、无序查找、插入、删除、唯一化、遍历）
- [ ] 写：permute、unsort、find、insert、remove（单个和区间）、deduplicate、traverse（函数指针和函数对象两种）
- [ ] 测：随机操作序列和 `std::vector` 对拍 10⁵ 次以上
- [ ] 题：problems 第2章前半
- [ ] 记：为什么区间删除比逐个删除快；deduplicate 的正确性（不变式）；commit

### D05 · 11-03 周二 · 第2章 向量（三）· 有序向量与排序
- [ ] 学：教材 §2.6–2.8（有序向量、二分查找 A/B/C、Fibonacci 查找、排序下界、起泡排序、归并排序）
- [ ] 写：disordered、uniquify（O(n)）、search 的三个二分版本和 Fibonacci 查找、sort 统一入口、bubbleSort、mergeSort
- [ ] 测：search 的语义是“返回不大于 e 的最后一个元素的秩”，和 `std::upper_bound` 对拍；排序和 `std::sort` 对拍，含大量重复元素的数据
- [ ] 题：第2章课后习题；problems 第2章后半（含洛谷 P1908 逆序对，用自己的归并排序）
- [ ] 记：三个二分版本的不变式和返回值、Fibonacci 查找的平均查找长度、比较排序 Ω(n log n) 下界的比较树证明；commit

### D06 · 11-04 周三 · 第3章 列表（一）
- [ ] 学：教材 §3.1–3.3（从向量到列表、接口、列表）
- [ ] 写：`include/dsa/list.h`：ListNode、头尾哨兵、init、insertAsFirst/Last、insertA/B、copyNodes、remove、clear、find、deduplicate、traverse
- [ ] 测：`tests/test_ch03_list.cpp` 和 `std::list` 对拍
- [ ] 题：problems 第3章前半
- [ ] 记：哨兵为什么能消除边界判断；按秩访问为什么是 O(n)；commit

### D07 · 11-05 周四 · 第3章 列表（二）· 有序列表与排序
- [ ] 学：教材 §3.4–3.5（有序列表、排序器）
- [ ] 写：uniquify、search（有序）、insertionSort、selectionSort、mergeSort（列表版）
- [ ] 测：排序和 `std::sort` 对拍，检查排序是否稳定
- [ ] 题：第3章课后习题；problems 第3章后半
- [ ] 记：插入排序的比较次数与逆序对数的关系、选择排序为什么不受输入影响、列表归并的细节；commit

### D08 · 11-06 周五 · 第4章 栈与队列（一）
- [ ] 学：教材 §4.1–4.2（栈的接口、Stack 模板类、函数调用栈、避免递归）
- [ ] 写：`include/dsa/stack.h`（基于自己的 Vector，再写一个基于 List 的版本）；进制转换 convert(n, base)
- [ ] 测：`tests/test_ch04_stack.cpp`
- [ ] 题：problems 第4章前几题
- [ ] 记：栈帧里有什么；用栈把递归改成迭代的一般方法；commit

### D09 · 11-07 周六 · 第4章 栈与队列（二）· 栈的典型应用
- [ ] 学：教材 §4.3（逆序输出、递归嵌套、延迟缓冲、逆波兰表达式）
- [ ] 写：括号匹配、栈混洗判定、中缀表达式求值（同时输出逆波兰式）
- [ ] 测：表达式求值和自己写的递归下降求值器对拍（随机生成表达式）
- [ ] 题：problems 第4章中间几题（括号、逆波兰、计算器）
- [ ] 记：运算符优先级表的构造、栈混洗的计数（Catalan 数）和禁形“312”；commit

### D10 · 11-08 周日 · 第4章 栈与队列（三）· 回溯与队列
- [ ] 学：教材 §4.4–4.6（试探回溯法、八皇后、迷宫寻径、队列、循环分配器、银行服务模拟）
- [ ] 写：用栈实现的八皇后（输出解的个数）、迷宫寻径；`include/dsa/queue.h`；银行服务模拟
- [ ] 测：八皇后的解数对照 OEIS A000170（n ≤ 12）；队列和 `std::queue` 对拍
- [ ] 题：第4章课后习题；problems 第4章剩下的题
- [ ] 记：剪枝和回溯的模板、递归版与栈版的对应关系；commit

## 阶段二 · 树与图（D11–D18）

### D11 · 11-09 周一 · 第5章 二叉树（一）
- [ ] 学：教材 §5.1–5.3（二叉树及其表示、编码树、二叉树的实现）
- [ ] 写：`include/dsa/bintree.h`：BinNode（height、size、insertAsLC/RC、succ）、BinTree（updateHeight、updateHeightAbove、insert、attach、remove、secede）
- [ ] 测：`tests/test_ch05_bintree.cpp`：随机建树，检查高度和规模
- [ ] 题：problems 第5章前几题
- [ ] 记：长子-兄弟表示法；为什么 updateHeightAbove 只需要向上走；commit

### D12 · 11-10 周二 · 第5章 二叉树（二）· 遍历
- [ ] 学：教材 §5.4（先序、中序、后序、层次遍历）
- [ ] 写：四种遍历的递归版；先序迭代版（两种）、中序迭代版（三种：栈、succ、无栈无标志）、后序迭代版、层次遍历；由先序+中序重构二叉树；由先序+后序重构真二叉树
- [ ] 测：所有迭代版和递归版对拍；重构后再遍历，结果应与原序列一致
- [ ] 题：problems 第5章中间几题（迭代遍历、重构）
- [ ] 记：每种迭代遍历的“藤缠树”思路；为什么先序+后序只能重构真二叉树；commit

### D13 · 11-11 周三 · 第5章 二叉树（三）· 编码树与 Huffman
- [ ] 学：教材 §5.2、§5.5（PFC 编码、Huffman 编码）
- [ ] 写：PFC 编码树；Huffman 树（优先级队列先用列表实现）、编码表、编码与解码
- [ ] 测：随机文本编码后再解码，应还原原文；带权路径长度和贪心法的最优值一致
- [ ] 题：第5章课后习题；problems 第5章剩下的题（含洛谷 P1090 合并果子）
- [ ] 记：Huffman 最优性的证明（双子性、不唯一性、层次性、交换论证）；commit

### D14 · 11-12 周四 · 第6章 图（一）· 表示
- [ ] 学：教材 §6.1–6.4（概述、抽象数据类型、邻接矩阵、邻接表）
- [ ] 写：`include/dsa/graph.h`：Graph 抽象基类、GraphMatrix，再自己写一个邻接表版 GraphList
- [ ] 测：`tests/test_ch06_graph.cpp`：随机插入、删除顶点和边，两种表示的结果一致
- [ ] 记：两种表示在各操作上的复杂度对比表；commit

### D15 · 11-13 周五 · 第6章 图（二）· BFS 与 DFS
- [ ] 学：教材 §6.5–6.7（遍历算法概述、广度优先搜索、深度优先搜索）
- [ ] 写：BFS（顶点的 dTime、树边与跨边）；DFS（dTime/fTime，边分为 TREE、BACKWARD、FORWARD、CROSS 四类）；先写递归版，再写栈版
- [ ] 测：BFS 距离和朴素松弛算法对拍；DFS 的括号引理（任意两个顶点的活跃期要么嵌套要么不相交）
- [ ] 题：problems 第6章前几题
- [ ] 记：边分类的判定规则、括号引理的证明；commit

### D16 · 11-14 周六 · 第6章 图（三）· 拓扑排序与双连通
- [ ] 学：教材 §6.8–6.9（拓扑排序、双连通域分解）
- [ ] 写：拓扑排序（基于 DFS 的版本和零入度版本）、双连通域分解（hca）
- [ ] 测：拓扑序检验（每条边从前指向后）；关节点和暴力做法（逐个删点判连通）对拍
- [ ] 题：problems 第6章中间几题（拓扑、割点）
- [ ] 记：为什么“有向无环 ⇔ DFS 没有后向边”；hca 的定义与更新规则；commit

### D17 · 11-15 周日 · 第6章 图（四）· 优先级搜索
- [ ] 学：教材 §6.10–6.12（优先级搜索、最小支撑树、最短路径）
- [ ] 写：PFS 框架加 prioUpdater；用它写出 Prim 和 Dijkstra（先用 O(n²) 版本，第10章以后换成堆）
- [ ] 测：Prim 和 Kruskal 对拍；Dijkstra 和 Bellman-Ford 对拍
- [ ] 题：第6章课后习题；problems 第6章剩下的题（最小生成树、单源最短路）
- [ ] 记：割的性质与 Prim 的正确性、Dijkstra 为什么不能有负权边；commit

### D18 · 11-16 周一 · 阶段复习一（第1–6章）
- [ ] 不看书、不看自己的代码，在新分支上限时重写，用原来的测试检验：Vector 的 expand、insert、remove、二分查找 C 版、mergeSort（60 分钟）
- [ ] 限时重写 List 的哨兵、insert、remove、insertionSort（45 分钟）；BinTree 的迭代中序和迭代后序（30 分钟）；BFS、DFS、拓扑排序（45 分钟）
- [ ] 把重写时卡住的地方补进对应章节的笔记“易错点”
- [ ] 第1–6章笔记补齐，没做完的习题补上；commit

## 阶段三 · 搜索树（D19–D25）

### D19 · 11-17 周二 · 第7章 搜索树（一）· 二叉搜索树
- [ ] 学：教材 §7.1–7.2（查找、二叉搜索树）
- [ ] 写：`include/dsa/bst.h`：search（返回引用，并维护 _hot）、insert、remove（removeAt 借助 succ）
- [ ] 测：`tests/test_ch07_bst.cpp`：随机操作和 `std::set` 对拍；每次操作后检查中序遍历有序
- [ ] 题：problems 第7章前几题
- [ ] 记：_hot 的语义与它带来的便利；随机生成与随机组成的平均高度；commit

### D20 · 11-18 周三 · 第7章 搜索树（二）· AVL 树
- [ ] 学：教材 §7.3–7.4（平衡二叉搜索树、AVL 树）
- [ ] 写：`include/dsa/avl.h`：等价变换（zig、zag）、insert、remove、connect34、rotateAt
- [ ] 测：每次操作后检查 AVL 性质（平衡因子、高度）和中序有序；和 `std::set` 对拍 10⁵ 次
- [ ] 题：第7章课后习题；problems 第7章剩下的题（洛谷 P3369 普通平衡树，用自己的 AVL）
- [ ] 记：插入只需一次调整、删除可能需要 O(log n) 次调整的原因；“3+4 重构”为什么能统一四种旋转；commit

### D21 · 11-19 周四 · 第8章 高级搜索树（一）· 伸展树
- [ ] 学：教材 §8.1（伸展树）
- [ ] 写：`include/dsa/splay.h`：双层伸展（zig-zig、zig-zag）、search、insert、remove
- [ ] 测：和 `std::set` 对拍；`bench/ch08_splay.cpp` 比较单层伸展与双层伸展在顺序访问下的耗时
- [ ] 题：problems 第8章伸展树的题（P3369 再用伸展树过一次，P3391 文艺平衡树）
- [ ] 记：势能函数、双层伸展的分摊 O(log n) 证明；单层伸展的最坏情况；commit

### D22 · 11-20 周五 · 第8章 高级搜索树（二）· B-树 查找与插入
- [ ] 学：教材 §8.2（多路平衡查找、B-树的定义、查找、插入、高度）
- [ ] 写：`include/dsa/btree.h`：BTNode、search、insert、solveOverflow（分裂）
- [ ] 测：m 取 3 到 8，每次插入后检查 B-树性质（每个节点的关键码数在 ⌈m/2⌉-1 到 m-1 之间、所有叶子同深）；和 `std::set` 对拍
- [ ] 记：B-树的高度上下界；为什么 B-树适合外存；commit

### D23 · 11-21 周六 · 第8章 高级搜索树（三）· B-树 删除
- [ ] 学：教材 §8.2（删除、下溢与合并）
- [ ] 写：remove、solveUnderflow（先向左右兄弟借，借不到就合并）
- [ ] 测：随机插入、删除交替进行，和 `std::set` 对拍，每步检查 B-树性质
- [ ] 记：上溢、下溢各种情况的示意图；commit

### D24 · 11-22 周日 · 第8章 高级搜索树（四）· 红黑树 插入
- [ ] 学：教材 §8.3（红黑树的定义、和 (2,4)-树的等价、黑高度、插入）
- [ ] 写：`include/dsa/redblack.h`：updateHeight（黑高度）、insert、solveDoubleRed（RR-1、RR-2）
- [ ] 测：每次插入后检查红黑性质（根黑、红节点的孩子是黑的、各路径黑高度相同）
- [ ] 记：红黑树和 4 阶 B-树的对应关系；插入的两种情况各需几次旋转；commit

### D25 · 11-23 周一 · 第8章 高级搜索树（五）· 红黑树 删除 ＋ kd-树
- [ ] 学：教材 §8.3（删除）、§8.4（kd-树）
- [ ] 写：remove、solveDoubleBlack（BB-1、BB-2R、BB-2B、BB-3）；2d-树的构造与范围查询
- [ ] 测：红黑树随机插入、删除，和 `std::set` 对拍，每步检查红黑性质；kd-树的范围查询和暴力扫描对拍
- [ ] 题：第8章课后习题；problems 第8章剩下的题（P3369 用红黑树再过一次，P1429 平面最近点对）
- [ ] 记：删除时四种情况的判定顺序和各自的拓扑变化次数；kd-树范围查询 O(√n + r) 的证明；commit

## 阶段四 · 词典、优先级队列、串、排序（D26–D37）

### D26 · 11-24 周二 · 第9章 词典（一）· 跳转表
- [ ] 学：教材 §9.1–9.2（词典 ADT、跳转表）
- [ ] 写：`include/dsa/skiplist.h`：四联表 Quadlist、get、put、remove
- [ ] 测：和 `std::map` 对拍；统计塔高分布，和几何分布的理论值对比
- [ ] 题：problems 第9章跳表的题（LeetCode 1206）
- [ ] 记：期望高度 O(log n) 和查找的期望复杂度证明；commit

### D27 · 11-25 周三 · 第9章 词典（二）· 散列表
- [ ] 学：教材 §9.3（散列函数、冲突解决、懒惰删除、重散列）
- [ ] 写：`include/dsa/hashtable.h`：除余法、MAD 法、多项式字符串散列；开放定址（线性试探、平方试探）、懒惰删除、重散列
- [ ] 测：和 `std::unordered_map` 对拍；`bench/ch09_probe.cpp` 比较不同装填因子下两种试探的平均试探次数
- [ ] 题：problems 第9章散列的题
- [ ] 记：为什么表长取素数；平方试探在装填因子 ≤ 1/2 时一定能找到空桶的证明；commit

### D28 · 11-26 周四 · 第9章 词典（三）· 散列应用
- [ ] 学：教材 §9.4（桶排序、最大间隙、基数排序、计数排序）
- [ ] 写：`include/dsa/sort_linear.h`：桶排序、计数排序、基数排序
- [ ] 测：和 `std::sort` 对拍，检查稳定性
- [ ] 题：第9章课后习题；problems 第9章剩下的题（LeetCode 164 最大间距）
- [ ] 记：基数排序为什么要求每一趟稳定；“最大间隙”的鸽巢原理；commit

### D29 · 11-27 周五 · 第10章 优先级队列（一）· 完全二叉堆
- [ ] 学：教材 §10.1–10.2（优先级队列 ADT、堆）
- [ ] 写：`include/dsa/pq_heap.h`：percolateUp、percolateDown、Floyd 建堆、堆排序（顺便补上 Vector::heapSort）
- [ ] 测：和 `std::priority_queue` 对拍；`bench/ch10_heapify.cpp` 比较逐个插入建堆与 Floyd 建堆
- [ ] 题：problems 第10章前几题（洛谷 P3378 堆）
- [ ] 记：Floyd 建堆为什么是 O(n)（所有节点高度之和）；commit

### D30 · 11-28 周六 · 第10章 优先级队列（二）· 左式堆
- [ ] 学：教材 §10.3（左式堆）
- [ ] 写：`include/dsa/leftheap.h`：NPL、merge（递归版和迭代版）；把第5章的 Huffman、第6章的 PFS 改用堆
- [ ] 测：合并操作和 `std::priority_queue` 对拍；Huffman 改用堆后结果不变、速度变快
- [ ] 题：第10章课后习题；problems 第10章剩下的题（P3377 左偏树、P1456 Monkey King）
- [ ] 记：左式堆右侧链长度 O(log n) 的证明；commit

### D31 · 11-29 周日 · 第11章 串（一）· 蛮力与 KMP
- [ ] 学：教材 §11.1–11.3（串及串匹配、蛮力算法、KMP 算法）
- [ ] 写：`include/dsa/string_match.h`：蛮力匹配的两个版本、KMP（next 表）
- [ ] 测：和 `std::string::find` 对拍，包括小字符集的随机串（例如只有 a、b）
- [ ] 题：problems 第11章前几题（洛谷 P3375 KMP）
- [ ] 记：next 表的含义与递推构造；KMP 为什么是 O(n + m)（分摊分析）；commit

### D32 · 11-30 周一 · 第11章 串（二）· KMP 改进与 BM 坏字符
- [ ] 学：教材 §11.3（next 表的改进）、§11.4（BM 算法：坏字符策略）
- [ ] 写：改进的 next 表；BM 的 bc 表与只用坏字符的匹配
- [ ] 测：同 D31 的对拍
- [ ] 题：problems 第11章中间几题（P4391 无线传输）
- [ ] 记：改进 next 表修正了什么问题；bc 表的构造与最坏情况；commit

### D33 · 12-01 周二 · 第11章 串（三）· BM 好后缀与 Karp-Rabin
- [ ] 学：教材 §11.4（好后缀策略、gs 表）、§11.5（Karp-Rabin 算法）
- [ ] 写：ss 表与 gs 表的构造、完整的 BM；Karp-Rabin（指纹与滚动散列）
- [ ] 测：所有串匹配算法互相对拍；`bench/ch11_match.cpp` 在大字符集和小字符集下比较各算法
- [ ] 题：第11章课后习题；problems 第11章剩下的题
- [ ] 记：gs 表的 O(m) 构造；各算法适用场景的对比表；commit

### D34 · 12-02 周三 · 第12章 排序（一）· 快速排序
- [ ] 学：教材 §12.1（快速排序）
- [ ] 写：轴点构造的 LUG 版、DUP 版、LGU 版，随机选轴点，迭代版（用栈）
- [ ] 测：含大量重复元素的随机数据和 `std::sort` 对拍；`bench/ch12_quicksort.cpp` 比较各版本在重复元素多时的表现
- [ ] 题：problems 第12章前几题（洛谷 P1177、LeetCode 75）
- [ ] 记：快排的平均比较次数约 1.386 n log n 的推导；DUP 版为什么能避免重复元素导致的退化；commit

### D35 · 12-03 周四 · 第12章 排序（二）· 选取与中位数
- [ ] 学：教材 §12.2（众数、中位数、k-选取）
- [ ] 写：majority（摩尔投票）、两个有序向量的中位数、quickSelect、linearSelect
- [ ] 测：和 `std::nth_element` 对拍
- [ ] 题：problems 第12章中间几题（洛谷 P1923、LeetCode 4、169、215）
- [ ] 记：linearSelect 为什么是 O(n)（分组大小取 5 的分析）；commit

### D36 · 12-04 周五 · 第12章 排序（三）· 希尔排序与总结
- [ ] 学：教材 §12.3（希尔排序），回顾 §2.7 的排序下界
- [ ] 写：希尔排序，支持 Shell、Papernov-Stasevic、Pratt、Sedgewick 四种增量序列
- [ ] 测：和 `std::sort` 对拍；`bench/ch12_shell.cpp` 比较各增量序列
- [ ] 题：第12章课后习题；problems 第12章剩下的题
- [ ] 记：h-有序与 g-有序的保持性（邮资问题）；全书排序算法对比表（时间、空间、稳定性、是否就地）；commit

### D37 · 12-05 周六 · 阶段复习二（第7–12章）
- [ ] 限时重写，用原来的测试检验：AVL（60 分钟）、红黑树的插入和删除（90 分钟）
- [ ] 限时重写 B-树（60 分钟）、KMP 和 BM 坏字符（30 分钟）、快速排序和 quickSelect（20 分钟）
- [ ] 把卡住的地方补进笔记的“易错点”
- [ ] 第7–12章笔记补齐，没做完的习题补上；commit

## 综合项目与收尾（D38–D40）

### D38 · 12-06 周日 · 综合项目一：minikv
- [ ] 按 [projects/README.md](projects/README.md) 的要求，用自己的 B-树（或跳表）做一个支持 put、get、del、range 的命令行键值库
- [ ] 用随机操作和 `std::map` 对拍
- [ ] 写好项目的 README（设计、用法、复杂度）；commit

### D39 · 12-07 周一 · 综合项目二：huffzip
- [ ] 用自己的 Huffman 树、左式堆和位图做一个文件压缩工具（压缩、解压）
- [ ] 测：随机文件、空文件、只有一种字节的文件，压缩后再解压都要和原文件一致；记录压缩率
- [ ] 写好项目的 README；commit

### D40 · 12-08 周二 · 总复习与发布
- [ ] `DSA_STRICT=1 tools/test.sh` 全部通过
- [ ] 通读全部笔记，写一篇总结 `notes/总结.md`：各结构的复杂度总表、证明方法、最大的收获
- [ ] `python3 tools/progress.py` 更新 README；打 tag `v1.0` 并发布
