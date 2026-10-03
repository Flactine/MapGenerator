#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Print a window as tile/Llevel.  python dump_lv.py <map> x0 x1 y0 y1"""
import sys

sys.path.insert(0, ".")
import analyze_isopack5 as A

path = sys.argv[1]
x0, x1, y0, y1 = (int(v) for v in sys.argv[2:6])
c, _a, _b = A.load_map(path)
print(path)
print("      " + "".join("%10d" % x for x in range(x0, x1 + 1)))
for y in range(y0, y1 + 1):
    cells = []
    for x in range(x0, x1 + 1):
        v = c.get((x, y))
        cells.append(".........." if v is None
                     else "%d/L%d" % (v["tile"], v["level"]))
    print("y=%-4d %s" % (y, "".join("%10s" % s for s in cells)))
