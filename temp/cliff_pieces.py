#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Verify every CliffSet/WaterCliff multi-cell piece in a map against the REAL
TMP geometry measured from cliffNN.tem / wcliffNN.tem.

A piece is valid when, for every cell carrying a cliff-family tile, all
occupied cells of that TMP (relative to the anchor inferred from Height)
carry the same tile with the matching Height. Reports BROKEN anchors.
"""
import os, struct, sys
from collections import Counter
sys.path.insert(0, ".")
import analyze_isopack5 as A

MAP = sys.argv[1] if len(sys.argv) > 1 else r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20260930_230401.map"
TD = r"d:\新建文件夹\VSProject\MapGenerator\Tile资源\温和"


def geom(prefix, k):
    p = os.path.join(TD, "%s%02d.tem" % (prefix, k))
    if not os.path.isfile(p):
        return None
    d = open(p, "rb").read()
    bw, bh = struct.unpack_from("<ii", d, 0)
    idx = [struct.unpack_from("<I", d, 16 + 4 * i)[0] for i in range(bw * bh)]
    occ = set()
    for i, o in enumerate(idx):
        if o:
            occ.add((i % bw, i // bw))
    return bw, bh, occ


FAM = [(49, 40, "cliff"), (148, 28, "wcliff")]
GEOM = {}
for base, n, pre in FAM:
    for k in range(1, n + 1):
        g = geom(pre, k)
        if g:
            GEOM[base + k - 1] = g

cells, _, _ = A.load_map(MAP)

bad = []
ok_pieces = 0
seen_anchor = set()
for (x, y), c in cells.items():
    t = c["tile"]
    if t not in GEOM:
        continue
    w, h, occ = GEOM[t]
    hgt = c["height"]
    col, row = hgt % w, hgt // w
    if (col, row) not in occ:
        bad.append(("HEIGHT-OUT-OF-FRAME", x, y, t, hgt, w, h))
        continue
    ax, ay = x - col, y - row
    if (ax, ay, t) in seen_anchor:
        continue
    seen_anchor.add((ax, ay, t))
    miss = []
    for (cc, rr) in occ:
        q = cells.get((ax + cc, ay + rr))
        want_h = cc + rr * w
        if q is None or q["tile"] != t or q["height"] != want_h:
            miss.append((ax + cc, ay + rr, want_h,
                         None if q is None else (q["tile"], q["height"])))
    if miss:
        bad.append(("BROKEN", ax, ay, t, len(occ), miss))
    else:
        ok_pieces += 1

print("map:", os.path.basename(MAP))
print("intact cliff/wcliff pieces: %d   broken anchors: %d" % (ok_pieces, len(bad)))
print("break kinds:", Counter(b[0] for b in bad))
for b in bad[:60]:
    if b[0] == "BROKEN":
        _, ax, ay, t, n, miss = b
        pre = "cliff" if 49 <= t <= 88 else "wcliff"
        slot = t - (49 if pre == "cliff" else 148) + 1
        print("  %s%02d anchor(%d,%d) occ=%d missing %d:" % (pre, slot, ax, ay, n, len(miss)))
        for mx, my, wh, got in miss:
            print("      (%d,%d) want h%d got %s" % (mx, my, wh, got))
    else:
        print("  %s tile=%d at (%d,%d) height=%d frame=%dx%d" %
              (b[0], b[3], b[1], b[2], b[4], b[5], b[6]))
