# OJ 题单

一共 182 道题，分到第 1–36 天，和当天学的内容对应。每道题都分了层：

| 层次 | 数量 | 说明 |
|---|---|---|
| **必做** | 98 | 用当天学的结构或算法解决，难度从普及到提高+，这是训练的主体 |
| 热身 | 43 | 简单题，用来检验实现是否熟练；有把握可以跳过 |
| 挑战 | 41 | 提高+ 到 NOI 难度（含 Codeforces），时间够时做，做不出来可以留到复习日 |

括号里是 OJ 自己标的难度：洛谷的“入门 → 普及− → 普及/提高− → 普及+/提高 → 提高+/省选− → 省选/NOI− → NOI/NOI+/CTSC”，力扣的简单/中等/困难，Codeforces 的 rating。题号和标题都用各 OJ 的接口核对过（2026-10-30）。

做完一道就把前面的 `[ ]` 改成 `[x]`，`python3 tools/progress.py` 会统计完成数。

## 怎么做一道题

```bash
python3 tools/new.py problem ch02 luogu-P1908 逆序对   # 新建 problems/ch02/luogu-P1908-逆序对/
# 写 sol.cpp，把样例存成 1.in / 1.out（多组就 2.in / 2.out ……）
tools/run.sh problems/ch02/luogu-P1908-逆序对          # 编译并比对样例
# 想对拍：再写 brute.cpp（暴力）和 gen.py（随机生成输入，第一个参数是种子）
tools/duipai.sh problems/ch02/luogu-P1908-逆序对
```

- 每道题的 `README.md` 写：题意（自己概括）、思路、复杂度、用到的结构、踩过的坑。
- 能用自己在 `include/dsa/` 里写的结构就尽量用（`tools/run.sh` 编译时已带上 `-I include` 和 `src/*.cpp`）；提交到 OJ 时，把用到的部分粘进同一个文件。
- 一道必做题卡住超过 40 分钟，先看题解的思路（不看代码），再自己写。

## 第1章 绪论

### D01

- [ ] **必做** · [洛谷 P1226 【模板】快速幂](https://www.luogu.com.cn/problem/P1226)（普及−，反复平方）
- [ ] **必做** · [力扣 50. Pow(x, n)](https://leetcode.cn/problems/powx-n/)（中等，快速幂，注意负指数）
- [ ] **热身** · [力扣 191. 位1的个数](https://leetcode.cn/problems/number-of-1-bits/)（简单，countOnes）
- [ ] **挑战** · [洛谷 P1045 [NOIP 2003 普及组] 麦森数](https://www.luogu.com.cn/problem/P1045)（普及/提高−，快速幂 + 高精度）

### D02

- [ ] **必做** · [洛谷 P1029 [NOIP 2001 普及组] 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)（普及−，gcd）
- [ ] **必做** · [洛谷 P1464 [PacNW 1999] Function](https://www.luogu.com.cn/problem/P1464)（普及−，记忆化递归）
- [ ] **必做** · [洛谷 P1255 数楼梯](https://www.luogu.com.cn/problem/P1255)（普及−，Fibonacci + 高精度）
- [ ] **必做** · [力扣 1143. 最长公共子序列](https://leetcode.cn/problems/longest-common-subsequence/)（中等，lcsI）
- [ ] **热身** · [力扣 509. 斐波那契数](https://leetcode.cn/problems/fibonacci-number/)（简单，三种写法都交一次）
- [ ] **热身** · [力扣 70. 爬楼梯](https://leetcode.cn/problems/climbing-stairs/)（简单，递推）
- [ ] **挑战** · [洛谷 P1439 两个排列的最长公共子序列](https://www.luogu.com.cn/problem/P1439)（普及+/提高，排列的 LCS 转 LIS，O(n log n)）
- [ ] **挑战** · [洛谷 P1962 斐波那契数列](https://www.luogu.com.cn/problem/P1962)（普及+/提高，矩阵快速幂）
- [ ] **挑战** · [洛谷 P1939 矩阵加速（数列）](https://www.luogu.com.cn/problem/P1939)（普及+/提高，矩阵快速幂）

## 第2章 向量

### D04

- [ ] **必做** · [力扣 283. 移动零](https://leetcode.cn/problems/move-zeroes/)（简单，就地、一趟）
- [ ] **必做** · [力扣 189. 轮转数组](https://leetcode.cn/problems/rotate-array/)（中等，三次倒置）
- [ ] **热身** · [力扣 27. 移除元素](https://leetcode.cn/problems/remove-element/)（简单，区间删除的思路）

### D05

- [ ] **必做** · [力扣 34. 在排序数组中查找元素的第一个和最后一个位置](https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/)（中等，二分的边界）
- [ ] **必做** · [洛谷 P2249 【深基13.例1】查找](https://www.luogu.com.cn/problem/P2249)（普及−，二分，返回第一次出现）
- [ ] **必做** · [洛谷 P1908 逆序对](https://www.luogu.com.cn/problem/P1908)（普及/提高−，归并时统计）
- [ ] **必做** · [洛谷 P1873 [COCI 2011/2012 #5] EKO / 砍树](https://www.luogu.com.cn/problem/P1873)（普及−，二分答案）
- [ ] **必做** · [洛谷 P2678 [NOIP 2015 提高组] 跳石头](https://www.luogu.com.cn/problem/P2678)（普及/提高−，二分答案）
- [ ] **热身** · [力扣 704. 二分查找](https://leetcode.cn/problems/binary-search/)（简单）
- [ ] **热身** · [力扣 35. 搜索插入位置](https://leetcode.cn/problems/search-insert-position/)（简单，search 的语义）
- [ ] **热身** · [力扣 26. 删除有序数组中的重复项](https://leetcode.cn/problems/remove-duplicates-from-sorted-array/)（简单，uniquify）
- [ ] **热身** · [力扣 88. 合并两个有序数组](https://leetcode.cn/problems/merge-sorted-array/)（简单，merge）
- [ ] **挑战** · [洛谷 P1083 [NOIP 2012 提高组] 借教室](https://www.luogu.com.cn/problem/P1083)（普及/提高−，二分 + 差分）
- [ ] **挑战** · [洛谷 P1966 [NOIP 2013 提高组] 火柴排队](https://www.luogu.com.cn/problem/P1966)（提高+/省选−，转化为逆序对）
- [ ] **挑战** · [洛谷 P1309 [NOIP 2011 普及组] 瑞士轮](https://www.luogu.com.cn/problem/P1309)（普及/提高−，每轮只需归并，不用重排）
- [ ] **挑战** · [力扣 493. 翻转对](https://leetcode.cn/problems/reverse-pairs/)（困难，归并中统计）
- [ ] **挑战** · [力扣 315. 计算右侧小于当前元素的个数](https://leetcode.cn/problems/count-of-smaller-numbers-after-self/)（困难，归并中统计）

## 第3章 列表

### D06

- [ ] **必做** · [力扣 19. 删除链表的倒数第 N 个结点](https://leetcode.cn/problems/remove-nth-node-from-end-of-list/)（中等，双指针 + 哨兵）
- [ ] **必做** · [力扣 141. 环形链表](https://leetcode.cn/problems/linked-list-cycle/)（简单，快慢指针）
- [ ] **必做** · [力扣 142. 环形链表 II](https://leetcode.cn/problems/linked-list-cycle-ii/)（中等，快慢指针求入口）
- [ ] **必做** · [洛谷 P1160 队列安排](https://www.luogu.com.cn/problem/P1160)（普及/提高−，双向链表的插入、删除）
- [ ] **必做** · [洛谷 P1996 约瑟夫问题](https://www.luogu.com.cn/problem/P1996)（普及−，循环链表）
- [ ] **热身** · [力扣 206. 反转链表](https://leetcode.cn/problems/reverse-linked-list/)（简单）
- [ ] **热身** · [力扣 203. 移除链表元素](https://leetcode.cn/problems/remove-linked-list-elements/)（简单，哨兵）
- [ ] **热身** · [力扣 21. 合并两个有序链表](https://leetcode.cn/problems/merge-two-sorted-lists/)（简单）

### D07

- [ ] **必做** · [力扣 148. 排序链表](https://leetcode.cn/problems/sort-list/)（中等，列表归并排序）
- [ ] **必做** · [力扣 146. LRU 缓存](https://leetcode.cn/problems/lru-cache/)（中等，哈希 + 双向链表）
- [ ] **必做** · [力扣 25. K 个一组翻转链表](https://leetcode.cn/problems/reverse-nodes-in-k-group/)（困难）
- [ ] **挑战** · [力扣 460. LFU 缓存](https://leetcode.cn/problems/lfu-cache/)（困难）
- [ ] **挑战** · [洛谷 P7912 [CSP-J 2021] 小熊的果篮](https://www.luogu.com.cn/problem/P7912)（普及+/提高，链表维护块）

## 第4章 栈与队列

### D08

- [ ] **必做** · [洛谷 P4387 【深基15.习9】验证栈序列](https://www.luogu.com.cn/problem/P4387)（普及/提高−，栈混洗判定）
- [ ] **必做** · [洛谷 P1044 [NOIP 2003 普及组] 栈](https://www.luogu.com.cn/problem/P1044)（普及−，栈混洗计数（Catalan））
- [ ] **热身** · [力扣 232. 用栈实现队列](https://leetcode.cn/problems/implement-queue-using-stacks/)（简单）
- [ ] **热身** · [力扣 155. 最小栈](https://leetcode.cn/problems/min-stack/)（中等）

### D09

- [ ] **必做** · [洛谷 P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739)（入门）
- [ ] **必做** · [洛谷 P1981 [NOIP 2013 普及组] 表达式求值](https://www.luogu.com.cn/problem/P1981)（普及−，优先级）
- [ ] **必做** · [洛谷 P1175 表达式的转换](https://www.luogu.com.cn/problem/P1175)（普及+/提高，中缀转后缀并逐步计算）
- [ ] **必做** · [力扣 224. 基本计算器](https://leetcode.cn/problems/basic-calculator/)（困难，含一元负号）
- [ ] **必做** · [洛谷 P5788 【模板】单调栈](https://www.luogu.com.cn/problem/P5788)（普及/提高−）
- [ ] **必做** · [力扣 84. 柱状图中最大的矩形](https://leetcode.cn/problems/largest-rectangle-in-histogram/)（困难，单调栈）
- [ ] **热身** · [力扣 20. 有效的括号](https://leetcode.cn/problems/valid-parentheses/)（简单）
- [ ] **热身** · [力扣 150. 逆波兰表达式求值](https://leetcode.cn/problems/evaluate-reverse-polish-notation/)（中等）
- [ ] **热身** · [洛谷 P1449 后缀表达式](https://www.luogu.com.cn/problem/P1449)（普及−）
- [ ] **挑战** · [力扣 85. 最大矩形](https://leetcode.cn/problems/maximal-rectangle/)（困难，单调栈）

### D10

- [ ] **必做** · [力扣 51. N 皇后](https://leetcode.cn/problems/n-queens/)（困难）
- [ ] **必做** · [力扣 622. 设计循环队列](https://leetcode.cn/problems/design-circular-queue/)（中等）
- [ ] **必做** · [洛谷 P1886 【模板】单调队列 / 滑动窗口](https://www.luogu.com.cn/problem/P1886)（普及/提高−，单调队列）
- [ ] **热身** · [洛谷 P1219 [USACO1.5] 八皇后 Checker Challenge](https://www.luogu.com.cn/problem/P1219)（普及/提高−，回溯）
- [ ] **热身** · [洛谷 P1605 迷宫](https://www.luogu.com.cn/problem/P1605)（普及−，回溯）
- [ ] **挑战** · [洛谷 P2216 [HAOI2007] 理想的正方形](https://www.luogu.com.cn/problem/P2216)（普及+/提高，二维单调队列）
- [ ] **挑战** · [洛谷 P1725 琪露诺](https://www.luogu.com.cn/problem/P1725)（普及+/提高，单调队列优化 DP）

## 第5章 二叉树

### D11

- [ ] **必做** · [洛谷 P1087 [NOIP 2004 普及组] FBI 树](https://www.luogu.com.cn/problem/P1087)（普及−，递归建树）
- [ ] **热身** · [力扣 104. 二叉树的最大深度](https://leetcode.cn/problems/maximum-depth-of-binary-tree/)（简单）
- [ ] **热身** · [力扣 226. 翻转二叉树](https://leetcode.cn/problems/invert-binary-tree/)（简单）
- [ ] **热身** · [洛谷 P4913 【深基16.例3】二叉树深度](https://www.luogu.com.cn/problem/P4913)（普及−）
- [ ] **热身** · [洛谷 P1305 新二叉树](https://www.luogu.com.cn/problem/P1305)（普及−）

### D12

- [ ] **必做** · [力扣 105. 从前序与中序遍历序列构造二叉树](https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)（中等）
- [ ] **必做** · [力扣 106. 从中序与后序遍历序列构造二叉树](https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal/)（中等）
- [ ] **必做** · [力扣 889. 根据前序和后序遍历构造二叉树](https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-postorder-traversal/)（中等，真二叉树）
- [ ] **必做** · [洛谷 P1030 [NOIP 2001 普及组] 求先序排列](https://www.luogu.com.cn/problem/P1030)（普及−）
- [ ] **必做** · [洛谷 P1827 [USACO3.4] 美国血统 American Heritage](https://www.luogu.com.cn/problem/P1827)（普及−）
- [ ] **必做** · [洛谷 P1229 遍历问题](https://www.luogu.com.cn/problem/P1229)（普及/提高−，先序 + 后序时的可能数）
- [ ] **热身** · [力扣 144. 二叉树的前序遍历](https://leetcode.cn/problems/binary-tree-preorder-traversal/)（简单，用迭代写）
- [ ] **热身** · [力扣 94. 二叉树的中序遍历](https://leetcode.cn/problems/binary-tree-inorder-traversal/)（简单，用迭代写）
- [ ] **热身** · [力扣 145. 二叉树的后序遍历](https://leetcode.cn/problems/binary-tree-postorder-traversal/)（简单，用迭代写）
- [ ] **热身** · [力扣 102. 二叉树的层序遍历](https://leetcode.cn/problems/binary-tree-level-order-traversal/)（中等）
- [ ] **挑战** · [力扣 297. 二叉树的序列化与反序列化](https://leetcode.cn/problems/serialize-and-deserialize-binary-tree/)（困难）
- [ ] **挑战** · [力扣 124. 二叉树中的最大路径和](https://leetcode.cn/problems/binary-tree-maximum-path-sum/)（困难）

### D13

- [ ] **必做** · [洛谷 P1090 [NOIP 2004 提高组] 合并果子](https://www.luogu.com.cn/problem/P1090)（普及/提高−，Huffman 的带权路径长度）
- [ ] **挑战** · [洛谷 P2168 [NOI2015] 荷马史诗](https://www.luogu.com.cn/problem/P2168)（提高+/省选−，k 叉 Huffman）

## 第6章 图

### D14

- [ ] **热身** · [力扣 997. 找到小镇的法官](https://leetcode.cn/problems/find-the-town-judge/)（简单，入度、出度）

### D15

- [ ] **必做** · [洛谷 P5318 【深基18.例3】查找文献](https://www.luogu.com.cn/problem/P5318)（普及−，BFS、DFS）
- [ ] **必做** · [洛谷 P3916 图的遍历](https://www.luogu.com.cn/problem/P3916)（普及/提高−，反向建图）
- [ ] **必做** · [力扣 200. 岛屿数量](https://leetcode.cn/problems/number-of-islands/)（中等）
- [ ] **必做** · [力扣 994. 腐烂的橘子](https://leetcode.cn/problems/rotting-oranges/)（中等，多源 BFS）
- [ ] **必做** · [洛谷 P1135 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)（普及/提高−，BFS）
- [ ] **挑战** · [洛谷 P1144 最短路计数](https://www.luogu.com.cn/problem/P1144)（普及+/提高，BFS 计数）

### D16

- [ ] **必做** · [力扣 207. 课程表](https://leetcode.cn/problems/course-schedule/)（中等，拓扑排序判环）
- [ ] **必做** · [力扣 210. 课程表 II](https://leetcode.cn/problems/course-schedule-ii/)（中等）
- [ ] **必做** · [洛谷 P1113 [USACO02FEB] 杂务](https://www.luogu.com.cn/problem/P1113)（普及/提高−，拓扑序上的 DP）
- [ ] **必做** · [洛谷 P1347 [ECNA 2001] 排序](https://www.luogu.com.cn/problem/P1347)（普及+/提高，逐条加边做拓扑排序）
- [ ] **必做** · [洛谷 P3388 【模板】割点](https://www.luogu.com.cn/problem/P3388)（普及+/提高，hca）
- [ ] **挑战** · [洛谷 P8435 【模板】点双连通分量](https://www.luogu.com.cn/problem/P8435)（普及+/提高，bcc）
- [ ] **挑战** · [洛谷 P2860 [USACO06JAN] Redundant Paths G](https://www.luogu.com.cn/problem/P2860)（提高+/省选−，边双连通）
- [ ] **挑战** · [洛谷 P3387 【模板】缩点 / 强连通分量](https://www.luogu.com.cn/problem/P3387)（普及+/提高，强连通 + DAG DP）

### D17

- [ ] **必做** · [洛谷 P3366 【模板】最小生成树](https://www.luogu.com.cn/problem/P3366)（普及/提高−，Prim）
- [ ] **必做** · [洛谷 P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)（普及/提高−，Dijkstra + 堆）
- [ ] **必做** · [力扣 743. 网络延迟时间](https://leetcode.cn/problems/network-delay-time/)（中等）
- [ ] **必做** · [力扣 1631. 最小体力消耗路径](https://leetcode.cn/problems/path-with-minimum-effort/)（中等）
- [ ] **必做** · [洛谷 P1396 营救](https://www.luogu.com.cn/problem/P1396)（普及/提高−，瓶颈路）
- [ ] **必做** · [洛谷 P1119 灾后重建](https://www.luogu.com.cn/problem/P1119)（普及+/提高，Floyd 的本质）
- [ ] **挑战** · [洛谷 P2865 [USACO06NOV] Roadblocks G](https://www.luogu.com.cn/problem/P2865)（提高+/省选−，次短路）
- [ ] **挑战** · [洛谷 P4568 [JLOI2011] 飞行路线](https://www.luogu.com.cn/problem/P4568)（普及+/提高，分层图）
- [ ] **挑战** · [洛谷 P3008 [USACO11JAN] Roads and Planes G](https://www.luogu.com.cn/problem/P3008)（提高+/省选−，负权边 + 拓扑 + Dijkstra）
- [ ] **挑战** · [力扣 787. K 站中转内最便宜的航班](https://leetcode.cn/problems/cheapest-flights-within-k-stops/)（中等）

## 第7章 搜索树

### D19

- [ ] **必做** · [力扣 450. 删除二叉搜索树中的节点](https://leetcode.cn/problems/delete-node-in-a-bst/)（中等，removeAt）
- [ ] **必做** · [力扣 230. 二叉搜索树中第 K 小的元素](https://leetcode.cn/problems/kth-smallest-element-in-a-bst/)（中等）
- [ ] **必做** · [力扣 235. 二叉搜索树的最近公共祖先](https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-search-tree/)（中等）
- [ ] **必做** · [洛谷 P5076 【深基16.例7】普通二叉树（简化版）](https://www.luogu.com.cn/problem/P5076)（普及+/提高）
- [ ] **热身** · [力扣 700. 二叉搜索树中的搜索](https://leetcode.cn/problems/search-in-a-binary-search-tree/)（简单）
- [ ] **热身** · [力扣 701. 二叉搜索树中的插入操作](https://leetcode.cn/problems/insert-into-a-binary-search-tree/)（中等）
- [ ] **热身** · [力扣 98. 验证二叉搜索树](https://leetcode.cn/problems/validate-binary-search-tree/)（中等）

### D20

- [ ] **必做** · [洛谷 P3369 【模板】普通平衡树](https://www.luogu.com.cn/problem/P3369)（省选/NOI−，用你的 AVL）
- [ ] **必做** · [力扣 1382. 将二叉搜索树变平衡](https://leetcode.cn/problems/balance-a-binary-search-tree/)（中等）
- [ ] **必做** · [洛谷 P2234 [HNOI2002] 营业额统计](https://www.luogu.com.cn/problem/P2234)（普及−，前驱后继）
- [ ] **热身** · [力扣 110. 平衡二叉树](https://leetcode.cn/problems/balanced-binary-tree/)（简单）
- [ ] **挑战** · [力扣 99. 恢复二叉搜索树](https://leetcode.cn/problems/recover-binary-search-tree/)（中等）
- [ ] **挑战** · [洛谷 P1503 鬼子进村](https://www.luogu.com.cn/problem/P1503)（普及+/提高，前驱后继）

## 第8章 高级搜索树

### D21

- [ ] **必做** · [洛谷 P3391 【模板】文艺平衡树](https://www.luogu.com.cn/problem/P3391)（省选/NOI−，伸展树区间翻转）
- [ ] **挑战** · [洛谷 P2042 [NOI2005] 维护数列](https://www.luogu.com.cn/problem/P2042)（NOI/NOI+/CTSC，伸展树综合）

### D24

- [ ] **必做** · [洛谷 P2286 [HNOI2004] 宠物收养场](https://www.luogu.com.cn/problem/P2286)（普及/提高−，平衡树前驱后继）

### D25

- [ ] **必做** · [洛谷 P1486 [NOI2004] 郁闷的出纳员](https://www.luogu.com.cn/problem/P1486)（提高+/省选−，平衡树）
- [ ] **必做** · [洛谷 P1429 平面最近点对（加强版）](https://www.luogu.com.cn/problem/P1429)（提高+/省选−，kd-树或分治）
- [ ] **挑战** · [洛谷 P6136 【模板】普通平衡树（数据加强版）](https://www.luogu.com.cn/problem/P6136)（省选/NOI−，强制在线）
- [ ] **挑战** · [洛谷 P4148 简单题](https://www.luogu.com.cn/problem/P4148)（NOI/NOI+/CTSC，kd-树）
- [ ] **挑战** · [洛谷 P3224 [HNOI2012] 永无乡](https://www.luogu.com.cn/problem/P3224)（省选/NOI−，平衡树启发式合并）

## 第9章 词典

### D26

- [ ] **必做** · [力扣 1206. 设计跳表](https://leetcode.cn/problems/design-skiplist/)（困难）

### D27

- [ ] **必做** · [力扣 49. 字母异位词分组](https://leetcode.cn/problems/group-anagrams/)（中等）
- [ ] **必做** · [力扣 128. 最长连续序列](https://leetcode.cn/problems/longest-consecutive-sequence/)（中等）
- [ ] **必做** · [力扣 560. 和为 K 的子数组](https://leetcode.cn/problems/subarray-sum-equals-k/)（中等，前缀和 + 散列）
- [ ] **必做** · [洛谷 P3370 【模板】字符串哈希](https://www.luogu.com.cn/problem/P3370)（普及−）
- [ ] **必做** · [洛谷 P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)（普及−）
- [ ] **必做** · [洛谷 P4305 [JLOI2011] 不重复数字](https://www.luogu.com.cn/problem/P4305)（普及−）
- [ ] **必做** · [洛谷 P3405 [USACO16DEC] Cities and States S](https://www.luogu.com.cn/problem/P3405)（普及−）
- [ ] **热身** · [力扣 1. 两数之和](https://leetcode.cn/problems/two-sum/)（简单）
- [ ] **热身** · [力扣 705. 设计哈希集合](https://leetcode.cn/problems/design-hashset/)（简单）
- [ ] **热身** · [力扣 706. 设计哈希映射](https://leetcode.cn/problems/design-hashmap/)（简单）
- [ ] **挑战** · [洛谷 P1381 单词背诵](https://www.luogu.com.cn/problem/P1381)（普及+/提高，散列 + 双指针）
- [ ] **挑战** · [洛谷 P1955 [NOI2015] 程序自动分析](https://www.luogu.com.cn/problem/P1955)（普及+/提高，离散化 + 并查集）
- [ ] **挑战** · [CF 4C Registration System](https://codeforces.com/problemset/problem/4/C)（CF 1300）

### D28

- [ ] **必做** · [力扣 164. 最大间距](https://leetcode.cn/problems/maximum-gap/)（中等，桶）
- [ ] **必做** · [洛谷 P1177 【模板】排序](https://www.luogu.com.cn/problem/P1177)（普及−，用基数排序交一次）
- [ ] **热身** · [洛谷 P1271 【深基9.例1】选举学生会](https://www.luogu.com.cn/problem/P1271)（普及−，计数排序）

## 第10章 优先级队列

### D29

- [ ] **必做** · [力扣 215. 数组中的第K个最大元素](https://leetcode.cn/problems/kth-largest-element-in-an-array/)（中等）
- [ ] **必做** · [洛谷 P1168 中位数](https://www.luogu.com.cn/problem/P1168)（普及/提高−，对顶堆）
- [ ] **必做** · [力扣 295. 数据流的中位数](https://leetcode.cn/problems/find-median-from-data-stream/)（困难，对顶堆）
- [ ] **必做** · [洛谷 P1631 序列合并](https://www.luogu.com.cn/problem/P1631)（普及+/提高）
- [ ] **必做** · [洛谷 P2085 最小函数值](https://www.luogu.com.cn/problem/P2085)（普及/提高−）
- [ ] **热身** · [洛谷 P3378 【模板】堆](https://www.luogu.com.cn/problem/P3378)（普及/提高−）
- [ ] **热身** · [力扣 703. 数据流中的第 K 大元素](https://leetcode.cn/problems/kth-largest-element-in-a-stream/)（简单）
- [ ] **热身** · [力扣 1046. 最后一块石头的重量](https://leetcode.cn/problems/last-stone-weight/)（简单）
- [ ] **挑战** · [洛谷 P2827 [NOIP 2016 提高组] 蚯蚓](https://www.luogu.com.cn/problem/P2827)（提高+/省选−，三个单调队列代替堆）
- [ ] **挑战** · [洛谷 P1484 种树](https://www.luogu.com.cn/problem/P1484)（提高+/省选−，反悔贪心）

### D30

- [ ] **必做** · [力扣 23. 合并 K 个升序链表](https://leetcode.cn/problems/merge-k-sorted-lists/)（困难）
- [ ] **必做** · [洛谷 P3377 【模板】可并堆 1](https://www.luogu.com.cn/problem/P3377)（提高+/省选−）
- [ ] **必做** · [洛谷 P1456 Monkey King](https://www.luogu.com.cn/problem/P1456)（提高+/省选−，左式堆）
- [ ] **挑战** · [洛谷 P4331 [BalticOI 2004] Sequence (Day1)](https://www.luogu.com.cn/problem/P4331)（NOI/NOI+/CTSC，左式堆）

## 第11章 串

### D31

- [ ] **必做** · [洛谷 P3375 【模板】KMP](https://www.luogu.com.cn/problem/P3375)（普及+/提高）
- [ ] **必做** · [力扣 459. 重复的子字符串](https://leetcode.cn/problems/repeated-substring-pattern/)（简单，next 表）
- [ ] **热身** · [力扣 28. 找出字符串中第一个匹配项的下标](https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/)（简单，KMP、BM 各交一次）
- [ ] **热身** · [力扣 796. 旋转字符串](https://leetcode.cn/problems/rotate-string/)（简单）

### D32

- [ ] **必做** · [洛谷 P4391 [BalticOI 2009] Radio Transmission 无线传输](https://www.luogu.com.cn/problem/P4391)（普及+/提高，next 表）
- [ ] **必做** · [洛谷 P2375 [NOI2014] 动物园](https://www.luogu.com.cn/problem/P2375)（提高+/省选−，next 表）
- [ ] **必做** · [洛谷 P4824 [USACO15FEB] Censoring S](https://www.luogu.com.cn/problem/P4824)（提高+/省选−，KMP + 栈）
- [ ] **必做** · [洛谷 P3435 [POI 2006] OKR-Periods of Words](https://www.luogu.com.cn/problem/P3435)（提高+/省选−，next 表）
- [ ] **挑战** · [力扣 214. 最短回文串](https://leetcode.cn/problems/shortest-palindrome/)（困难）
- [ ] **挑战** · [力扣 1392. 最长快乐前缀](https://leetcode.cn/problems/longest-happy-prefix/)（困难）

### D33

- [ ] **必做** · [力扣 187. 重复的DNA序列](https://leetcode.cn/problems/repeated-dna-sequences/)（中等，Karp-Rabin）
- [ ] **必做** · [力扣 1044. 最长重复子串](https://leetcode.cn/problems/longest-duplicate-substring/)（困难，二分 + Karp-Rabin）
- [ ] **挑战** · [洛谷 P3193 [HNOI2008] GT考试](https://www.luogu.com.cn/problem/P3193)（省选/NOI−，KMP + 矩阵快速幂）
- [ ] **挑战** · [CF 126B Password](https://codeforces.com/problemset/problem/126/B)（CF 1700，next 表）

## 第12章 排序

### D34

- [ ] **必做** · [力扣 75. 颜色分类](https://leetcode.cn/problems/sort-colors/)（中等，三路划分）
- [ ] **热身** · [力扣 912. 排序数组](https://leetcode.cn/problems/sort-an-array/)（中等，用快排交，注意大量重复）

### D35

- [ ] **必做** · [洛谷 P1923 【深基9.例4】求第 k 小的数](https://www.luogu.com.cn/problem/P1923)（普及−，quickSelect）
- [ ] **必做** · [力扣 229. 多数元素 II](https://leetcode.cn/problems/majority-element-ii/)（中等）
- [ ] **必做** · [力扣 4. 寻找两个正序数组的中位数](https://leetcode.cn/problems/median-of-two-sorted-arrays/)（困难）
- [ ] **必做** · [力扣 324. 摆动排序 II](https://leetcode.cn/problems/wiggle-sort-ii/)（中等，选取 + 三路划分）
- [ ] **热身** · [力扣 169. 多数元素](https://leetcode.cn/problems/majority-element/)（简单，摩尔投票）
- [ ] **热身** · [洛谷 P1138 第 k 小整数](https://www.luogu.com.cn/problem/P1138)（普及−）

