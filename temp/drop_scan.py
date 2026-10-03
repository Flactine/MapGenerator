"""Print a family+level map for a window of an *.isopack5.txt dump.

usage: python drop_scan.py <dump.txt> <x0> <x1> <y0> <y1>

Each cell is drawn as two characters: the tile family and the level digit.
The family letters follow the absolute tile numbers of the temperate theater.
"""

import sys
from collections import Counter

from analyze_isopack5 import load, DIRS


def fam(t):
    if t == 0 or t == 65535:
        return "P"          # placeholder / no own tile
    if 49 <= t <= 88:
        return "C"          # cliff set
    if 148 <= t <= 175:
        return "W"          # water cliffs
    if 314 <= t <= 327:
        return "~"          # water
    if 89 <= t <= 130:
        return "S"          # shore
    if t == 131:
        return "r"          # ruff
    if 132 <= t <= 147:
        return "c"          # clat
    if t == 418:
        return "d"          # sand
    if 419 <= t <= 434:
        return "D"          # dlat
    if 463 <= t <= 478:
        return "p"          # plat
    if t == 493:
        return "G"          # green
    if 494 <= t <= 509:
        return "g"          # glat
    if 29 <= t <= 48:
        return "R"          # ramp base
    if 510 <= t <= 521:
        return "F"          # rmpfx
    return "?"


def main():
    path = sys.argv[1]
    x0, x1, y0, y1 = (int(a) for a in sys.argv[2:6])
    cells = load(path)

    print("family+level, x %d..%d  y %d..%d" % (x0, x1, y0, y1))
    header = "    " + "".join("%-2d" % (x % 100) for x in range(x0, x1 + 1))
    print(header)
    for y in range(y0, y1 + 1):
        row = ""
        for x in range(x0, x1 + 1):
            c = cells.get((x, y))
            if c is None:
                row += ".."
            else:
                row += fam(c["tile"]) + str(c["level"] % 10)
        print("%3d " % y + row)

    # ---- the 4-level steps in the window -------------------------------
    kinds = Counter()
    naked = []
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            c = cells.get((x, y))
            if c is None:
                continue
            for dx, dy in ((1, 0), (1, 1), (0, 1), (-1, 1)):
                n = cells.get((x + dx, y + dy))
                if n is None:
                    continue
                if abs(n["level"] - c["level"]) != 4:
                    continue
                hi, lo = (c, n) if c["level"] > n["level"] else (n, c)
                kinds[(fam(hi["tile"]) + "/" + fam(lo["tile"]))] += 1
                if fam(hi["tile"]) not in "CW" and fam(lo["tile"]) not in "CW":
                    naked.append((hi, lo))

    print("\n-- level steps of 4, by (high family / low family) --")
    for k, v in kinds.most_common():
        print("   %-6s %d" % (k, v))

    print("\n-- %d steps with no cliff on either side; the high cells --"
          % len(naked))
    seen = set()
    for hi, lo in naked:
        key = (hi["tile"], hi["level"])
        if key in seen:
            continue
        seen.add(key)
        print("   high tile=%d level=%d slope=%d  low tile=%d level=%d slope=%d"
              % (hi["tile"], hi["level"], hi["slope"],
                 lo["tile"], lo["level"], lo["slope"]))


main()
