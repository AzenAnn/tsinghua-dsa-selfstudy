#!/usr/bin/env python3
"""统计学习进度，写进 README.md 的进度区（<!-- progress:start --> 和 <!-- progress:end --> 之间）。

数据来源：
  PLAN.md 里每天的复选框：一天的框全打勾才算这一天完成
  problems/ 下有 sol.cpp 的题目目录数
  exercises/ 下的习题文件数

用法：python3 tools/progress.py          更新 README.md
      python3 tools/progress.py --print  只打印，不改文件
"""
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
START, END = "<!-- progress:start -->", "<!-- progress:end -->"


def parse_plan():
    days = []  # [(标题, 已勾数, 总数)]
    for line in (ROOT / "PLAN.md").read_text(encoding="utf-8").splitlines():
        if line.startswith("### D"):
            days.append([line[4:].strip(), 0, 0])
        elif days and re.match(r"\s*- \[[ xX]\]", line):
            days[-1][2] += 1
            if re.match(r"\s*- \[[xX]\]", line):
                days[-1][1] += 1
    return days


def main() -> None:
    days = parse_plan()
    done_days = sum(1 for _, d, t in days if t and d == t)
    done_tasks = sum(d for _, d, _ in days)
    all_tasks = sum(t for _, _, t in days)
    current = next((title for title, d, t in days if d < t), "全部完成 🎉")
    bar = "".join("■" if t and d == t else ("◧" if d else "□") for _, d, t in days)
    problems = sum(1 for p in (ROOT / "problems").rglob("sol.cpp"))
    exercises = sum(1 for p in (ROOT / "exercises").rglob("*.md") if p.name != "README.md")

    block = "\n".join([
        START,
        f"`{bar}`",
        "",
        "| 项目 | 进度 |",
        "|---|---|",
        f"| 天数 | {done_days} / {len(days)} |",
        f"| 计划里的任务 | {done_tasks} / {all_tasks} |",
        f"| 下一步 | {current} |",
        f"| OJ 题（problems/） | {problems} 道 |",
        f"| 课后习题（exercises/） | {exercises} 道 |",
        "",
        "■ 完成　◧ 做了一部分　□ 还没开始。这一块由 `python3 tools/progress.py` 生成，不要手改。",
        END,
    ])
    if "--print" in sys.argv:
        print(block)
        return
    readme = ROOT / "README.md"
    text = readme.read_text(encoding="utf-8")
    if START not in text or END not in text:
        sys.exit("README.md 里找不到进度区的标记")
    pre, rest = text.split(START, 1)
    _, post = rest.split(END, 1)
    readme.write_text(pre + block + post, encoding="utf-8")
    print(f"已更新 README.md：{done_days}/{len(days)} 天，{done_tasks}/{all_tasks} 项任务")


if __name__ == "__main__":
    main()
