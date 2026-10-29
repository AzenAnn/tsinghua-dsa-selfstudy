#!/usr/bin/env bash
# 对拍：用随机数据比较你的解法和暴力解法，找到第一组输出不同的数据就停下。
#   tools/duipai.sh problems/ch02/luogu-P1908-逆序对 [次数，默认 1000]
# 题目目录里需要：
#   sol.cpp    要检查的解法
#   brute.cpp  暴力解法（慢但保证对）
#   gen.py     生成一组随机输入打印到标准输出；第一个参数是种子，用 random.seed(int(sys.argv[1]))
# 找到反例时，输入存为目录里的 wrong.in，方便单独调试。
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"

[ $# -ge 1 ] || { sed -n '2,9p' "$0"; exit 1; }
dir="${1%/}"
times="${2:-1000}"
for f in sol.cpp brute.cpp gen.py; do
    [ -f "$dir/$f" ] || { echo "$dir 里缺少 $f"; exit 1; }
done

work="$ROOT/build/duipai/$(basename "$dir")"
mkdir -p "$work"
g++ -std=c++17 -O2 -I "$ROOT/include" "$dir/sol.cpp" "$ROOT"/src/*.cpp -o "$work/sol"
g++ -std=c++17 -O2 -I "$ROOT/include" "$dir/brute.cpp" "$ROOT"/src/*.cpp -o "$work/brute"

for ((i = 1; i <= times; i++)); do
    python3 "$dir/gen.py" "$i" > "$work/in"
    "$work/sol" < "$work/in" > "$work/sol.out"
    "$work/brute" < "$work/in" > "$work/brute.out"
    if ! diff -wB "$work/sol.out" "$work/brute.out" >/dev/null; then
        cp "$work/in" "$dir/wrong.in"
        echo "第 $i 组（种子 $i）输出不同，输入已存为 $dir/wrong.in"
        echo "── 输入"; head -20 "$work/in"
        echo "── 左边是 sol，右边是 brute"
        diff -wB --side-by-side --width=100 "$work/sol.out" "$work/brute.out" | head -20 || true
        exit 1
    fi
    if ((i % 100 == 0)); then echo "已通过 $i 组"; fi
done
echo "$times 组随机数据全部一致"
