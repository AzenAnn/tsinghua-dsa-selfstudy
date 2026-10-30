// 第4章 栈与队列的应用：函数的实现。声明和说明见 learn/include/dsa/stack_apps.h
// 每个函数现在都是 DSA_TODO();，把它换成你的实现。要用自己写的 Stack / Queue。

#include "dsa/stack_apps.h"

#include <cctype>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "dsa/queue.h"
#include "dsa/stack.h"

namespace dsa {

// ---------------- 第 8 天 ----------------

std::string convert(long long n, int base) {
    DSA_TODO();
}


void hanoiI(int n, char from, char via, char to, std::vector<std::pair<char, char>>& moves) {
    DSA_TODO();
}

// ---------------- 第 9 天 ----------------

bool paren(const std::string& exp) {
    DSA_TODO();
}

bool isStackPermutation(const std::vector<int>& B) {
    DSA_TODO();
}


double evaluate(const std::string& expr, std::string& rpn) {
    DSA_TODO();
}

double evaluateRPN(const std::string& rpn) {
    DSA_TODO();
}

// ---------------- 第 10 天 ----------------

long long placeQueens(int n) {
    DSA_TODO();
}


std::vector<std::pair<int, int>> labyrinth(const std::vector<std::string>& grid, std::pair<int, int> s,
                                           std::pair<int, int> t) {
    DSA_TODO();
}

std::vector<int> bankSimulate(int nWin, const std::vector<int>& serviceTimes) {
    DSA_TODO();
}

}  // namespace dsa
