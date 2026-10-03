#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Render one shore tile's full multi-cell art as its designed layout.

    python art_piece.py <tile> <out.png> [scale]

Stamps every sub image at its art pixel offset ((col-row)*30, (col+row)*15),
so the picture shows exactly which cells of the piece are water and which are
land, in isometric layout.
"""
import sys

sys.path.insert(0, ".")
import tmp_render as R


def main():
    tile = int(sys.argv[1])
    out = sys.argv[2]
    scale = int(sys.argv[3]) if len(sys.argv) > 3 else 3
    name = R.tile_file(tile)
    print("tile %d -> %s" % (tile, name))
    tmp = R.get_tmp(name)
    pal = R.load_pal()

    # bbox of art offsets
    n = len(tmp.idx)
    coords = []
    for sub in range(n):
        col = sub % tmp.bw
        row = sub // tmp.bw
        coords.append((sub, col, row, (col - row) * 30, (col + row) * 15))
    ox = min(c[3] for c in coords)
    oy = min(c[4] for c in coords)
    w = (max(c[3] for c in coords) - ox) + 60
    h = (max(c[4] for c in coords) - oy) + 30

    W, H = w * scale, h * scale
    canvas = [[None] * W for _ in range(H)]
    for sub, col, row, ax, ay in coords:
        im = tmp.image(sub)
        if im is None:
            continue
        _x, _y, rows = im
        for r, sx, data in rows:
            for k, v in enumerate(data):
                px = (ax - ox + sx + k) * scale
                py = (ay - oy + r) * scale
                rr, gg, bb = pal[v]
                for dy in range(scale):
                    for dx in range(scale):
                        if 0 <= py + dy < H and 0 <= px + dx < W:
                            canvas[py + dy][px + dx] = (rr, gg, bb)

    buf = bytearray(W * H * 4)
    flat = [px if px else (0, 0, 0) for row in canvas for px in row]
    for i, (r, g, b) in enumerate(flat):
        buf[4 * i:4 * i + 4] = bytes((r, g, b, 255))
    R.write_png(out, W, H, bytes(buf))
    print("wrote %s %dx%d subs=%d bw=%d bh=%d" % (out, W, H, n, tmp.bw, tmp.bh))


main()
