#!/usr/bin/env python3
"""For every land cell that touches water, report the shore coverage.

    python bank_check.py <map>

For each land cell with at least one water neighbour (8-way) it prints the
neighbour mask, the cell's own tile/Height, and whether the shore strip that
*should* cover it is present.  "Should" = the port's rule: a piece of width w
starting on the water side of the cell, i.e. columns [x-w+1, x] when the water
is east, [x, x+w-1] when it is west (same for rows).

Only cells whose strip is incomplete are listed in the summary section.
"""
import sys

sys.path.insert(0, ".")
import analyze_isopack5 as A

WATER = range(314, 328)
SHORE = range(89, 131)

# mask bits: NE 1, E 2, SE 4, S 8, SW 16, W 32, NW 64, N 128
DIRS = [
    (0x01, 1, -1), (0x02, 1, 0), (0x04, 1, 1), (0x08, 0, 1),
    (0x10, -1, 1), (0x20, -1, 0), (0x40, -1, -1), (0x80, 0, -1),
]


def is_water(cells, x, y):
    c = cells.get((x, y))
    return c is not None and c["tile"] in WATER


def main():
    path = sys.argv[1]
    cells, _s, _n = A.load_map(path)

    bad = []
    total = 0
    for (x, y), c in sorted(cells.items()):
        if c["tile"] in WATER:
            continue
        mask = 0
        for bit, dx, dy in DIRS:
            if is_water(cells, x + dx, y + dy):
                mask |= bit
        if mask == 0:
            continue
        total += 1
        own = c["tile"] in SHORE
        # where the piece covering (x,y) must have started
        ox = x if not (mask & 0x07) else None      # placeholder, filled below
        bad.append(((x, y), mask, c["tile"], c["height"], own))

    print("land cells touching water: %d" % total)
    print("cells whose OWN tile is shore: %d" % sum(1 for b in bad if b[4]))
    missing = [b for b in bad if not b[4]]
    print("cells with no shore tile on them: %d" % len(missing))
    print()
    for (x, y), mask, t, h, _own in missing:
        nb = []
        for name, bit, dx, dy in [
            ("N", 0x80, 0, -1), ("NE", 0x01, 1, -1), ("E", 0x02, 1, 0),
            ("SE", 0x04, 1, 1), ("S", 0x08, 0, 1), ("SW", 0x10, -1, 1),
            ("W", 0x20, -1, 0), ("NW", 0x40, -1, -1),
        ]:
            c = cells.get((x + dx, y + dy))
            mark = "*" if mask & bit else " "
            nb.append("%s%s=%s" % (mark, name, "?" if c is None else c["tile"]))
        print("(%3d,%3d) mask=%02X tile=%4d h=%d  %s"
              % (x, y, mask, t, h, " ".join(nb)))

    # group the missing ones by which side the water is on
    buckets = {"E": 0, "W": 0, "N": 0, "S": 0, "diag": 0}
    for (_p, mask, _t, _h, _o) in missing:
        sides = []
        if mask & 0x02:
            sides.append("E")
        if mask & 0x20:
            sides.append("W")
        if mask & 0x08:
            sides.append("S")
        if mask & 0x80:
            sides.append("N")
        if not sides:
            buckets["diag"] += 1
        for s in sides:
            buckets[s] += 1
    print()
    print("missing by water side: %s" % buckets)


main()