# -*- coding: utf-8 -*-
# 用瓦片家族把快照区域画成符号图：~水 o岸片 s沙LAT C崖 R坡大片 r小坡 .占位 h高度片 ?其它
import io, os, sys

base = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput"

def cls(t):
    if t == 0: return "."
    if t == 0xFFFF: return "X"
    if 29 <= t <= 48: return "r"
    if 49 <= t <= 88: return "C"
    if 89 <= t <= 130: return "o"
    if 148 <= t <= 175: return "W"
    if 314 <= t <= 327: return "~"
    if 384 <= t <= 393: return "R"
    if 493 <= t <= 509: return "s"
    if 1 <= t <= 28: return "h"
    return "?"

name = sys.argv[1]
x0, x1, y0, y1 = [int(v) for v in sys.argv[2:6]]

cells = {}
with io.open(os.path.join(base, name), "r", encoding="utf-8", errors="replace") as fp:
    for line in fp:
        p = line.split()
        if len(p) < 12: continue
        try:
            x = int(p[0]); y = int(p[1])
        except Exception:
            continue
        cells[(x, y)] = (int(p[2]), int(p[8]), int(p[9]), int(p[11]))

# 列标
hdr = "     " + "".join("%4d" % x for x in range(x0, x1 + 1))
print(hdr)
for y in range(y0, y1 + 1):
    row = []
    for x in range(x0, x1 + 1):
        v = cells.get((x, y))
        if v is None:
            row.append("   .")
        else:
            row.append("%4s" % cls(v[0]))
    print("y%-3d %s" % (y, "".join(row)))

print()
print("图例: ~水 o岸片 s沙LAT C崖 R坡大片 r小坡 h高度片 W崖水片 .占位 X空瓦 ?其它")
print("逗号分隔明细(tile/Level/LandType/Pass):")
for y in range(y0, y1 + 1):
    for x in range(x0, x1 + 1):
        v = cells.get((x, y))
        if v is None: continue
        c = cls(v[0])
        if c in ("~", ".", "X", "?"):
            print("  (%d,%d) %s t=%d L=%d LT=%d P=%d" % (x, y, c, v[0], v[1], v[2], v[3]))