# -*- coding: utf-8 -*-
# 实证 IsoMapPack5 记录坐标顺序：取真实原版 yrm 的建筑，两种解释对比地基
import base64, re, struct, sys
sys.path.insert(0, r"d:\新建文件夹\VSProject\MapGenerator\temp")
import analyze_isopack5 as A

p = r"D:\Ra2\sov01umd.map"
raw = open(p, "rb").read()

def section_b64(name):
    m = re.search(("\\[%s\\]" % name).encode(), raw)
    s = m.end(); e = raw.find(b"[", s)
    body = b""
    for ln in raw[s:e].splitlines():
        i = ln.find(b"=")
        if i >= 0: body += ln[i+1:]
    return base64.b64decode(body)

# [Map] Size
ms = re.search(rb"\[Map\][^\[]*?Size=(\d+),(\d+),(\d+),(\d+)", raw)
w0,h0,mw,mh = [int(v) for v in ms.groups()]
iso = mw + mh + 1
print("map width=%d height=%d iso=%d" % (mw, mh, iso))

blob = section_b64("IsoMapPack5")
data = b""
pos = 0
while pos + 4 <= len(blob):
    si, so = struct.unpack("<HH", blob[pos:pos+4])
    data += A.lzo1x_decompress(bytes(blob[pos+4:pos+4+si]), so)
    pos += 4 + si
print("decoded", len(data), "expected", iso*iso*11)

recs = {}
for i in range(0, len(data) - 10, 11):
    a, b = struct.unpack("<HH", data[i:i+4])
    tile = data[i+4] | (data[i+5] << 8)
    recs[(a, b)] = (tile, data[i+8], data[i+9])  # tile,byte8,byte9

# structures
m = re.search(rb"\[Structures\]", raw)
s = m.end(); e = raw.find(b"[", s)
strs = []
for ln in raw[s:e].splitlines():
    pp = ln.split(b"=", 1)
    if len(pp) != 2: continue
    f = pp[1].split(b",")
    if len(f) < 5: continue
    strs.append((f[0].decode(), f[1].decode(), int(f[3]), int(f[4])))
print("structures:", len(strs))
for house, typ, p3, p4 in strs[:6]:
    # 解释A: X=p4,Y=p3 (当前我方写法) ; 解释B: X=p3,Y=p4
    for tag, X, Y in [("A X=p4,Y=p3", p4, p3), ("B X=p3,Y=p4", p3, p4)]:
        hits = [recs.get((X+dx, Y+dy)) for dy in (0,1) for dx in (0,1)]
        print("  %s %s (%d,%d) -> %s" % (typ, tag, X, Y, hits))
