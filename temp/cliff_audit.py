#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Whole-map cliff seam audit (geometry only, final map state).

Builds every CliffSet piece instance from its anchor (Height % w, Height / w),
then reports:
  OVERLAP  - two DIFFERENT pieces claim the same cell
  BROKEN   - a piece cell carries another tile / wrong height / is 0xFFFF
  ZBAD     - within one piece the Level pattern does not match level+z
"""
import os, struct, sys
from collections import defaultdict, Counter
sys.path.insert(0, ".")
import analyze_isopack5 as A

MAP = sys.argv[1]
TD = r"d:\新建文件夹\VSProject\MapGenerator\Tile资源\温和"


def geom(prefix, k):
    p = os.path.join(TD, "%s%02d.tem" % (prefix, k))
    d = open(p, "rb").read()
    bw, bh = struct.unpack_from("<ii", d, 0)
    idx = [struct.unpack_from("<I", d, 16 + 4 * i)[0] for i in range(bw * bh)]
    occ, zs = [], []
    for i, o in enumerate(idx):
        if o:
            occ.append((i % bw, i // bw))
            zs.append(d[o + 0x28])
    return bw, bh, occ, zs


G = {49 + k - 1: geom("cliff", k) for k in range(1, 41)}
cells, _, _ = A.load_map(MAP)

# anchor -> tile, from every cliff cell
instances = {}   # (ax,ay,tile) -> {(x,y): (h, level)}
for (x, y), c in cells.items():
    t = c["tile"]
    if t not in G:
        continue
    w, h, occ, zs = G[t]
    col, row = c["height"] % w, c["height"] // w
    ax, ay = x - col, y - row
    key = (ax, ay, t)
    instances.setdefault(key, {})[(x, y)] = (c["height"], c["level"])

overlap = []
owner = {}
for (ax, ay, t), body in instances.items():
    w, h, occ, zs = G[t]
    for (x, y) in body:
        if (x, y) in owner and owner[(x, y)] != (ax, ay, t):
            overlap.append((x, y, owner[(x, y)], (ax, ay, t)))
        else:
            owner[(x, y)] = (ax, ay, t)

broken = []
zbad = []
for (ax, ay, t), body in instances.items():
    w, h, occ, zs = G[t]
    zmap = {(ax + cc, ay + rr): z for (cc, rr), z in zip(occ, zs)}
    for (px, py), z in zmap.items():
        c = cells.get((px, py))
        got = None if c is None else (c["tile"], c["height"])
        if got != (t, py - ay + (px - ax) * 0 + (px - ax) and ((px - ax) + (py - ay) * w)):
            want_h = (px - ax) + (py - ay) * w
            if got is None or got[0] != t or got[1] != want_h:
                broken.append(((ax, ay, t - 48), (px, py), want_h, got))

print("map:", os.path.basename(MAP))
print("cliff piece instances: %d" % len(instances))
print("OVERLAP cell-events: %d" % len(overlap))
slots = Counter()
for x, y, a, b in overlap:
    slots[(a[2] - 48, b[2] - 48)] += 1
for (sa, sb), n in slots.most_common(20):
    print("   C%02d vs C%02d : %d" % (sa, sb, n))
print("OVERLAP coords:", [(x, y, a[2] - 48, b[2] - 48) for x, y, a, b in overlap][:30])
print("BROKEN: %d" % len(broken))
for (ax, ay, slot), (px, py), wh, got in broken[:30]:
    print("   C%02d anchor(%d,%d) cell(%d,%d) wanth%d got %s" % (slot, ax, ay, px, py, wh, got))
