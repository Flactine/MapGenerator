# -*- coding: utf-8 -*-
import io, os
base=r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput"
def load(stem):
    f=os.path.join(base,stem+".isopack5.txt")
    d={}
    with io.open(f,"r",encoding="utf-8",errors="replace") as fp:
        for line in fp:
            p=line.split()
            if len(p)<12: continue
            try: x=int(p[0]);y=int(p[1])
            except: continue
            d[(x,y)]=dict(t=int(p[2]),h=int(p[5]),L=int(p[8]),lt=int(p[9]),sl=int(p[10]))
    return d
pc=load("20261002_212051_PlaceCliffs")
cr=load("20261002_212051_CarveRegionRamps7")
def cls(t):
    if t in (0,0xFFFF): return "."
    if 29<=t<=48: return "r%02d"%(t-29)
    if 49<=t<=88: return "C%02d"%(t-49)
    return "%3d"%t
for name,D in (("PlaceCliffs",pc),("CarveRamps7",cr)):
    print("==== %s x86..95 y112..120 ===="%name)
    print("      "+" ".join("x%-4d"%x for x in range(86,96)))
    for y in range(112,121):
        cells=[]
        for x in range(86,96):
            c=D.get((x,y))
            if not c: cells.append("  ##"); continue
            cells.append("%s/L%d/s%d"%(cls(c["t"]),c["L"],c["sl"]))
        print("y%-3d %s"%(y," ".join(cells)))
    print()