# -*- coding: utf-8 -*-
# 打印快照指定区域网格: tile/Level/Slope; 并列出斜坡瓦(t29..43)与大片(384..403)
import io, os, sys

base = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput"

def load(name):
    cells = {}
    with io.open(os.path.join(base, name), "r", encoding="utf-8", errors="replace") as fp:
        for line in fp:
            p = line.split()
            if len(p) < 12:
                continue
            try:
                x = int(p[0]); y = int(p[1])
            except Exception:
                continue
            cells[(x,y)] = (int(p[2]), int(p[8]), int(p[10]))  # tile, Level, Slope
    return cells

name = sys.argv[1]
x0, x1, y0, y1 = [int(v) for v in sys.argv[2:6]]
c = load(name)

for y in range(y0, y1+1):
    parts = []
    for x in range(x0, x1+1):
        v = c.get((x,y))
        if v is None:
            parts.append("  ..  ")
            continue
        t,l,s = v
        if t == 0:
            parts.append("%2d/%d" % (l, s))
        else:
            parts.append("*%03d" % t)
    print("y=%-3d | %s" % (y, " | ".join(parts)))

print()
print("-- 斜坡相关瓦片 in region --")
for y in range(y0, y1+1):
    for x in range(x0, x1+1):
        v = c.get((x,y))
        if v and (29 <= v[0] <= 43 or 384 <= v[0] <= 403):
            print("  (%d,%d) t%d L%d s%d" % (x,y,v[0],v[1],v[2]))
