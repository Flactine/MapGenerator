#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Compare how two maps tile the cells whose water contact is a single corner.

    python cmp_corner.py <mapA> <mapB>

For every land cell that has a water neighbour at a diagonal (sharing one
vertex only), bucket the cell's own tile. Print the two histograms side by
side, then dump every occurrence of the tiles that map B leaves bare.
"""
import sys
from collections import Counter

sys.path.insert(0, ".")
import analyze_isopack5 as A

WATER = set(range(314, 328))
CDIR = [("NE", 1, -1), ("SE", 1, 1), ("SW", -1, 1), ("NW", -1, -1)]
EDIR = [("E", 1, 0), ("S", 0, 1), ("W", -1, 0), ("N", 0, -1)]


def corner_cells(cells):
    """land cells that touch water at >=1 corner -> (pos, cell, corner sides,
    side-contact flags)."""
    out = []
    for (x, y), c in cells.items():
        if c["tile"] in WATER or c["tile"] == 0xFFFF:
            continue
        csides = []
        esides = []
        for name, dx, dy in CDIR:
            n = cells.get((x + dx, y + dy))
            if n and n["tile"] in WATER:
                csides.append(name)
        for name, dx, dy in EDIR:
            n = cells.get((x + dx, y + dy))
            if n and n["tile"] in WATER:
                esides.append(name)
        if csides:
            out.append(((x, y), c, csides, esides))
    return out


def hist(path):
    cells, _a, _b = A.load_map(path)
    cc = corner_cells(cells)
    h = Counter(c["tile"] for _p, c, _cs, _es in cc)
    return cells, cc, h


def main():
    pa, pb = sys.argv[1], sys.argv[2]
    ca, cca, ha = hist(pa)
    cb, ccb, hb = hist(pb)
    print("A: %s  corner-contact land cells: %d" % (pa, len(cca)))
    print("B: %s  corner-contact land cells: %d" % (pb, len(ccb)))
    tiles = sorted(set(ha) | set(hb))
    print()
    print(" tile   A   B")
    for t in tiles:
        print(" %5d %4d %4d" % (t, ha.get(t, 0), hb.get(t, 0)))

    # For each corner-contact cell in B whose tile is one of {115,126,128},
    # print the 8-neighbour tile layout. Then show every corner-contact cell
    # in A that carries the SAME tile, with its layout.
    def layout(cells, x, y):
        row = []
        for dy in (-1, 0, 1):
            for dx in (-1, 0, 1):
                n = cells.get((x + dx, y + dy))
                row.append("...." if n is None else "%4d" % n["tile"])
        return row

    watch = sorted({c["tile"] for _p, c, _cs, _es in ccb
                    if c["tile"] in (115, 126, 128)})
    print()
    print("watch tiles (bare in B):", watch)
    for label, cells, cc in (("A", ca, cca), ("B", cb, ccb)):
        print("--- map %s ---" % label)
        for (x, y), c, csides, esides in cc:
            if c["tile"] not in watch:
                continue
            L = layout(cells, x, y)
            print(" (%3d,%3d) tile %d corner=%s side=%s"
                  % (x, y, c["tile"], "".join(csides), "".join(esides)))
            print("    [%s %s %s]" % (L[0], L[1], L[2]))
            print("    [%s %s %s]" % (L[3], L[4], L[5]))
            print("    [%s %s %s]" % (L[6], L[7], L[8]))


main()
