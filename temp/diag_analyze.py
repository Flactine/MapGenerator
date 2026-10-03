#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Analyse cliff_diag.txt: find cells whose Level was changed by a later cliff
piece (STAMP-cell oldL != newL), and the SELECT scene around them."""
import re, sys
from collections import defaultdict

LOG = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\temp\cliff_diag.txt"
lines = open(LOG, encoding="utf-8", errors="replace").read().splitlines()
print("total lines:", len(lines))

# ---- all STAMP-cell level changes ----
changes = []   # (x,y, oldt, oldL, newL, newtslot, baseL, lineidx)
for i, ln in enumerate(lines):
    m = re.search(r"-> cell\((\d+),(\d+)\) oldt(-?\d+) oldL(\d+) newL(\d+) z(\d+) baseL(\d+)", ln)
    if m:
        x, y, ot, ol, nl, z, bl = map(int, m.groups())
        if ol != nl:
            changes.append((x, y, ot, ol, nl, z, bl, i))
print("cliff cells with Level rewritten:", len(changes))

# ---- event timeline per cell: SELECT at (x,y) or STAMP-cell touching (x,y) --
# we want a case where a FACE piece (1x2 z=[4,0], slots 2 or 8) was selected,
# then its wall cell later got raised to high by a z=4 piece.
FACE = {2, 8}  # 1x2 [#|#] z 4,0

# parse SELECTs in order
sels = []
for i, ln in enumerate(lines):
    m = re.match(r"SELECT \((\d+),(\d+)\) slot=(\d+) selfL=(\d+) mask=(0x[0-9A-Fa-f]+)", ln)
    if m:
        x, y, slot, selfL, mask = m.groups()
        sels.append((int(x), int(y), int(slot), int(selfL), int(mask, 16), i, ln))

print("SELECT events:", len(sels))

# Build per-cell ordered stamp events (from changes only) keyed by coord
print("\n--- Level rewrite delta histogram (all cliff stamp cells) ---")
from collections import Counter
print(Counter(nl - ol for *_, ol, nl, z, bl, i in
              [(c[0],c[1],c[2],c[3],c[4],c[5],c[6],c[7]) for c in changes]))
print("old-tile histogram for +4 rewrites:")
def lab(t):
    if t in (0, 0xFFFF): return "placeholder"
    if 49 <= t <= 88: return "C%02d" % (t-48)
    if 29 <= t <= 48: return "slope"
    return str(t)
c4 = Counter()
ex = []
for (x, y, ot, ol, nl, z, bl, i) in changes:
    if nl - ol == 4:
        c4[lab(ot)] += 1
        if len(ex) < 20:
            ex.append((x, y, ot, ol, nl, z, bl, i))
print(c4)
for e in ex:
    x,y,ot,ol,nl,z,bl,i = e
    print("  cell(%d,%d) oldt%s L%d->L%d z%d baseL%d @%d" % (x,y,lab(ot),ol,nl,z,bl,i))
