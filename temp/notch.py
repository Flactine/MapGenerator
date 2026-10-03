#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Tight notch detector:
 two west-end L4 ramp toes, |dy| == 2 rows, |dx| <= 1, but from DIFFERENT
 slope groups (one strip cannot carry two slopes), with the row between them
 checked. A notch "clashes" when a toe's W neighbour is a CliffSet tile
 >=2 levels higher. Summary + clashes only. Read-only."""
import glob
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import analyze_isopack5 as A

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def is_ramp(t):
    return (29 <= t <= 48) or (510 <= t <= 521) or (384 <= t <= 393)


for p in sorted(glob.glob(os.path.join(ROOT, "Map.*.yrm"))) + \
        sorted(glob.glob(os.path.join(ROOT, "rmg_*.map"))):
    cells = A.load_map(p)[0]
    toes = []
    for (x, y), c in cells.items():
        if not is_ramp(c["tile"]) or c["level"] != 4:
            continue
        w = cells.get((x - 1, y))
        if w is not None and is_ramp(w["tile"]):
            continue
        toes.append((x, y, c["tile"], c["slope"]))

    notches = 0
    clashes = []
    for i in range(len(toes)):
        ax, ay, at, asp = toes[i]
        for j in range(i + 1, len(toes)):
            bx, by, bt, bsp = toes[j]
            if abs(ay - by) != 2 or abs(ax - bx) > 1:
                continue
            if asp == bsp and asp != 0:
                continue  # same strip / same carving
            # what is between the two toes (the y+1 row around x)?
            ymid = (ay + by) // 2
            mid = []
            for mx in range(min(ax, bx) - 1, max(ax, bx) + 2):
                mc = cells.get((mx, ymid))
                mid.append("ramp" if mc and is_ramp(mc["tile"]) else
                           ("cliff" if mc and 49 <= mc["tile"] <= 88 else "other"))
            notches += 1

            def wclash(x, y):
                q = cells.get((x - 1, y))
                return q is not None and 49 <= q["tile"] <= 88 \
                    and q["level"] - cells[(x, y)]["level"] >= 2
            ca, cb = wclash(ax, ay), wclash(bx, by)
            if ca or cb:
                wa = cells.get((ax - 1, ay))
                wb = cells.get((bx - 1, by))
                clashes.append((ax, ay, at, asp, wa["tile"], wa["level"], ca,
                                bx, by, bt, bsp, wb["tile"], wb["level"], cb))

    name = os.path.basename(p)
    print("%-34s westL4toes=%-3d crossSlopeNotches=%-2d clashes=%d%s"
          % (name, len(toes), notches, len(clashes),
             "  <<<" if clashes else ""))
    for c in clashes:
        print("      A(%d,%d)t%d/s%d W=t%dL%d[%s]  B(%d,%d)t%d/s%d W=t%dL%d[%s]"
              % (c[0], c[1], c[2], c[3], c[4], c[5], "CLASH" if c[6] else "ok",
                 c[7], c[8], c[9], c[10], c[11], c[12],
                 "CLASH" if c[13] else "ok"))
