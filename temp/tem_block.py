#!/usr/bin/env python3
"""Render a whole shore/water tile (all sub-cells of its footprint block) into
one PNG, on a magenta background so transparent areas are obvious.

    python tem_block.py <tile> <scale> <out.png>

The block canvas is 30*(bw+bh) x 15*(bw+bh) pixels; sub-cell (col,row) of the
bw x bh footprint is drawn at local ((col-row)*30, (col+row)*15) relative to the
anchor cell centre, which itself sits at canvas (30*bh, 15).
"""
import os
import sys

sys.path.insert(0, ".")
from tmp_render import Tmp, tile_file, load_pal, write_png, TILE_DIR


def main():
    tile = int(sys.argv[1])
    scale = int(sys.argv[2])
    out = sys.argv[3]

    name = tile_file(tile)
    if not name:
        print("tile %d has no .tem mapping" % tile)
        return
    path = os.path.join(TILE_DIR, name)
    if not os.path.isfile(path):
        print("missing %s" % path)
        return

    tmp = Tmp(path)
    pal = load_pal()
    bw, bh = tmp.bw, tmp.bh
    W = 30 * (bw + bh)
    H = 15 * (bw + bh)
    ox, oy = 30 * bh, 15            # anchor cell centre on the canvas

    buf = bytearray()
    for _ in range(W * H):
        buf += bytes((255, 0, 255, 255))

    for i in range(bw * bh):
        col, row = i % bw, i // bw
        im = tmp.image(i)
        if im is None:
            print("  sub %d (col %d row %d): empty record" % (i, col, row))
            continue
        _x, _y, rows = im
        # The record's own pixel coordinates are relative to the cell's 60x30
        # bounding box, so the box origin is the cell centre minus (30, 15).
        sx0 = ox + (col - row) * 30 - 30
        sy0 = oy + (col + row) * 15 - 15
        for r, sx, data in rows:
            dy = sy0 + r
            if dy < 0 or dy >= H:
                continue
            for k, v in enumerate(data):
                dx = sx0 + sx + k
                if dx < 0 or dx >= W:
                    continue
                rr, gg, bb = pal[v]
                o = (dy * W + dx) * 4
                buf[o] = rr
                buf[o + 1] = gg
                buf[o + 2] = bb
                buf[o + 3] = 255

    if scale > 1:
        big = bytearray()
        for y in range(H):
            rowb = bytearray()
            for x in range(W):
                rowb += buf[(y * W + x) * 4:(y * W + x) * 4 + 4] * scale
            big += rowb * scale
        buf, W, H = big, W * scale, H * scale

    write_png(out, W, H, buf)
    print("tile %d = %s  block %dx%d -> %s (%dx%d)"
          % (tile, name, bw, bh, out, W, H))


if __name__ == "__main__":
    main()
