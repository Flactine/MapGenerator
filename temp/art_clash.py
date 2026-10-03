#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Scan land-land edge pairs for a water/sand art clash.

    python art_clash.py <map> [<map> ...]

For every edge-sharing pair of non-water cells, look at each cell's OWN art
just inside the shared edge (same sampling as edge_probe):

    water pixels on one side + sand pixels on the other, no foam on the
    water side -> the two pieces clash (water visually touches plain sand).
"""
import math
import sys

sys.path.insert(0, ".")
import analyze_isopack5 as A
from tmp_render import get_tmp, tile_file, load_pal

PAL = load_pal()
WATER = set(range(314, 328))

EDGES = {
    "N": ((30.0, 0.0), (60.0, 15.0), (-1.0, 2.0)),
    "E": ((60.0, 15.0), (30.0, 30.0), (-1.0, -2.0)),
    "S": ((30.0, 30.0), (0.0, 15.0), (1.0, -2.0)),
    "W": ((0.0, 15.0), (30.0, 0.0), (1.0, 2.0)),
}
DIRS = {"N": (0, -1), "E": (1, 0), "S": (0, 1), "W": (-1, 0)}
OPPOSITE = {"N": "S", "S": "N", "E": "W", "W": "E"}


def cell_art(cell):
    tile = cell["tile"]
    name = tile_file(tile)
    if not name:
        return None
    tmp = get_tmp(name)
    if tmp is None:
        return None
    sub = cell["height"]
    if sub >= len(tmp.idx):
        sub = 0
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


def sample(canvas, side):
    (ax, ay), (bx, by), (nx, ny) = EDGES[side]
    ln = math.hypot(nx, ny)
    nx, ny = nx / ln, ny / ln
    water = sand = foam = total = 0
    for i in range(5):
        t = 0.15 + 0.175 * i
        px = ax + (bx - ax) * t
        py = ay + (by - ay) * t
        for d in (2, 4, 6, 8, 10):
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
                foam += 1
            elif r > 150 and g > 120 and b < 120:
                sand += 1
    return water, sand, foam, total


def classify(v):
    w, s, f, t = v
    if t == 0:
        return "none"
    if w >= 6 and f == 0:
        return "water"
    if s >= 8 and w == 0:
        return "sand"
    if f >= 3:
        return "foam"
    return "mix"


def main():
    for path in sys.argv[1:]:
        cells, _a, _b = A.load_map(path)
        clashes = []
        for (x, y), c in sorted(cells.items()):
            if c["tile"] in WATER or c["tile"] == 65535:
                continue
            artA = None
            for side, (dx, dy) in DIRS.items():
                n = cells.get((x + dx, y + dy))
                if n is None or n["tile"] in WATER or n["tile"] == 65535:
                    continue
                if artA is None:
                    artA = cell_art(c)
                if artA is None:
                    continue
                artB = cell_art(n)
                if artB is None:
                    continue
                kA = classify(sample(artA, side))
                kB = classify(sample(artB, OPPOSITE[side]))
                if {kA, kB} == {"water", "sand"}:
                    clashes.append((x, y, side, kA, kB,
                                    c["tile"], n["tile"]))
        print("%s : %d water/sand art clashes" % (path, len(clashes)))
        for x, y, side, kA, kB, tA, tB in clashes:
            print("   (%d,%d)%s: %s(tile %d) / %s(tile %d)"
                  % (x, y, side, kA, tA, kB, tB))


main()
