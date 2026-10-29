#!/usr/bin/env bash
# 用 Release（-O2，不带 sanitizer）编译并运行计时程序，结果写到 bench/results/<名字>.csv
#   tools/bench.sh              列出所有计时程序
#   tools/bench.sh ch01_fib     运行 bench/ch01_fib.cpp
set -euo pipefail
source "$(dirname "$0")/env.sh"

if [ $# -eq 0 ]; then
    echo "可以运行的计时程序："
    for f in "$ROOT"/bench/*.cpp; do [ -f "$f" ] && echo "  $(basename "$f" .cpp)"; done
    exit 0
fi

BUILD="$ROOT/build/release"
cmake -S "$ROOT" -B "$BUILD" "${GEN[@]}" -DCMAKE_BUILD_TYPE=Release -DDSA_SANITIZE=OFF >/dev/null
cmake --build "$BUILD" -j "$JOBS" --target "bench_$1"
mkdir -p "$ROOT/bench/results"
"$BUILD/bench_$1" "${@:2}"
