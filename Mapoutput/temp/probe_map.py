# -*- coding: utf-8 -*-
# 探测 .map 编码并打印 Waypoints 段
import io, sys
p = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261002_155735.map"
raw = open(p, "rb").read()
print("前 8 字节:", raw[:8].hex())
enc = None
if raw[:2] in (b"\xff\xfe", b"\xfe\xff"):
    enc = "utf-16"
elif raw[:3] == b"\xef\xbb\xbf":
    enc = "utf-8-sig"
else:
    enc = "latin-1"
print("判定编码:", enc, " 文件长度:", len(raw))
txt = raw.decode(enc, errors="replace")
lines = txt.splitlines()
print("行数:", len(lines))
for i, ln in enumerate(lines):
    if ln.strip().lower() == "[waypoints]":
        for j in range(i, min(i+20, len(lines))):
            print(repr(lines[j]))
        break
else:
    print("没找到 [Waypoints]，打印前 5 行:")
    for ln in lines[:5]:
        print(repr(ln[:100]))