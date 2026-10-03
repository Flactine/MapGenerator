#!/usr/bin/env python3
"""Shore piece integrity: is every placed shoreNN.tem actually complete?

    python analyze_piece.py <map> [min_y] [max_y]

A shore piece is stamped by PlaceIsoTile as one tile index over the piece's
whole footprint (kShoreFootprints), with Height = col + row*w on each cell.
So a complete piece = the same tile index on every cell of the footprint, with
Height 0..w*h-1 as the sub-cell id.

For every cell holding a shore tile we look at its 8-neighbour connected blob
of the SAME tile index, take the blob's bounding box, and compare the heights
actually present with the expected {0 .. w*h-1} of that variant.

Classifies each blob:
    ok        heights present == expected set, blob size == w*h
    PARTIAL   some heights present, others missing  (lists them)
    CLUMPED   more cells than the footprint (two pieces merged)
Anything else (blob of a single height only) is reported as ORPHAN.
"""
import sys
from collections import defaultdict, Counter

sys.path.insert(0, ".")
import analyze_isopack5 as A

SHORE_LO, SHORE_HI = 89, 130
FOOT = {
    1: (2, 2), 2: (2, 2), 3: (2, 2), 4: (1, 2), 5: (2, 3), 6: (2, 3),
    7: (2, 2), 8: (2, 2), 9: (2, 2), 10: (2, 2), 11: (2, 2), 12: (2, 1),
    13: (3, 2), 14: (3, 2), 15: (2, 2), 16: (2, 2), 17: (2, 2), 18: (2, 2),
    19: (2, 2), 20: (1, 2), 21: (2, 3), 22: (2, 3), 23: (2, 2), 24: (2, 2),
    25: (2, 2), 26: (2, 2), 27: (2, 2), 28: (2, 1), 29: (3, 2), 30: (3, 2),
    31: (2, 2), 32: (2, 2), 33: (2, 2), 34: (2, 2), 35: (2, 2), 36: (2, 2),
    37: (2, 2), 38: (2, 2), 39: (2, 2), 40: (2, 2), 41: (6, 4), 42: (9, 5),
}

N8 = [(1, 0), (1, 1), (0, 1), (-1, 1), (-1, 0), (-1, -1), (0, -1), (1, -1)]


def main():
    path = sys.argv[1]
    lo_y = int(sys.argv[2]) if len(sys.argv) > 2 else None
    hi_y = int(sys.argv[3]) if len(sys.argv) > 3 else None

    cells, _s, _n = A.load_map(path)
    shore = {p: c for p, c in cells.items()
             if SHORE_LO <= c["tile"] <= SHORE_HI}

    seen = set()
    kinds = Counter()
    rows = []
    for p in sorted(shore):
        if p in seen:
            continue
        t = shore[p]["tile"]
        blob = []
        stack = [p]
        seen.add(p)
        while stack:
            q = stack.pop()
            blob.append(q)
            for dx, dy in N8:
                r = (q[0] + dx, q[1] + dy)
                if r not in seen and r in shore and shore[r]["tile"] == t:
                    seen.add(r)
                    stack.append(r)

        n12 = t - SHORE_LO + 1
        w, h = FOOT[n12]
        want = set(range(w * h))
        got = set(shore[q]["height"] for q in blob)
        xs = [q[0] for q in blob]
        ys = [q[1] for q in blob]
        status = "ok"
        if got == want and len(blob) == w * h:
            pass
        elif got == want:
            status = "clumped"
        elif got.issubset(want):
            status = "PARTIAL"
        else:
            status = "ORPHAN"
        kinds[status] += 1
        if status != "ok":
            rows.append((status, n12, w, h, len(blob), sorted(got),
                         sorted(want - got), (min(xs), min(ys), max(xs), max(ys))))

    print("%s" % path)
    print("shore blobs: %d   %s" % (len(kinds) and sum(kinds.values()) or 0,
                                    dict(kinds)))
    if lo_y is not None:
        rows = [r for r in rows if lo_y <= r[7][1] <= hi_y]
        print("  (filtered to Y %d..%d -> %d bad blobs)" % (lo_y, hi_y, len(rows)))
    for status, n12, w, h, n, got, missing, bb in rows[:80]:
        print("  %-8s n12=%-2d %dx%d  cells=%-2d heights=%-18s missing=%-12s bbox=%s"
              % (status, n12, w, h, n, got, missing, bb))
    if len(rows) > 80:
        print("  ... %d more" % (len(rows) - 80))


main()
