#!/usr/bin/env bash
# 编译并运行测试（Debug，带 AddressSanitizer 和 UBSan）
#   tools/test.sh                     全部测试
#   tools/test.sh ch02                只跑文件名里带 ch02 的测试
#   tools/test.sh ch02 二分           只跑 ch02 里名字含“二分”的用例
#   DSA_STRICT=1 tools/test.sh ch02   “待实现”也算失败，用来确认一章已经全部完成
#   DSA_SEED=123 tools/test.sh ch02   用固定的随机种子，复现某一次失败
set -euo pipefail
source "$(dirname "$0")/env.sh"

BUILD="$ROOT/build/debug"
cmake -S "$ROOT" -B "$BUILD" "${GEN[@]}" -DCMAKE_BUILD_TYPE=Debug -DDSA_SANITIZE=ON >/dev/null
cmake --build "$BUILD" -j "$JOBS"

file_filter="${1:-}"
case_filter=("${@:2}")
status=0
found=0
for t in "$BUILD"/test_*; do
    [ -f "$t" ] && [ -x "$t" ] || continue
    name="$(basename "$t")"
    [[ -z "$file_filter" || "$name" == *"$file_filter"* ]] || continue
    found=1
    echo
    echo "━━━━ $name"
    "$t" "${case_filter[@]}" || status=1
done
[ "$found" = 1 ] || { echo "没有找到名字里带“$file_filter”的测试"; exit 1; }
exit $status
