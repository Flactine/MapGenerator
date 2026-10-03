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
    tot = cliff = ramp = t0 = 0
    for p in paths:
        cells = A.load_map(p)[0]
        tot += len(cells)
        for c in cells.values():
            t = c["tile"]
            if 49 <= t < 89:
                cliff += 1
            if c["slope"] != 0 or (29 <= t < 49) or (510 <= t < 525) \
               or (384 <= t < 394):
                ramp += 1
            if t == 0:
                t0 += 1
    n = len(paths)
    print("%s n=%2d cliff/map=%.0f ramp/map=%.0f t0/map=%.0f (%.2f%%)"
          % (pat, n, cliff / n, ramp / n, t0 / n, 100.0 * t0 / max(tot, 1)))
