#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Measure every cliff01..cliff40 TMP footprint and compare with the port's
hard-coded kCliffFootprints table in MapGenRiver.cpp."""
import os
import re

TILE_DIR = r"d:\新建文件夹\VSProject\MapGenerator\Tile资源\温和"
SRC = r"d:\新建文件夹\VSProject\MapGenerator\MapGenerator\MapGenRiver.cpp"


def measure(k):
    p = os.path.join(TILE_DIR, "cliff%02d.tem" % k)
    b = open(p, "rb").read()
    bw = int.from_bytes(b[0:4], "little")
    bh = int.from_bytes(b[4:8], "little")
    n = bw * bh
    idx = [int.from_bytes(b[16 + 4 * i:20 + 4 * i], "little") for i in range(n)]
    mask = 0
    cnt = 0
    for i, o in enumerate(idx):
        if o != 0:
            mask |= 1 << i
            cnt += 1
    return bw, bh, mask, cnt


# parse the hard-coded table
src = open(SRC, encoding="utf-8").read()
m = re.search(r"kCliffFootprints\[40\]\s*=\s*\{(.*?)\};", src, re.S)
body = m.group(1)
entries = re.findall(r"\{\s*(\d+),\s*(\d+),\s*(?:0x([0-9A-Fa-f]+)ULL|(0x[0-9A-Fa-f]+))",
                     body)
print("parsed entries:", len(entries))
bad = 0
for k in range(1, 41):
    w, h, mask, cnt = measure(k)
    ew, eh, emhex, _alt = entries[k - 1]
    em = int(emhex, 16)
    ok = (int(w) == int(ew) and int(h) == int(eh) and mask == em)
    if not ok:
        bad += 1
    print("cliff%02d TMP %dx%d mask=0x%X occ=%d | table %sx%s 0x%X  %s"
          % (k, w, h, mask, cnt, ew, eh, em, "OK" if ok else "*** MISMATCH ***"))
print("mismatches:", bad)
