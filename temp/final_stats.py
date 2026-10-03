#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import glob
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import analyze_isopack5 as A

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
for pat in sys.argv[1:]:
    tot = t0 = ffff = 0
    for p in sorted(glob.glob(os.path.join(ROOT, pat))):
        cells = A.load_map(p)[0]
        tot += len(cells)
        for c in cells.values():
            if c["tile"] == 0:
                t0 += 1
            if c["tile"] == 65535:
                ffff += 1
    print("%s  maps=%d cells=%d t0=%d(%.2f%%) FFFF=%d"
          % (pat, len(glob.glob(os.path.join(ROOT, pat))), tot, t0,
             100.0 * t0 / max(tot, 1), ffff))
