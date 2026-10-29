#!/usr/bin/env python3
"""在 Linux 上编译、运行邓老师代码包里的示例（deng/code，原文件一个都不改）。

用法：
  python3 tools/deng.py list                  列出所有示例
  python3 tools/deng.py vector                编译并运行 deng/code/src/vector
  python3 tools/deng.py vector -- 参数...      把参数传给示例程序
  python3 tools/deng.py vector --build-only   只编译
  python3 tools/deng.py --check-all           逐个编译所有示例，报告哪些能编译

代码包原本是 Windows 上 VS2019 的工程，在 Linux 上直接编译有三个问题，这里在副本里处理：
  1. Windows 文件名不分大小写，代码里 #include "Vector.h" 实际文件是 vector.h
     → 复制到 build/deng/ 后，把 #include 改成磁盘上的真实路径
  2. 用了 MSVC 才有的 __int64、_atoi64、memcpy_s 等，还依赖 MSVC 宽松的模板检查
     → 编译时加 -fpermissive 和一个兼容头文件，个别地方在副本里打补丁（见 PATCHES）
  3. 个别文件 #include <windows.h> → 提供一个只含 Sleep() 的替身
每个示例编译哪些 .cpp，按它的 .vcxproj 里列的来。程序在示例自己的目录里运行，
所以代码里的 ../../_input/... 能找到输入文件。
"""
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
ORIG = ROOT / "deng" / "code"
WORK = ROOT / "build" / "deng"
STAMP = WORK / ".synced"
# 邓老师的代码里常见 /*DSA*/#include "..." 这样带前缀的写法
INCLUDE_RE = re.compile(r'^(\s*(?:/\*DSA\*/)?\s*#\s*include\s*")([^"]+)(")', re.M)
MSVC_COMPAT_H = """#pragma once
// tools/deng.py 提供：编译时用 -include 自动加到每个文件最前面，补上 MSVC 默认就有的东西
#include <climits>
#include <cstdlib>
#include <cstring>
#include <type_traits>
#include <unistd.h>
#define __int64 long long
#define _atoi64 atoll
inline void _sleep(unsigned long ms) { usleep(ms * 1000); }
inline int memcpy_s(void* dst, size_t, const void* src, size_t n) { memcpy(dst, src, n); return 0; }
using Rank = unsigned int;  // 和代码包里的定义相同，重复声明是合法的
template <typename T> class Stack;
template <typename T> class Queue;
"""
# 只改 build/deng 里的副本：MSVC 对模板的检查比 g++ 宽松，这几处 g++ 不认
PATCHES = {
    "src/vector/vector_quickSort_iterative.h": [
        ("Stack<Rank> Task;", "Stack<typename std::enable_if<sizeof(T) != 0, Rank>::type> Task;"),
    ],
}
WINDOWS_H = """#pragma once
// tools/deng.py 提供的替身：代码包里只用到了 Sleep()
#include <unistd.h>
inline void Sleep(unsigned int ms) { usleep(ms * 1000); }
"""


def newest_mtime(d: Path) -> float:
    return max((p.stat().st_mtime for p in d.rglob("*") if p.is_file()), default=0)


def resolve_ci(base: Path, rel: str):
    """在 base 下按不分大小写的方式找 rel，找到就返回真实路径。"""
    cur = base
    for part in re.split(r"[\\/]", rel):
        if part in ("", "."):
            continue
        if part == "..":
            cur = cur.parent
            continue
        if (cur / part).exists():
            cur = cur / part
            continue
        if not cur.is_dir():
            return None
        match = next((c for c in cur.iterdir() if c.name.lower() == part.lower()), None)
        if match is None:
            return None
        cur = match
    return cur if cur.is_file() else None


def sync() -> None:
    """把 deng/code 复制到 build/deng，并修好 #include 的大小写。代码包有更新时重新复制。"""
    if STAMP.exists() and STAMP.stat().st_mtime >= newest_mtime(ORIG):
        return
    print("正在准备 build/deng（复制代码包并修正文件名大小写）……")
    if WORK.exists():
        shutil.rmtree(WORK)
    shutil.copytree(ORIG, WORK)
    src = WORK / "src"
    (WORK / "compat").mkdir()
    (WORK / "compat" / "windows.h").write_text(WINDOWS_H)
    (WORK / "compat" / "msvc_compat.h").write_text(MSVC_COMPAT_H)
    for rel, subs in PATCHES.items():
        f = WORK / rel
        text = f.read_text(encoding="utf-8", errors="surrogateescape")
        for old, new in subs:
            text = text.replace(old, new)
        f.write_text(text, encoding="utf-8", errors="surrogateescape")
    fixed = 0
    for f in list(src.rglob("*.h")) + list(src.rglob("*.cpp")):
        text = f.read_text(encoding="utf-8", errors="surrogateescape")

        def fix(m):
            nonlocal fixed
            inc = m.group(2)
            for base in (f.parent, src):
                if (base / inc).is_file():
                    return m.group(0)
            for base in (f.parent, src):
                real = resolve_ci(base, inc)
                if real is not None:
                    fixed += 1
                    return m.group(1) + os.path.relpath(real, f.parent) + m.group(3)
            return m.group(0)

        new = INCLUDE_RE.sub(fix, text)
        if new != text:
            f.write_text(new, encoding="utf-8", errors="surrogateescape")
    STAMP.touch()
    print(f"修正了 {fixed} 处 #include 的大小写或路径分隔符")


def projects():
    """所有带 .vcxproj 的示例目录：{名字: (目录, [要编译的 .cpp])}"""
    result = {}
    for proj in sorted((WORK / "src").glob("*/*.vcxproj")):
        text = proj.read_text(encoding="utf-8", errors="ignore")
        cpps = []
        for name in re.findall(r'<ClCompile\s+Include="([^"]+)"', text):
            real = resolve_ci(proj.parent, name)
            if real is not None:
                cpps.append(real)
        if cpps:
            result[proj.parent.name] = (proj.parent, cpps)
    return result


def build(name: str, d: Path, cpps, quiet=False) -> Path | None:
    out = WORK / "bin" / name
    out.parent.mkdir(exist_ok=True)
    cmd = ["g++", "-std=c++17", "-O1", "-w", "-fpermissive",
           "-include", str(WORK / "compat" / "msvc_compat.h"),
           "-I", str(WORK / "src"), "-I", str(WORK / "compat"),
           *map(str, cpps), "-o", str(out)]
    r = subprocess.run(cmd, capture_output=True, text=True)
    if r.returncode != 0:
        if not quiet:
            print(f"编译 {name} 失败：")
            print("\n".join(r.stderr.splitlines()[:30]))
        return None
    return out


def main() -> None:
    argv = sys.argv[1:]
    if not argv:
        print(__doc__)
        sys.exit(1)
    sync()
    projs = projects()

    if argv[0] == "list":
        print("可以运行的示例（python3 tools/deng.py <名字>）：")
        names = list(projs)
        for i in range(0, len(names), 6):
            print("  " + "  ".join(f"{n:<22}" for n in names[i:i + 6]))
        return
    if argv[0] == "--check-all":
        bad = [n for n, (d, c) in projs.items() if build(n, d, c, quiet=True) is None]
        ok = [n for n in projs if n not in bad]
        print(f"{len(ok)} / {len(projs)} 个示例能在 Linux 上编译：" + "、".join(ok))
        if bad:
            print("编译不过的：" + "、".join(bad))
        return

    name = argv[0]
    key = next((k for k in projs if k.lower() == name.lower()), None)
    if key is None:
        sys.exit(f"没有叫 {name} 的示例，运行 python3 tools/deng.py list 看看有哪些")
    d, cpps = projs[key]
    exe = build(key, d, cpps)
    if exe is None:
        sys.exit(1)
    print(f"已编译：{exe.relative_to(ROOT)}", flush=True)
    if "--build-only" in argv:
        return
    args = argv[argv.index("--") + 1:] if "--" in argv else []
    print(f"── 在 {d.relative_to(ROOT)} 里运行 ──", flush=True)
    sys.exit(subprocess.run([str(exe), *args], cwd=d).returncode)


if __name__ == "__main__":
    main()
