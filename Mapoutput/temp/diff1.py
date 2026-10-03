# -*- coding: utf-8 -*-
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
a=load("20261002_004353_CarveRegionRamps0.isopack5.txt")
b=load("20261002_004353_CarveRegionRamps1.isopack5.txt")
xs=[]
for (x,y),v in b.items():
    if a.get((x,y))!=v:
        xs.append((x,y,a.get((x,y)),v))
print("changed:",len(xs))
for x,y,ca,cb in sorted(xs,key=lambda z:(z[0][1],z[0][0])):
    print("(%3d,%3d) %s -> %s" % (x,y,
        ("t%d/L%d/s%d"%ca) if ca else "none",
        ("t%d/L%d/s%d"%cb) if cb else "none"))
