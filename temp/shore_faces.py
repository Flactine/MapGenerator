#!/usr/bin/env python3
"""One line per shore tile: how much water its art carries on each outer side.

    python shore_faces.py
"""
import os
import sys

sys.path.insert(0, ".")
from tmp_render import Tmp, tile_file, TILE_DIR
from block_face import SIDES, canvas_of


def counts(cv, W, H):
    out = {}
    for side, ((ax, ay), (bx, by), (nx, ny)) in SIDES.items():
        ln = (nx * nx + ny * ny) ** 0.5
        ux, uy = nx / ln, ny / ln
        w = 0
        for i in range(5):
            t = 0.2 + 0.15 * i
            px, py = ax + (bx - ax) * t, ay + (by - ay) * t
            for d in (3, 6, 9, 12, 15):
                x, y = int(round(px + ux * d)), int(round(py + uy * d))
                if not (0 <= x < W and 0 <= y < H):
                    continue
                rgb = cv[y][x]
                if rgb is None:
                    continue
                r, g, b = rgb
                if b > r + 12 and b > 55 and r < 130:
                    w += 1
        out[side] = w
    return out


def _centroid(tile):
    """Where inside the block the art's water pixels sit (canvas coords)."""
    path = os.path.join(TILE_DIR, tile_file(tile))
    tmp = Tmp(path)
    cv = canvas_of(tmp, tmp.bw, tmp.bh)
    H, W = len(cv), len(cv[0])
    xs = []
    ys = []
    for y in range(H):
        for x in range(W):
            p = cv[y][x]
            if p and p[2] > p[0] + 12 and p[2] > 55 and p[0] < 130:
                xs.append(x)
                ys.append(y)
    top = (30 * tmp.bh, 0)
    right = (30 * (tmp.bw + tmp.bh), 15 * tmp.bw)
    bottom = (30 * (tmp.bw - tmp.bh), 15 * (tmp.bw + tmp.bh - 1))
    left = (0, 15 * tmp.bh)
    cx = sum(xs) / len(xs)
    cy = sum(ys) / len(ys)
    d = {n: ((cx - p[0]) ** 2 + (cy - p[1]) ** 2) ** 0.5
         for n, p in (("top", top), ("right", right),
                      ("bottom", bottom), ("left", left))}
    print("tile %d %s canvas %dx%d  n=%d centroid=(%.1f,%.1f) nearest corner %s"
          % (tile, tile_file(tile), W, H, len(xs), cx, cy,
             min(d, key=d.get)))


def main():
    for a in sys.argv[1:]:
        _centroid(int(a))
    for tile in range(89, 131):
        name = tile_file(tile)
        path = os.path.join(TILE_DIR, name)
        if not os.path.isfile(path):
            print("tile %d: MISSING %s" % (tile, name))
            continue
        tmp = Tmp(path)
        cv = canvas_of(tmp, tmp.bw, tmp.bh)
        H, W = len(cv), len(cv[0])
        c = counts(cv, W, H)
        total = sum(1 for row in cv for p in row
                    if p and p[2] > p[0] + 12 and p[2] > 55 and p[0] < 130)
        print("tile %3d %-12s %dx%d   N=%2d E=%2d S=%2d W=%2d  water=%4d/%d"
              % (tile, name, tmp.bw, tmp.bh, c["N"], c["E"], c["S"], c["W"],
                 total, W * H))


if __name__ == "__main__":
    main()
