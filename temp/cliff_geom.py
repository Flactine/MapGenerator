#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Measure REAL geometry of cliff01..42 + wcliff01..28 and compare with the
port's kCliffFootprints table (MapGenRiver.cpp)."""
import os, struct, re

TD = r"d:\新建文件夹\VSProject\MapGenerator\Tile资源\温和"
SRC = r"d:\新建文件夹\VSProject\MapGenerator\MapGenerator\MapGenRiver.cpp"


def geom(prefix, k):
    p = os.path.join(TD, "%s%02d.tem" % (prefix, k))
    if not os.path.isfile(p):
        return None
    d = open(p, "rb").read()
    bw, bh = struct.unpack_from("<ii", d, 0)
    idx = [struct.unpack_from("<I", d, 16 + 4 * i)[0] for i in range(bw * bh)]
    occ = [i for i, o in enumerate(idx) if o]
    mask = 0
    zs = []
    for i in occ:
        mask |= 1 << i
        zs.append(d[idx[i] + 0x28])
    return bw, bh, mask, zs


# pull the C++ table
src = open(SRC, "r", encoding="utf-8-sig").read()
m = re.search(r"kCliffFootprints\[40\]\s*=\s*\{(.*?)\};", src, re.S)
entries = re.findall(r"\{\s*(\d+),\s*(\d+),\s*0x([0-9A-Fa-f]+)ULL,\s*\{([^}]*)\}\s*\}", m.group(1))
cpp = {}
for i, e in enumerate(entries, 1):
    w, h, mask, zs = e
    cpp[i] = (int(w), int(h), int(mask, 16),
              tuple(int(v) for v in zs.split(",") if v.strip()))

mism = 0
for k in range(1, 41):
    g = geom("cliff", k)
    if g is None:
        print("cliff%02d MISSING FILE" % k); mism += 1; continue
    w, h, mask, zs = g
    real = (w, h, mask, tuple(zs))
    if k not in cpp:
        print("cliff%02d not in cpp table" % k); mism += 1; continue
    if real != cpp[k]:
        mism += 1
        print("cliff%02d REAL %dx%d mask=0x%X z=%s | CPP %dx%d mask=0x%X z=%s"
              % (k, w, h, mask, zs, cpp[k][0], cpp[k][1], cpp[k][2], list(cpp[k][3])))
print("cliff mismatches: %d / 40" % mism)

# also print the 09/10/11 cluster geometry explicitly + wcliff quick count
wm = 0
for k in range(1, 29):
    g = geom("wcliff", k)
    if g is None:
        wm += 1
print("wcliff missing files:", wm)
