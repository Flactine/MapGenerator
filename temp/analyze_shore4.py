#!/usr/bin/env python3
"""Do the anchor cells' water masks reproduce the variant the code would pick?

Usage: python analyze_shore4.py <map> ...

Only anchor cells (Height == 0) are tested - those are the cells the placement
loop actually visits.  A neighbour that carries the SAME shore tile belongs to
this very stamp, so at mask time it was either water (the piece covers the
water side) or a placeholder.  Two masks are therefore tried:

    m_wat  = water neighbours only
    m_rel  = water neighbours, plus same-tile neighbours (assumed water)

A cell counts as "consistent" when one of the two masks makes the mode-2 or the
mode-1 rules produce the variant actually found on the map.
"""
import sys
from collections import Counter

sys.path.insert(0, ".")
import analyze_isopack5 as A

SHORE_LO, SHORE_HI = 89, 130
WATER_LO, WATER_HI = 314, 327
BITS = [0x80, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40]

FOOT = {}
for n in range(1, 43):
    FOOT[n] = None
W3 = {4, 12, 20, 28}


def mode2(mask, roll):
    if (mask & 0xA0) == 0xA0:
        return {(roll & 1) + 23, 23, 24} if (mask & 0x11) == 0x11 else {21, 30}
    if (mask & 0x82) == 0x82:
        return {(roll & 1) + 15, 15, 16} if (mask & 0x44) == 0x44 else {14, 22}
    if (mask & 0x0A) == 0x0A:
        return {(roll & 1) + 7, 7, 8} if (mask & 0x11) == 0x11 else {13, 6}
    if (mask & 0x28) == 0x28:
        return {(roll & 1) + 31, 31, 32} if (mask & 0x44) == 0x44 else {5, 29}
    return set()


def mode1(mask, roll):
    if mask == 0:
        return set()
    if mask & 0x02:
        return {12} if ((mask & 0x80) == 0 or (mask & 4) == 0 or (mask & 0x18)) \
            else {9, 10, 11}
    if mask & 0x20:
        return {28} if ((mask & 0x80) == 0 or (mask & 0x10) == 0 or (mask & 0x0C)) \
            else {25, 26, 27}
    if mask & 0x08:
        return {4}
    if mask & 0x80:
        return {20}
    if mask & 0x01:
        return {35, 36}
    if mask & 0x04:
        return {33, 34}
    if mask & 0x10:
        return {39, 40}
    if mask & 0x40:
        return {37, 38}
    return set()


for path in sys.argv[1:]:
    cells, _secs, _n = A.load_map(path)
    print("=" * 72)
    print(path)

    ok = Counter()
    bad = Counter()
    for (x, y), c in sorted(cells.items()):
        t = c["tile"]
        if not (SHORE_LO <= t <= SHORE_HI) or c["height"] != 0:
            continue
        n12 = t - SHORE_LO + 1
        mw = mr = 0
        for (dx, dy), bit in zip(A.DIRS, BITS):
            n = cells.get((x + dx, y + dy))
            if n is None:
                continue
            if WATER_LO <= n["tile"] <= WATER_HI:
                mw |= bit
                mr |= bit
            elif n["tile"] == t:
                mr |= bit
        hit = None
        for name, m in (("wat", mw), ("rel", mr)):
            for r in (0, 1):
                if n12 in mode2(m, r):
                    hit = "%s/m2" % name
                elif n12 in mode1(m, r):
                    hit = "%s/m1" % name
        if hit:
            ok[hit] += 1
        else:
            bad[(n12, mw, mr)] += 1

    tot = sum(ok.values()) + sum(bad.values())
    print("anchor cells: %d   explained: %d (%.0f%%)  %s"
          % (tot, sum(ok.values()), 100.0 * sum(ok.values()) / max(tot, 1),
             dict(ok)))
    print("unexplained anchors (n12, mask_water, mask_relaxed) - top 15:")
    for k, v in bad.most_common(15):
        print("   n12=%-3d wat=0x%02X rel=0x%02X  x%d" % (k[0], k[1], k[2], v))
