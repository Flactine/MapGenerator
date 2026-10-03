#!/usr/bin/env python3
"""Find cliffs that sit against water and show the height drop they leave.

    python cliff_water.py <map> [--near x,y]

CliffSet tiles are 49..88 (anchor cells carry the index, the rest of the
footprint carries the same tile with Height encoding col+row*w).  WaterCliffs
(Cliff/Water pieces) are 148..175.  A "seam" cell is a land cell that carries a
cliff tile and is 8-adjacent to a water cell: nothing there renders the drop.
"""
import sys

sys.path.insert(0, ".")
import analyze_isopack5 as A

WATER = set(range(314, 328))
CLIFF = set(range(49, 89))
WCLIFF = set(range(148, 176))
SHORE = set(range(89, 131))

DIRS = [(-1, -1), (0, -1), (1, -1), (-1, 0), (1, 0), (-1, 1), (0, 1), (1, 1)]


def sym(t):
    if t == 0xFFFF:
        return "."
    if t == 0:
        return "clr"
    if t in WATER:
        return "~~~"
    if t in SHORE:
        return "S%02d" % (t - 89 + 1)
    if t in CLIFF:
        return "cf%02d" % (t - 48)
    if t in WCLIFF:
        return "wc%02d" % (t - 148)
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

    def water(x, y):
        c = cells.get((x, y))
        return c is not None and c["tile"] in WATER

    seams = []
    for (x, y), c in sorted(cells.items()):
        t = c["tile"]
        if t not in CLIFF and t not in WCLIFF:
            continue
        wet = [d for d in DIRS if water(x + d[0], y + d[1])]
        if wet:
            seams.append((x, y, t, c["height"], len(wet)))

    print("cliff cells 8-adjacent to water: %d" % len(seams))
    for x, y, t, h, n in seams:
        print("    (%3d,%3d) %-6s h=%-3d water on %d side(s)"
              % (x, y, sym(t), h, n))

    # Height / level census of the two sides of every seam, so the size of the
    # drop the generator is leaving unrendered is visible.
    drops = {}
    for x, y, t, h, n in seams:
        for d in DIRS:
            wx, wy = x + d[0], y + d[1]
            if not water(wx, wy):
                continue
            key = cells[(x, y)]["height"] - cells[(wx, wy)]["height"]
            drops[key] = drops.get(key, 0) + 1
    print()
    print("cliff Height - water Height, over all seam pairs:")
    for k in sorted(drops):
        print("    %+3d : %d" % (k, drops[k]))

    if focus is None:
        return
    fx, fy = focus
    print()
    print("neighbourhood of (%d,%d):" % (fx, fy))
    for y in range(fy - 4, fy + 5):
        row = "y=%4d " % y
        for x in range(fx - 4, fx + 5):
            c = cells.get((x, y))
            s = ("%s/%d" % (sym(c["tile"]), c["height"])) if c else "?"
            row += ("[%9s]" % s) if (x, y) == (fx, fy) else ("%11s" % s)
        print(row)


main()