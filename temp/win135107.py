#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Window dump for rmg_135107 clash at ramp (120,82)/cliff (119,82).
Shows tile/L and slope flag. Read-only."""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import analyze_isopack5 as A

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
cells = A.load_map(os.path.join(ROOT, "rmg_20261001_135107.map"))[0]

cx, cy = 119, 82
for y in range(cy - 4, cy + 5):
    row = []
    for x in range(cx - 4, cx + 6):
        c = cells.get((x, y))
        if c is None:
            row.append("  ...  ")
        else:
            t = c["tile"]
            ts = "FFFF" if t == 0xFFFF else ("  0" if t == 0 else "%4d" % t)
            sl = c["slope"]
            ss = ("s%-2d" % sl) if sl else "   "
            mark = "*" if (x, y) in ((120, 82), (119, 82)) else " "
            row.append("%s%s/L%d%s" % (mark, ts, c["level"], ss))
    print("y=%-3d %s" % (y, " ".join(row)))
