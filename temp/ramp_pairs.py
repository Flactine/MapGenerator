#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Split ramp cells into 8-connected ramp strips (one strip = one carved ramp),
then look for two strips whose WEST (low-end) toe cells sit within
|dx| <= 1 and |dy| == 2 - the double-ramp geometry behind the residual
orthogonal two-level clash. Read-only."""
import glob
import os
import sys
from collections import Counter, deque

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import analyze_isopack5 as A

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DIRS8 = [(dx, dy) for dx in (-1, 0, 1) for dy in (-1, 0, 1) if dx or dy]
ORTH = [(0, -1, "N"), (1, 0, "E"), (0, 1, "S"), (-1, 0, "W")]


def ramp_families(t):
    return (29 <= t <= 48) or (510 <= t <= 521) or (384 <= t <= 393)


def analyze(path):
    cells = A.load_map(path)[0]
    ramp = {p for p, c in cells.items() if ramp_families(c["tile"])}

    # connected strips
    strips = []
    seen = set()
    for p in ramp:
        if p in seen:
            continue
        q = deque([p])
        seen.add(p)
        blob = []
        while q:
            u = q.popleft()
            blob.append(u)
            for dx, dy in DIRS8:
                v = (u[0] + dx, u[1] + dy)
                if v in ramp and v not in seen:
                    seen.add(v)
                    q.append(v)
        strips.append(blob)

    # toe = westmost (min x, tie: min level) cells of each strip
    toes = []
    for i, blob in enumerate(strips):
        xmin = min(x for x, _ in blob)
        west = [p for p in blob if p[0] == xmin]
        lmin = min(cells[p]["level"] for p in west)
        toe = sorted(p for p in west if cells[p]["level"] == lmin)
        toes.append((i, toe[0], len(blob)))

    # close toe pairs
    pairs = []
    for a in range(len(toes)):
        for b in range(a + 1, len(toes)):
            _, (ax, ay), _ = toes[a]
            _, (bx, by), _ = toes[b]
            if abs(ax - bx) <= 2 and abs(ay - by) <= 3:
                pairs.append((toes[a][1], toes[b][1]))

    # clashes: strip toe's W neighbour is a CliffSet cell >= 2 levels higher
    clashes = []
    for _, (tx, ty), _ in toes:
        w = cells.get((tx - 1, ty))
        if w is not None and 49 <= w["tile"] <= 88 and w["level"] - cells[(tx, ty)]["level"] >= 2:
            clashes.append((tx, ty, cells[(tx, ty)]["tile"], cells[(tx, ty)]["level"],
                            w["tile"], w["level"]))
    return len(strips), sorted(pairs), clashes


for p in sorted(glob.glob(os.path.join(ROOT, "Map.*.yrm"))) + \
        sorted(glob.glob(os.path.join(ROOT, "rmg_*.map"))):
    n, pairs, clashes = analyze(p)
    flag = "  <<< CLASH" if clashes else ""
    print("%-34s strips=%-3d closeToePairs=%-2d toeWclashes=%d%s"
          % (os.path.basename(p), n, len(pairs), len(clashes), flag))
    for a, b in pairs:
        print("      pair toes %s %s" % (a, b))
    for c in clashes:
        print("      CLASH toe(%d,%d) t%d L%d  W=t%d L%d" % c)
