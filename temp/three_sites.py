#!/usr/bin/env python3
# -*- coding: utf-8 utf-8 -*-
"""Window dumps for the three reported sites in rmg_20261001_144439."""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import analyze_isopack5 as A

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
cells = A.load_map(os.path.join(ROOT, "rmg_20261001_144439.map"))[0]

SITES = [
    ("P1 (94,127)", 94, 127, 5, 5),
    ("P2 (64,113)/(65,112)", 65, 112, 6, 6),
    ("P3 (39,64)/(38,64)", 39, 64, 6, 6),
]


def show(title, cx, cy, rx, ry):
    print("==== %s ====" % title)
    for y in range(cy - ry, cy + ry + 1):
        row = []
        for x in range(cx - rx, cx + rx + 1):
            c = cells.get((x, y))
            if c is None:
                row.append("  ...  ")
            else:
                t = c["tile"]
                ts = "FFFF" if t == 0xFFFF else ("  0" if t == 0 else "%4d" % t)
                sl = c["slope"]
                ss = ("s%-2d" % sl) if sl else "   "
                row.append("%s/L%d%s" % (ts, c["level"], ss))
        print("y=%-3d %s" % (y, " ".join(row)))
    print()


for t, x, y, rx, ry in SITES:
    show(t, x, y, rx, ry)
