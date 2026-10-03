#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import glob
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import analyze_isopack5 as A

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
paths = sorted(glob.glob(os.path.join(ROOT, sys.argv[1] if len(sys.argv) > 1
                                     else "rmg_*.map")))
ORTH = [(0, -1), (1, 0), (0, 1), (-1, 0)]
for p in paths:
    cells = A.load_map(p)[0]
    hits = []
    for (x, y), c in cells.items():
        if not (29 <= c["tile"] <= 48 or 510 <= c["tile"] <= 521):
            continue
        for dx, dy in ORTH:
            q = cells.get((x + dx, y + dy))
            if q is not None and 49 <= q["tile"] <= 88 \
                    and q["level"] - c["level"] >= 2:
                hits.append((x, y, c["tile"], x + dx, y + dy, q["tile"]))
    print("%s orth=%d %s" % (os.path.basename(p), len(hits),
                             hits[:4] if hits else ""))
