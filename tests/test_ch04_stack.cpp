// 第4章 栈及其应用的测试（D08–D09）

#include <algorithm>
#include <cctype>
#include <cmath>
#include <numeric>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#include "dsa/stack.h"
#include "dsa/stack_apps.h"
#include "dsa_test.h"

using namespace dsa;
using dsa_test::randInt;

namespace {

void hanoiRef(int n, char a, char b, char c, std::vector<std::pair<char, char>>& m) {
    if (n == 0) return;
    hanoiRef(n - 1, a, c, b, m);
    m.push_back({a, c});
    hanoiRef(n - 1, b, a, c, m);
}

std::string convertRef(long long n, int base) {
    if (n == 0) return "0";
    std::string s;
    for (; n > 0; n /= base) s += "0123456789ABCDEF"[n % base];
    std::reverse(s.begin(), s.end());
    return s;
}

// ---------- 表达式的参考实现：递归下降，同时生成逆波兰式 ----------
struct RefParser {
    std::string s;
    std::size_t i = 0;
    std::string rpn;
    void out(const std::string& t) { rpn += (rpn.empty() ? "" : " ") + t; }
    double fact(double x) {
        long long n = (long long)x, r = 1;
        while (n > 1) r *= n--;
        return (double)r;
    }
    double primary() {
        if (s[i] == '(') {
            ++i;
            double v = expr();
            ++i;  // ')'
            return v;
        }
        std::size_t j = i;
        while (j < s.size() && (std::isdigit((unsigned char)s[j]) || s[j] == '.')) ++j;
        std::string num = s.substr(i, j - i);
        i = j;
        out(num);
        return std::stod(num);
    }
    double postfix() {
        double v = primary();
        while (i < s.size() && s[i] == '!') {
            ++i;
            out("!");
            v = fact(v);
        }
        return v;
    }
    double power() {
        double v = postfix();
        while (i < s.size() && s[i] == '^') {
            ++i;
            double b = postfix();
            out("^");
            v = std::pow(v, b);
        }
        return v;
    }
    double term() {
        double v = power();
        while (i < s.size() && (s[i] == '*' || s[i] == '/')) {
            char op = s[i++];
            double b = power();
            out(std::string(1, op));
            v = op == '*' ? v * b : v / b;
        }
        return v;
    }
    double expr() {
        double v = term();
        while (i < s.size() && (s[i] == '+' || s[i] == '-')) {
            char op = s[i++];
            double b = term();
            out(std::string(1, op));
            v = op == '+' ? v + b : v - b;
        }
        return v;
    }
};

double refEval(const std::string& e, std::string* rpn = nullptr) {
    RefParser p;
    for (char c : e)
        if (c != ' ') p.s += c;
    double v = p.expr();
    if (rpn) *rpn = p.rpn;
    return v;
}

// 参考的逆波兰式求值，用来检查 evaluate 写出的 rpn
double refRPN(const std::string& rpn) {
    std::vector<double> S;
    std::istringstream in(rpn);
    std::string t;
    while (in >> t) {
        if (std::isdigit((unsigned char)t[0])) {
            S.push_back(std::stod(t));
        } else if (t == "!") {
            long long n = (long long)S.back(), r = 1;
            while (n > 1) r *= n--;
            S.back() = (double)r;
        } else {
            if (S.size() < 2) return NAN;
            double b = S.back();
            S.pop_back();
            double a = S.back();
            S.pop_back();
            switch (t[0]) {
                case '+': S.push_back(a + b); break;
                case '-': S.push_back(a - b); break;
                case '*': S.push_back(a * b); break;
                case '/': S.push_back(a / b); break;
                case '^': S.push_back(std::pow(a, b)); break;
                default: return NAN;
            }
        }
    }
    return S.size() == 1 ? S[0] : NAN;
}

std::string genExpr(int depth) {
    if (depth == 0 || randInt(0, 3) == 0) {
        if (randInt(0, 4) == 0) return std::to_string(randInt(0, 9)) + "." + std::to_string(randInt(1, 9));
        long long x = randInt(0, 12);
        if (x <= 5 && randInt(0, 3) == 0) return std::to_string(x) + "!";
        return std::to_string(x);
    }
    if (randInt(0, 3) == 0) return "(" + genExpr(depth - 1) + ")";
    static const char ops[] = "+-*/^";
    char op = ops[randInt(0, 4)];
    if (op == '^') {  // 指数取小整数，有时带 !，检验 ! 比 ^ 优先
        std::string ex = std::to_string(randInt(0, 3));
        if (randInt(0, 3) == 0) ex += "!";
        return genExpr(depth - 1) + "^" + ex;
    }
    return genExpr(depth - 1) + op + genExpr(depth - 1);
}

bool near(double a, double b) { return std::fabs(a - b) <= 1e-9 * std::max(1.0, std::fabs(b)); }

}  // namespace

// ======================= 第 8 天 =======================

TEST("D08 Stack：push / pop / top 和 std::vector 对拍") {
    Stack<int> S;
    std::vector<int> ref;
    for (int op = 0; op < 20000; ++op) {
        if (ref.empty() || randInt(0, 2)) {
            int e = (int)randInt(0, 1000);
            S.push(e);
            ref.push_back(e);
        } else {
            REQUIRE_EQ(S.top(), ref.back());
            REQUIRE_EQ(S.pop(), ref.back());
            ref.pop_back();
        }
        REQUIRE_EQ(S.size(), (Rank)ref.size());
    }
    if (!ref.empty()) {
        S.top() = -7;  // top 返回引用，可以改
        CHECK_EQ(S.pop(), -7);
    }
}

TEST("D08 ListStack：push / pop / top 和 std::vector 对拍") {
    ListStack<int> S;
    std::vector<int> ref;
    for (int op = 0; op < 20000; ++op) {
        if (ref.empty() || randInt(0, 2)) {
            int e = (int)randInt(0, 1000);
            S.push(e);
            ref.push_back(e);
        } else {
            REQUIRE_EQ(S.top(), ref.back());
            REQUIRE_EQ(S.pop(), ref.back());
            ref.pop_back();
        }
        REQUIRE_EQ(S.size(), (Rank)ref.size());
    }
}

TEST("D08 convert：进制转换") {
    CHECK_EQ(convert(0, 2), std::string("0"));
    CHECK_EQ(convert(10, 2), std::string("1010"));
    CHECK_EQ(convert(255, 16), std::string("FF"));
    CHECK_EQ(convert(2026, 8), std::string("3752"));
    for (int round = 0; round < 5000; ++round) {
        long long n = randInt(0, round % 2 ? 1000 : 4000000000000000000LL);
        int base = (int)randInt(2, 16);
        REQUIRE_EQ(convert(n, base), convertRef(n, base));
    }
}

TEST("D08 hanoiI：用栈消除递归，结果和递归版一模一样") {
    for (int n = 0; n <= 12; ++n) {
        std::vector<std::pair<char, char>> a, b;
        hanoiI(n, 'A', 'B', 'C', a);
        hanoiRef(n, 'A', 'B', 'C', b);
        REQUIRE_EQ(a, b);
    }
}

// ======================= 第 9 天 =======================

TEST("D09 paren：括号匹配") {
    CHECK(paren(""));
    CHECK(paren("a(b[c]{d})e"));
    CHECK(paren("{[()()]}"));
    CHECK(!paren("("));
    CHECK(!paren(")("));
    CHECK(!paren("([)]"));
    CHECK(!paren("{[}"));
    for (int round = 0; round < 5000; ++round) {
        std::string s;
        int len = (int)randInt(0, 20);
        for (int i = 0; i < len; ++i) s += "()[]{}x"[randInt(0, 6)];
        std::stack<char> st;
        bool ok = true;
        for (char c : s) {
            if (c == '(' || c == '[' || c == '{') {
                st.push(c);
            } else if (c != 'x') {
                char want = c == ')' ? '(' : c == ']' ? '[' : '{';
                if (st.empty() || st.top() != want) {
                    ok = false;
                    break;
                }
                st.pop();
            }
        }
        ok = ok && st.empty();
        REQUIRE_EQ(paren(s), ok);
    }
}

TEST("D09 isStackPermutation：栈混洗的个数是 Catalan 数，并且恰好不含 312 模式") {
    const long long catalan[] = {1, 1, 2, 5, 14, 42, 132, 429};
    for (int n = 1; n <= 7; ++n) {
        std::vector<int> B(n);
        std::iota(B.begin(), B.end(), 1);
        long long count = 0;
        do {
            bool has312 = false;  // 存在 i < j < k 使 B[j] < B[k] < B[i]
            for (int i = 0; i < n && !has312; ++i)
                for (int j = i + 1; j < n && !has312; ++j)
                    for (int k = j + 1; k < n && !has312; ++k)
                        if (B[j] < B[k] && B[k] < B[i]) has312 = true;
            bool got = isStackPermutation(B);
            REQUIRE_EQ(got, !has312);
            count += got;
        } while (std::next_permutation(B.begin(), B.end()));
        REQUIRE_EQ(count, catalan[n]);
    }
}

TEST("D09 evaluate：固定的例子") {
    std::string rpn;
    CHECK(near(evaluate("1+2*3", rpn), 7));
    CHECK_EQ(rpn, std::string("1 2 3 * +"));
    CHECK(near(evaluate("(1+2)*3", rpn), 9));
    CHECK_EQ(rpn, std::string("1 2 + 3 *"));
    CHECK(near(evaluate("2^3^2", rpn), 64));  // 左结合
    CHECK(near(evaluate("3!", rpn), 6));
    CHECK(near(evaluate("2*3!^2", rpn), 72));  // ! 比 ^ 优先
    CHECK(near(evaluate("2^3!", rpn), 64));
    CHECK_EQ(rpn, std::string("2 3 ! ^"));
    CHECK(near(evaluate("10/4", rpn), 2.5));
    CHECK(near(evaluate("1.5+2.25", rpn), 3.75));
    CHECK(near(evaluate(" ( 1 + 2 ) * ( 3 - 4 ) ", rpn), -3));
    CHECK(near(evaluate("0!", rpn), 1));
}

TEST("D09 evaluate：随机表达式，值和逆波兰式都要对") {
    int checked = 0;
    for (int round = 0; round < 3000; ++round) {
        std::string e = genExpr((int)randInt(1, 5));
        std::string refRpn;
        double expect = refEval(e, &refRpn);
        if (!std::isfinite(expect) || std::fabs(expect) > 1e12) continue;
        std::string rpn;
        double got = evaluate(e, rpn);
        if (!near(got, expect)) {
            REQUIRE_EQ(e, std::string("（这个表达式算错了）"));
        }
        if (!near(refRPN(rpn), expect)) {
            REQUIRE_EQ(e + " 的逆波兰式 " + rpn, "正确的是 " + refRpn);
        }
        ++checked;
    }
    CHECK(checked > 1000);
}

TEST("D09 evaluateRPN：逆波兰式求值") {
    CHECK(near(evaluateRPN("1 2 + 3 *"), 9));
    CHECK(near(evaluateRPN("2 3 2 ^ ^"), 512));
    CHECK(near(evaluateRPN("3 ! 2 /"), 3));
    for (int round = 0; round < 3000; ++round) {
        std::string e = genExpr((int)randInt(1, 5)), rpn;
        double expect = refEval(e, &rpn);
        if (!std::isfinite(expect) || std::fabs(expect) > 1e12) continue;
        if (!near(evaluateRPN(rpn), expect)) {
            REQUIRE_EQ(rpn, std::string("（这个逆波兰式算错了）"));
        }
    }
}
