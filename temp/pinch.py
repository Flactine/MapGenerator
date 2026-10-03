#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Count diagonal water pinches around 2x2 land blocks.

    python pinch.py <map> [<map> ...]

A 2x2 block at (x,y) (all four cells non-water) is pinched when water sits at
two diagonally opposite outer corners:

    NW outer (x-1,y-1) and SE outer (x+2,y+2), or
    NE outer (x+2,y-1) and SW outer (x-1,y+2).

Every such block is a shape the 2x2 corner shore pieces cannot tile: one
piece wins, the other corner is left bare.
"""
import sys

sys.path.insert(0, ".")
import analyze_isopack5 as A

WATER = set(range(314, 328))


def is_water(cells, x, y):
    n = cells.get((x, y))
    return bool(n and n["tile"] in WATER)


def main():
    for path in sys.argv[1:]:
        cells, _a, _b = A.load_map(path)
        xs = sorted({x for x, _ in cells})
        ys = sorted({y for _, y in cells})
        pinches = []
        for y in range(min(ys), max(ys) - 1):
            for x in range(min(xs), max(xs) - 1):
                if any(is_water(cells, x + dx, y + dy)
                       for dx in (0, 1) for dy in (0, 1)):
                    continue                        # block must be all land
                nw = is_water(cells, x - 1, y - 1)
                se = is_water(cells, x + 2, y + 2)
                ne = is_water(cells, x + 2, y - 1)
                sw = is_water(cells, x - 1, y + 2)
                pairs = []
                if nw and se:
                    pairs.append("NW-SE")
                if ne and sw:
                    pairs.append("NE-SW")
                if pairs:
                    pinches.append((x, y, pairs))
        print("%s : %d pinched 2x2 blocks" % (path, len(pinches)))
        if "--layout" in sys.argv:
            for x, y, pairs in pinches:
                # 4x4 window centred on the 2x2 block: outer corners included
                print("   block (%d,%d) %s" % (x, y, ",".join(pairs)))
                for wy in range(y - 1, y + 3):
                    line = []
                    for wx in range(x - 1, x + 3):
                        n = cells.get((wx, wy))
                        line.append("...." if n is None else "%4d" % n["tile"])
                    print("      [%s]" % " ".join(line))
        else:
            for x, y, pairs in pinches:
                print("   block (%d,%d) %s" % (x, y, ",".join(pairs)))


main()
