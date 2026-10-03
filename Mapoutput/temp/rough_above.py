# -*- coding: utf-8 -*-
import sys
sys.path.insert(0,r"d:\新建文件夹\VSProject\MapGenerator\temp")
import analyze_isopack5 as A
p=r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261002_205302.map"
cells=A.load_map(p)[0]
# 出生点0 (110,112) 上方大范围 6x12 全部非占位/非绿瓦，找粗地/异常瓦
sx,sy=110,112
from collections import Counter
c=Counter()
print("x%d..%d y%d..%d 非空地瓦分布:"%(sx-5,sx+5,sy-8,sy+2))
for y in range(sy-8,sy+3):
    for x in range(sx-5,sx+6):
        cell=cells.get((x,y))
        if not cell: continue
        t=cell["tile"]
        if t in (0,0xFFFF): continue
        c[t]+=1
print(dict(c))
# 逐格画上方 6 行
print()
for y in range(sy-8,sy+1):
    row=[]
    for x in range(sx-6,sx+6):
        cell=cells.get((x,y)); t=cell["tile"] if cell else -1
        if t in (0,0xFFFF): s=" ."
        elif 131<=t<=147: s=" g"   # green lat 系
        elif 493<=t<=509: s=" L"
        else: s="%02d"%(t%100)
        mark="*" if (x,y)==(sx,sy-1) else " "
        row.append(mark+s)
    print("y%-3d %s"%(y," ".join(row)))
print("      "+" ".join("x%-4d"%(x%100) for x in range(sx-6,sx+6)))