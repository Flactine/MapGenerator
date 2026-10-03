#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Raw water-mask distribution over land cells, and diagonal co-occurrence.

    python raw_mask_dist.py <map> [<map> ...]

Raw mask: same 8-bit layout, straight from actual water tiles, no gates.
Additionally flags every diagonal pair of land cells (A at (x,y), B at
(x+1,y+1)) where A's mask has water N/NE/E (and B land) and B's mask has
water E/SE - the raw staircase that makes piece22 clash with piece14.
"""
import sys
from collections import Counter

sys.path.insert(0, ".")
import analyze_isopack5 as A

WATER = set(range(314, 328))
BITS = [((-1, -1), 0x40), ((0, -1), 0x80), ((1, -1), 0x01),
        ((-1, 0), 0x20), ((1, 0), 0x02),
        ((-1, 1), 0x10), ((0, 1), 0x08), ((1, 1), 0x04)]


def raw_masks(cells):
    out = {}
    for (x, y), c in cells.items():
        if c["tile"] in WATER or c["tile"] == 65535:
            continue
        m = 0
        for (dx, dy), bit in BITS:
            n = cells.get((x + dx, y + dy))
            if n and n["tile"] in WATER:
                m |= bit
        out[(x, y)] = m
    return out


def main():
    for path in sys.argv[1:]:
        cells, _a, _b = A.load_map(path)
        masks = raw_masks(cells)
        h = Counter(masks.values())
        print("== %s : %d land cells" % (path, len(masks)))
        for m in sorted(h):
            tag = ""
            if m == 0xC3:
                tag = " <- A-type (NW,N,NE,E)"
            if m == 0x86:
                tag = " <- B-type (N,E,SE)"
            print("   0x%02X : %d%s" % (m, h[m], tag))

        # staircase co-occurrence
        stair = []
        for (x, y), m in masks.items():
            b = masks.get((x + 1, y + 1))
            if b is None:
                continue
            # A: water N,NE,E (0x83 subset incl 0x80,0x01,0x02), no SE;
            # B: water E and SE (0x06)
            if (m & 0x83) == 0x83 and (m & 0x04) == 0 and (b & 0x06) == 0x06:
                stair.append((x, y, m, b))
        print("   staircase A/B diagonal pairs: %d" % len(stair))
        for x, y, m, b in stair:
            print("      A(%d,%d)=0x%02X  B(%d,%d)=0x%02X"
                  % (x, y, m, x + 1, y + 1, b))
        print()


main()
