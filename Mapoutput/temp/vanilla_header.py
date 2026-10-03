# -*- coding: utf-8 -*-
# 全量解码原版 sov01umd.map，钉死 IsoMapPack5 记录头 (word0,word2) 与
# Structures 行 field3/field4 的对应关系。
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

ms = re.search(rb"\[Map\][^\[]*?Size=(\d+),(\d+),(\d+),(\d+)", raw)
mw, mh = int(ms.group(3)), int(ms.group(4))
iso = mw + mh + 1

blob = section_b64("IsoMapPack5")
data = b""
pos = 0
while pos + 4 <= len(blob):
    si, so = struct.unpack("<HH", blob[pos:pos+4])
    data += A.lzo1x_decompress(bytes(blob[pos+4:pos+4+si]), so)
    pos += 4 + si
print("iso=%d decoded=%d expectedFull=%d" % (iso, len(data), iso*iso*11))

def rec(w0, w2):
    o = (w0 + w2*iso) * 11
    r = data[o:o+11]
    if len(r) < 11: return None
    return (r[0], r[1], r[2], r[3], r[4] | (r[5] << 8), r[8], r[9])

m = re.search(rb"\[Structures\]", raw); s = m.end(); e = raw.find(b"[", s)
n = 0
for ln in raw[s:e].splitlines():
    pp = ln.split(b"=", 1)
    if len(pp) != 2: continue
    f = pp[1].split(b",")
    if len(f) < 5: continue
    typ = f[1].decode(); f3, f4 = int(f[3]), int(f[4])
    h1 = rec(f4, f3)    # (word0=field4, word2=field3)
    h2 = rec(f3, f4)    # (word0=field3, word2=field4)
    print("%-8s f3(y?)=%3d f4(x?)=%3d | hdr(w0=f4,w2=f3)=%s | hdr(w0=f3,w2=f4)=%s"
          % (typ, f3, f4, h1, h2))
    n += 1
    if n >= 8: break
