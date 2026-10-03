#!/usr/bin/env python3
"""What does a water tile touch?  Usage: python analyze_coast.py <map> ...

For every cell whose tile is in the WaterSet family (314..327) look at its
eight in-diamond neighbours and count the tiles that are NOT water.  The
resulting census tells which families line the water: ShorePieces (89..130),
ClearToGreenLat (494..509), GreenTile (493), Clear (0), bare 0xFFFF, ...
"""
import sys
from collections import Counter

sys.path.insert(0, ".")
import analyze_isopack5 as A

WATER_LO, WATER_HI = 314, 327

FAMILIES = [
    ("Clear 0", 0, 0), ("blank 1", 1, 1), ("RampBase 29-48", 29, 48),
    ("CliffSet 49-88", 49, 88), ("Shore 89-130", 89, 130),
    ("Ruff 131", 131, 131), ("clat 132-147", 132, 147),
    ("WCliff 148-175", 148, 175), ("Water 314-327", 314, 327),
    ("dlat 419-434", 419, 434), ("plat 463-478", 463, 478),
    ("Green 493", 493, 493), ("glat 494-509", 494, 509),
    ("Rmpfx 510-521", 510, 521), ("Pvclr 534", 534, 534),
    ("0xFFFF", 65535, 65535),
]


def fam(t):
    for name, lo, hi in FAMILIES:
        if lo <= t <= hi:
            return name
    return "other"


for path in sys.argv[1:]:
    cells, _secs, _n = A.load_map(path)

    # whole-map family census: does ANY tile of a given family survive?
    whole = Counter()
    for c in cells.values():
        whole[fam(c["tile"])] += 1

    raw = Counter()
    fams = Counter()
    water = 0
    for (x, y), c in cells.items():
        t = c["tile"]
        if not (WATER_LO <= t <= WATER_HI):
            continue
        water += 1
        for dx, dy in A.DIRS:
            n = cells.get((x + dx, y + dy))
            if n is None:
                continue
            nt = n["tile"]
            if WATER_LO <= nt <= WATER_HI:
                continue
            raw[nt] += 1
            fams[fam(nt)] += 1
    print("=" * 70)
    print(path)
    print("whole-map family census (0 = family entirely absent):")
    for name, lo, hi in FAMILIES:
        print("   %-18s %d" % (name, whole.get(name, 0)))
    print("water cells: %d" % water)
    print("water->non-water edges by FAMILY:")
    for name, k in fams.most_common():
        print("   %-18s %d" % (name, k))
    print("top raw neighbour tiles:")
    for t, k in raw.most_common(20):
        print("   tile %-6d x%d   (%s)" % (t, k, fam(t)))