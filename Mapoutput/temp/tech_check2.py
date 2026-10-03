# -*- coding: utf-8 -*-
# 检查科技建筑地基+外圈3格的 tile/Level/SlopeIndex/Passability
import sys

path = sys.argv[1] if len(sys.argv) > 1 else \
    r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261003_125504.isopack5.txt"

cells = {}
for line in open(path, encoding="utf-8", errors="replace"):
    if line.startswith(";"):
        continue
    p = line.split()
    if len(p) < 12:
        continue
    cells[(int(p[0]), int(p[1]))] = {
        "tile": int(p[2]), "H": int(p[7]), "L": int(p[8]),
        "slope": int(p[10]), "pass": int(p[11]),
    }

blds = [
    ("CAAIRP", 169, 206, 3, 3),
    ("CAMACH", 117, 69, 3, 3),
    ("CAPOWR", 164, 151, 2, 2),
    ("CAPOWR", 76, 145, 2, 2),
]

for name, x0, y0, w, h in blds:
    print("=" * 78)
    print("%s %dx%d anchor=(%d,%d)" % (name, w, h, x0, y0))
    R = 3
    for y in range(y0 - R, y0 + h + R):
        row = "y%-3d " % y
        for x in range(x0 - R, x0 + w + R):
            c = cells.get((x, y))
            inside = x0 <= x < x0 + w and y0 <= y < y0 + h
            tag = "[" if inside else " "
            if c is None:
                row += tag + " MISS] " if inside else "   .    "
                continue
            mark = tag
            row += "%s%4d/L%02d/s%02d/p%d " % (
                mark, c["tile"], c["L"], c["slope"], c["pass"])
        print(row)

    # 地基内统计
    bad = []
    for y in range(y0, y0 + h):
        for x in range(x0, x0 + w):
            c = cells.get((x, y))
            if c is None:
                bad.append((x, y, "MISSING"))
            elif c["slope"] != 0 or c["tile"] not in (0, 0xFFFF):
                bad.append((x, y, c))
    print("FOUNDATION non-flat/non-placeholder cells:", len(bad))
    for b in bad:
        print("   ", b)
