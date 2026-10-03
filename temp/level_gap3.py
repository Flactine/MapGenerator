#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""4-level steps with NEITHER side carrying a cliff OR ramp tile family
(rampBase 29-48, cliffRamps 384-393, rampSmooth 510-521 count as legal)."""
import sys
sys.path.insert(0, ".")
import analyze_isopack5 as A

DIRS = [(0, -1), (1, -1), (1, 0), (1, 1), (0, 1), (-1, 1), (-1, 0), (-1, -1)]


def legal(t):
    if t == 65535:
        return "gap"
    if 49 <= t <= 88 or 148 <= t <= 175:
        return "cliff"
    if (29 <= t <= 48) or (384 <= t <= 393) or (510 <= t <= 521):
        return "ramp"
    if t in (0, 1):
        return "clear"
    return "other"


for path in sys.argv[1:]:
    cells, _, _ = A.load_map(path)
    bare = []
    kinds = {}
    for (x, y), c in cells.items():
        for dx, dy in DIRS:
            n = cells.get((x + dx, y + dy))
            if n is None:
                continue
            d = n["level"] - c["level"]
            if d != 4:
                continue
            if legal(c["tile"]) in ("cliff", "ramp") or legal(n["tile"]) in ("cliff", "ramp"):
                continue
            bare.append((x, y, c["tile"], c["level"],
                         x + dx, y + dy, n["tile"], n["level"]))
            k = legal(c["tile"]) + " <-> " + legal(n["tile"])
            kinds[k] = kinds.get(k, 0) + 1
    print("=== %s  bare steps: %d  %s" % (path, len(bare), kinds))
    for b in bare[:12]:
        print("   ", b)
