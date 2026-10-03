#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Distribution of the 8-neighbour water masks of land cells.

    python mask_dist.py <map> [<map> ...]

For every land (non-water, non-0xFFFF) cell build the same bit mask as
TileNeighbourMask: NW=0x40 N=0x80 NE=0x01 W=0x20 E=0x02 SW=0x10 S=0x08
SE=0x04. Print each mask value with its count and the cell list when small.
"""
import sys
from collections import Counter, defaultdict

sys.path.insert(0, ".")
import analyze_isopack5 as A

WATER = set(range(314, 328))
BITS = [((-1, -1), 0x40), ((0, -1), 0x80), ((1, -1), 0x01),
        ((-1, 0), 0x20), ((1, 0), 0x02),
        ((-1, 1), 0x10), ((0, 1), 0x08), ((1, 1), 0x04)]


def main():
    for path in sys.argv[1:]:
        cells, _a, _b = A.load_map(path)
        h = Counter()
        where = defaultdict(list)
        for (x, y), v in cells.items():
            if v["tile"] in WATER or v["tile"] == 0xFFFF:
                continue
            m = 0
            for (dx, dy), bit in BITS:
                n = cells.get((x + dx, y + dy))
                if n and n["tile"] in WATER:
                    m |= bit
            if m:
                h[m] += 1
                where[m].append((x, y))
        print("== %s : %d land cells touching water, %d distinct masks"
              % (path, sum(h.values()), len(h)))
        for m in sorted(h):
            mark = "   <== corner-only" if m in (1, 4, 0x40, 0x01) else ""
            print("   mask 0x%02X count %3d%s" % (m, h[m], mark))
        print()


main()
