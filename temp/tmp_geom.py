#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Measure the REAL TMP geometry of ramp01-10 / slope01-20 / rmpfx pieces."""
import os

TILE_DIR = r"d:\新建文件夹\VSProject\MapGenerator\Tile资源\温和"


def measure(name):
    p = os.path.join(TILE_DIR, name)
    if not os.path.isfile(p):
        return None
    d = open(p, "rb").read()
    bw = int.from_bytes(d[0:4], "little")
    bh = int.from_bytes(d[4:8], "little")
    iw = int.from_bytes(d[8:12], "little")
    ih = int.from_bytes(d[12:16], "little")
    n = bw * bh
    idx = [int.from_bytes(d[16 + 4 * i:20 + 4 * i], "little") for i in range(n)]
    occ = [i for i, o in enumerate(idx) if o != 0]
    # per occupied sub-cell: header x, y
    cells = []
    for i in occ:
        o = idx[i]
        hx = int.from_bytes(d[o:o + 4], "little", signed=True)
        hy = int.from_bytes(d[o + 4:o + 8], "little", signed=True)
        cells.append((i % bw, i // bw, hx, hy))
    return bw, bh, iw, ih, occ, cells


for prefix, lo, hi in [("ramp", 1, 11), ("slope", 1, 21), ("rmpfx", 1, 13)]:
    print("=" * 70)
    for k in range(lo, hi):
        names = ["%s%02d.tem" % (prefix, k)]
        if prefix == "rmpfx":
            for suf in ("", "a", "b", "c"):
                nm = "rmpfx%02d%s.tem" % (k, suf)
                if nm not in names:
                    names.append(nm)
        for nm in names:
            r = measure(nm)
            if r is None:
                continue
            bw, bh, iw, ih, occ, cells = r
            mask = ["."] * (bw * bh)
            for i in occ:
                mask[i] = "#"
            rows = []
            for rrow in range(bh):
                rows.append("".join(mask[rrow * bw:(rrow + 1) * bw]))
            hdr = "; ".join("(%d,%d)x=%d y=%d" % c for c in cells[:8])
            print("%-12s grid=%dx%d img=%dx%d occupied=%d/%d  [%s]  %s"
                  % (nm, bw, bh, iw, ih, len(occ), bw * bh, " | ".join(rows), hdr))
