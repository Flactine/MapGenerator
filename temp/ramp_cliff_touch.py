#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Find ramp tiles (rampBase 29-48 / rampSmooth 510-521) directly adjacent to
CliffSet tiles (49-88) with a Level mismatch - the "ramp carved into a cliff"
configuration visible as a white facade triangle."""
import sys
sys.path.insert(0, ".")
import analyze_isopack5 as A

DIRS = [(1, 0), (-1, 0), (0, 1), (0, -1), (1, 1), (1, -1), (-1, 1), (-1, -1)]


def fam(t):
    if 49 <= t <= 88:
        return "cliff"
    if 29 <= t <= 48 or 510 <= t <= 521:
        return "ramp"
    return None


for p in sys.argv[1:]:
    cells = A.load_map(p)[0]
    hits = []
    for (x, y), c in cells.items():
        if fam(c["tile"]) != "ramp":
            continue
        for dx, dy in DIRS:
            q = cells.get((x + dx, y + dy))
            if q is None or fam(q["tile"]) != "cliff":
                continue
            if abs(q["level"] - c["level"]) >= 1:
                hits.append((x, y, c["tile"], c["level"],
                             x + dx, y + dy, q["tile"], q["level"]))
    print("=== %s  ramp-next-to-level-mismatched-cliff: %d" % (p, len(hits)))
    for h in hits[:15]:
        print("   ramp(%d,%d t%d L%d) cliff(%d,%d t%d L%d)" % h)
