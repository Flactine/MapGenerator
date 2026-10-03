#!/usr/bin/env python3
"""Does pass 2 (CleanupTile) reclaim the water cells it is supposed to?

CleanupTile turns a water cell into 0xFFFF when its morphology code (the 8-bit
water-neighbour mask) is one of 199 / 124 / 241 / 31 / 198 / 108 / 177 / 27.
Water cells are never overwritten afterwards, so such a cell must appear as
0xFFFF in the final map.  Any cell that still carries a water tile while its
mask is one of those eight codes means pass 2 did not fire.

Usage: python analyze_cleanup.py <map> ...
"""
import sys
from collections import Counter

sys.path.insert(0, ".")
import analyze_isopack5 as A

WATER_LO, WATER_HI = 314, 327
SHORE_LO, SHORE_HI = 89, 130
BITS = [0x80, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40]
CODES = {199, 124, 241, 31, 198, 108, 177, 27}


def mask(cells, x, y, want_water=True):
    m = 0
    for (dx, dy), bit in zip(A.DIRS, BITS):
        n = cells.get((x + dx, y + dy))
        if n is None:
            continue
        t = n["tile"]
        iswater = WATER_LO <= t <= WATER_HI
        if iswater == want_water:
            m |= bit
    return m


for path in sys.argv[1:]:
    cells, _secs, _n = A.load_map(path)
    print("=" * 72)
    print(path)

    water_total = 0
    water_hit = Counter()
    ph_total = 0
    ph_hit = Counter()
    for (x, y), c in cells.items():
        t = c["tile"]
        m = mask(cells, x, y)
        if WATER_LO <= t <= WATER_HI:
            water_total += 1
            if m in CODES:
                water_hit[m] += 1
        elif t == 0xFFFF:
            ph_total += 1
            if m in CODES:
                ph_hit[m] += 1

    print("water cells: %d   of which still carrying a reclaim code: %d"
          % (water_total, sum(water_hit.values())))
    print("   by code: %s" % dict(water_hit))
    print("0xFFFF cells: %d   of which matching a reclaim code: %d"
          % (ph_total, sum(ph_hit.values())))
    print("   by code: %s" % dict(ph_hit))
