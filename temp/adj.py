#!/usr/bin/env python3
"""Count how often a CliffSet cell touches each other family.

    python adj.py <map> [<map> ...]

For every cell carrying a CliffSet tile (49..88) or WaterCliff (148..175) the
eight neighbours are tallied by family.  A port that places its normal terrain
ramps (RampBase 29..48 / RampSmooth 510..521) hard against a cliff wall shows a
large cliff<->rampB/rampS count; the retail generator instead uses the
CliffRamps family (384..393) for that seam.
"""
import sys
from collections import Counter

sys.path.insert(0, ".")
import analyze_isopack5 as A

DIRS = [(0, -1), (1, -1), (1, 0), (1, 1), (0, 1), (-1, 1), (-1, 0), (-1, -1)]


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
    touch = Counter()
    pairs = Counter()
    for (x, y), c in cells.items():
        f = fam(c["tile"])
        if f not in ("cliff", "wcliff", "cliffRamp"):
            continue
        for dx, dy in DIRS:
            n = cells.get((x + dx, y + dy))
            if n is None:
                continue
            g = fam(n["tile"])
            touch[(f, g)] += 1
            if f in ("cliff", "wcliff") and g in ("rampBase", "rampSmooth"):
                pairs[(f, g, c["tile"], n["tile"])] += 1
    print("=== %s" % path)
    for k in sorted(touch):
        if k[1] in ("rampBase", "rampSmooth", "cliffRamp", "cliff", "wcliff", "gap"):
            print("   %-10s <-> %-11s %d" % (k[0], k[1], touch[k]))
    print("   cliff<->terrain-ramp detail (top 20):")
    for (f, g, a, b), n in pairs.most_common(20):
        print("      %s(t%d) vs %s(t%d): %d" % (f, a, g, b, n))


for p in sys.argv[1:]:
    run(p)