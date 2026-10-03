#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Compare vanilla .yrm vs ported .map:
 1. orthogonal two-level ramp/cliff defects (orth_gap criterion)
 2. ramp family cell counts: rampBase 29-48, rampSmooth 510-521, cliffRamps 384-393
 3. level-difference histogram of every ramp-cell <-> CliffSet-cell ORTH edge
 4. detail windows around given defect points
Read-only: just parses [IsoMapPack5], writes nothing.
"""
import glob
import os
import sys
from collections import Counter

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import analyze_isopack5 as A

ORTH = [(0, -1, "N"), (1, 0, "E"), (0, 1, "S"), (-1, 0, "W")]
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def is_ramp(t):
    return 29 <= t <= 48 or 510 <= t <= 521


def family(t):
    if 29 <= t <= 48:
        return "rampBase"
    if 510 <= t <= 521:
        return "rampSmooth"
    if 384 <= t <= 393:
        return "cliffRamp"
    if 49 <= t <= 88:
        return "cliff"
    if t == 0:
        return "t0"
    if t == 0xFFFF:
        return "FFFF"
    return "other"


def stats(path):
    cells = A.load_map(path)[0]
    cnt = Counter()
    for c in cells.values():
        cnt[family(c["tile"])] += 1

    defects = []
    edge_hist = Counter()       # (rampFam, cliffLevel - rampLevel)
    touch_edges = 0
    for (x, y), c in cells.items():
        if not is_ramp(c["tile"]):
            continue
        rf = family(c["tile"])
        for dx, dy, dn in ORTH:
            q = cells.get((x + dx, y + dy))
            if q is None or not (49 <= q["tile"] <= 88):
                continue
            touch_edges += 1
            d = q["level"] - c["level"]
            edge_hist[(rf, d)] += 1
            if d >= 2:
                defects.append((x, y, c["tile"], c["level"], dn,
                                x + dx, y + dy, q["tile"], q["level"]))
    return cells, cnt, defects, edge_hist, touch_edges


def show_window(cells, cx, cy, r=4):
    print("   window around (%d,%d), format ttt/L [s slope]:" % (cx, cy))
    for y in range(cy - r, cy + r + 1):
        row = []
        for x in range(cx - r, cx + r + 1):
            c = cells.get((x, y))
            if c is None:
                row.append("  ...  ")
            else:
                mark = "*" if (x, y) == (cx, cy) else " "
                t = c["tile"]
                ts = "FFFF" if t == 0xFFFF else ("  0" if t == 0 else "%4d" % t)
                sl = c["slope"]
                ss = ("s%d" % sl) if sl else "  "
                row.append("%s%s/L%d%s" % (mark, ts, c["level"], ss))
        print("   y=%2d %s" % (y, " ".join(row)))


paths = sorted(glob.glob(os.path.join(ROOT, "Map.*.yrm")))
paths += sorted(p for p in glob.glob(os.path.join(ROOT, "rmg_*.map")))

targets = {}
for arg in sys.argv[1:]:
    if "=" in arg:
        name, coords = arg.split("=", 1)
        pts = []
        for pair in coords.split(","):
            px, py = pair.split(":")
            pts.append((int(px), int(py)))
        targets[name] = pts

for p in paths:
    name = os.path.basename(p)
    cells, cnt, defects, edge_hist, touch = stats(p)
    print("== %s" % name)
    print("   cliff=%d rampBase=%d rampSmooth=%d cliffRamp=%d t0=%d FFFF=%d"
          % (cnt["cliff"], cnt["rampBase"], cnt["rampSmooth"],
             cnt["cliffRamp"], cnt["t0"], cnt["FFFF"]))
    print("   ramp<->cliff ORTH edges=%d  level-diff hist=%s"
          % (touch, dict(sorted(edge_hist.items()))))
    print("   ORTH-TWO-LEVEL DEFECTS=%d" % len(defects))
    for d in defects:
        print("     ramp(%d,%d) t%d L%d -%s cliff(%d,%d) t%d L%d" %
              (d[0], d[1], d[2], d[3], d[4], d[5], d[6], d[7], d[8]))
    for key, pts in targets.items():
        if key in name:
            for px, py in pts:
                show_window(cells, px, py)
    print("")
