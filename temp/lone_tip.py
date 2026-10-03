#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Count lone diagonal water tips in a map.

    python lone_tip.py <map> [<map> ...]

A lone tip: land cell L has water at a diagonal D, but neither of the two
side neighbours that frame that vertex is water.

    NE water (x+1,y-1): require N (x,y-1) or E (x+1,y) water
    SE water (x+1,y+1): require S (x,y+1) or E (x+1,y) water
    SW water (x-1,y+1): require S (x,y+1) or W (x-1,y) water
    NW water (x-1,y-1): require N (x,y-1) or W (x-1,y) water

Vanilla water never leaves such a tip; a lone tip forces the wrong corner
shore piece and the cell on the far side stays bare.
"""
import sys

sys.path.insert(0, ".")
import analyze_isopack5 as A

WATER = set(range(314, 328))

# corner -> (diagonal offset, two framing side offsets)
TIPS = [
    ("NE", (1, -1), ((0, -1), (1, 0))),
    ("SE", (1, 1), ((0, 1), (1, 0))),
    ("SW", (-1, 1), ((0, 1), (-1, 0))),
    ("NW", (-1, -1), ((0, -1), (-1, 0))),
]


def w(cells, x, y):
    n = cells.get((x, y))
    return bool(n and n["tile"] in WATER)


def main():
    for path in sys.argv[1:]:
        cells, _a, _b = A.load_map(path)
        bad = []
        for (x, y), c in cells.items():
            if c["tile"] in WATER or c["tile"] == 0xFFFF:
                continue
            for name, (ddx, ddy), sides in TIPS:
                if not w(cells, x + ddx, y + ddy):
                    continue
                if not any(w(cells, x + sx, y + sy) for sx, sy in sides):
                    bad.append((x, y, name, c["tile"]))
        print("%s : %d lone diagonal water tips" % (path, len(bad)))
        for x, y, name, tile in bad:
            print("    land (%d,%d) %s tip, own tile %d" % (x, y, name, tile))


main()
