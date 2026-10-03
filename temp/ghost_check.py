#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Detect ghost cliff cells: same tile + same deduced anchor, duplicate Height.

A multi-cell CliffSet piece may use each sub-cell Height at most once. The old
B-fill copied a sibling foot (e.g. t66/h1) into a third cell, which deduces the
same anchor and repeats Height=1. Also flags any Height outside the footprint's
occupied sub-cells.
"""
import glob
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import analyze_isopack5 as A

# (w, h, occupied sub-cell indices) for CliffSet slot 1..40 (0-based index).
W = [2,1,2,2,2,2,2,1,2,2,2,1,1,1,2,2,2,2,3,3,3,2,2,2,2,1,2,2,1,1,2,2,1,1,1,1,1,1,1,1]
OCC = [
    {0,2,3,5},{0,1},{0,2,3,5},{0,2,3,5},
    {0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1},
    {0,1,2},{0,1,2},{0,1,2},{0},{0},{0},
    {0,1,2,3},{0,1,2,3},{0,1,2,3},{0,1},
    {0,1,4,5},{0,1,4,5},{0,1,4,5},{0,1},
    {0,1},{0,1},{0,1},{0},{0,1,2},{1,2,3},
    {0},{0},{0,1,2},{1,2,3},{0},{0},{0,1},{0,1},{0,1},
    {0},{0},{0},
]
SHORE = 49

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
bad_total = 0
for pat in sys.argv[1:]:
    for p in sorted(glob.glob(os.path.join(ROOT, pat))):
        cells = A.load_map(p)[0]
        groups = {}
        for (x, y), c in cells.items():
            t = c["tile"]
            if not (SHORE <= t < SHORE + 40):
                continue
            idx = t - SHORE
            h = c["bSubTile"]
            w = W[idx]
            ax, ay = x - h % w, y - h // w
            groups.setdefault((t, ax, ay), []).append((x, y, h))
        bad = []
        for key, members in groups.items():
            t, ax, ay = key
            idx = t - SHORE
            heights = [m[2] for m in members]
            dup = sorted({h for h in heights if heights.count(h) > 1})
            out = sorted({h for h in heights if h not in OCC[idx]})
            if dup or out:
                bad.append(("dup/out", key, members, dup, out))
                continue
            # Pieces whose footprint occupies sub-cell 0 must keep the anchor
            # cell alive at h=0 with the same tile. cliff28/32 (mask 0xE) have
            # no h=0 cell, so a live group is just >=1 valid member.
            if 0 in OCC[idx] and 0 not in heights:
                bad.append(("anchorDead", key, members))
        if bad:
            bad_total += len(bad)
            print(os.path.basename(p), "GHOST groups=%d" % len(bad))
            for b in bad[:12]:
                print("  ", b)
print("TOTAL ghost groups:", bad_total)
