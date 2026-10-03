#!/usr/bin/env python3
"""Find 4-level elevation steps that carry no cliff-family tile on either side.

    python level_gap.py <map> [<map> ...]

A neighbour pair whose Levels differ by 4 is a cliff step.  In the retail
generator such a seam is always walled by a CliffSet (49..88) / WaterCliff
(148..175) / CliffRamps (384..393) cell on at least one side.  Pairs where both
sides are ordinary terrain (ClearTile / RampBase 29..48 / RampSmooth 510..521 /
...) are the "height difference without a cliff transition" the report is about.
"""
import sys
from collections import Counter

sys.path.insert(0, ".")
import analyze_isopack5 as A

DIRS = [(0, -1), (1, -1), (1, 0), (1, 1)]


def is_cliff_family(t):
    return (49 <= t <= 88) or (148 <= t <= 175) or (384 <= t <= 393)


def fam(t):
    if t == 65535:
        return "gap"
    if t in (0, 1):
        return "clear"
    if 29 <= t <= 48:
        return "rampBase"
    if 510 <= t <= 521:
        return "rampSmooth"
    if 49 <= t <= 88:
        return "cliff"
    if 148 <= t <= 175:
        return "wcliff"
    if 384 <= t <= 393:
        return "cliffRamp"
    return "other"


def run(path):
    cells, _, _ = A.load_map(path)
    bare = []
    kinds = Counter()
    for (x, y), c in cells.items():
        for dx, dy in DIRS:
            n = cells.get((x + dx, y + dy))
            if n is None:
                continue
            d = abs(n["level"] - c["level"])
            if d != 4:
                continue
            if is_cliff_family(c["tile"]) or is_cliff_family(n["tile"]):
                continue
            bare.append((x, y, c["tile"], c["level"],
                         x + dx, y + dy, n["tile"], n["level"]))
            kinds[(fam(c["tile"]), fam(n["tile"]))] += 1
    print("=== %s" % path)
    print("   4-level steps with no cliff tile on either side: %d" % len(bare))
    for k, v in kinds.most_common(10):
        print("      %-11s <-> %-11s %d" % (k[0], k[1], v))
    for b in bare[:25]:
        print("      (%d,%d t%d L%d) -- (%d,%d t%d L%d)"
              % (b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7]))
    return bare


for p in sys.argv[1:]:
    run(p)