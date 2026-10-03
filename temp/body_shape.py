#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Print the shape of the water body containing a given cell.

    python body_shape.py <map> <x> <y> [cellw]

8-neighbour body. Prints its bbox as '#'=water '.'=land, and an ASCII line for
each row with a ruler every `cellw` columns (default 1).
"""
import sys
from collections import deque

sys.path.insert(0, ".")
import analyze_isopack5 as A

WATER = set(range(314, 328))
N8 = [(dx, dy) for dx in (-1, 0, 1) for dy in (-1, 0, 1) if dx or dy]


def main():
    path = sys.argv[1]
    sx, sy = int(sys.argv[2]), int(sys.argv[3])
    c, _a, _b = A.load_map(path)
    water = {p for p, v in c.items() if v["tile"] in WATER}
    q = deque([(sx, sy)])
    seen = {(sx, sy)}
    while q:
        x, y = q.popleft()
        for dx, dy in N8:
            n = (x + dx, y + dy)
            if n in water and n not in seen:
                seen.add(n)
                q.append(n)
    xs = sorted({x for x, _ in seen})
    ys = sorted({y for _, y in seen})
    print("body cells %d  bbox X %d..%d (%d)  Y %d..%d (%d)"
          % (len(seen), min(xs), max(xs), max(xs) - min(xs) + 1,
             min(ys), max(ys), max(ys) - min(ys) + 1))
    x0, x1, y0, y1 = min(xs), max(xs), min(ys), max(ys)
    for y in range(y0, y1 + 1):
        line = "".join("#" if (x, y) in seen else "."
                       for x in range(x0, x1 + 1))
        print("y=%-4d|%s|" % (y, line))


main()
