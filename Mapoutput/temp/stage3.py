# -*- coding: utf-8 -*-
# 三阶段并排对比 lakeStartA / SelectShoreTile / SelectShoreTile2
import io, os
base = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput"
stages = ["20261002_165759_lakeStartA.isopack5.txt",
          "20261002_165759_SelectShoreTile.isopack5.txt",
          "20261002_165759_SelectShoreTile2.isopack5.txt"]
x0, x1, y0, y1 = 45, 53, 45, 54

def load(name):
    d = {}
    with io.open(os.path.join(base, name), "r", encoding="utf-8", errors="replace") as fp:
        for line in fp:
            p = line.split()
            if len(p) < 12: continue
            try: x = int(p[0]); y = int(p[1])
            except Exception: continue
            d[(x,y)] = (int(p[2]), int(p[8]), int(p[9]), int(p[11]))
    return d

D = [load(s) for s in stages]

def sym(t):
    if t == 0: return "  .0"
    if t == 0xFFFF: return " FFF"
    if 314 <= t <= 327: return "~%3d" % t
    if 89 <= t <= 130: return "o%3d" % t
    if 493 <= t <= 509: return "s%3d" % t
    if 49 <= t <= 88: return "C%3d" % t
    return "%4d" % t

for y in range(y0, y1+1):
    print("y=%d" % y)
    for si, name in enumerate(("铺前", "第一遍后", "第二遍后")):
        row = "  ".join(sym(D[si].get((x,y), (-1,0,0,0))[0]) for x in range(x0, x1+1))
        print("   %-6s %s" % (name, row))
    print()

# 只列出三阶段 tile 发生变化的格
print("=== 三阶段 tile 有变化的格 ===")
for y in range(y0, y1+1):
    for x in range(x0, x1+1):
        ts = [D[i].get((x,y),(0,))[0] for i in range(3)]
        if ts[0] != ts[1] or ts[1] != ts[2]:
            print("   (%d,%d): 铺前 %d -> 一遍 %d -> 二遍 %d" % (x,y,ts[0],ts[1],ts[2]))