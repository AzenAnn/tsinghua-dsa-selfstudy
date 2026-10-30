#!/usr/bin/env python3
"""统计学习进度，写进 README.md 的进度区（<!-- progress:start --> 和 <!-- progress:end --> 之间），
同时更新标题下面的进度徽章（<!-- badge:start --> 和 <!-- badge:end --> 之间，和其他徽章写在同一行，不能换行）。

数据来源：
  learn/days/分组/DNN/README.md 末尾“完成清单”里的复选框：一天的框全打勾才算这一天完成
  learn/problems/README.md 里打了勾的题数
  learn/exercises/ 下“我的解答”写了内容的习题数

用法：python3 tools/progress.py          更新 README.md
      python3 tools/progress.py --print  只打印，不改文件
"""
import re
import sys
from urllib.parse import quote
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
START, END = "<!-- progress:start -->", "<!-- progress:end -->"
BADGE_START, BADGE_END = "<!-- badge:start -->", "<!-- badge:end -->"


def parse_plan():
    days = []  # [(标题, 已勾数, 总数)]
    for f in sorted((ROOT / "learn" / "days").glob("D*-D*/D[0-9][0-9]/README.md")):
        lines = f.read_text(encoding="utf-8").splitlines()
        title = lines[0].lstrip("# ").strip() if lines else f.parent.name
        done = total = 0
        for line in lines:
            if re.match(r"\s*- \[[ xX]\]", line):
                total += 1
                done += bool(re.match(r"\s*- \[[xX]\]", line))
        days.append([title, done, total])
    return days


def replace_between(text: str, start: str, end: str, block: str) -> str:
    """把 text 里从 start 到 end（含两端标记）的部分换成 block。"""
    pre, rest = text.split(start, 1)
    _, post = rest.split(end, 1)
    return pre + block + post


def main() -> None:
    days = parse_plan()
    done_days = sum(1 for _, d, t in days if t and d == t)
    done_tasks = sum(d for _, d, _ in days)
    all_tasks = sum(t for _, _, t in days)
    current = next((title for title, d, t in days if d < t), "全部完成 🎉")
    bar = "".join("■" if t and d == t else ("◧" if d else "□") for _, d, t in days)
    oj = (ROOT / "learn" / "problems" / "README.md").read_text(encoding="utf-8")
    oj_done, oj_total = len(re.findall(r"^- \[[xX]\]", oj, re.M)), len(re.findall(r"^- \[[ xX]\]", oj, re.M))
    ex_total = ex_done = 0
    for p in (ROOT / "learn" / "exercises").glob("ch*/*.md"):
        if p.name == "README.md":
            continue
        ex_total += 1
        text = p.read_text(encoding="utf-8")
        mine = text.split("## 我的解答", 1)[-1].split("## 对照官方解答后的反思", 1)[0]
        mine = "\n".join(l for l in mine.splitlines() if not l.startswith("代码写在同目录"))
        ex_done += bool(mine.strip())

    block = "\n".join([
        START,
        f"`{bar}`",
        "",
        "| 项目 | 进度 |",
        "|---|---|",
        f"| 天数 | {done_days} / {len(days)} |",
        f"| 计划里的任务 | {done_tasks} / {all_tasks} |",
        f"| 下一步 | {current} |",
        f"| OJ 题（learn/problems/README.md） | {oj_done} / {oj_total} 道 |",
        f"| 课后习题（learn/exercises/） | {ex_done} / {ex_total} 道 |",
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
    text = replace_between(text, START, END, block)
    if BADGE_START in text and BADGE_END in text:
        color = "lightgrey" if done_tasks == 0 else ("brightgreen" if done_days == len(days) else "blue")
        url = f"https://img.shields.io/badge/{quote('进度')}-{quote(f'{done_days}/{len(days)} 天', safe='')}-{color}"
        text = replace_between(text, BADGE_START, BADGE_END, f"{BADGE_START}![进度]({url}){BADGE_END}")
    readme.write_text(text, encoding="utf-8")
    print(f"已更新 README.md：{done_days}/{len(days)} 天，{done_tasks}/{all_tasks} 项任务")


if __name__ == "__main__":
    main()
