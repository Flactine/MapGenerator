#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import sys
sys.path.insert(0, ".")
import analyze_isopack5 as A

DIRS = [(dx, dy) for dx in (-1, 0, 1) for dy in (-1, 0, 1)
        if (dx, dy) != (0, 0)]

for p in sys.argv[1:]:
    cells = A.load_map(p)[0]
    hits = []
    for (x, y), c in cells.items():
        if c["tile"] != 65535:
            continue
        for dx, dy in DIRS:
            q = cells.get((x + dx, y + dy))
            if q is not None and 384 <= q["tile"] <= 393:
                hits.append((x, y, c["level"], x + dx, y + dy,
                             q["tile"], q["level"]))
                break
    print("%s FFFF-next-to-rampSet=%d %s" % (p, len(hits), hits[:8]))
