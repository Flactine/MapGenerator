#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""High-zoom render of a window, like FA2 (no grid, no fill)."""
import sys

sys.path.insert(0, ".")
import analyze_isopack5 as A
import tmp_render as R

path = sys.argv[1]
x0, x1, y0, y1 = (int(v) for v in sys.argv[2:6])
out = sys.argv[6]
S = int(sys.argv[7]) if len(sys.argv) > 7 else 4

cells, _a, _b = A.load_map(path)
pal = R.load_pal()
xs = range(x0, x1 + 1)
ys = range(y0, y1 + 1)
minx = min(x - y for x in xs for y in ys)
miny = min(x + y for x in xs for y in ys)
maxx = max(x - y for x in xs for y in ys)
maxy = max(x + y for x in xs for y in ys)
W = (maxx - minx) * 30 + 60
H = (maxy - miny) * 15 + 30
buf = bytearray(W * S * H * S * 4)


def put(px, py, r, g, b):
    if 0 <= px < W * S and 0 <= py < H * S:
        o = (py * W * S + px) * 4
        buf[o:o + 4] = bytes((r, g, b, 255))


for y in ys:
    for x in xs:
        c = cells.get((x, y))
        if not c or c["tile"] == 65535:
            continue
        tmp = R.get_tmp(R.tile_file(c["tile"]))
        if tmp is None:
            continue
        sub = c["height"]
        if sub >= len(tmp.idx):
            sub = 0
        im = tmp.image(sub)
        if not im:
            continue
        _ox, _oy, rows = im
        sx0 = (x - y - minx) * 30
        sy0 = (x + y - miny) * 15
        for r, sx, data in rows:
            for k, v in enumerate(data):
                rr, gg, bb = pal[v]
                for dy in range(S):
                    for dx in range(S):
                        put((sx0 + sx + k) * S + dx, (sy0 + r) * S + dy,
                            rr, gg, bb)

R.write_png(out, W * S, H * S, bytes(buf))
print("wrote %s %dx%d" % (out, W * S, H * S))
