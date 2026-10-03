#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Water-body connectivity and minimum gap between distinct bodies.

    python body_gap.py <map> [<map> ...]

Water tiles are grouped into bodies with 8-neighbour connectivity (diagonal
contact joins them, since such cells are one shore piece). For every pair of
distinct bodies the minimum coordinate Manhattan gap between water cells is
recorded. Small gaps (2..5) are where two separately-smoothed bodies fight
over the same land cells.
"""
import sys
from collections import deque

sys.path.insert(0, ".")
import analyze_isopack5 as A

WATER = set(range(314, 328))
N8 = [(dx, dy) for dx in (-1, 0, 1) for dy in (-1, 0, 1) if dx or dy]


def bodies(cells):
    water = {p for p, v in cells.items() if v["tile"] in WATER}
    seen = set()
    out = []
    for start in water:
        if start in seen:
            continue
        q = deque([start])
        seen.add(start)
        body = set()
        while q:
            x, y = q.popleft()
            body.add((x, y))
            for dx, dy in N8:
                n = (x + dx, y + dy)
                if n in water and n not in seen:
                    seen.add(n)
                    q.append(n)
        out.append(body)
    return out


def main():
    for path in sys.argv[1:]:
        cells, _a, _b = A.load_map(path)
        bs = bodies(cells)
        print("%s : %d water bodies" % (path, len(bs)))
        for i, b in enumerate(bs):
            print("   body %d: %d cells" % (i, len(b)))
        gaps = []
        for i in range(len(bs)):
            for j in range(i + 1, len(bs)):
                g = min(abs(x1 - x2) + abs(y1 - y2)
                        for x1, y1 in bs[i] for x2, y2 in bs[j])
                gaps.append((g, i, j))
        for g, i, j in sorted(gaps):
            flag = "  <-- NARROW" if g <= 5 else ""
            print("   gap body %d - body %d = %d%s" % (i, j, g, flag))


main()
