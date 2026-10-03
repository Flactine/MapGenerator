# -*- coding: utf-8 -*-
# 第一次刻坡 = LinkRegionNeighbours(全刻坡前) -> CarveRegionRamps0(第一次后)
import io, os
base = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput"
def load(n):
    d={}
    with io.open(os.path.join(base,n),encoding="utf-8",errors="replace") as f:
        for ln in f:
            p=ln.split()
            if len(p)<12: continue
            try: x=int(p[0]); y=int(p[1])
            except: continue
            d[(x,y)]=(int(p[2]),int(p[8]),int(p[10]))
    return d
a=load("20261002_004353_LinkRegionNeighbours.isopack5.txt")
b=load("20261002_004353_CarveRegionRamps0.isopack5.txt")
ch=[]
for k in b:
    if a.get(k)!=b.get(k) and 60<=k[0]<=88 and 60<=k[1]<=88:
        ch.append((k,a.get(k),b.get(k)))
print("in-window changed:",len(ch))
for (x,y),ca,cb in sorted(ch,key=lambda z:(z[0][1],z[0][0])):
    print("(%3d,%3d) %-12s -> %-12s" % (x,y,
        ("t%d/L%d/s%d"%ca) if ca else "none",
        ("t%d/L%d/s%d"%cb) if cb else "none"))
