# 邓俊辉老师的原版资料

本目录里的文件都是原样保留的，**不做任何修改**。版权归原作者所有。

- 作者：邓俊辉，清华大学计算机科学与技术系
- 课程主页：<https://dsa.cs.tsinghua.edu.cn/~deng/ds/dsacpp/>
- 课程主页的版权声明：“Copyleft (c) 2003-3002, Junhui Deng”
- 代码文件头的声明：“Copyright (c) 2003-2024.”
- 下载日期：2026-10-29

| 文件 | 内容 | 是否在仓库里 |
|---|---|---|
| `code/` | 示例代码，由 `dsacpp-src.vs2019.240729.7z` 解压得到（VS2019 工程） | 是 |
| `勘误.xlsx` | 教材勘误表 | 是 |
| `local-only/dsacpp-3rd-edn.pdf` | 《数据结构（C++语言版）》第 3 版教材 | 否，体积大，请从课程主页下载 |
| `local-only/DSA-2026F-10up-V.pdf` | 2026 年秋季学期讲义（每页 10 张幻灯片） | 否，同上 |
| `local-only/dsacpp-src.vs2019.240729.7z` | 示例代码压缩包 | 否，内容已解压在 `code/` |

## 在 Linux 上运行示例代码

代码包是给 Windows 上的 VS2019 准备的，在 Linux 上不能直接编译。`tools/deng.py` 会把它复制到 `build/deng/`，在副本里修正文件名大小写，并补上 MSVC 特有的函数，然后用 g++ 编译。这里的原文件不会被改动。

```bash
python3 tools/deng.py list              # 列出所有示例
python3 tools/deng.py fibonacci -- 20   # 编译并运行，-- 后面是传给程序的参数
python3 tools/deng.py --check-all       # 检查哪些示例能编译
```

目前 63 个示例里有 24 个能用 g++ 编译。剩下的依赖 MSVC 对模板宽松的检查方式，比如派生类直接使用模板基类的成员，g++ 不接受。这些示例的源码仍然可以直接阅读、对照。
