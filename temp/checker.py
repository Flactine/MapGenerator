#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Count diagonal checkerboard contacts along the water boundary.

    python checker.py <map> [<map> ...]

A 2x2 window is a diagonal contact when two diagonally opposite cells are
water and the other two are land:

    W .      . W      (W = water, L = land tile)
    . W  or  W .

Such spots join at one vertex only. They are split into:
  joined : the two land cells end up under the SAME shore tile (one piece
           wraps the vertex, drawn correctly);
  split  : they end up under DIFFERENT tiles (or one is bare) - the bend no
           longer belongs to one piece.
"""
import sys

sys.path.insert(0, ".")
import analyze_isopack5 as A

WATER = set(range(314, 328))
SHORE = set(range(89, 131))


def w(c, x, y):
    n = c.get((x, y))
    return bool(n and n["tile"] in WATER)


def tile(c, x, y):
    n = c.get((x, y))
    return None if n is None else n["tile"]


def main():
    for path in sys.argv[1:]:
        c, _a, _b = A.load_map(path)
        xs = sorted({x for x, _ in c})
        ys = sorted({y for _, y in c})
        hits = []
        for y in range(min(ys), max(ys)):
            for x in range(min(xs), max(xs)):
                a = w(c, x, y)
                b = w(c, x + 1, y)
                d = w(c, x, y + 1)
                e = w(c, x + 1, y + 1)
                if a and e and not b and not d:
                    kind = r"\\"
                elif b and d and not a and not e:
                    kind = "/"
                else:
                    continue
                # the two land cells: (x+1,y) & (x,y+1)
                t1 = tile(c, x + 1, y)
                t2 = tile(c, x, y + 1)
                same = (t1 == t2 and t1 in SHORE)
                hits.append((x, y, kind, t1, t2, same))
        joined = sum(1 for h in hits if h[5])
        print("%s : %d diagonal checkerboard contacts, %d joined / %d split"
              % (path, len(hits), joined, len(hits) - joined))
        for x, y, kind, t1, t2, same in hits:
            if not same:
                print("    SPLIT at (%d,%d) %s  land tiles %d / %d"
                      % (x, y, kind, t1, t2))


main()
