#!/usr/bin/env bash
# 编译并运行一道题（-O2，带 AddressSanitizer 和 UBSan；可以 #include "dsa/..." 用 learn/include 里自己写的结构）
#   tools/run.sh learn/problems/D01-D08/D05/luogu-P1908-逆序对        目录里的 sol.cpp
#   tools/run.sh learn/problems/D01-D08/D05/luogu-P1908-逆序对/x.cpp  指定文件
# 目录里有 1.in / 1.out 这样成对的样例就逐个比对（忽略行尾空白），没有就从键盘读输入。
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"

[ $# -ge 1 ] || { sed -n '2,6p' "$0"; exit 1; }
if [ -d "$1" ]; then dir="$1"; src="$1/sol.cpp"; else src="$1"; dir="$(dirname "$1")"; fi
[ -f "$src" ] || { echo "找不到 $src"; exit 1; }

rel="$(realpath --relative-to="$ROOT" "$src")"
bin="$ROOT/build/run/${rel//\//__}"
bin="${bin%.cpp}"
mkdir -p "$ROOT/build/run"
# 带上 src/*.cpp，题解里就能用 learn/include/dsa/ 中声明的函数；还没写完的函数不报“参数未使用”的警告
g++ -std=c++17 -O2 -Wall -Wextra -Wno-unused-parameter -fsanitize=address,undefined -I "$ROOT/learn/include" "$src" "$ROOT"/src/*.cpp -o "$bin"

shopt -s nullglob
samples=("$dir"/*.in)
if [ ${#samples[@]} -eq 0 ]; then
    echo "（目录里没有 .in 样例，从键盘输入，Ctrl-D 结束）"
    exec "$bin"
fi
pass=0 fail=0
for in in "${samples[@]}"; do
    expect="${in%.in}.out"
    name="$(basename "$in")"
    got="$("$bin" < "$in")"
    if [ ! -f "$expect" ]; then
        echo "── $name 的输出（没有 ${name%.in}.out 可比对）："
        echo "$got"
    elif diff -wB <(echo "$got") "$expect" >/dev/null; then
        echo "通过  $name"
        pass=$((pass + 1))
    else
        echo "不对  $name（左边是你的输出，右边是答案）"
        diff -wB --side-by-side --width=100 <(echo "$got") "$expect" | head -30 || true
        fail=$((fail + 1))
    fi
done
echo "样例：通过 $pass，不对 $fail"
[ $fail -eq 0 ]
