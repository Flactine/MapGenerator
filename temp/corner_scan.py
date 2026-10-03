#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Corner-ramp concave side scan.

A B1/B2-style corner ramp has a slope-5 diagonal cell (tile rampBase+4 = 33..35
after Recalc variants are still in 29..48 with slope==5) at its inside corner, a
slope-2 band heading west and a slope-1 band heading south.

For every slope==5 L4 cell that has a slope-1 band cell directly SOUTH and a
slope-2 band cell directly EAST (i.e. the band-C/band-B junction), report the
two concave-side plateau cells W and SW of the junction:
  W  = (x-1, y)
  SW = (x-1, y+1)
Read-only."""
import glob
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import analyze_isopack5 as A

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
paths = sorted(glob.glob(os.path.join(ROOT, "Map.20261001-13*.yrm")))
paths += [os.path.join(ROOT, "rmg_20261001_135107.map")]
paths += sorted(glob.glob(os.path.join(ROOT, "rmg_20261001_13*.map")))


def f(c):
    if c is None:
        return " ... "
    t = c["tile"]
    ts = "FFFF" if t == 0xFFFF else ("  0" if t == 0 else "%4d" % t)
    return "%s/L%d/s%s" % (ts, c["level"], c["slope"])


seen = set()
for p in paths:
    name = os.path.basename(p)
    if name in seen:
        continue
    seen.add(name)
    cells = A.load_map(p)[0]
    corners = []
    for (x, y), c in cells.items():
        if c["slope"] != 5 or c["level"] > 5:
            continue
        s = cells.get((x, y + 1))
        e = cells.get((x + 1, y))
        if s is None or e is None:
            continue
        if s["slope"] == 1 and e["slope"] == 2:
            corners.append((x, y))
    print("== %s : %d B/A/C corner junctions" % (name, len(corners)))
    for x, y in corners[:8]:
        print("    J(%d,%d)%s | W=%s SW=%s NW=%s"
              % (x, y, f(cells[(x, y)]),
                 f(cells.get((x - 1, y))), f(cells.get((x - 1, y + 1))),
                 f(cells.get((x - 1, y - 1)))))
