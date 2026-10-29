#!/usr/bin/env python3
"""按模板新建一道题或一道课后习题。

用法：
  python3 tools/new.py problem ch02 luogu-P1908 逆序对
      → problems/ch02/luogu-P1908-逆序对/{sol.cpp, README.md}
  python3 tools/new.py exercise ch02 2-12
      → exercises/ch02/2-12.md，并在 exercises/ch02/README.md 的表格里加一行
  python3 tools/new.py exercise ch02 2-12 --code
      → 同上，另外建 exercises/ch02/2-12.cpp
"""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

SOL = """\
// {source} {title}
// 思路：
// 复杂度：
#include <bits/stdc++.h>
using namespace std;

int main() {{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}}
"""

PROBLEM_README = """\
# {source} {title}

- 来源：{source}
- 章节：{chapter}
- 状态：未完成

## 题意（自己概括）

## 思路

## 复杂度

## 用到的结构或算法

## 踩过的坑
"""

EXERCISE_MD = """\
# 习题 [{num}]

## 题目要点（自己概括）

## 解答

## 反思
"""

EXERCISE_CPP = """\
// 习题 [{num}]
#include <bits/stdc++.h>
using namespace std;

int main() {{
    return 0;
}}
"""


def write(path: Path, text: str) -> None:
    if path.exists():
        print(f"已存在，没有覆盖：{path.relative_to(ROOT)}")
        return
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8")
    print(f"新建 {path.relative_to(ROOT)}")


def main() -> None:
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    if len(args) < 3 or args[0] not in ("problem", "exercise"):
        print(__doc__)
        sys.exit(1)
    kind, chapter = args[0], args[1]
    if not (chapter.startswith("ch") and chapter[2:].isdigit() and len(chapter) == 4):
        sys.exit("章节写成 ch01 到 ch12 这样的格式")

    if kind == "problem":
        if len(args) < 4:
            sys.exit("用法：python3 tools/new.py problem ch02 luogu-P1908 逆序对")
        source, title = args[2], " ".join(args[3:])
        d = ROOT / "problems" / chapter / f"{source}-{title}"
        write(d / "sol.cpp", SOL.format(source=source, title=title))
        write(d / "README.md", PROBLEM_README.format(source=source, title=title, chapter=chapter))
        print(f"把样例存成 1.in / 1.out，然后运行 tools/run.sh {d.relative_to(ROOT)}")
    else:
        num = args[2]
        d = ROOT / "exercises" / chapter
        write(d / f"{num}.md", EXERCISE_MD.format(num=num))
        if "--code" in sys.argv:
            write(d / f"{num}.cpp", EXERCISE_CPP.format(num=num))
        index = d / "README.md"
        if index.exists() and f"[{num}]" not in index.read_text(encoding="utf-8"):
            with open(index, "a", encoding="utf-8") as f:
                f.write(f"| [{num}]({num}.md) | 未完成 | |\n")


if __name__ == "__main__":
    main()
