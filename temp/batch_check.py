#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import sys, glob, os
sys.path.insert(0, ".")
import analyze_isopack5 as A

DIRS = [(1, 0), (-1, 0), (0, 1), (0, -1), (1, 1), (1, -1), (-1, 1), (-1, -1)]


def fam(t):
    if 49 <= t <= 88:
        return "cliff"
    if 29 <= t <= 48 or 510 <= t <= 521:
        return "ramp"
    return None


n = int(sys.argv[1]) if len(sys.argv) > 1 else 8
fs = sorted(glob.glob("rmg_*.map"))[-n:]
for p in fs:
    cells = A.load_map(p)[0]
    tot = two = sp = 0
    for (x, y), c in cells.items():
        if 384 <= c["tile"] <= 393:
            sp += 1
        if fam(c["tile"]) != "ramp":
            continue
        for dx, dy in DIRS:
            q = cells.get((x + dx, y + dy))
            if q is not None and fam(q["tile"]) == "cliff":
                tot += 1
                if q["level"] - c["level"] >= 2:
                    two += 1
                break
    print("%s touches=%3d twoLevel=%d setpieces=%d"
          % (os.path.basename(p), tot, two, sp))
