#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Find corner shore pieces whose non-anchor cells have side water.

    python bad_corner.py <map> [<map> ...]

Shore pieces 33..40 (tiles 121..128) are all 2x2. A piece cluster at anchor
(a,b) covers (a,b)(a+1,b)(a,b+1)(a+1,b+1). For every non-anchor cell, if a
SIDE neighbour (N/E/S/W, sharing an edge) is water, that cell needed its own
side-facing piece; the corner piece has swallowed it -> bare contact.
"""
import sys

sys.path.insert(0, ".")
import analyze_isopack5 as A

WATER = set(range(314, 328))
SIDES = [("N", 0, -1), ("E", 1, 0), ("S", 0, 1), ("W", -1, 0)]


def iswater(c, x, y):
    n = c.get((x, y))
    return bool(n and n["tile"] in WATER)


def main():
    for path in sys.argv[1:]:
        c, _a, _b = A.load_map(path)
        corners = {(x, y) for (x, y), v in c.items() if 121 <= v["tile"] <= 128}
        anchors = set()
        for x, y in corners:
            t = c[(x, y)]["tile"]
            # anchor = top-left of the same-tile 2x2: neither (x-1,y) nor
            # (x,y-1) carries the same tile.
            left = c.get((x - 1, y))
            up = c.get((x, y - 1))
            if not (left and left["tile"] == t) and not (up and up["tile"] == t):
                anchors.add((x, y))
        bad = []
        for a, b in sorted(anchors):
            t = c[(a, b)]["tile"]
            for nx, ny in ((a + 1, b), (a, b + 1), (a + 1, b + 1)):
                hits = [name for name, dx, dy in SIDES
                        if iswater(c, nx + dx, ny + dy)]
                if hits:
                    bad.append((a, b, t, nx, ny, hits))
        print("%s : %d corner-piece anchors, %d swallow a side-water cell"
              % (path, len(anchors), len(bad)))
        for a, b, t, nx, ny, hits in bad:
            print("   piece tile %d anchor (%d,%d): cell (%d,%d) side water %s"
                  % (t, a, b, nx, ny, ",".join(hits)))


main()
