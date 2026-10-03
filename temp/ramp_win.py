#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Dump a tile/level window around waypoints 2-5 in rmg_20260930_222419.map.

Cell glyph encodes tile family; the second char of each cell is the Level.
"""
import sys
sys.path.insert(0, ".")
import analyze_isopack5 as A

MAP = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20260930_222419.map"


def glyph(t):
    if t == 0xFFFF:
        return ".."        # covered / no own tile
    if 29 <= t <= 48:
        return "r%02d" % (t - 28)   # ramp base, pattern 1..20
    if 510 <= t <= 521:
        return "s%02d" % (t - 509)  # ramp smooth
    if 89 <= t <= 130:
        return "Sh"
    if t == 0:
        return "00"
    return "%2d" % (t % 100)


def main():
    cells, secs, total = A.load_map(MAP)
    xs = [p[0] for p in cells]
    ys = [p[1] for p in cells]
    print("bounds X %d..%d Y %d..%d records=%d" % (min(xs), max(xs), min(ys), max(ys), len(cells)))

    x0, x1, y0, y1 = 68, 92, 56, 78
    # header
    print("       " + "".join("  x=%-3d" % x for x in range(x0, x1 + 1)))
    for y in range(y0, y1 + 1):
        row = "y=%-3d  " % y
        for x in range(x0, x1 + 1):
            c = cells.get((x, y))
            if c is None:
                row += "   .  "
            else:
                row += "%s/L%-2d" % (glyph(c["tile"]), c["level"])
        print(row)

    # tile census inside the waypoint quad
    from collections import Counter
    cen = Counter()
    for (x, y), c in cells.items():
        if 74 <= x <= 86 and 60 <= y <= 72:
            cen[c["tile"]] += 1
    print("\nlocal tile census (x74..86,y60..72):")
    for t, n in cen.most_common():
        tag = ""
        if t == 0xFFFF: tag = "PLACEHOLDER"
        elif 29 <= t <= 48: tag = "RAMPBASE pattern %d" % (t - 28)
        elif 510 <= t <= 521: tag = "RAMPSMOOTH %d" % (t - 509)
        elif 89 <= t <= 130: tag = "SHORE"
        print("  tile %-6d x%-3d %s" % (t, n, tag))


main()
