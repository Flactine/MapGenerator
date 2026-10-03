"""Re-assemble every shore piece from the map dump and report broken ones.

usage: python shore_check.py <dump.txt>

A shore tile is stamped as one multi-cell piece: every covered cell stores the
same tile index and its own sub-tile offset (bSubTile), which the port writes as
sub = dy * w + dx inside the piece.  So anchor = (x - sub % w, y - sub // w) and
a sound piece has every one of its w * h cells present with the same tile.
"""

import sys
from collections import defaultdict

from analyze_isopack5 import load

# kShoreFootprints (MapGenRiver.cpp): slot 1..42 -> (w, h)
SHORE = [(2, 2), (2, 2), (2, 2), (1, 2), (2, 3), (2, 3), (2, 2), (2, 2), (2, 2),
         (2, 2), (2, 2), (2, 1), (3, 2), (3, 2), (2, 2), (2, 2), (2, 2), (2, 2),
         (2, 2), (1, 2), (2, 3), (2, 3), (2, 2), (2, 2), (2, 2), (2, 2), (2, 2),
         (2, 1), (3, 2), (3, 2), (2, 2), (2, 2), (2, 2), (2, 2), (2, 2), (2, 2),
         (2, 2), (2, 2), (2, 2), (2, 2), (6, 4), (9, 5)]


def main():
    cells = load(sys.argv[1])
    groups = defaultdict(dict)
    problems = []

    for (x, y), c in cells.items():
        t = c["tile"]
        if not (89 <= t <= 130):
            continue
        w, h = SHORE[t - 89]
        sub = c["bSubTile"]
        dx, dy = sub % w, sub // w
        if dx >= w or dy >= h:
            problems.append(("sub out of range", x, y, t, sub, w, h))
            continue
        key = (x - dx, y - dy, t)
        cell = (x, y, sub, c["level"])
        if (dx, dy) in groups[key] and groups[key][(dx, dy)] != cell:
            problems.append(("duplicate cell", x, y, t, sub))
        groups[key][(dx, dy)] = cell

    for (ax, ay, t), got in sorted(groups.items()):
        w, h = SHORE[t - 89]
        want = {(dx, dy) for dy in range(h) for dx in range(w)}
        missing = sorted(want - set(got))
        extra = sorted(set(got) - want)
        if missing or extra:
            problems.append(("partial", ax, ay, "tile=%d" % t,
                             "missing=%s" % missing, "extra=%s" % extra))

    print("%d shore pieces, %d problems" % (len(groups), len(problems)))
    for p in problems[:80]:
        print("  ", p)


main()
