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
snaps=[load("20261002_004353_CarveRegionRamps%d.isopack5.txt"%i) for i in range(6)]
# 找包含 (64..84,64..82) 改动的跳
for i in range(5):
    a,b=snaps[i],snaps[i+1]
    ch=[(k,a.get(k),b.get(k)) for k in b if a.get(k)!=b.get(k)
        and 60<=k[0]<=88 and 60<=k[1]<=88]
    allch=[k for k in b if a.get(k)!=b.get(k)]
    print("jump %d->%d : total changed=%d, in-window=%d" % (i,i+1,len(allch),len(ch)))
    for k,ca,cb in sorted(ch,key=lambda z:(z[0][1],z[0][0])):
        print("   (%3d,%3d) %s -> %s" % (k[0],k[1],
            ("t%d/L%d/s%d"%ca) if ca else "none",
            ("t%d/L%d/s%d"%cb) if cb else "none"))
