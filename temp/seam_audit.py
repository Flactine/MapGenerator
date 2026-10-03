#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Comprehensive seam audit:
 A) empty (t0/FFFF) L-foot cell wedged between facade-bearing families
    (CliffSet 49-88 OR CliffRamps 384-393) on W/N/E with a 4-level-up neighbour.
 B) orthogonally adjacent CLIFF-SET cells whose Levels differ by >= 4
    (two cliffs meeting in a 4-level step with no facade between).
 C) empty cell right beside a cliffRamps (384-393) piece.
"""
import sys
sys.path.insert(0, ".")
import analyze_isopack5 as A

CLIFF = lambda t: 49 <= t <= 88
RAMPP = lambda t: 384 <= t <= 393
FACADE = lambda t: CLIFF(t) or RAMPP(t)
EMPTY = lambda t: t in (0, 65535)

for p in sys.argv[1:]:
    cells = A.load_map(p)[0]
    A_hits, B_hits, C_hits = [], [], []
    for (x, y), c in cells.items():
        w = cells.get((x - 1, y)); e = cells.get((x + 1, y))
        n = cells.get((x, y - 1)); s = cells.get((x, y + 1))
        foot = any(cells.get((x + dx, y + dy)) is not None
                   and cells[(x + dx, y + dy)]["level"] == c["level"] + 4
                   for dx in (-1, 0, 1) for dy in (-1, 0, 1)
                   if (dx, dy) != (0, 0))
        if EMPTY(c["tile"]) and w and e and n and foot \
                and FACADE(w["tile"]) and FACADE(e["tile"]) and FACADE(n["tile"]) \
                and w["level"] == c["level"] and e["level"] == c["level"]:
            A_hits.append((x, y, c["tile"], c["level"],
                           w["tile"], n["tile"], e["tile"]))
        # B: cliff-cliff 4-level orth steps
        for q, dn in ((w, "W"), (e, "E"), (n, "N"), (s, "S")):
            if q is not None and CLIFF(c["tile"]) and CLIFF(q["tile"]) \
                    and abs(q["level"] - c["level"]) >= 4:
                B_hits.append((x, y, c["tile"], c["level"],
                               dn, q["tile"], q["level"]))
        # C: empty cell adjacent to a cliffRamps piece
        if EMPTY(c["tile"]) and foot:
            for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1),
                           (1, 1), (1, -1), (-1, 1), (-1, -1)):
                q = cells.get((x + dx, y + dy))
                if q is not None and RAMPP(q["tile"]):
                    C_hits.append((x, y, c["tile"], c["level"],
                                   x + dx, y + dy, q["tile"], q["level"]))
                    break
    print("=== %s" % p)
    print("  A empty-between-facades: %d" % len(A_hits))
    for h in A_hits[:8]:
        print("     ", h)
    print("  B cliff-cliff 4-level steps: %d" % len(B_hits))
    for h in sorted(set(B_hits))[:10]:
        print("     ", h)
    print("  C empty+4up next to cliffRamps: %d" % len(C_hits))
    for h in C_hits[:10]:
        print("     ", h)
