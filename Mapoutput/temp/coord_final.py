# -*- coding: utf-8 -*-
# 定论：工程 yrm 中，建筑 Structures 行 (field3,field4) 与 IsoMapPack5
# 记录头两个 word 的对应；以及两种解释下建筑脚下瓦片是否平坦。
import base64, re, struct, sys
sys.path.insert(0, r"d:\新建文件夹\VSProject\MapGenerator\temp")
import analyze_isopack5 as A

p = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261003_132414.yrm"
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
seg = 0
while pos + 4 <= len(blob):
    si, so = struct.unpack("<HH", blob[pos:pos+4])
    chunk = A.lzo1x_decompress(bytes(blob[pos+4:pos+4+si]), so)
    print("seg%d si=%d so=%d got=%d" % (seg, si, so, len(chunk)))
    data += chunk
    pos += 4 + si
    seg += 1
print("iso=%d decoded=%d expected=%d segments=%d blob=%d"
      % (iso, len(data), iso*iso*11, seg, len(blob)))

def rec(w0, w2):
    o = (w0 + w2*iso) * 11
    r = data[o:o+11]
    if len(r) < 11: return None
    return (r[4] | (r[5] << 8), r[8], r[9])

# Structures
m = re.search(rb"\[Structures\]", raw); s = m.end(); e = raw.find(b"[", s)
strs = []
for ln in raw[s:e].splitlines():
    pp = ln.split(b"=", 1)
    if len(pp) != 2: continue
    f = pp[1].split(b",")
    if len(f) < 5: continue
    strs.append((f[1].decode(), int(f[3]), int(f[4])))   # type, field3, field4

for typ, f3, f4 in strs:
    # 解释1: field4=x(fielddata列), field3=y → 记录头(word0,word2)=(x,y)
    a = rec(f4, f3)
    # 解释2: 记录头=(y,x)
    b = rec(f3, f4)
    print("%s field3=%d field4=%d  rec(word0=f4,word2=f3)=%s  rec(word0=f3,word2=f4)=%s"
          % (typ, f3, f4, a, b))
