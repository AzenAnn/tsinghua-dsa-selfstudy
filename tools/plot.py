#!/usr/bin/env python3
"""把 bench/results/<名字>.csv 画成曲线，存为同名 .png。

用法：
  python3 tools/plot.py ch01_fib          线性坐标
  python3 tools/plot.py ch01_fib --log    纵轴取对数（看指数增长时用）

需要 matplotlib：运行 tools/install_deps.sh --plot 安装。
"""
import csv
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent


def main() -> None:
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    if not args:
        print(__doc__)
        sys.exit(1)
    try:
        import matplotlib
        matplotlib.use("Agg")
        import matplotlib.pyplot as plt
    except ImportError:
        sys.exit("没有 matplotlib：先运行 tools/install_deps.sh --plot")

    path = ROOT / "bench" / "results" / f"{args[0]}.csv"
    with open(path, newline="") as f:
        rows = list(csv.reader(f))
    header, data = rows[0], rows[1:]
    xs = [float(r[0]) for r in data]
    fig, ax = plt.subplots(figsize=(7, 4.5))
    for col in range(1, len(header)):
        pts = [(x, float(r[col])) for x, r in zip(xs, data) if col < len(r) and r[col]]
        if pts:
            ax.plot(*zip(*pts), marker="o", label=header[col])
    if "--log" in sys.argv:
        ax.set_yscale("log")
    ax.set_xlabel(header[0])
    ax.set_ylabel("time")
    ax.grid(alpha=0.3)
    ax.legend()
    out = path.with_suffix(".png")
    fig.tight_layout()
    fig.savefig(out, dpi=150)
    print(f"已保存 {out}")


if __name__ == "__main__":
    main()
