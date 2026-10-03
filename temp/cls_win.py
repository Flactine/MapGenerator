#!/usr/bin/env python3
"""Family-class ASCII map of a window, plus a Level view.

    python cls_win.py <map> <x0> <x1> <y0> <y1>
"""
import sys

sys.path.insert(0, ".")
import analyze_isopack5 as A


def cls(t):
    if t == 65535:
        return "."
    if t in (0, 1):
        return "_"
    if 29 <= t <= 48:
        return "B"          # RampBase  (slope = t-28)
    if 510 <= t <= 521:
        return "S"          # RampSmooth
    if 49 <= t <= 88:
        return "C"          # CliffSet cliff01..40
    if 148 <= t <= 175:
        return "X"          # WaterCliff
    if 89 <= t <= 130:
        return "W"          # Shore
    if t == 131:
        return "r"          # Ruff
    if 132 <= t <= 147:
        return "q"          # clat
    if 314 <= t <= 327:
        return "~"          # Water
    if 384 <= t <= 393:
        return "R"          # CliffRamps (RAMP 384..393)
    if 418 <= t <= 434:
        return "d"          # Sandy / dlat
    if 493 == t:
        return "G"
    if 494 <= t <= 509:
        return "g"
    if 534 == t:
        return "P"
    if 551 <= t <= 565:
        return "h"
    if 821 <= t <= 836:
        return "b"
    return "?"


def main():
    path = sys.argv[1]
    x0, x1, y0, y1 = (int(v) for v in sys.argv[2:6])
    cells, _s, _n = A.load_map(path)
    print(path)
    print("     " + "".join("%-3d" % x for x in range(x0, x1 + 1)))
    for y in range(y0, y1 + 1):
        row = "%-4d " % y
        for x in range(x0, x1 + 1):
            c = cells.get((x, y))
            row += "%-3s" % (" " if c is None else cls(c["tile"]))
        print(row)
    print()
    print("Level view (blank = no cell)")
    print("     " + "".join("%-3d" % x for x in range(x0, x1 + 1)))
    for y in range(y0, y1 + 1):
        row = "%-4d " % y
        for x in range(x0, x1 + 1):
            c = cells.get((x, y))
            row += "%-3s" % (" " if c is None else c["level"])
        print(row)


main()