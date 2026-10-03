#!/usr/bin/env python3
"""Tile-family census of one or more maps, condensed."""
import sys
sys.path.insert(0, ".")
import analyze_isopack5 as A
from collections import Counter

FAM = [("Clear 0", 0, 0), ("blank 1", 1, 1), ("RampBase 29-48", 29, 48),
       ("CliffSet 49-88", 49, 88), ("Shore 89-130", 89, 130),
       ("Ruff 131", 131, 131), ("clat 132-147", 132, 147),
       ("WCliff 148-175", 148, 175), ("Water 314-327", 314, 327),
       ("sandy 418", 418, 418), ("dlat 419-434", 419, 434),
       ("plat 463-478", 463, 478), ("Green 493", 493, 493),
       ("glat 494-509", 494, 509), ("Rmpfx 510-521", 510, 521),
       ("Pvclr 534", 534, 534)]


def fam(t):
    if t == 0xFFFF:
        return "0xFFFF"
    for n, lo, hi in FAM:
        if lo <= t <= hi:
            return n
    return "other"


for p in sys.argv[1:]:
    cells, _s, _n = A.load_map(p)
    c = Counter(fam(v["tile"]) for v in cells.values())
    tot = sum(c.values())
    print("%s  (%d cells)" % (p, tot))
    for n, _lo, _hi in FAM:
        v = c.get(n, 0)
        if v:
            print("    %-16s %6d  %5.1f%%" % (n, v, 100.0 * v / tot))
    v = c.get("0xFFFF", 0)
    print("    %-16s %6d  %5.1f%%" % ("0xFFFF", v, 100.0 * v / tot))
    print("    %-16s %6d  %5.1f%%" % ("other", c.get("other", 0),
                                      100.0 * c.get("other", 0) / tot))
