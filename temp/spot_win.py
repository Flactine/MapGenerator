#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import sys
sys.path.insert(0, ".")
import analyze_isopack5 as A

txt = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20260930_232832.isopack5.txt"
cells = A.load(txt)

def lab(t):
    if t == 0xFFFF: return " ..."
    if 49 <= t <= 88: return "c%02d" % (t-48)
    if 29 <= t <= 48: return "s%02d" % (t-28)
    if 510 <= t <= 521: return "f%02d" % (t-509)
    if 89 <= t <= 130: return "S%02d" % (t-88)
    if t == 0: return " 00"
    return "%4d" % t

for (x0,x1,y0,y1,title) in [(70,74,85,90,"A: cliff10/11/09 chain (71,87)"),
                            (63,68,110,114,"B: (66,111) chain"),
                            (52,56,117,120,"C: (54,118)"),
                            (98,102,129,132,"D: (100,130)")]:
    print("=== %s ===" % title)
    print("       " + "".join("  x=%-3d " % x for x in range(x0,x1+1)))
    for y in range(y0,y1+1):
        row="y=%-3d " % y
        for x in range(x0,x1+1):
            c=cells.get((x,y))
            if c is None: row+="   .    "
            else: row+="%s/h%-2dL%d/s%-2d" % (lab(c["tile"]),c["height"],c["level"],c["slope"])
        print(row)
