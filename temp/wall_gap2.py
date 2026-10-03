#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Like wall_gap.py but treat BOTH tile 0 and 0xFFFF as empty placeholder."""
import sys

sys.path.insert(0, ".")
import analyze_isopack5 as A


def is_cliff(t):
    return 49 <= t <= 88


def run(path):
    cells, _, _ = A.load_map(path)
    holes = []
    for (x, y), c in cells.items():
        if c["tile"] not in (0, 65535):
            continue
        w = cells.get((x - 1, y))
        e = cells.get((x + 1, y))
        n = cells.get((x, y - 1))
        if w is None or e is None or n is None:
            continue
        if not (is_cliff(w["tile"]) and is_cliff(e["tile"]) and is_cliff(n["tile"])):
            continue
        if w["level"] != c["level"] or e["level"] != c["level"]:
            continue
        foot = any(cells.get((x + dx, y + dy)) is not None
                   and cells[(x + dx, y + dy)]["level"] == c["level"] + 4
                   for dx in (-1, 0, 1) for dy in (-1, 0, 1)
                   if (dx, dy) != (0, 0))
        if not foot:
            continue
        holes.append((x, y, c["level"], c["tile"],
                      w["tile"], n["tile"], e["tile"]))
    print("=== %s" % path)
    print("   facade holes (t0/0xFFFF between cliff pieces): %d" % len(holes))
    for h in holes[:20]:
        print("      (%d,%d) L%d t=%d W=t%d N=t%d E=t%d" % h)
    return holes


for p in sys.argv[1:]:
    run(p)
