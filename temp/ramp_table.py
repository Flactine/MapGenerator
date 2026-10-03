#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Extract real footprint {w,h,mask,z[],slope[]} of ramp01-10 (TileSet0025)."""
import os, struct

TD = r"d:\新建文件夹\VSProject\MapGenerator\Tile资源\温和"

for k in range(1, 11):
    nm = "ramp%02d.tem" % k
    d = open(os.path.join(TD, nm), "rb").read()
    bw, bh = struct.unpack_from("<ii", d, 0)
    idx = [struct.unpack_from("<I", d, 16 + 4 * i)[0] for i in range(bw * bh)]
    mask = 0
    zs, sl, occ = [], [], 0
    for i in range(bw * bh):
        col, row = i % bw, i // bw
        if idx[i]:
            mask |= 1 << i
            occ += 1
            zs.append(d[idx[i] + 0x28])
            sl.append(d[idx[i] + 0x2A])
    # visual
    grid = []
    for row in range(bh):
        line = ""
        for col in range(bw):
            line += "#" if (mask >> (row * bw + col)) & 1 else "."
        grid.append(line)
    print("{ // %s  %dx%d occ=%d  [%s]" % (nm, bw, bh, occ, " | ".join(grid)))
    print("  %d, %d, 0x%XULL, { %s }," % (bw, bh, mask, ", ".join(map(str, zs))))
    print("  // slope per occupied cell: { %s }" % ", ".join(map(str, sl)))
    print("},")
