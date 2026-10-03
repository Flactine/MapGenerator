#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Find one-cell holes inside a continuous cliff facade row.

    python wall_gap.py <map> [<map> ...]

The 4-level elevation step itself can be legitimately covered by a multi-cell
CliffSet piece one row ahead (its z=0 cells sit on the lower Level beside the
upper rim), so level_gap.py cannot see the failure where two neighbouring cliff
pieces fail to stitch: a lower-Level placeholder (tile 0xFFFF) sits in the
facade row with CliffSet cells immediately on its W, E and N sides.  Such a
cell is surrounded on all facade sides by cliff pieces yet holds no piece of
its own - the visible wall gap.
"""
import sys

sys.path.insert(0, ".")
import analyze_isopack5 as A


def is_cliff(t):
    return 49 <= t <= 88


def run(path):
    cells, _, _ = A.load_map(path)
    holes = []
    for (x, y), c in cells.items():
        if c["tile"] != 65535:
            continue
        w = cells.get((x - 1, y))
        e = cells.get((x + 1, y))
        n = cells.get((x, y - 1))
        if w is None or e is None or n is None:
            continue
        if not (is_cliff(w["tile"]) and is_cliff(e["tile"])):
            continue
        if w["level"] != c["level"] or e["level"] != c["level"]:
            continue
        if not is_cliff(n["tile"]):
            continue
        # Must sit at the cliff foot: at least one of the 8 neighbours is a
        # full level (4) higher.  A placeholder on a same-Level plateau top
        # (all neighbours equal) is not a facade gap.
        foot = False
        for dx in (-1, 0, 1):
            for dy in (-1, 0, 1):
                if dx == 0 and dy == 0:
                    continue
                q = cells.get((x + dx, y + dy))
                if q is not None and q["level"] == c["level"] + 4:
                    foot = True
        if not foot:
            continue
        holes.append((x, y, c["level"],
                      w["tile"], n["tile"], e["tile"]))
    print("=== %s" % path)
    print("   facade holes (placeholder wedged between cliff pieces): %d"
          % len(holes))
    for h in holes:
        print("      (%d,%d) L%d  W=t%d N=t%d E=t%d" % h)
    return holes


for p in sys.argv[1:]:
    run(p)
