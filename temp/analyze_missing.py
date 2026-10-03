#!/usr/bin/env python3
"""For every PARTIAL shore piece, what occupies the cells it failed to stamp?

    python analyze_missing.py <map> [limit]

If the blocker is WATER the piece's footprint ran into the water body; if it is
another shore variant, two pieces collided; if 0xFFFF it was never stamped by
anyone; anything else is a third family.
"""
import sys
from collections import Counter

sys.path.insert(0, ".")
import analyze_isopack5 as A

SHORE_LO, SHORE_HI = 89, 130
WATER_LO, WATER_HI = 314, 327
FOOT = {k: (2, 2) for k in range(1, 41)}
FOOT.update({4: (1, 2), 20: (1, 2), 12: (2, 1), 28: (2, 1),
             5: (2, 3), 6: (2, 3), 21: (2, 3), 22: (2, 3),
             13: (3, 2), 14: (3, 2), 29: (3, 2), 30: (3, 2),
             41: (6, 4), 42: (9, 5)})
N8 = [(1, 0), (1, 1), (0, 1), (-1, 1), (-1, 0), (-1, -1), (0, -1), (1, -1)]


def fam(t):
    if t == 0xFFFF or t == 0:
        return "EMPTY(0xFFFF/0)"
    if WATER_LO <= t <= WATER_HI:
        return "WATER"
    if SHORE_LO <= t <= SHORE_HI:
        return "other-shore"
    return "tile-%d" % t


def main():
    path = sys.argv[1]
    limit = int(sys.argv[2]) if len(sys.argv) > 2 else 12
    cells, _s, _n = A.load_map(path)
    shore = {p: c for p, c in cells.items() if SHORE_LO <= c["tile"] <= SHORE_HI}

    seen = set()
    why = Counter()
    first_at = Counter()
    npartial = 0
    for p in sorted(shore):
        if p in seen:
            continue
        t = shore[p]["tile"]
        blob = [p]
        seen.add(p)
        stack = [p]
        while stack:
            q = stack.pop()
            for dx, dy in N8:
                r = (q[0] + dx, q[1] + dy)
                if r not in seen and r in shore and shore[r]["tile"] == t:
                    seen.add(r)
                    stack.append(r)
                    blob.append(r)
        w, h = FOOT[t - SHORE_LO + 1]
        got = dict((q, shore[q]["height"]) for q in blob)
        ax = min(got, key=lambda q: got[q])          # height-0 cell = anchor
        if set(got.values()) == set(range(w * h)):
            continue
        npartial += 1
        for row in range(h):
            for col in range(w):
                want = col + row * w
                q = (ax[0] + col, ax[1] + row)
                if q in got and got[q] == want:
                    continue
                occ = fam(cells[q]["tile"]) if q in cells else "out-of-map"
                why[occ] += 1
                first_at[occ] = why  # keep last
                if sum(why.values()) <= 0:
                    pass
    print("%s   partial pieces: %d" % (path, npartial))
    print("what sits on the cells a partial piece failed to stamp:")
    for k, v in why.most_common():
        print("    %-18s %d" % (k, v))


main()
