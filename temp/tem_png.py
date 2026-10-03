#!/usr/bin/env python3
"""Render one .tem tile file (all cells of its block) to a PNG.

    python tem_png.py <name.tem> <scale> <out.png>
"""
import os
import sys

sys.path.insert(0, ".")
import tmp_render as R

CW, CH = 60, 30


def main():
    name, scale, out = sys.argv[1], int(sys.argv[2]), sys.argv[3]
    tm = R.get_tmp(name)
    bw, bh = tm.bw, tm.bh
    pal = R.load_pal()
    W = (bw + bh) * (CW // 2)
    H = (bw + bh) * (CH // 2)
    buf = bytearray(W * H * 4)
    for row in range(bh):
        for col in range(bw):
            sub = col + row * bw
            if sub >= len(tm.idx):
                continue
            im = tm.image(sub)
            if im is None:
                continue
            sx0 = (col - row) * (CW // 2) + bh * (CW // 2)
            sy0 = (col + row) * (CH // 2)
            for r, sx, data in im[2]:
                for k, v in enumerate(data):
                    x, y = sx0 + sx + k, sy0 + r
                    if 0 <= x < W and 0 <= y < H:
                        o = (y * W + x) * 4
                        buf[o:o + 3] = bytes(pal[v])
                        buf[o + 3] = 255
    big = bytearray()
    for y in range(H):
        row = buf[y * W * 4:(y + 1) * W * 4]
        expanded = b"".join(row[k * 4:k * 4 + 4] * scale for k in range(W))
        for _ in range(scale):
            big.append(0)
            big += expanded
    R.write_png(out, W * scale, H * scale, big)
    print("wrote %s  %s %dx%d cells -> %dx%d" % (out, name, bw, bh, W * scale, H * scale))


main()
