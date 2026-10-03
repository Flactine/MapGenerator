#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""For every cliff02 (tile 50, NE-only, footprint {1,2}) origin cell (x,y),
identified by t50 at (x,y) with t50 at (x,y+1), inspect the SW diagonal cell
(x-1,y+1) - the exact position that stays empty in the port. Report its tile.
"""
import sys
import collections

sys.path.insert(0, ".")
import analyze_isopack5 as A

T50 = 50

for p in sys.argv[1:]:
    cells, _, _ = A.load_map(p)
    sw_tiles = collections.Counter()
    examples = collections.defaultdict(list)
    n = 0
    for (x, y), c in cells.items():
        if c["tile"] != T50:
            continue
        south = cells.get((x, y + 1))
        if south is None or south["tile"] != T50:
            continue
        n += 1
        sw = cells.get((x - 1, y + 1))
        t = sw["tile"] if sw else -1
        sw_tiles[t] += 1
        if len(examples[t]) < 6:
            examples[t].append((x, y, sw["level"] if sw else -1))
    print("=== %s" % p)
    print("   cliff02 origin pieces: %d" % n)
    for t, cnt in sw_tiles.most_common():
        print("   SW-diag tile=%-6d count=%-4d %s"
              % (t, cnt, examples[t][:4]))
