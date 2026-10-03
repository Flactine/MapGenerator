#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Two INDEPENDENT cliff pieces colliding: orthogonal CliffSet neighbours with
a 4-level difference that belong to DIFFERENT tile slots (a single multi-cell
piece always carries the same index, so equal index = intra-piece, fine)."""
import sys
sys.path.insert(0, ".")
import analyze_isopack5 as A

ORTH = [(0, -1, "N"), (1, 0, "E"), (0, 1, "S"), (-1, 0, "W")]

for p in sys.argv[1:]:
    cells = A.load_map(p)[0]
    hits = []
    for (x, y), c in cells.items():
        if not (49 <= c["tile"] <= 88):
            continue
        for dx, dy, dn in ORTH:
            q = cells.get((x + dx, y + dy))
            if q is None or not (49 <= q["tile"] <= 88):
                continue
            if q["tile"] == c["tile"]:
                continue  # same multi-cell piece
            if q["level"] - c["level"] >= 4:
                hits.append((x, y, c["tile"], c["level"],
                             dn, x + dx, y + dy, q["tile"], q["level"]))
            elif c["level"] - q["level"] >= 4:
                hits.append((x + dx, y + dy, q["tile"], q["level"],
                             dn + "i", x, y, c["tile"], c["level"]))
    uniq = sorted(set(hits))
    print("%s different-piece orth 4-level: %d" % (p, len(uniq)))
    for h in uniq[:12]:
        print("   ", h)
