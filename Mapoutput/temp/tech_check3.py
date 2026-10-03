# -*- coding: utf-8 -*-
# [Structures] 行字段: house,type,strength,Y,X,facing,...
# 正确解析 Y=field3, X=field4，再查地基+外圈
import sys

path = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261003_125504.isopack5.txt"

cells = {}
for line in open(path, encoding="utf-8", errors="replace"):
    if line.startswith(";"): continue
    p = line.split()
    if len(p) < 12: continue
    cells[(int(p[0]), int(p[1]))] = {
        "tile": int(p[2]), "H": int(p[7]), "L": int(p[8]),
        "slope": int(p[10]), "pass": int(p[11]),
    }

# (name, X, Y, w, h)  X=field4 Y=field3
blds = [
    ("CAAIRP", 206, 169, 3, 3),
    ("CAMACH", 69, 117, 3, 3),
    ("CAPOWR", 151, 164, 2, 2),
    ("CAPOWR", 145, 76, 2, 2),
]

for name, x0, y0, w, h in blds:
    print("=" * 78)
    print("%s %dx%d anchor=(X=%d,Y=%d)" % (name, w, h, x0, y0))
    R = 3
    for y in range(y0 - R, y0 + h + R):
        row = "y%-3d " % y
        for x in range(x0 - R, x0 + w + R):
            c = cells.get((x, y))
            inside = x0 <= x < x0 + w and y0 <= y < y0 + h
            if c is None:
                row += "[ MISS]" if inside else "   .   "
                continue
            s = "[%4d/L%02d/s%02d/p%d]" % (c["tile"], c["L"], c["slope"], c["pass"]) if inside \
                else " %4d/L%02d/s%02d  " % (c["tile"], c["L"], c["slope"])
            row += s
        print(row)
    bad = []
    for y in range(y0, y0 + h):
        for x in range(x0, x0 + w):
            c = cells.get((x, y))
            if c is None:
                bad.append((x, y, "MISSING"))
            elif c["slope"] != 0 or c["tile"] not in (0, 0xFFFF):
                bad.append((x, y, c["tile"], c["L"], c["slope"], c["pass"]))
    print("FOUNDATION bad cells:", len(bad), bad)
