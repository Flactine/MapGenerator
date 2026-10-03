#!/usr/bin/env python3
"""Which outer side of a shore/water piece does its art draw water on?

    python block_face.py <tile> [<tile> ...]

The piece's whole footprint is rebuilt on one canvas (anchor cell centre at
(30*bh, 15)), and the four outer boundary edges are sampled a few pixels inward.
Reported per side: how many samples are water-blue, how many are the bright
foam line, and the most common colour.

Side naming follows the map neighbour the boundary faces:
    N = the top-right boundary (N edges of row 0)   -> neighbours (ax+c, ay-1)
    E = the bottom-right boundary (E edges of col w-1)
    S = the bottom-left boundary (S edges of row h-1)
    W = the top-left boundary (W edges of col 0)
"""
import os
import sys
from collections import Counter

sys.path.insert(0, ".")
from tmp_render import Tmp, tile_file, load_pal, TILE_DIR

PAL = load_pal()

# side -> (start, end) on the block canvas, inward normal
SIDES = {
    "N": ((60.0, 0.0), (120.0, 30.0), (-1.0, 2.0)),
    "E": ((120.0, 30.0), (60.0, 60.0), (-1.0, -2.0)),
    "S": ((60.0, 60.0), (0.0, 30.0), (1.0, -2.0)),
    "W": ((0.0, 30.0), (60.0, 0.0), (1.0, 2.0)),
}


def canvas_of(tmp, bw, bh):
    """uth. build the whole block art on a 30*(bw+bh) x 15*(bw+bh) canvas."""
    W = 30 * (bw + bh)
    H = 15 * (bw + bh)
    ox, oy = 30 * bh, 15
    cv = [[None] * W for _ in range(H)]
    for i in range(bw * bh):
        col, row = i % bw, i // bw
        im = tmp.image(i)
        if im is None:
            continue
        _x, _y, rows = im
        sx0 = ox + (col - row) * 30 - 30
        sy0 = oy + (col + row) * 15 - 15
        for r, sx, data in rows:
            dy = sy0 + r
            if dy < 0 or dy >= H:
                continue
            for k, v in enumerate(data):
                dx = sx0 + sx + k
                if 0 <= dx < W:
                    cv[dy][dx] = PAL[v]
    return cv


def main():
    for arg in sys.argv[1:]:
        tile = int(arg)
        path = os.path.join(TILE_DIR, tile_file(tile))
        tmp = Tmp(path)
        cv = canvas_of(tmp, tmp.bw, tmp.bh)
        H = len(cv)
        W = len(cv[0])
        print("tile %d (%s)  canvas %dx%d" % (tile, tile_file(tile), W, H))
        for side, ((ax, ay), (bx, by), (nx, ny)) in SIDES.items():
            ln = (nx * nx + ny * ny) ** 0.5
            nx, ny = nx / ln, ny / ln
            water = surf = total = 0
            cols = Counter()
            for i in range(5):
                t = 0.2 + 0.15 * i
                px, py = ax + (bx - ax) * t, ay + (by - ay) * t
                for d in (3, 6, 9, 12, 15):
                    x, y = int(round(px + nx * d)), int(round(py + ny * d))
                    if not (0 <= x < W and 0 <= y < H):
                        continue
                    rgb = cv[y][x]
                    if rgb is None:
                        continue
                    total += 1
                    cols[rgb] += 1
                    r, g, b = rgb
                    if b > r + 12 and b > 55 and r < 130:
                        water += 1
                    elif min(r, g, b) > 170:
                        surf += 1
            top = cols.most_common(3)
            print("   %s: n=%d water=%d surf=%d  top=%s"
                  % (side, total, water, surf, top))
        print()


if __name__ == "__main__":
    main()
