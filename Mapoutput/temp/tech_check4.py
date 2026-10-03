# -*- coding: utf-8 -*-
# rmg_20261003_143645: 逐格查4个建筑地基+外圈2格
# [Structures]: house,type,strength,Y=field3,X=field4,...
import sys
path = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261003_143645.isopack5.txt"

cells = {}
for line in open(path, encoding="utf-8", errors="replace"):
    if line.startswith(";"): continue
    p = line.split()
    if len(p) < 12: continue
    cells[(int(p[0]), int(p[1]))] = {
        "tile": int(p[2]), "H": int(p[7]), "L": int(p[8]),
        "slope": int(p[10]), "pass": int(p[11]),
    }

# (name, X=field4, Y=field3, w, h)
blds = [
    ("CAOUTP", 66, 110, 4, 3),
    ("CAMACH", 60, 48, 3, 3),
    ("CAAIRP", 49, 98, 3, 3),
    ("CAOILD", 86, 50, 2, 2),
]

def fam(t):
    if t in (0, 0xFFFF): return "."
    if 49 <= t <= 88: return "C"      # cliff
    if 148 <= t <= 175: return "W"
    if 314 <= t <= 327: return "~"
    if 384 <= t <= 393: return "R"
    if 510 <= t <= 521: return "r"
    return " "

for name, x0, y0, w, h in blds:
    print("=" * 80)
    print("%s %dx%d anchor=(X=%d,Y=%d)" % (name, w, h, x0, y0))
    R = 2
    bad_in = []
    bad_ring = []
    for y in range(y0 - R, y0 + h + R):
        row = "y%-3d " % y
        for x in range(x0 - R, x0 + w + R):
            c = cells.get((x, y))
            inside = x0 <= x < x0 + w and y0 <= y < y0 + h
            if c is None:
                row += "[MISS]" if inside else " MISS "
                continue
            tag = "[" if inside else " "
            end = "]" if inside else " "
            row += "%s%4d/L%02d/s%02d/p%d%s" % (
                tag, c["tile"], c["L"], c["slope"], c["pass"], end)
            if inside and (c["slope"] != 0 or c["tile"] not in (0, 0xFFFF)):
                bad_in.append((x, y, c["tile"], c["L"], c["slope"], c["pass"]))
            if not inside and (c["slope"] != 0 or
                (c["pass"] not in (0, 3)) or
                (c["tile"] not in (0, 0xFFFF))):
                bad_ring.append((x, y, c["tile"], c["L"], c["slope"], c["pass"]))
        print(row)
    print("FOUNDATION bad:", bad_in)
    print("RING(2) nonflat/nonwalkable:", bad_ring)
