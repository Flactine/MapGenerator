#!/usr/bin/env python3
"""Check that every shore piece faces the water.

    python shore_orient.py <map>

For every shore piece (tiles 89..130) placed in the map:

  * the footprint is the .tem block size (bw x bh) and the sub-cell index stored
    in the cell gives the anchor: anchor = (x - sub % bw, y - sub / bw);
  * the art's water side is read from the TMP: the four diamond edge midpoints
    of a boundary cell are (44,7) N, (44,22) E, (15,22) S, (15,7) W relative to
    the diamond's top-left, and a side counts as "water" when the majority of
    the sampled pixels are water blue;
  * the map's water side is read from the cells just outside the footprint.

A piece whose art-water side does not match the map-water side leaves a bare
water/land seam exactly where the art has no waterline - that is the reported
defect.
"""
import sys
from collections import defaultdict

sys.path.insert(0, ".")
import analyze_isopack5 as A
import tmp_render as R

CW, CH = 60, 30
SHORE = range(89, 131)
WATER = range(314, 328)

# (name, dx, dy) for the diamond edge midpoint of a cell, in pixel space
EDGES = (
    ("N", 44, 7),
    ("E", 44, 22),
    ("S", 15, 22),
    ("W", 15, 7),
)
# footprint side -> map offset of the cell just outside that side
SIDE_OFF = {"N": (0, -1), "E": (1, 0), "S": (0, 1), "W": (-1, 0)}


def is_water_blue(rgb):
    r, g, b = rgb
    return b > r + 12 and b > 55 and r < 130 and g < 130


def piece_art(path):
    """flag[N/E/S/W] -> True when that outer side of the art shows water."""
    tm = R.get_tmp(path)
    if tm is None:
        return None, None
    bw, bh = tm.bw, tm.bh
    # paint the piece into a local buffer
    minx = min((c - r) for c in range(bw) for r in range(bh)) * (CW // 2)
    miny = min((c + r) for c in range(bw) for r in range(bh)) * (CH // 2)
    W = (max((c - r) for c in range(bw) for r in range(bh))
         - min((c - r) for c in range(bw) for r in range(bh))) * (CW // 2) + CW
    H = (max((c + r) for c in range(bw) for r in range(bh))
         - min((c + r) for c in range(bw) for r in range(bh))) * (CH // 2) + CH
    buf = {}
    pal = R.load_pal()
    for row in range(bh):
        for col in range(bw):
            sub = col + row * bw
            if sub >= len(tm.idx):
                continue
            im = tm.image(sub)
            if im is None:
                continue
            sx0 = (col - row) * (CW // 2) - minx
            sy0 = (col + row) * (CH // 2) - miny
            for r, sx, data in im[2]:
                for k, v in enumerate(data):
                    buf[(sx0 + sx + k, sy0 + r)] = pal[v]

    flag = {}
    for side, ex, ey in EDGES:
        # boundary cells on that side of the footprints
        if side == "N":
            boundary = [(c, 0) for c in range(bw)]
        elif side == "S":
            boundary = [(c, bh - 1) for c in range(bw)]
        elif side == "E":
            boundary = [(bw - 1, r) for r in range(bh)]
        else:
            boundary = [(0, r) for r in range(bh)]
        votes = []
        for col, row in boundary:
            sx0 = (col - row) * (CW // 2) - minx
            sy0 = (col + row) * (CH // 2) - miny
            for dx in range(-3, 4):
                for dy in range(-2, 3):
                    px, py = sx0 + ex + dx, sy0 + ey + dy
                    if (px, py) in buf:
                        votes.append(is_water_blue(buf[(px, py)]))
        flag[side] = bool(votes) and (sum(votes) * 2 > len(votes))
    return flag, (bw, bh)


def main():
    path = sys.argv[1]
    cells, _s, _n = A.load_map(path)

    def tile(p):
        c = cells.get(p)
        return None if c is None else c["tile"]

    # group shore cells into pieces by (tile, anchor)
    groups = defaultdict(list)
    meta = {}
    for (x, y), c in cells.items():
        t = c["tile"]
        if t not in SHORE:
            continue
        fp, size = piece_art(R.tile_file(t))
        meta[t] = (fp, size)
        bw, bh = size or (1, 1)
        sub = c["bSubTile"]
        groups[(t, x - sub % bw, y - sub // bw)].append((x, y))

    bad = 0
    incomplete = 0
    for (t, ax, ay), covered in sorted(groups.items()):
        fp, (bw, bh) = meta[t]
        if fp is None:
            continue
        full = {(ax + c, ay + r) for c in range(bw) for r in range(bh)}
        if set(covered) != full:
            incomplete += 1
            print("PARTIAL  tile %d anchor (%d,%d) covered %d/%d"
                  % (t, ax, ay, len(covered), bw * bh))
            continue
        for side, (dx, dy) in SIDE_OFF.items():
            outs = {(ax + c + dx, ay + r + dy)
                    for c in range(bw) for r in range(bh)}
            outs -= full
            outs = {p for p in outs if cells.get(p) is not None}
            if not outs:
                continue
            water_out = sum(1 for p in outs if tile(p) in WATER)
            map_water = water_out * 2 > len(outs)
            if map_water != fp[side]:
                bad += 1
                print("MISMATCH tile %d (shore%02d) anchor (%d,%d) side %s"
                      "  art water=%s map water=%s (%d/%d water outside)"
                      % (t, t - 88, ax, ay, side, fp[side], map_water,
                         water_out, len(outs)))
    print("pieces %d  incomplete %d  orientation mismatches %d"
          % (len(groups), incomplete, bad))


if __name__ == "__main__":
    main()
