#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import sys
sys.path.insert(0, ".")
import analyze_isopack5 as A

cells = A.load(r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20260930_232832.isopack5.txt")

def lab(t):
    if t == 0xFFFF: return " ..."
    if 49 <= t <= 88: return "c%02d" % (t-48)
    if 29 <= t <= 48: return "s%02d" % (t-28)
    if 510 <= t <= 521: return "f%02d" % (t-509)
    if 89 <= t <= 130: return "S%02d" % (t-88)
    if 384 <= t <= 393: return "R%02d" % (t-383)
    if t == 0: return " 00"
    return "%4d" % t

x0,x1,y0,y1 = 84,93,109,118
print("       " + "".join(" x=%-3d  " % x for x in range(x0,x1+1)))
for y in range(y0,y1+1):
    row="y=%-3d " % y
    for x in range(x0,x1+1):
        c=cells.get((x,y))
        if c is None: row+="   .     "
        else: row+="%s/h%-2dL%d/s%-2d" % (lab(c["tile"]),c["height"],c["level"],c["slope"])
    print(row)
