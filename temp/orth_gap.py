#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Orthogonal-only two-level ramp/cliff defect:
 a rampBase(29-48)/rampSmooth(510-521) cell sharing an EDGE (N/S/E/W) with a
 CliffSet(49-88) cell whose Level is >= 2 higher. Diagonal touches and
 one-level touches are vanilla-legal (verified on the reference map)."""
import sys
sys.path.insert(0, ".")
import analyze_isopack5 as A

ORTH = [(0, -1, "N"), (1, 0, "E"), (0, 1, "S"), (-1, 0, "W")]


def is_ramp(t):
    return 29 <= t <= 48 or 510 <= t <= 521


for p in sys.argv[1:]:
    cells = A.load_map(p)[0]
    hits = []
    for (x, y), c in cells.items():
        if not is_ramp(c["tile"]):
            continue
        for dx, dy, dn in ORTH:
            q = cells.get((x + dx, y + dy))
            if q is not None and 49 <= q["tile"] <= 88 \
                    and q["level"] - c["level"] >= 2:
                hits.append((x, y, c["tile"], c["level"],
                             dn, x + dx, y + dy, q["tile"], q["level"]))
    print("%s orth-two-level: %d" % (p, len(hits)))
    for h in hits:
        print("   ", h)
