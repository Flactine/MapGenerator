#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Find land holes enclosed by water.  python holes.py <map> [<map> ...]

A hole is a group of non-water cells connected by 4-neighbours that cannot
reach the map's bounding border (water forms a closed ring around it). Each
hole's cell count is printed.
"""
import sys
from collections import deque

sys.path.insert(0, ".")
import analyze_isopack5 as A

WATER = set(range(314, 328))
N4 = [(1, 0), (-1, 0), (0, 1), (0, -1)]


def main():
    for path in sys.argv[1:]:
        c, _a, _b = A.load_map(path)
        xs = sorted({x for x, _ in c})
        ys = sorted({y for _, y in c})
        x0, x1, y0, y1 = min(xs), max(xs), min(ys), max(ys)
        land = {p for p, v in c.items() if v["tile"] not in WATER}
        seen = set()
        holes = []
        outside = 0
        for start in land:
            if start in seen:
                continue
            q = deque([start])
            seen.add(start)
            group = set()
            reaches = False
            while q:
                x, y = q.popleft()
                group.add((x, y))
                if x in (x0, x1) or y in (y0, y1):
                    reaches = True
                for dx, dy in N4:
                    n = (x + dx, y + dy)
                    if n in land and n not in seen:
                        seen.add(n)
                        q.append(n)
            if reaches:
                outside += len(group)
            else:
                holes.append(group)
        print("%s : %d enclosed land holes, outside land %d cells"
              % (path, len(holes), outside))
        for g in sorted(holes, key=len):
            cells = sorted(g)
            print("   hole %d cells: %s" % (len(g), cells[:12]))


main()
