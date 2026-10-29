# OJ 题

每章 5–10 道，用来检验这一章的结构和算法会不会用。题目做完在下面打勾。能用自己在 `include/dsa/` 里写的结构就尽量用：`tools/run.sh` 编译时已经带上了 `-I include`。

## 怎么做一道题

```bash
python3 tools/new.py problem ch02 luogu-P1908 逆序对   # 新建 problems/ch02/luogu-P1908-逆序对/
# 写 sol.cpp，把样例存成 1.in / 1.out（多组就 2.in / 2.out ……）
tools/run.sh problems/ch02/luogu-P1908-逆序对          # 编译并比对样例
# 想对拍：再写 brute.cpp（暴力）和 gen.py（随机生成输入，第一个参数是种子）
tools/duipai.sh problems/ch02/luogu-P1908-逆序对
```

每道题的 `README.md` 写：题意（自己概括）、思路、复杂度、用到的结构、踩过的坑。

提交到 OJ 时，如果用了 `include/dsa/` 里的头文件，要把用到的部分粘进同一个文件。

## 题单

清华 DSA 课程的编程作业（PA）如果能访问到，优先做，并按章节补充到下面。

### 第1章 绪论
- [ ] LeetCode 509 斐波那契数（三种写法都交一次）
- [ ] LeetCode 191 位1的个数
- [ ] LeetCode 50 Pow(x, n)（快速幂）
- [ ] 洛谷 P1029 最大公约数和最小公倍数问题

### 第2章 向量
- [ ] LeetCode 27 移除元素
- [ ] LeetCode 26 删除有序数组中的重复项
- [ ] LeetCode 704 二分查找
- [ ] LeetCode 35 搜索插入位置
- [ ] LeetCode 88 合并两个有序数组
- [ ] 洛谷 P1908 逆序对（归并排序）

### 第3章 列表
- [ ] LeetCode 206 反转链表
- [ ] LeetCode 21 合并两个有序链表
- [ ] LeetCode 141 环形链表
- [ ] LeetCode 148 排序链表
- [ ] LeetCode 146 LRU 缓存

### 第4章 栈与队列
- [ ] LeetCode 155 最小栈
- [ ] LeetCode 20 有效的括号
- [ ] LeetCode 150 逆波兰表达式求值
- [ ] LeetCode 224 基本计算器
- [ ] 洛谷 P1449 后缀表达式
- [ ] LeetCode 51 N 皇后
- [ ] LeetCode 622 设计循环队列
- [ ] LeetCode 84 柱状图中最大的矩形

### 第5章 二叉树
- [ ] LeetCode 144 / 94 / 145 二叉树的前序、中序、后序遍历（都用迭代写）
- [ ] LeetCode 102 二叉树的层序遍历
- [ ] LeetCode 105 从前序与中序遍历序列构造二叉树
- [ ] LeetCode 889 根据前序和后序遍历构造二叉树
- [ ] 洛谷 P1030 求先序排列
- [ ] 洛谷 P1090 合并果子（Huffman）

### 第6章 图
- [ ] 洛谷 P5318 查找文献（BFS、DFS）
- [ ] LeetCode 200 岛屿数量
- [ ] LeetCode 207 课程表、LeetCode 210 课程表 II（拓扑排序）
- [ ] 洛谷 P1113 杂务
- [ ] 洛谷 P3388 割点
- [ ] 洛谷 P3366 最小生成树
- [ ] 洛谷 P4779 单源最短路径（标准版）
- [ ] LeetCode 743 网络延迟时间

### 第7章 搜索树
- [ ] LeetCode 98 验证二叉搜索树
- [ ] LeetCode 701 二叉搜索树中的插入操作
- [ ] LeetCode 450 删除二叉搜索树中的节点
- [ ] LeetCode 110 平衡二叉树
- [ ] 洛谷 P3369 普通平衡树（AVL）

### 第8章 高级搜索树
- [ ] 洛谷 P3369 普通平衡树（伸展树、红黑树各过一次）
- [ ] 洛谷 P3391 文艺平衡树（伸展树）
- [ ] 洛谷 P1429 平面最近点对（kd-树）

### 第9章 词典
- [ ] LeetCode 1206 设计跳表
- [ ] LeetCode 705 设计哈希集合、LeetCode 706 设计哈希映射
- [ ] LeetCode 1 两数之和
- [ ] 洛谷 P3370 字符串哈希
- [ ] LeetCode 164 最大间距（桶）

### 第10章 优先级队列
- [ ] 洛谷 P3378 堆
- [ ] LeetCode 23 合并 K 个升序链表
- [ ] 洛谷 P3377 左偏树（可并堆）
- [ ] 洛谷 P1456 Monkey King

### 第11章 串
- [ ] LeetCode 28 找出字符串中第一个匹配项的下标（KMP、BM 各交一次）
- [ ] 洛谷 P3375 KMP 字符串匹配
- [ ] 洛谷 P4391 无线传输
- [ ] LeetCode 459 重复的子字符串
- [ ] LeetCode 187 重复的 DNA 序列（Karp-Rabin）

### 第12章 排序
- [ ] 洛谷 P1177 快速排序
- [ ] LeetCode 75 颜色分类（三路划分）
- [ ] 洛谷 P1923 求第 k 小的数
- [ ] LeetCode 169 多数元素
- [ ] LeetCode 215 数组中的第 K 个最大元素
- [ ] LeetCode 4 寻找两个正序数组的中位数
