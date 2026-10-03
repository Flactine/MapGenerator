#!/usr/bin/env python3
"""Print the neighbourhood of every complete shore stamp in a map.

Usage: python analyze_shore2.py <map> [<map> ...]

For each shore variant n12 = 1..42 the script takes the FIRST cell whose tile is
that variant AND whose Height byte is 0 (the top-left cell of the stamp) and
prints a window around it, one character column per map cell:

    .  = placeholder / 0xFFFF (or 0)
    wN = water tile (314 + N - 1)
    NN = any other tile index
    S  = the shore tile itself (only for the variant being shown)

The window is 8 x 5 cells centred on the anchor, which is where the piece's
2x2 / 2x3 / 3x2 footprint lives.
"""
import sys

sys.path.insert(0, ".")
import analyze_isopack5 as A

SHORE_LO, SHORE_HI = 89, 130
WATER_LO, WATER_HI = 314, 327


def render(cells, cx, cy, tile):
    out = []
    for y in range(cy - 2, cy + 3):
        row = []
        for x in range(cx - 2, cx + 4):
            c = cells.get((x, y))
            if c is None:
                row.append(" .  ")
                continue
            t = c["tile"]
            if t == tile:
                row.append(" S%2d " % c["height"])
            elif t == 0xFFFF or t == 0:
                row.append(" .  ")
            elif WATER_LO <= t <= WATER_HI:
                row.append(" w%2d " % (t - WATER_LO + 1))
            else:
                row.append("%4d " % t)
        out.append("y=%-4d %s" % (y, "".join(row)))
    return "\n".join(out)


for path in sys.argv[1:]:
    cells, _secs, _n = A.load_map(path)
    print("=" * 72)
    print(path)

    first = {}
    for (x, y), c in sorted(cells.items()):
        t = c["tile"]
        if not (SHORE_LO <= t <= SHORE_HI):
            continue
        if c["height"] != 0:
            continue
        n12 = t - SHORE_LO + 1
        first.setdefault(n12, (x, y, t))

    for n12 in sorted(first):
        x, y, t = first[n12]
        print()
        print("--- n12=%d  tile=%d  anchor=(%d,%d) ---" % (n12, t, x, y))
        print(render(cells, x, y, t))
