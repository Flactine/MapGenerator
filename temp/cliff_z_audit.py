#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Compare the per-frame Z byte (TMP frame header +0x28, read by vanilla
sub_57B440 via [frame+0x28]) with the port's hand-coded z[] arrays."""
import os
import re

TILE_DIR = r"d:\新建文件夹\VSProject\MapGenerator\Tile资源\温和"
SRC = r"d:\新建文件夹\VSProject\MapGenerator\MapGenerator\MapGenRiver.cpp"


def frame_zs(k):
    p = os.path.join(TILE_DIR, "cliff%02d.tem" % k)
    b = open(p, "rb").read()
    bw = int.from_bytes(b[0:4], "little")
    bh = int.from_bytes(b[4:8], "little")
    out = []
    for i in range(bw * bh):
        o = int.from_bytes(b[16 + 4 * i:20 + 4 * i], "little")
        if o != 0:
            z = int.from_bytes(b[o + 0x28:o + 0x29], "little", signed=True)
            out.append(z)
    return out


src = open(SRC, encoding="utf-8").read()
m = re.search(r"kCliffFootprints\[40\]\s*=\s*\{(.*?)\};", src, re.S)
body = m.group(1)
# split into per-entry brace groups
entries = re.findall(r"\{[^{}]*\{([^}]*)\}[^{}]*\}", body)
if len(entries) != 40:
    # fallback: grab each outer {...} line
    entries = [g for g in re.findall(r"\{[^\n]*\}", body)]
print("entries parsed:", len(entries))
bad = 0
for k in range(1, 41):
    zs = frame_zs(k)
    nums = [int(x) for x in re.findall(r"-?\d+", entries[k - 1])]
    ok = zs == nums
    if not ok:
        bad += 1
    print("cliff%02d tmp+28=%s table=%s %s"
          % (k, zs, nums, "OK" if ok else "*** MISMATCH ***"))
print("mismatches:", bad)
