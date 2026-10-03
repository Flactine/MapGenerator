# -*- coding: utf-8 -*-
# 注释掉所有 SaveStageSnapshot(...) 调用语句，保留定义/声明；保留原 BOM。
import re, io
files = [
    r"d:\新建文件夹\VSProject\MapGenerator\MapGenerator\WinMain.cpp",
    r"d:\新建文件夹\VSProject\MapGenerator\MapGenerator\MapGenRiver.cpp",
    r"d:\新建文件夹\VSProject\MapGenerator\MapGenerator\MapGenMaking.cpp",
    r"d:\新建文件夹\VSProject\MapGenerator\MapGenerator\MapGenMakingSub.cpp",
    r"d:\新建文件夹\VSProject\MapGenerator\MapGenerator\MapGen.cpp",
]
# 调用行：去空白后以 SaveStageSnapshot( 或 rmg.SaveStageSnapshot( 开头，
# 且不是函数定义（不含 "void "）。
pat = re.compile(r'^(\s*)((?:rmg\.)?SaveStageSnapshot\s*\()')
total = 0
for p in files:
    raw = open(p, "rb").read()
    bom = raw[:3] == b"\xef\xbb\xbf"
    text = raw.decode("utf-8-sig")
    lines = text.split("\n")
    n = 0
    for i, ln in enumerate(lines):
        if "void " in ln:          # 函数定义，跳过
            continue
        m = pat.match(ln)
        if m:
            lines[i] = m.group(1) + "// [SNAPSHOT-OFF] " + ln[m.end(1):]
            n += 1
    out = ("\n".join(lines)).encode("utf-8")
    if bom:
        out = b"\xef\xbb\xbf" + out
    open(p, "wb").write(out)
    total += n
    print("%-20s 注释 %d 处" % (p.split("\\")[-1], n))
print("合计", total)