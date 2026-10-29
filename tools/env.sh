# 由其他脚本 source：设好 ROOT，检查 cmake，选构建工具（有 ninja 用 ninja，没有用 make）
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
if ! command -v cmake >/dev/null; then
    echo "找不到 cmake。先运行 tools/install_deps.sh 安装项目需要的环境。" >&2
    exit 1
fi
GEN=()
if command -v ninja >/dev/null; then GEN=(-G Ninja); fi
JOBS="$(nproc 2>/dev/null || echo 4)"
