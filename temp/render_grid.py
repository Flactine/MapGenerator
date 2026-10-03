#!/usr/bin/env python3
"""Render a window with a cell grid underneath, so uncovered cells are visible.

    python render_grid.py <map> <x0> <x1> <y0> <y1> <out.png> [tag ...]

Every cell's full 60x30 diamond is first filled with dark grey, then the real
TMP pixels are stamped on top, then the diamond outline is drawn in magenta.
Cells listed as `tag` (x,y pairs) get a red overlay so they can be found.
"""
import os
import sys

sys.path.insert(0, ".")
import analyze_isopack5 as A
import tmp_render as R

CW, CH = 60, 30


def diamond_rows():
    """(row, x_start, width) for the full 60x30 isometric diamond."""
    out = []
    for r in range(CH):
        w = 4 * min(r + 1, CH - 1 - r)
        if w <= 0:
            continue
        out.append((r, (CW - w) // 2, w))
    return out


def main():
    path, x0, x1, y0, y1, out = (sys.argv[1], int(sys.argv[2]), int(sys.argv[3]),
                                 int(sys.argv[4]), int(sys.argv[5]), sys.argv[6])
    tags = set()
    for a in sys.argv[7:]:
        p = a.split(",")
        tags.add((int(p[0]), int(p[1])))

    cells, _s, _n = A.load_map(path)
    pal = R.load_pal()
    xs = list(range(x0, x1 + 1))
    ys = list(range(y0, y1 + 1))
    minx = min(x - y for x in xs for y in ys) * (CW // 2)
    miny = min(x + y for x in xs for y in ys) * (CH // 2)
    W = (max(x - y for x in xs for y in ys) - min(x - y for x in xs for y in ys)) * (CW // 2) + CW
    H = (max(x + y for x in xs for y in ys) - min(x + y for x in xs for y in ys)) * (CH // 2) + CH
    buf = bytearray(W * H * 4)

    def put(px, py, rgb, alpha=255):
        if 0 <= px < W and 0 <= py < H:
            o = (py * W + px) * 4
            buf[o], buf[o + 1], buf[o + 2], buf[o + 3] = rgb[0], rgb[1], rgb[2], alpha

    rows = diamond_rows()
    for (x, y) in ((x, y) for x in xs for y in ys):
        sx0 = (x - y) * (CW // 2) - minx
        sy0 = (x + y) * (CH // 2) - miny
        base = (170, 30, 30) if (x, y) in tags else (60, 60, 60)
        for r, xs_, w in rows:
            for k in range(w):
                put(sx0 + xs_ + k, sy0 + r, base)

    for (x, y) in sorted(((x, y) for x in xs for y in ys), key=lambda c: c[0] + c[1]):
        c = cells.get((x, y))
        if c is None:
            continue
        tile = c["tile"]
        if tile == 65535:
            continue
        name = R.tile_file(tile)
        if not name:
            continue
        tmp = R.get_tmp(name)
        if tmp is None:
            continue
        sub = c["bSubTile"]
        if sub >= len(tmp.idx):
            sub = 0
        im = tmp.image(sub)
        if im is None:
            continue
        _ox, _oy, trs = im
        sx0 = (x - y) * (CW // 2) - minx
        sy0 = (x + y) * (CH // 2) - miny
        for row, sx, data in trs:
            for k, v in enumerate(data):
                put(sx0 + sx + k, sy0 + row, pal[v])

    # outlines drawn last so the cell boundaries stay readable on top of the art
    for (x, y) in ((x, y) for x in xs for y in ys):
        sx0 = (x - y) * (CW // 2) - minx
        sy0 = (x + y) * (CH // 2) - miny
        col = (255, 0, 0) if (x, y) in tags else (255, 0, 255)
        for r, xs_, w in rows:
            put(sx0 + xs_, sy0 + r, col)
            put(sx0 + xs_ + w - 1, sy0 + r, col)
        put(sx0 + CW // 2, sy0, col)
        put(sx0 + CW // 2, sy0 + CH - 1, col)

    R.write_png(out, W, H, buf)
    print("wrote %s (%dx%d)" % (out, W, H))


main()
