#!/usr/bin/env python3
"""Reconstruct every shore piece in a map and report the incomplete ones.

    python shore_pieces.py <map> [--near x,y]

A shore cell carries tile 89+n12-1 and Height = col + row*w of its own piece,
so the piece's origin is (x - Height%w, y - Height/w).  Grouping cells by
(origin, tile) recovers each stamp.  A piece whose rectangle is not fully
covered by that tile means the stamp was abandoned part-way (PlaceIsoTile
returns on the first rejected cell), which is what a coastline defect looks
like from the tile data alone.
"""
import sys

sys.path.insert(0, ".")
import analyze_isopack5 as A

# kShoreFootprints (MapGenRiver.cpp): n12 1..42 -> (w, h)
FOOT = [
    (2, 2), (2, 2), (2, 2), (1, 2), (2, 3), (2, 3), (2, 2), (2, 2), (2, 2),
    (2, 2), (2, 2), (2, 1), (3, 2), (3, 2), (2, 2), (2, 2), (2, 2), (2, 2),
    (2, 2), (1, 2), (2, 3), (2, 3), (2, 2), (2, 2), (2, 2), (2, 2), (2, 2),
    (2, 1), (3, 2), (3, 2), (2, 2), (2, 2), (2, 2), (2, 2), (2, 2), (2, 2),
    (2, 2), (2, 2), (2, 2), (2, 2), (6, 4), (9, 5),
]

SHORE_BASE = 89
WATER = range(314, 328)

# Which edge of the piece the art faces water on, read off the n12 dispatch in
# SelectShoreTile (MapGenRiver.cpp L1909-1986): the group that picked n12 names
# the water sides, e.g. 6-8/13 come from E+S, 33/34 from the SE fallback.
EAST = {6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 22, 33, 34, 35, 36}
SOUTH = {1, 2, 3, 4, 5, 6, 7, 8, 13, 29, 31, 32, 33, 34, 39, 40}
WEST = {5, 21, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 37, 38, 39, 40}
NORTH = {14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 30, 35, 36, 37, 38}


def sym(t):
    if t == 0xFFFF:
        return "."
    if t == 0:
        return "clr"
    if SHORE_BASE <= t <= 130:
        return "S%02d" % (t - SHORE_BASE + 1)
    if t in WATER:
        return "~~~"
    if 49 <= t <= 88:
        return "cf%02d" % (t - 48)
    if 29 <= t <= 48:
        return "rb%02d" % (t - 28)
    if 132 <= t <= 147:
        return "clat%02d" % (t - 131)
    if t == 131:
        return "ruff"
    if t == 493:
        return "G"
    if 494 <= t <= 509:
        return "glat%02d" % (t - 493)
    if 419 <= t <= 434:
        return "dlat%02d" % (t - 418)
    if 510 <= t <= 521:
        return "R%02d" % (t - 509)
    return "T%X" % t


def main():
    path = sys.argv[1]
    focus = None
    if "--near" in sys.argv:
        fx, fy = sys.argv[sys.argv.index("--near") + 1].split(",")
        focus = (int(fx), int(fy))

    cells, _s, _n = A.load_map(path)

    groups = {}
    for (x, y), c in cells.items():
        t = c["tile"]
        if not (SHORE_BASE <= t <= 130):
            continue
        n12 = t - SHORE_BASE + 1
        w, hgt = FOOT[n12 - 1]
        sub = c["height"]
        ox = x - sub % w
        oy = y - sub // w
        groups.setdefault(((ox, oy), t), set()).add((x, y))

    print("shore stamps recovered: %d" % len(groups))
    bad = []
    for ((ox, oy), t), have in sorted(groups.items()):
        n12 = t - SHORE_BASE + 1
        w, hgt = FOOT[n12 - 1]
        want = {(ox + i % w, oy + i // w) for i in range(w * hgt)}
        if want == have:
            continue
        bad.append(((ox, oy), t, w, hgt, sorted(want - have)))

    print("incomplete stamps: %d" % len(bad))
    print()
    for (ox, oy), t, w, hgt, miss in bad:
        n12 = t - SHORE_BASE + 1
        print("S%02d %dx%d origin (%d,%d)  missing %d cell(s):"
              % (n12, w, hgt, ox, oy, len(miss)))
        for (mx, my) in miss:
            c = cells.get((mx, my))
            print("    (%3d,%3d) -> %s"
                  % (mx, my, "absent" if c is None else
                     "%s h=%d" % (sym(c["tile"]), c["height"])))

    # Alignment: every group of n12 was picked by SelectShoreTile because the
    # trigger cell has water on a named set of sides (or on one diagonal).  The
    # stamp must be placed so that the trigger cell - derived from the origin by
    # undoing that group's pull-back - really has water exactly there.  A piece
    # whose trigger has no water on the named side is drawn off the coastline,
    # which is what a "wrong at the bend" cell looks like.
    DIRS = {"N": (0, -1), "NE": (1, -1), "E": (1, 0), "SE": (1, 1),
            "S": (0, 1), "SW": (-1, 1), "W": (-1, 0), "NW": (-1, -1)}

    def water_at(x, y):
        c = cells.get((x, y))
        return c is not None and c["tile"] in WATER

    def expectations(n12):
        if n12 in (33, 34):
            return ["SE"]
        if n12 in (35, 36):
            return ["NE"]
        if n12 in (37, 38):
            return ["NW"]
        if n12 in (39, 40):
            return ["SW"]
        if n12 <= 4 or n12 in (5, 29, 31, 32):
            return ["S"] if n12 <= 4 else ["S", "W"]
        if 9 <= n12 <= 12:
            return ["E"]
        if 17 <= n12 <= 20:
            return ["N"]
        if 25 <= n12 <= 28:
            return ["W"]
        if n12 in (6, 7, 8, 13):
            return ["E", "S"]
        if n12 in (14, 15, 16, 22):
            return ["N", "E"]
        if n12 in (21, 23, 24, 30):
            return ["N", "W"]
        return []

    print()
    print("misaligned stamps (piece's trigger has no water on its named side):")
    misaligned = 0
    for ((ox, oy), t), have in sorted(groups.items()):
        n12 = t - SHORE_BASE + 1
        w, hgt = FOOT[n12 - 1]
        if len(have) != w * hgt:
            continue                      # already reported as incomplete
        tx = ox + (w - 1 if n12 in EAST else 0)
        ty = oy + (hgt - 1 if n12 in SOUTH else 0)
        missing = [s for s in expectations(n12)
                   if not water_at(tx + DIRS[s][0], ty + DIRS[s][1])]
        if not missing:
            continue
        misaligned += 1
        print("  S%02d %dx%d origin (%d,%d) trigger (%d,%d) -> no water to %s"
              % (n12, w, hgt, ox, oy, tx, ty, ",".join(missing)))
    print("misaligned stamps: %d" % misaligned)

    # The bend defect: a land cell that has water on a SIDE (E/W/S/N) but whose
    # own tile came from a diagonal piece (n12 33-40).  The diagonal art has no
    # transition on that side, so the water abuts plain land.  This happens when
    # an earlier diagonal stamp covered the cell (mode 1 rejects a cell that is
    # no longer a placeholder), pre-empting the side-facing stamp that cell
    # would otherwise have made.
    DIAG = set(range(33, 41))
    SIDE = {"E": (1, 0, 0x02), "S": (0, 1, 0x08), "N": (0, -1, 0x80),
            "W": (-1, 0, 0x20)}
    offenders = []
    for (x, y), c in sorted(cells.items()):
        t = c["tile"]
        if not (SHORE_BASE <= t <= 130):
            continue
        n12 = t - SHORE_BASE + 1
        if n12 not in DIAG:
            continue
        wet = [s for s, (dx, dy, _b) in SIDE.items() if water_at(x + dx, y + dy)]
        if wet:
            offenders.append((x, y, n12, ",".join(sorted(wet))))
    print()
    print("diagonal pieces sitting on a side-facing water edge: %d"
          % len(offenders))
    for x, y, n12, wet in offenders:
        print("    (%3d,%3d) S%02d  water to %s" % (x, y, n12, wet))

    if focus is None:
        return

    fx, fy = focus
    print()
    print("neighbourhood of tag (%d,%d):" % (fx, fy))
    for y in range(fy - 4, fy + 5):
        row = "y=%4d " % y
        for x in range(fx - 4, fx + 5):
            c = cells.get((x, y))
            s = ("%s/%d" % (sym(c["tile"]), c["height"])) if c else "?"
            row += ("[%8s]" % s) if (x, y) == (fx, fy) else ("%10s" % s)
        print(row)


main()