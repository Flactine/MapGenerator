#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Dump 52-byte sub-cell headers to locate the z (frame+0x28) field,
then extract real geometry of ramp01-10 for the footprint table."""
import os, struct

TD = r"d:\新建文件夹\VSProject\MapGenerator\Tile资源\温和"


def load(name):
    d = open(os.path.join(TD, name), "rb").read()
    bw, bh = struct.unpack_from("<ii", d, 0)
    idx = [struct.unpack_from("<I", d, 16 + 4 * i)[0] for i in range(bw * bh)]
    return d, bw, bh, idx


# ---- locate the z field on cliff01 (known footprint 2x3 mask 0x2D, z=4,0,4,0)
d, bw, bh, idx = load("cliff01.tem")
print("cliff01 %dx%d" % (bw, bh))
occ = [(i % bw, i // bw, idx[i]) for i in range(bw * bh) if idx[i]]
for col, row, off in occ:
    hdr = d[off:off + 52]
    print("cell(%d,%d):" % (col, row), " ".join("%02x" % b for b in hdr))

# scan each byte offset: values across the 4 occupied cells, looking for 4,0,4,0
print("\nbyte offsets whose value sequence is (4,0,4,0):")
for off_b in range(52):
    seq = [d[o + off_b] for _, _, o in occ]
    if seq == [4, 0, 4, 0]:
        print("  +%d (0x%X)" % (off_b, off_b))

# also dump ramp07 (2x2, 3 occ) for a second opinion
d2, bw2, bh2, idx2 = load("ramp07.tem")
print("\nramp07 %dx%d" % (bw2, bh2))
for i in range(bw2 * bh2):
    if idx2[i]:
        hdr = d2[idx2[i]:idx2[i] + 52]
        print("cell(%d,%d):" % (i % bw2, i // bw2), " ".join("%02x" % b for b in hdr))
