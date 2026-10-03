# -*- coding: utf-8 -*-
import sys
sys.path.insert(0,r"d:\新建文件夹\VSProject\MapGenerator\temp")
import analyze_isopack5 as A
cells=A.load_map(r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261002_205302.map")[0]
# 出生点0=(110,112)，6x6 净地判定矩形 (x-3,y-3,6,6) = x107..112 y109..114
print("出生点选取的 6x6 净地矩形 x107..112 y109..114:")
for y in range(109,115):
    for x in range(107,113):
        c=cells.get((x,y)); t=c["tile"] if c else -1
        flag=""
        if t in (0,0xFFFF): flag="空地(占位)"
        elif 49<=t<=88: flag="<<<悬崖!"
        elif 131<=t<=147: flag="绿LAT"
        elif 89<=t<=130: flag="岸"
        else: flag="其它"
        if flag not in ("空地(占位)",):
            print("   (%d,%d) tile=%d %s"%(x,y,t,flag))
print("(以上只列非空地；无输出则6x6全空地)")