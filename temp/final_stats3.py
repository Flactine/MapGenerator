#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import glob
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import analyze_isopack5 as A

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ORTH = [(0, -1), (1, 0), (0, 1), (-1, 0)]
for pat in sys.argv[1:]:
    paths = sorted(glob.glob(os.path.join(ROOT, pat)))
    tot = t0 = near = 0
    for p in paths:
        cells = A.load_map(p)[0]
        tot += len(cells)
        for (x, y), c in cells.items():
            if c["tile"] != 0:
                continue
            t0 += 1
            for dx, dy in ORTH:
                q = cells.get((x + dx, y + dy))
                if q is not None and (49 <= q["tile"] <= 88
                                      or 29 <= q["tile"] <= 48):
                    near += 1
                    break
    print("%s t0=%d nearCliff/Ramp=%d (%.2f%% of t0)"
          % (pat, t0, near, 100.0 * near / max(t0, 1)))
