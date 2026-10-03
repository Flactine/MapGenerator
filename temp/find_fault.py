#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Find the white-seam configuration: a high (L+4) single/top cliff cell sitting
orthogonally next to a LOW face wall cell of a different cliff piece, with no
face tile bridging them. Then cross-reference the SELECT scene in cliff_diag."""
import sys, re
sys.path.insert(0, ".")
import analyze_isopack5 as A

MAP = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261001_000251.isopack5.txt"
cells = A.load(MAP)
CLIFF = lambda t: 49 <= t <= 88
DIRS = {0:(0,-1,"N"),2:(1,0,"E"),4:(0,1,"S"),6:(-1,0,"W")}

found = []
for (x,y), c in cells.items():
    if not CLIFF(c["tile"]):
        continue
    # wall cells of face pieces carry z0 -> their stored Level is low; top z4 high
    # detect: this cell is HIGH top (its piece slot in the flat-top family) while
    # an orthogonal neighbour is a cliff cell exactly 4 lower.
    for d,(dx,dy,nm) in DIRS.items():
        q = cells.get((x+dx,y+dy))
        if q and CLIFF(q["tile"]) and c["level"] - q["level"] == 4:
            found.append((x,y,c["tile"]-48,c["level"],q["tile"]-48,q["level"],nm,(x+dx,y+dy)))

# de-dup, show
seen=set()
print("high-cliff-cell adjacent to low-cliff-cell (4-step) edges: %d" % len(found))
for f in found[:40]:
    print("  (%d,%d) C%02d L%d  --%s--> (%d,%d) C%02d L%d" %
          (f[0],f[1],f[2],f[3],f[6],f[7][0],f[7][1],f[4],f[5]))

# cross-ref SELECT selfL for the HIGH cells
sel = {}
for ln in open(r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\temp\cliff_diag.txt",encoding="utf-8",errors="replace"):
    m=re.match(r"SELECT \((\d+),(\d+)\) slot=(\d+) selfL=(\d+) mask=(0x[0-9A-Fa-f]+) \|(.*)",ln)
    if m:
        sel[(int(m.group(1)),int(m.group(2)))] = (int(m.group(3)),int(m.group(4)),m.group(5),m.group(6))
print("\nSELECT scene for those HIGH cells:")
for f in found[:25]:
    k=(f[0],f[1])
    if k in sel:
        slot,selfL,mask,nbrs = sel[k]
        print("  (%d,%d) final C%02d L%d | SELECT slot=%d selfL=%d mask=%s%s"
              % (f[0],f[1],f[2],f[3],slot,selfL,mask,nbrs))
