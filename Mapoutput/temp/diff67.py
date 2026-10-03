# -*- coding: utf-8 -*-
# 对比 CarveRegionRamps6 -> 7，找 region7 这次刻坡实际改动
import io, os
base=r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput"
def load(stem):
    d={}
    with io.open(os.path.join(base,stem+".isopack5.txt"),"r",encoding="utf-8",errors="replace") as fp:
        for line in fp:
            p=line.split()
            if len(p)<12: continue
            try: x=int(p[0]);y=int(p[1])
            except: continue
            d[(x,y)]=dict(t=int(p[2]),L=int(p[8]),sl=int(p[10]),m=int(p[3]) if False else 0)
    return d
a=load("20261002_212051_CarveRegionRamps6")
b=load("20261002_212051_CarveRegionRamps7")
RAMP0=29
def fam(t):
    if t in (0,0xFFFF): return "."
    if RAMP0<=t<=RAMP0+19: return "R%d"%(t-RAMP0+1)
    if 49<=t<=88: return "C%d"%(t-49)
    if 384<=393: 
        if 384<=t<=403: return "P%d"%(t-384)
    return str(t)
# 只看差异格，聚焦 x84..98 y108..122
print("6->7 差异(x84..98,y108..122):  格: 旧 -> 新")
for y in range(108,123):
    for x in range(84,99):
        ca=a.get((x,y)); cb=b.get((x,y))
        if not ca or not cb: continue
        if ca["t"]!=cb["t"] or ca["L"]!=cb["L"] or ca["sl"]!=cb["sl"]:
            print("  (%d,%d): t %d(L%d sl%d) -> %d(L%d sl%d)  [%s->%s]"%(
                x,y, ca["t"],ca["L"],ca["sl"], cb["t"],cb["L"],cb["sl"],
                fam(ca["t"]),fam(cb["t"])))