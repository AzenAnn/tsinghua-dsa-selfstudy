#pragma once
// 第4章 栈与队列的应用（教材 §4.2–4.6）
//
// 这里只有声明；实现写在 src/stack_apps.cpp 里，那边现在都是 DSA_TODO();。
// 每个函数都要用你自己写的 Stack / Queue（include/dsa/stack.h、queue.h），不要用 std::stack。

#include <string>
#include <utility>
#include <vector>

#include "dsa/common.h"

namespace dsa {

// ---------------- 第 8 天：§4.1–4.2 ----------------

// §4.3.1 进制转换：把 n（n >= 0）写成 base 进制（2 <= base <= 16），数字用 0-9、A-F；n = 0 时返回 "0"
std::string convert(long long n, int base);

// §4.2.2 用栈消除递归：汉诺塔的迭代版，结果和第1章递归版 hanoi 完全相同
void hanoiI(int n, char from, char via, char to, std::vector<std::pair<char, char>>& moves);

// ---------------- 第 9 天：§4.3 ----------------

// §4.3.2 括号匹配：检查 ()、[]、{} 是否正确配对和嵌套，其他字符一律忽略
bool paren(const std::string& exp);

// §4.3.2 栈混洗：B 是 1..n 的一个排列。把 1, 2, ..., n 依次入栈、中间随时可以出栈，
// 能否让出栈序列恰好是 B？
bool isStackPermutation(const std::vector<int>& B);

// §4.3.3–4.3.4 中缀表达式求值，同时把它转成逆波兰式（后缀式）写进 rpn
// 支持：非负数（整数或小数，如 3、2.5）、+ - * / ^ !、括号；空格忽略
// 优先级从高到低：!（阶乘，后缀单目，只作用于非负整数）> ^（左结合，与书上一致）> * / > + -
// rpn 里的各项（数和运算符）用一个空格隔开，例如 "(1+2)*3" 得到 "1 2 + 3 *"
double evaluate(const std::string& expr, std::string& rpn);

// 逆波兰式求值：输入格式和 evaluate 写出的 rpn 相同
double evaluateRPN(const std::string& rpn);

// ---------------- 第 10 天：§4.4–4.6 ----------------

// §4.4.2 n 皇后：用栈实现试探回溯（不要用递归），返回解的个数
long long placeQueens(int n);

// §4.4.3 迷宫寻径：grid 里 '#' 是墙，'.' 是空地；只能上下左右走。
// 用栈做深度优先的试探回溯，返回从 s 到 t 的一条路径（含两端，相邻两格必须相邻），没有路径时返回空
std::vector<std::pair<int, int>> labyrinth(const std::vector<std::string>& grid, std::pair<int, int> s,
                                           std::pair<int, int> t);

// §4.6.2 银行服务模拟：有 nWin 个窗口，第 i 位顾客在第 i 分钟到达（i 从 0 开始），需要 serviceTimes[i] 分钟（>= 1）。
// 每分钟 t = 0, 1, 2, ... 依次发生：
//   1. 若 t < 顾客数，第 t 位顾客到达，排到人数最少的窗口（人数含正在办理的；并列时选编号最小的）；
//   2. 每个有人的窗口，队头顾客的剩余时间减 1；减到 0 的顾客在这一分钟结束时离开，离开时刻记为 t + 1。
// 返回每位顾客的离开时刻。每个窗口的队列要用你自己的 Queue。
std::vector<int> bankSimulate(int nWin, const std::vector<int>& serviceTimes);

}  // namespace dsa
