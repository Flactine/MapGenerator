#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Cliff wall cell (CliffSet tile, sub-cell z=4 / L8 plateau) orthogonally
adjacent to a ramp cell with a >= 2 level gap. Such a wall stamps across a
ramp band - the defect CliffPieceHitsRamp is meant to prevent.

Ramp cell semantics mirror the C++ guard:
  slope != 0, or tile in CliffRamps[29..48] / RampBase[510..524] /
  SlopeSetPieces (detected empirically as the big ramp faces 384..393; the
  guard uses the runtime index, this checker scans the same window observed
  in this tileset).
"""
import glob
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import analyze_isopack5 as A

SHORE = 49
ORTH = [(0,-1),(1,0),(0,1),(-1,0)]
DIAG = [(1,-1),(1,1),(-1,1),(-1,-1)]
# Single-cell ramp families (CliffRamps, RampBase): only count on orthogonal
# neighbours because their art never reaches a diagonally placed wall.
SINGLE_RAMP_RANGES = [(29, 49), (510, 525)]
# Multi-cell big ramp pieces (SlopeSetPieces): art spans several cells and can
# reach the diagonal screen space of a wall, so they count on all 8 sides.
BIG_RAMP_RANGES = [(384, 394)]

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
total = 0
for pat in sys.argv[1:]:
    paths = sorted(glob.glob(os.path.join(ROOT, pat)))
    for p in paths:
        cells = A.load_map(p)[0]
        hits = []
        for (x, y), c in cells.items():
            t = c["tile"]
            if not (SHORE <= t < SHORE + 40):
                continue
            # wall cell = sub-cell frame z 4: subTile index belonging to a
            # z=4 footprint entry; simplest field signal is Level >= 7.
            if c["level"] < 7:
                continue
            low = top = False
            # Orthogonal sides: any ramp art counts.
            for dx, dy in ORTH:
                q = cells.get((x + dx, y + dy))
                if q is None:
                    continue
                qt = q["tile"]
                is_ramp = (q["slope"] != 0
                           or any(a <= qt < b for a, b in SINGLE_RAMP_RANGES)
                           or any(a <= qt < b for a, b in BIG_RAMP_RANGES))
                if not is_ramp:
                    continue
                if q["level"] <= c["level"] - 2:
                    low = True
                if q["level"] >= c["level"] - 1:
                    top = True
            # Diagonal sides: only big (multi-cell) ramp pieces count.
            for dx, dy in DIAG:
                q = cells.get((x + dx, y + dy))
                if q is None:
                    continue
                qt = q["tile"]
                is_big = any(a <= qt < b for a, b in BIG_RAMP_RANGES)
                if not is_big:
                    continue
                if q["level"] <= c["level"] - 2:
                    low = True
                if q["level"] >= c["level"] - 1:
                    top = True
            # Riding = ramp body below with no same-level ramp-top seam.
            if low and not top:
                hits.append((x, y, t, c["level"]))
        total += len(hits)
        if hits:
            print(os.path.basename(p), "WALL-RAMP=%d" % len(hits))
            for h in hits[:10]:
                print("   riding wall(%d,%d)t%dL%d" % h)
print("TOTAL wall-ramp conflicts:", total)
