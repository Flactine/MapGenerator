#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""CliffSet piece integrity check on final maps.

For every CliffSet cell (tile 49..88) its Height byte is the sub-cell index h
inside the piece image; the piece origin is (x-col, y-row) and every occupied
footprint cell must carry the SAME tile. A foreign CliffSet/CliffRamp tile
inside the footprint means a swallowed / half-rendered piece.
"""
import glob
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import analyze_isopack5 as A

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# slot 1..40 -> (w, h, occupied mask), copied from kCliffFootprints
FP = [
    (2, 3, 0x2D), (1, 2, 0x3), (2, 3, 0x2D), (2, 3, 0x2D),
    (2, 2, 0xF), (2, 2, 0xF), (2, 2, 0xF), (1, 2, 0x3),
    (2, 2, 0x7), (2, 2, 0x7), (2, 2, 0x7), (1, 1, 0x1),
    (1, 1, 0x1), (1, 1, 0x1), (2, 2, 0xF), (2, 2, 0xF),
    (2, 2, 0xF), (2, 1, 0x3), (3, 2, 0x33), (3, 2, 0x33),
    (3, 2, 0x33), (2, 1, 0x3), (2, 1, 0x3), (2, 1, 0x3),
    (1, 1, 0x1), (2, 2, 0x7), (2, 2, 0xE), (1, 1, 0x1),
    (1, 1, 0x1), (2, 2, 0x7), (2, 2, 0xE), (1, 1, 0x1),
    (1, 1, 0x1), (1, 1, 0x1), (1, 2, 0x3), (1, 2, 0x3),
    (1, 2, 0x3), (1, 1, 0x1), (1, 1, 0x1), (1, 1, 0x1),
]
CLIFF_LO, CLIFF_HI = 49, 88
CLIFF_FAM = lambda t: 49 <= t <= 88 or 384 <= t <= 393 or 428 <= t <= 430 \
    or 432 <= t <= 434


def check_map(path):
    cells = A.load_map(path)[0]
    seen_origins = set()
    bad = []
    for (x, y), c in cells.items():
        t = c["tile"]
        if not (CLIFF_LO <= t <= CLIFF_HI):
            continue
        slot = t - CLIFF_LO          # 0-based
        w, hgt, mask = FP[slot]
        h = c["bSubTile"]
        col, row = h % w, h // w
        ox, oy = x - col, y - row
        key = (ox, oy, t)
        if key in seen_origins:
            continue
        seen_origins.add(key)
        for rr in range(hgt):
            for cc in range(w):
                if not ((mask >> (rr * w + cc)) & 1):
                    continue
                q = cells.get((ox + cc, oy + rr))
                if q is None:
                    continue
                qt = q["tile"]
                if qt != t and CLIFF_FAM(qt):
                    bad.append((ox, oy, t, cc, rr, ox + cc, oy + rr, qt))
    return bad


def main():
    paths = sys.argv[1:] or sorted(
        glob.glob(os.path.join(ROOT, "rmg_*.map")))
    total_bad = 0
    for p in paths:
        bad = check_map(p)
        if bad:
            total_bad += len(bad)
            print(os.path.basename(p), "SWALLOWED=%d" % len(bad))
            for b in bad[:10]:
                print("   origin=(%d,%d) t%d foreign at(%d,%d)=t%d"
                      % (b[0], b[1], b[2], b[5], b[6], b[7]))
    if not total_bad:
        print("all maps: piece integrity OK (%d maps)" % len(paths))


if __name__ == "__main__":
    main()
