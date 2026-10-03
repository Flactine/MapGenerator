#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Cliff window for rmg_20260930_230401 around waypoints 0-3 (x96..102,y99..104)."""
import sys
sys.path.insert(0, ".")
import analyze_isopack5 as A

MAP = sys.argv[1] if len(sys.argv) > 1 else r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20260930_230401.map"
TXT = MAP.rsplit(".", 1)[0] + ".isopack5.txt"
import os
cells = A.load(TXT) if os.path.isfile(TXT) else A.load_map(MAP)[0]

CLIFF0 = 49   # shoreTileIndex_ (CliffSet), 40 wide
WCLIFF0 = 148 # WaterCliffs 28 wide


def tag(t):
    if t == 0xFFFF:
        return " .. "
    if 29 <= t <= 48:
        return " s%02d" % (t - 28)
    if 510 <= t <= 521:
        return " f%02d" % (t - 509)
    if CLIFF0 <= t < CLIFF0 + 40:
        return "C%02d " % (t - CLIFF0 + 1)
    if WCLIFF0 <= t < WCLIFF0 + 28:
        return "W%02d " % (t - WCLIFF0 + 1)
    if 384 <= t <= 393:
        return "R%02d " % (t - 384 + 1)
    if t == 0:
        return " 00 "
    return " %-3d" % t


x0, x1, y0, y1 = 90, 110, 93, 109
print("        " + "".join(" x=%-3d " % x for x in range(x0, x1 + 1)))
for y in range(y0, y1 + 1):
    row = "y=%-3d  " % y
    for x in range(x0, x1 + 1):
        c = cells.get((x, y))
        if c is None:
            row += "   .   "
        else:
            row += "%s/h%-2dL%d" % (tag(c["tile"]), c["height"], c["level"])
    print(row)

# waypoint markers
wp = {0: (96, 102), 1: (98, 104), 2: (102, 102), 3: (100, 99)}
print("\nwaypoints:", wp)
