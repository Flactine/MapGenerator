#!/usr/bin/env python3
"""Why are the shore pieces truncated?

For every anchor cell (Height == 0) of a shore tile, walk the piece's own
footprint (kShoreFootprints, n12 = tile - 89 + 1) and report, per expected
cell, what the map actually holds:

    =tile h   the cell carries this very piece (OK)
    WATER     it is a water tile (314..327) - the water side of the piece
    shore N   another shore variant
    .         placeholder (0xFFFF) - never stamped
    T<hex>    some other tile

Usage: python analyze_shore5.py [map ...]
"""
import sys
from collections import Counter

sys.path.insert(0, ".")
import analyze_isopack5 as A

SHORE_LO, SHORE_HI = 89, 130
WATER_LO, WATER_HI = 314, 327

# kShoreFootprints (MapGenRiver.cpp): n12 -> (w, h); all full rectangles 1..40
FOOT = {
    1: (2, 2), 2: (2, 2), 3: (2, 2), 4: (1, 2), 5: (2, 3), 6: (2, 3),
    7: (2, 2), 8: (2, 2), 9: (2, 2), 10: (2, 2), 11: (2, 2), 12: (2, 1),
    13: (3, 2), 14: (3, 2), 15: (2, 2), 16: (2, 2), 17: (2, 2), 18: (2, 2),
    19: (2, 2), 20: (1, 2), 21: (2, 3), 22: (2, 3), 23: (2, 2), 24: (2, 2),
    25: (2, 2), 26: (2, 2), 27: (2, 2), 28: (2, 1), 29: (3, 2), 30: (3, 2),
    31: (2, 2), 32: (2, 2), 33: (2, 2), 34: (2, 2), 35: (2, 2), 36: (2, 2),
    37: (2, 2), 38: (2, 2), 39: (2, 2), 40: (2, 2), 41: (6, 4), 42: (9, 5),
}


def kind(cells, x, y, tile, h):
    c = cells.get((x, y))
    if c is None:
        return "out"
    if c["tile"] == tile and c["height"] == h:
        return "ok"
    t = c["tile"]
    if WATER_LO <= t <= WATER_HI:
        return "WATER"
    if SHORE_LO <= t <= SHORE_HI:
        return "shore%d" % (t - SHORE_LO + 1)
    if t == 0xFFFF or t == 0:
        return "."
    return "T%X" % t


for path in sys.argv[1:]:
    cells, _s, _n = A.load_map(path)
    print("=" * 72)
    print(path)

    full = 0
    partial = Counter()
    examples = {}
    for (x, y), c in sorted(cells.items()):
        t = c["tile"]
        if not (SHORE_LO <= t <= SHORE_HI):
            continue
        if c["height"] != 0:
            continue
        n12 = t - SHORE_LO + 1
        w, hgt = FOOT[n12]
        missing = []
        for row in range(hgt):
            for col in range(w):
                k = kind(cells, x + col, y + row, t, col + row * w)
                if k != "ok":
                    missing.append((col, row, col + row * w, k))
        if not missing:
            full += 1
            continue
        sig = (n12, tuple(sorted(set(m[3] for m in missing))))
        partial[sig] += 1
        examples.setdefault(sig, (x, y, missing))

    tot = full + sum(partial.values())
    print("anchors: %d   complete: %d   truncated: %d"
          % (tot, full, sum(partial.values())))
    print("truncation signatures (n12, kinds)  xN   example:")
    for sig, n in partial.most_common(20):
        x, y, miss = examples[sig]
        print("   n12=%-3d %-28s x%-4d at (%d,%d) missing %s"
              % (sig[0], ",".join(sig[1]), n, x, y, miss))
