#!/usr/bin/env python3
"""Re-derive the shore variant from the water mask, and compare with the map.

Usage: python analyze_shore3.py <map> ...

Two facts make this exact:

  * a water tile is never overwritten by a shore stamp (PlaceIsoTile rejects any
    cell whose tile is outside the caller's [lo, hi] and is not a placeholder),
    so the final water pattern equals the water pattern seen by passes 3/4;
  * a neighbour that ends up carrying a shore tile was a placeholder at that
    moment, so it contributes no bit to the mask.

So mask(cell) = the eight water bits of the cell's neighbours in the FINAL map.
The script prints, per shore cell, the actual variant and the variant the code
rules would pick from that mask.
"""
import sys
from collections import Counter, defaultdict

sys.path.insert(0, ".")
import analyze_isopack5 as A

SHORE_LO, SHORE_HI = 89, 130
WATER_LO, WATER_HI = 314, 327

# direction order used by DIRS in analyze_isopack5: (0,-1),(1,-1),(1,0),(1,1),
# (0,1),(-1,1),(-1,0),(-1,-1)  =  N, NE, E, SE, S, SW, W, NW
BITS = [0x80, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40]


def water_mask(cells, x, y):
    m = 0
    for (dx, dy), bit in zip(A.DIRS, BITS):
        n = cells.get((x + dx, y + dy))
        if n is not None and WATER_LO <= n["tile"] <= WATER_HI:
            m |= bit
    return m


def mode2_n12(mask, roll):
    if (mask & 0xA0) == 0xA0:
        return (roll & 1) + 23 if (mask & 0x11) == 0x11 else (21 if (mask & 1) else 30)
    if (mask & 0x82) == 0x82:
        return (roll & 1) + 15 if (mask & 0x44) == 0x44 else (14 if (mask & 4) else 22)
    if (mask & 0x0A) == 0x0A:
        return (roll & 1) + 7 if (mask & 0x11) == 0x11 else (13 if (mask & 1) else 6)
    if (mask & 0x28) == 0x28:
        return (roll & 1) + 31 if (mask & 0x44) == 0x44 else (5 if (mask & 4) else 29)
    return None


def mode1_n12(mask, roll):
    if mask == 0:
        return None
    if mask & 0x02:
        return 12 if ((mask & 0x80) == 0 or (mask & 4) == 0 or (mask & 0x18)) else roll % 3 + 9
    if mask & 0x20:
        return 28 if ((mask & 0x80) == 0 or (mask & 0x10) == 0 or (mask & 0x0C)) else roll % 3 + 25
    if mask & 0x08:
        return 4
    if mask & 0x80:
        return 20
    if mask & 0x01:
        return (roll & 1) + 35
    if mask & 0x04:
        return (roll & 1) + 33
    if mask & 0x10:
        return (roll & 1) + 39
    if mask & 0x40:
        return (roll & 1) + 37
    return None


for path in sys.argv[1:]:
    cells, _secs, _n = A.load_map(path)
    print("=" * 72)
    print(path)

    agree = Counter()
    disagree = Counter()
    seen = defaultdict(int)
    for (x, y), c in sorted(cells.items()):
        t = c["tile"]
        if not (SHORE_LO <= t <= SHORE_HI):
            continue
        n12 = t - SHORE_LO + 1
        m = water_mask(cells, x, y)
        p2 = mode2_n12(m, 0) or mode2_n12(m, 1)
        p1 = mode1_n12(m, 0) or mode1_n12(m, 1)
        seen[(n12, m)] += 1
        if p2 is not None and (p2 == n12 or (p2 in (23, 24) and n12 in (23, 24))
                               or (p2 in (15, 16) and n12 in (15, 16))
                               or (p2 in (7, 8) and n12 in (7, 8))
                               or (p2 in (31, 32) and n12 in (31, 32))):
            agree["mode2"] += 1
        elif p1 is not None and p1 == n12:
            agree["mode1"] += 1
        else:
            disagree[(n12, m, "m2=%s" % p2, "m1=%s" % p1)] += 1

    total = sum(agree.values()) + sum(disagree.values())
    print("shore cells: %d   rule-match: %s   mismatch: %d"
          % (total, dict(agree), sum(disagree.values())))
    print("worst mismatches (n12, mask, which-rules-say):")
    for k, v in disagree.most_common(12):
        print("   n12=%-3d mask=0x%02X  %-10s %-10s  x%d" % (k[0], k[1], k[2], k[3], v))
    print("most common (n12, mask) pairs:")
    for k, v in sorted(seen.items(), key=lambda kv: -kv[1])[:12]:
        print("   n12=%-3d mask=0x%02X  x%d" % (k[0], k[1], v))
