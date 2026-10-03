#!/usr/bin/env python3
"""Check how the shore pieces are stamped.  Usage: python analyze_shore.py <map> ...

Shore family = tiles 89..130 (shore01 .. shore42).  The port's kShoreFootprints
says which foundation each variant occupies:

    n12   1-3 : 2x2      4: 1x2    5-6: 2x3   7-11: 2x2   12: 2x1
        13-14: 3x2    15-19: 2x2     20: 1x2   21-22: 2x3   23-27: 2x2
           28: 2x1    29-30: 3x2    31-40: 2x2     41: 6x4     42: 9x5

Every cell of one stamp carries the SAME tile index, so a cell's number of
same-tile in-diamond neighbours tells the stamp's shape:

    2x2 block -> 3 same-tile neighbours (the other 3 cells of the block)
    1x2 / 2x1 -> 1
    2x3 / 3x2 -> 2 (interior) or 4 ... a 2x3 block: (0,0) touches (0,1),(1,0),
                 (1,1) -> 3; the middle column cell touches 4.

So if "expected 2x2" variants show a same-tile neighbour count of 1, the port
is stamping only half the piece.
"""
import sys
from collections import Counter, defaultdict

sys.path.insert(0, ".")
import analyze_isopack5 as A

SHORE_LO, SHORE_HI = 89, 130          # shore01 .. shore42
WATER_LO, WATER_HI = 314, 327

# (w, h) per n12 = 1..42, straight from kShoreFootprints in MapGenRiver.cpp
FOOT = {
    1: (2, 2), 2: (2, 2), 3: (2, 2), 4: (1, 2), 5: (2, 3), 6: (2, 3),
    7: (2, 2), 8: (2, 2), 9: (2, 2), 10: (2, 2), 11: (2, 2), 12: (2, 1),
    13: (3, 2), 14: (3, 2), 15: (2, 2), 16: (2, 2), 17: (2, 2), 18: (2, 2),
    19: (2, 2), 20: (1, 2), 21: (2, 3), 22: (2, 3), 23: (2, 2), 24: (2, 2),
    25: (2, 2), 26: (2, 2), 27: (2, 2), 28: (2, 1), 29: (3, 2), 30: (3, 2),
    31: (2, 2), 32: (2, 2), 33: (2, 2), 34: (2, 2), 35: (2, 2), 36: (2, 2),
    37: (2, 2), 38: (2, 2), 39: (2, 2), 40: (2, 2), 41: (6, 4), 42: (9, 5),
}

FAMILIES = [
    ("Clear 0", 0, 0), ("RampBase 29-48", 29, 48), ("CliffSet 49-88", 49, 88),
    ("Shore 89-130", 89, 130), ("Ruff 131", 131, 131), ("clat 132-147", 132, 147),
    ("WCliff 148-175", 148, 175), ("Water 314-327", 314, 327),
    ("dlat 419-434", 419, 434), ("plat 463-478", 463, 478),
    ("Green 493", 493, 493), ("glat 494-509", 494, 509),
    ("Rmpfx 510-521", 510, 521), ("Pvclr 534", 534, 534), ("0xFFFF", 65535, 65535),
]


def fam(t):
    for name, lo, hi in FAMILIES:
        if lo <= t <= hi:
            return name
    return "other(%d)" % t


for path in sys.argv[1:]:
    cells, _secs, _n = A.load_map(path)
    print("=" * 72)
    print(path)

    tiles = Counter(c["tile"] for c in cells.values())
    print("top 12 tiles:", tiles.most_common(12))

    per_n12 = defaultdict(Counter)       # n12 -> {same-tile nb count: cells}
    neighbors = defaultdict(Counter)     # n12 -> {family of non-water/shore nb: edges}
    heights = defaultdict(Counter)       # n12 -> {Height value: cells}

    for (x, y), c in cells.items():
        t = c["tile"]
        if not (SHORE_LO <= t <= SHORE_HI):
            continue
        n12 = t - SHORE_LO + 1
        same = 0
        for dx, dy in A.DIRS:
            n = cells.get((x + dx, y + dy))
            if n is None:
                continue
            nt = n["tile"]
            if nt == t:
                same += 1
            elif not (WATER_LO <= nt <= WATER_HI) and not (SHORE_LO <= nt <= SHORE_HI):
                neighbors[n12][fam(nt)] += 1
        per_n12[n12][same] += 1
        heights[n12][c["height"]] += 1

    print("%-5s %-7s %-9s %s" % ("n12", "shape", "cells", "same-tile neighbour histogram"))
    for n12 in sorted(per_n12):
        w, h = FOOT[n12]
        print("%-5d %-7s %-9d %s" % (n12, "%dx%d" % (w, h),
                                     sum(per_n12[n12].values()),
                                     dict(sorted(per_n12[n12].items()))))

    # ---- a picture of one water body, shore cells as n12/height -----------
    print()
    water = [p for p, c in cells.items()
             if WATER_LO <= c["tile"] <= WATER_HI]
    if water:
        xs = [p[0] for p in water]
        ys = [p[1] for p in water]
        x0, x1 = min(xs), max(xs)
        y0, y1 = min(ys), max(ys)
        x0 = max(0, min(x0, x1 - 30))
        y0 = max(0, min(y0, y1 - 16))
        print("window x=%d..%d y=%d..%d   cell = tile(n12)/height" %
              (x0, min(x1, x0 + 30), y0, min(y1, y0 + 16)))
        for y in range(y0, min(y1, y0 + 16) + 1):
            row = []
            for x in range(x0, min(x1, x0 + 30) + 1):
                c = cells.get((x, y))
                if c is None:
                    row.append("  ......  ")
                    continue
                t = c["tile"]
                if WATER_LO <= t <= WATER_HI:
                    row.append("  ~~%2d~~  " % (t - WATER_LO + 1))
                elif SHORE_LO <= t <= SHORE_HI:
                    row.append("%4d/%d" % (t - SHORE_LO + 1, c["height"]) + "   ")
                elif t == 0xFFFF:
                    row.append("  ......  ")
                else:
                    row.append("  %6d" % t)
            print("y=%-3d %s" % (y, "".join(row)))

    print()
    print("non-water, non-shore neighbours of shore cells (what the sand touches):")
    agg = Counter()
    for n12, cnt in neighbors.items():
        for k, v in cnt.items():
            agg[k] += v
    for k, v in agg.most_common():
        print("   %-18s %d" % (k, v))

    print()
    print("Height byte written per variant (should be 0..w*h-1 of the piece):")
    for n12 in sorted(heights):
        w, h = FOOT[n12]
        print("   n12 %-3d %dx%d  -> %s" % (n12, w, h, dict(sorted(heights[n12].items()))))
