# -*- coding: utf-8 -*-
# 量山地图里"跨高度斜坡"处的格数据形态：
#  - 找 CliffRamps 瓦片(384..393) 与丘陵小坡瓦(510..521)
#  - 打印这些格自身及四邻的 tile/Level/SlopeIndex，看 Level 字节如何过渡
import sys

path = sys.argv[1] if len(sys.argv) > 1 else \
    r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261003_121340.isopack5.txt"

cells = {}
for line in open(path, encoding="utf-8", errors="replace"):
    if line.startswith(";"):
        continue
    p = line.split()
    if len(p) < 11:
        continue
    x, y = int(p[0]), int(p[1])
    cells[(x, y)] = {
        "tile": int(p[2]), "H": int(p[7]), "L": int(p[8]),
        "land": int(p[9]), "slope": int(p[10]), "pass": int(p[11]),
    }

def is_cliff_ramp(t):
    return 384 <= t <= 393
def is_hill_ramp(t):
    return 510 <= t <= 521

cr = [(x, y) for (x, y), c in cells.items() if is_cliff_ramp(c["tile"])]
hr = [(x, y) for (x, y), c in cells.items() if is_hill_ramp(c["tile"])]
print("cliff ramp cells(384-393):", len(cr), " hill ramp cells(510-521):", len(hr))

def show(points, title, n):
    print("==== %s ====" % title)
    for (x, y) in points[:n]:
        print("-- ramp at (%d,%d) tile=%d L=%d slope=%d pass=%d" %
              (x, y, cells[(x,y)]["tile"], cells[(x,y)]["L"],
               cells[(x,y)]["slope"], cells[(x,y)]["pass"]))
        for dy in (-1, 0, 1):
            row = ""
            for dx in (-1, 0, 1):
                c = cells.get((x+dx, y+dy))
                if c is None:
                    row += "   ....    "
                else:
                    row += ("%4d/L%02d/s%02d/p%d " %
                            (c["tile"], c["L"], c["slope"], c["pass"]))
            print("   " + row)

show(cr, "CLIFF RAMPS", 8)

# 统计：cliff ramp 格与四邻的 Level 差分布
diffs = {}
for (x, y) in cr:
    L0 = cells[(x,y)]["L"]
    for dx, dy in ((0,-1),(1,0),(0,1),(-1,0)):
        c = cells.get((x+dx, y+dy))
        if c:
            d = c["L"] - L0
            diffs[d] = diffs.get(d, 0) + 1
print("cliff ramp neighbor level-diff histogram:", dict(sorted(diffs.items())))

# 丘陵小坡：邻格 Level 差
diffs2 = {}
for (x, y) in hr:
    L0 = cells[(x,y)]["L"]
    for dx, dy in ((0,-1),(1,0),(0,1),(-1,0)):
        c = cells.get((x+dx, y+dy))
        if c:
            d = c["L"] - L0
            diffs2[d] = diffs2.get(d, 0) + 1
print("hill ramp neighbor level-diff histogram:", dict(sorted(diffs2.items())))
