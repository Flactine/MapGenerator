#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Map-wide diagnosis of ramp / hole layout in the generated map."""
import sys
from collections import Counter
sys.path.insert(0, ".")
import analyze_isopack5 as A

MAP = sys.argv[1] if len(sys.argv) > 1 else r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20260930_222419.map"
DIRS = [(1, 0), (1, 1), (0, 1), (-1, 1), (-1, 0), (-1, -1), (0, -1), (1, -1)]

cells, _, _ = A.load_map(MAP)

# 1. bare 0xFFFF holes: no multi-cell shore/cliff piece in the 8-neighbourhood
MULTI = lambda t: 89 <= t <= 130
bare_holes = []
covered = 0
for (x, y), c in cells.items():
    if c["tile"] != 0xFFFF:
        continue
    nb = [cells.get((x + dx, y + dy)) for dx, dy in DIRS]
    if any(q and MULTI(q["tile"]) for q in nb):
        covered += 1
        continue
    bare_holes.append((x, y, c["level"]))

print("0xFFFF cells: covered-by-shore=%d  BARE HOLES=%d" % (covered, len(bare_holes)))
print("bare-hole level histogram:", Counter(lv for _, _, lv in bare_holes))
# cluster bare holes
hole_set = {(x, y) for x, y, _ in bare_holes}
seen = set()
clusters = []
for p in hole_set:
    if p in seen:
        continue
    stack = [p]; seen.add(p); blob = []
    while stack:
        q = stack.pop(); blob.append(q)
        for dx, dy in DIRS:
            r = (q[0] + dx, q[1] + dy)
            if r in hole_set and r not in seen:
                seen.add(r); stack.append(r)
    clusters.append(blob)
clusters.sort(key=len, reverse=True)
print("bare-hole clusters: %d, biggest sizes: %s" %
      (len(clusters), [len(b) for b in clusters[:15]]))
for b in clusters[:10]:
    xs = [p[0] for p in b]; ys = [p[1] for p in b]
    lv = Counter(cells[p]["level"] for p in b)
    print("  size=%-3d bbox x%d..%d y%d..%d levels=%s" %
          (len(b), min(xs), max(xs), min(ys), max(ys), dict(lv)))

# 2. ramp cells whose 8-neighbourhood spans a level jump >= 2 (ramp cannot bridge it)
bad_span = Counter()
examples = []
for (x, y), c in cells.items():
    t = c["tile"]
    if not (29 <= t <= 48 or 510 <= t <= 521):
        continue
    nbl = [cells[p]["level"] for dx, dy in DIRS for p in [(x + dx, y + dy)] if p in cells]
    if nbl and max(nbl) - min(nbl) >= 2:
        bad_span[(min(nbl), max(nbl))] += 1
        if len(examples) < 12:
            examples.append((x, y, t, c["level"], min(nbl), max(nbl)))
print("\nramp cells spanning level gap >=2: %d  span histogram: %s" %
      (sum(bad_span.values()), dict(bad_span)))
for e in examples:
    print("  (x=%d y=%d) tile=%d ownL=%d neighL=%d..%d" % e)

# 3. any two non-placeholder neighbours differing >=2 levels (raw height chaos)
jump_rows = Counter()
n_jump_edges = 0
for (x, y), c in cells.items():
    for dx, dy in ((1, 0), (0, 1), (1, 1), (-1, 1)):
        q = cells.get((x + dx, y + dy))
        if q and q["tile"] != 0xFFFF and c["tile"] != 0xFFFF:
            d = q["level"] - c["level"]
            if abs(d) >= 2:
                n_jump_edges += 1
                jump_rows[y] += 1
print("\nnon-placeholder edges with level gap>=2: %d" % n_jump_edges)

# 4. TileSet0025 cliff-ramp pieces (absolute indices 384..393 = ramp01..10)
RAMP0 = 384
REAL = {  # slot -> (w, h, occupied height indices)
    0: (3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 10, 11}),
    1: (3, 4, {0, 1, 3, 4, 5, 6, 7, 8, 9, 10}),
    2: (4, 3, {0, 1, 2, 3, 4, 5, 6, 7, 9, 10}),
    3: (4, 3, {1, 2, 4, 5, 6, 7, 8, 9, 10, 11}),
    4: (3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 10, 11}),
    5: (3, 4, {0, 1, 3, 4, 5, 6, 9}),
    6: (2, 2, {0, 1, 2}),
    7: (4, 3, {1, 2, 4, 5, 6, 7, 8, 9, 10, 11}),
    8: (4, 3, {0, 1, 2, 3, 4, 5, 9}),
    9: (2, 2, {0, 1, 2}),
}
pc = Counter()
bad_h = 0
for (x, y), c in cells.items():
    if RAMP0 <= c["tile"] <= RAMP0 + 9:
        slot = c["tile"] - RAMP0
        pc[slot] += 1
        if c["height"] not in REAL[slot][2]:
            bad_h += 1
print("\nTileSet0025 ramp pieces: total=%d  bad-height=%d" % (sum(pc.values()), bad_h))
for slot in range(10):
    print("  ramp%02d (tile %d): %d" % (slot + 1, RAMP0 + slot, pc.get(slot, 0)))
