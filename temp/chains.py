#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import re, sys
sys.path.insert(0, ".")
import analyze_isopack5 as A

log = open(r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\temp\cliff_diag.txt",
           encoding="utf-8", errors="replace").read().splitlines()
cells = A.load(r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261001_000251.isopack5.txt")

# the three overlap-broken anchors from audit
targets = [(117,77),(109,80),(108,81),(104,89),(104,90),(91,95),(91,96)]
def lab(t):
    if t==0xFFFF: return "..."
    if 49<=t<=88: return "C%02d"%(t-48)
    if 29<=t<=48: return "s%02d"%(t-28)
    if 510<=t<=521: return "f%02d"%(t-509)
    return str(t)

for (tx,ty) in [(117,77),(108,81),(104,89),(91,95)]:
    print("="*70)
    print("broken anchor near (%d,%d)" % (tx,ty))
    for dy in range(-2,3):
        for dx in range(-2,3):
            x,y=tx+dx,ty+dy
            c=cells.get((x,y))
            if c and 49<=c["tile"]<=88:
                # find SELECT for this anchor-ish cell
                pass
    # print SELECT lines for cells in the 5x5 window that are cliffs
    for i,ln in enumerate(log):
        m=re.match(r"SELECT \((\d+),(\d+)\) slot=(\d+) selfL=(\d+) mask=(0x[0-9A-Fa-f]+) \|(.*)",ln)
        if not m: continue
        x,y=int(m.group(1)),int(m.group(2))
        if abs(x-tx)<=3 and abs(y-ty)<=3:
            print(ln)
