#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import glob
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import analyze_isopack5 as A

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
for pat in sys.argv[1:]:
    paths = sorted(glob.glob(os.path.join(ROOT, pat)))
    rows = []
    for p in paths:
        cells = A.load_map(p)[0]
        n = len(cells)
        t0 = sum(1 for c in cells.values() if c["tile"] == 0)
        ffff = sum(1 for c in cells.values() if c["tile"] == 65535)
        rows.append((100.0 * t0 / n, ffff))
    if rows:
        print("%s n=%2d  t0%% avg=%.2f min=%.2f max=%.2f | FFFF/map avg=%.0f"
              % (pat, len(rows),
                 sum(r[0] for r in rows) / len(rows),
                 min(r[0] for r in rows), max(r[0] for r in rows),
                 sum(r[1] for r in rows) / len(rows)))
