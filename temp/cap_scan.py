#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Compare how the west-side wall ends where a vertical slope1 band (t510-512,
slope==1) descends from high ground:

For each west-edge band toe b=(bx,by) L4 whose N neighbour is the band top and
whose W neighbour (bx-1,by) is high (L>=6), record the 2x2 pattern WEST of the
band at rows by and by+1:
  W0=(bx-1,by)  NW0=(bx-2,by)
  W1=(bx-1,by+1) W1E=(bx,by+1)
Run on vanilla .yrm and the defect port map. Read-only."""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import analyze_isopack5 as A

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
NAMES = [
    "Map.20261001-132734-00938.yrm",
    "Map.20261001-132800-00298.yrm",
    "Map.20261001-132822-00546.yrm",
    "Map.20261001-132849-00795.yrm",
    "rmg_20261001_135107.map",
]


def is_band(t):
    return 510 <= t <= 512


def fmt(c):
    if c is None:
        return "  ..."
    t = c["tile"]
    ts = "FFFF" if t == 0xFFFF else ("  0" if t == 0 else "%4d" % t)
    return "%s/L%d" % (ts, c["level"])


for name in NAMES:
    p = os.path.join(ROOT, name)
    if not os.path.exists(p):
        continue
    cells = A.load_map(p)[0]
    hits = []
    for (x, y), c in cells.items():
        if not is_band(c["tile"]) or c["level"] > 5:
            continue
        w = cells.get((x - 1, y))
        n = cells.get((x, y - 1))
        # west edge of a band (W is not a ramp tile) with high ground W
        if w is None or (29 <= w["tile"] <= 48) or (510 <= w["tile"] <= 521) \
                or (384 <= w["tile"] <= 393):
            continue
        if w["level"] < 6:
            continue
        hits.append((x, y, w["level"], n))
    print("== %s : %d high-west band toes" % (name, len(hits)))
    shown = 0
    for x, y, wl, n in hits:
        w0 = cells.get((x - 1, y)); w1 = cells.get((x - 1, y + 1))
        nw0 = cells.get((x - 2, y)); e1 = cells.get((x, y + 1))
        tag = ""
        if w1 is not None and 49 <= w1["tile"] <= 88 and w1["level"] >= 6 \
                and e1 is not None and e1["level"] <= 5:
            tag = "  <<< W1 HIGH CLIFF BESIDE LOW BAND"
        print("   toe(%d,%d)L%d | NW=%s W0=%s | W1=%s S1=%s%s"
              % (x, y, cells[(x, y)]["level"], fmt(nw0), fmt(w0),
                 fmt(w1), fmt(e1), tag))
        shown += 1
        if shown >= 12:
            print("    ...")
            break
