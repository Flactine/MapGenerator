#!/usr/bin/env python3
"""Print a rectangular window of cells as a compact grid.

    python dump_window.py <map> <x0> <x1> <y0> <y1>

Each cell is printed as tile:height (tile id, and the sub-cell Height byte).
Cells outside the file are blank.
"""
import sys

sys.path.insert(0, ".")
import analyze_isopack5 as A


def main():
    path = sys.argv[1]
    x0, x1, y0, y1 = (int(v) for v in sys.argv[2:6])
    cells, _s, _n = A.load_map(path)
    print(path)
    header = "      " + "".join("%-9d" % x for x in range(x0, x1 + 1))
    print(header)
    for y in range(y0, y1 + 1):
        row = "y=%-3d " % y
        for x in range(x0, x1 + 1):
            c = cells.get((x, y))
            if c is None:
                row += "%-9s" % "."
            else:
                row += "%-9s" % ("%d:%d" % (c["tile"], c["height"]))
        print(row)


main()
