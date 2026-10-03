#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Simulate the 8-neighbour version of CliffPieceHitsRamp on FINAL maps.

Group CliffSet cells into pieces (same tile + deduced anchor via Height), then
for every piece whose wall cells (Level >= 7) have ANY 8-neighbour ramp cell
with a level gap >= 2, mark the piece as blocked. Report blocked piece counts
and the tiles involved, to gauge over-blocking before changing the C++ guard.
"""
import glob
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import analyze_isopack5 as A

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
DIRS8 = [(0,-1),(1,-1),(1,0),(1,1),(0,1),(-1,1),(-1,0),(-1,-1)]

def is_ramp(t, s):
    return s != 0 or (29 <= t < 49) or (510 <= t < 525) or (384 <= t < 394)

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
for pat in sys.argv[1:]:
    paths = sorted(glob.glob(os.path.join(ROOT, pat)))
    for p in paths:
        cells = A.load_map(p)[0]
        pieces = {}
        for (x, y), c in cells.items():
            t = c["tile"]
            if not (SHORE <= t < SHORE + 40):
                continue
            idx = t - SHORE
            h = c["bSubTile"]
            if h not in OCC[idx]:
                continue
            w = W[idx]
            ax, ay = x - h % w, y - h // w
            pieces.setdefault((t, ax, ay), []).append((x, y, c))
        blocked = []
        for (t, ax, ay), members in pieces.items():
            hit = None
            for x, y, c in members:
                if c["level"] < 7:
                    continue
                for dx, dy in DIRS8:
                    q = cells.get((x + dx, y + dy))
                    if q is not None and is_ramp(q["tile"], q["slope"]) \
                            and c["level"] - q["level"] >= 2:
                        hit = (x, y, q["tile"], q["level"], dx, dy)
                        break
                if hit:
                    break
            if hit:
                blocked.append((t, ax, ay, len(members), hit))
        name = os.path.basename(p)
        if blocked:
            tiles = sorted({b[0] for b in blocked})
            cells_lost = sum(b[3] for b in blocked)
            print("%s blockedPieces=%d cells=%d tiles=%s"
                  % (name, len(blocked), cells_lost, tiles))
            for b in blocked[:12]:
                print("    t%d anchor(%d,%d) members=%d hit=%s"
                      % (b[0], b[1], b[2], b[3], b[4]))
        else:
            print("%s blockedPieces=0" % name)
