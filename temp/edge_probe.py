#!/usr/bin/env python3
"""Probe every water/land edge of a .map: does the LAND cell's own art carry a
water line (foam / water pixels) along the shared edge?

    python edge_probe.py <map> [x0 x1 y0 y1]

For each edge-sharing pair (land L, water W) the art of L is rebuilt into its
60x30 bounding box and a band of pixels just inside the shared edge is sampled
(5 points along the edge x 6 depths, 2..12 px inward).  Each sample is classified

    water : b > r + 12 and b > 55 and r < 130          (open water colour)
    surf  : min(r, g, b) > 170                          (white foam line)

A land cell whose own art has neither near the edge is a bare contact: the water
runs straight into plain terrain there.

Edge geometry in the 60x30 box (diamond centre is (30, 15)):
    N edge  (30,0)-(60,15)   E edge  (60,15)-(30,30)
    S edge  (30,30)-(0,15)   W edge  (0,15)-(30,0)
"""
import math
import os
import sys

sys.path.insert(0, ".")
import analyze_isopack5 as A
from tmp_render import get_tmp, tile_file, load_pal

PAL = load_pal()

WATER = range(314, 328)
SHORE = range(89, 131)

# direction -> (edge start, edge end, inward normal)
EDGES = {
    "N": ((30.0, 0.0), (60.0, 15.0), (-1.0, 2.0)),
    "E": ((60.0, 15.0), (30.0, 30.0), (-1.0, -2.0)),
    "S": ((30.0, 30.0), (0.0, 15.0), (1.0, -2.0)),
    "W": ((0.0, 15.0), (30.0, 0.0), (1.0, 2.0)),
}
DIRS = {"N": (0, -1), "E": (1, 0), "S": (0, 1), "W": (-1, 0)}

# corner-sharing neighbours: they only touch ONE vertex of the diamond.
# NE shares the right vertex, SE the bottom, SW the left, NW the top.
CORNERS = {
    "NE": (60.0, 15.0),
    "SE": (30.0, 30.0),
    "SW": (0.0, 15.0),
    "NW": (30.0, 0.0),
}
CORNER_DIRS = {"NE": (1, -1), "SE": (1, 1), "SW": (-1, 1), "NW": (-1, -1)}


def cell_art(cell):
    """Build the cell's 60x30 art as a list of 30 rows of (r,g,b) or None."""
    tile = cell["tile"]
    name = tile_file(tile)
    if not name:
        return None
    tmp = get_tmp(name)
    if tmp is None:
        return None
    sub = cell["bSubTile"]
    if sub >= len(tmp.idx):
        return None
    im = tmp.image(sub)
    if im is None:
        return None
    canvas = [[None] * 60 for _ in range(30)]
    _x, _y, rows = im
    for r, sx, data in rows:
        if r >= 30:
            continue
        for k, v in enumerate(data):
            x = sx + k
            if 0 <= x < 60:
                canvas[r][x] = PAL[v]
    return canvas


def probe(canvas, side):
    (ax, ay), (bx, by), (nx, ny) = EDGES[side]
    ln = math.hypot(nx, ny)
    nx, ny = nx / ln, ny / ln
    water = surf = total = 0
    for i in range(5):
        t = 0.15 + 0.175 * i
        px = ax + (bx - ax) * t
        py = ay + (by - ay) * t
        for d in (2, 4, 6, 8, 10, 12):
            x = int(round(px + nx * d))
            y = int(round(py + ny * d))
            if not (0 <= x < 60 and 0 <= y < 30):
                continue
            rgb = canvas[y][x]
            if rgb is None:
                continue
            total += 1
            r, g, b = rgb
            if b > r + 12 and b > 55 and r < 130:
                water += 1
            elif min(r, g, b) > 170:
                surf += 1
    return water, surf, total


def probe_corner(canvas, side, rad=12):
    """Sample the pixels of `canvas` that lie inside the cell diamond and
    within `rad` px of the shared vertex.  A shore piece that wraps the
    corner has foam (or open water) there."""
    vx, vy = CORNERS[side]
    water = surf = total = 0
    for py in range(int(vy - rad), int(vy + rad) + 1):
        for px in range(int(vx - rad), int(vx + rad) + 1):
            if not (0 <= px < 60 and 0 <= py < 30):
                continue
            if abs(px - 30) / 30.0 + abs(py - 15) / 15.0 > 1.0:
                continue                      # outside the diamond
            if (px - vx) ** 2 + (py - vy) ** 2 > rad * rad:
                continue
            rgb = canvas[py][px]
            if rgb is None:
                continue
            total += 1
            r, g, b = rgb
            if b > r + 12 and b > 55 and r < 130:
                water += 1
            elif min(r, g, b) > 170:
                surf += 1
    return water, surf, total


def main():
    path = sys.argv[1]
    corners = "--corners" in sys.argv
    argv = [a for a in sys.argv[2:] if not a.startswith("--")]
    cells, _s, _n = A.load_map(path)
    if len(argv) >= 4:
        x0, x1, y0, y1 = (int(argv[0]), int(argv[1]),
                          int(argv[2]), int(argv[3]))
    else:
        x0 = min(x for x, _ in cells)
        x1 = max(x for x, _ in cells)
        y0 = min(y for _, y in cells)
        y1 = max(y for _, y in cells)

    bad = []
    n_edge = 0
    n_corner = 0
    for (x, y), c in sorted(cells.items()):
        if not (x0 <= x <= x1 and y0 <= y <= y1):
            continue
        tile = c["tile"]
        if tile in WATER or tile == 0xFFFF:
            continue
        art = None
        for side, (dx, dy) in DIRS.items():
            n = cells.get((x + dx, y + dy))
            if n is None or n["tile"] not in WATER:
                continue
            n_edge += 1
            if art is None:
                art = cell_art(c)
            if art is None:
                bad.append((x, y, side, tile, c["bSubTile"], -1, -1, "NO-ART"))
                continue
            w, s, tot = probe(art, side)
            if w == 0 and s == 0:
                bad.append((x, y, side, tile, c["bSubTile"], w, s, "BARE"))
        if not corners:
            continue
        for side, (dx, dy) in CORNER_DIRS.items():
            n = cells.get((x + dx, y + dy))
            if n is None or n["tile"] not in WATER:
                continue
            n_corner += 1
            if art is None:
                art = cell_art(c)
            if art is None:
                bad.append((x, y, side, tile, c["bSubTile"], -1, -1, "NO-ART"))
                continue
            w, s, tot = probe_corner(art, side)
            if w == 0 and s == 0:
                bad.append((x, y, side, tile, c["bSubTile"], w, s, "BARE-C"))

    print("water-land edges in window: %d   bare: %d"
          % (n_edge, sum(1 for b in bad if b[7] == "BARE")))
    if corners:
        print("water-land corners in window: %d   bare: %d"
              % (n_corner, sum(1 for b in bad if b[7] == "BARE-C")))
    for b in bad:
        print("  land (%d,%d) side %s tile %d sub %d water=%d surf=%d %s" % b)


if __name__ == "__main__":
    main()
