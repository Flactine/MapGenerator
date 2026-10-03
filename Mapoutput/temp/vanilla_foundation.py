# -*- coding: utf-8 -*-
# 对比原版单人图 all01umd.map 建筑脚下的瓦片是否为真实地砖（非t0占位）
import base64, re, struct, sys
sys.path.insert(0, r"d:\新建文件夹\VSProject\MapGenerator\temp")
import analyze_isopack5 as A

p = r"D:\Ra2\all01umd.map"
raw = open(p, "rb").read()

def section_b64(name):
    m = re.search(("\\[%s\\]" % name).encode(), raw)
    s = m.end()
    e = raw.find(b"[", s)
    body = b""
    for ln in raw[s:e].splitlines():
        i = ln.find(b"=")
        if i >= 0: body += ln[i+1:]
    return base64.b64decode(body)

blob = section_b64("IsoMap5") if b"[IsoMap5]" in raw else section_b64("IsoMapPack5")
data = b""
pos = 0
while pos + 4 <= len(blob):
    si, so = struct.unpack("<HH", blob[pos:pos+4])
    data += A.lzo1x_decompress(bytes(blob[pos+4:pos+4+si]), so)
    pos += 4 + si

print("decoded bytes:", len(data), "expected:", 161*161*11)
def rec(x, y):
    stride = 161
    o = (x + y * stride) * 11
    r = data[o:o+11]
    if len(r) < 11: return ("MISS", -1, -1)
    return r[4] | (r[5] << 8), r[8], r[9]

# 0=YAPOWR 2x2 Y=27 X=78 ; 5=GACSPH ? Y=35 X=64
for name, X, Y, w, h in [("YAPOWR", 78, 27, 2, 2), ("NATBNK", 77, 34, 2, 2)]:
    print("==", name, X, Y)
    for yy in range(Y, Y+h):
        row = ""
        for xx in range(X, X+w):
            t, lv, hh = rec(xx, yy)
            row += "%5d/L%02d " % (t, lv)
        print(row)
