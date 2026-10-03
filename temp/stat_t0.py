#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import sys
sys.path.insert(0, ".")
import analyze_isopack5 as A

for p in sys.argv[1:]:
    cells = A.load_map(p)[0]
    vals = list(cells.values())
    t0 = sum(1 for c in vals if c["tile"] == 0)
    ff = sum(1 for c in vals if c["tile"] == 65535)
    seam = 0
    for (x, y), c in cells.items():
        if c["tile"] != 65535:
            continue
        for dx in (-1, 0, 1):
            for dy in (-1, 0, 1):
                if dx == 0 and dy == 0:
                    continue
                q = cells.get((x + dx, y + dy))
                if q is not None and q["level"] == c["level"] + 4:
                    seam += 1
                    break
            else:
                continue
            break
    print("%-40s t0=%-5d FFFF=%-5d seamFFFF=%d" % (p, t0, ff, seam))
