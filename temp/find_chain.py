#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Find the residual-defect fingerprint in ANY map: two west-end L4 toes 2
rows apart, one slope==1 (t510 family) and the other slope in 5..8 (t33..t36
family). Print a 7x9 window around each pair. Read-only."""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import analyze_isopack5 as A

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
NAMES = [
    "Map.20260929-233028-00663.yrm",
    "Map.20261001-122712-00234.yrm",
    "Map.20261001-122745-00730.yrm",
    "rmg_20261001_094330.map",
]
LIMIT = int(sys.argv[1]) if len(sys.argv) > 1 else 3


def is_ramp(t):
    return (29 <= t <= 48) or (510 <= t <= 521) or (384 <= t <= 393)


def show(cells, cx, cy):
    for y in range(cy - 3, cy + 4):
        row = []
        for x in range(cx - 4, cx + 5):
            c = cells.get((x, y))
            if c is None:
                row.append("  ... ")
            else:
                t = c["tile"]
                ts = "FFFF" if t == 0xFFFF else ("  0" if t == 0 else "%4d" % t)
                row.append("%s/L%d" % (ts, c["level"]))
        print("     y=%-3d %s" % (y, " ".join(row)))


for name in NAMES:
    p = os.path.join(ROOT, name)
    if not os.path.exists(p):
        continue
    cells = A.load_map(p)[0]
    toes = []
    for (x, y), c in cells.items():
        if is_ramp(c["tile"]) and c["level"] == 4:
            w = cells.get((x - 1, y))
            if w is None or not is_ramp(w["tile"]):
                toes.append((x, y, c["slope"]))
    chains = []
    for i, (ax, ay, asp) in enumerate(toes):
        for bx, by, bsp in toes[i + 1:]:
            if abs(ay - by) == 2 and abs(ax - bx) <= 1 \
                    and {asp, bsp} == {1, 5} or \
               (abs(ay - by) == 2 and abs(ax - bx) <= 1
                    and ((asp == 1 and bsp in (5, 8)) or (bsp == 1 and asp in (5, 8)))):
                chains.append((ax, ay, asp, bx, by, bsp))
    print("== %s : s1<->s5/8 toe pairs = %d" % (name, len(chains)))
    for ch in chains[:LIMIT]:
        ax, ay, asp, bx, by, bsp = ch
        wa = cells.get((ax - 1, ay))
        wb = cells.get((bx - 1, by))
        print("   A(%d,%d)s%d W=t%sL%s  B(%d,%d)s%d W=t%sL%s"
              % (ax, ay, asp, wa["tile"], wa["level"],
                 bx, by, bsp, wb["tile"], wb["level"]))
        show(cells, (ax + bx) // 2, (ay + by) // 2)
        print("")
