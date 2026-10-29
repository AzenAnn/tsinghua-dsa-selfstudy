#!/usr/bin/env bash
# 一键安装本项目需要的环境：克隆下来以后运行一次就行。
#
#   tools/install_deps.sh          必需的：g++（C++17）、make、cmake、ninja、python3、git
#   tools/install_deps.sh --plot   另外装 matplotlib（tools/plot.py 画复杂度曲线用，可选）
#
# 支持 Ubuntu / Debian（apt，会用 sudo，要输入开机密码）和 macOS（Homebrew）。
# 其他系统请照上面的清单用自己的包管理器装：cmake 需要 3.16 以上，编译器要支持 C++17。
set -euo pipefail

plot=0
if [ "${1:-}" = "--plot" ]; then plot=1; fi

if command -v apt-get >/dev/null; then
    pkgs=(build-essential cmake ninja-build python3 git)
    if [ $plot = 1 ]; then pkgs+=(python3-matplotlib); fi
    sudo apt-get update
    sudo apt-get install -y "${pkgs[@]}"
elif command -v brew >/dev/null; then
    xcode-select -p >/dev/null 2>&1 || xcode-select --install  # 提供 clang 和 make
    brew install cmake ninja python git coreutils               # coreutils 提供 realpath --relative-to
    if [ $plot = 1 ]; then echo "macOS 上请自行用 pip 安装 matplotlib"; fi
else
    echo "没有识别出 apt 或 Homebrew。请手动安装：C++17 编译器、make、cmake ≥ 3.16、ninja、python3、git"
    exit 1
fi

echo
echo "检查安装结果："
for c in g++ make cmake ninja python3 git; do
    if command -v "$c" >/dev/null; then
        printf "  %-8s %s\n" "$c" "$("$c" --version 2>&1 | head -1)"
    else
        printf "  %-8s 没有找到\n" "$c"
    fi
done
if [ $plot = 1 ]; then
    python3 -c "import matplotlib; print('  matplotlib', matplotlib.__version__)" 2>/dev/null ||
        echo "  matplotlib 没有找到"
fi
