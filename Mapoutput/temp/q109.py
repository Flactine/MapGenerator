# -*- coding: utf-8 -*-
import sys
sys.path.insert(0,r"d:\新建文件夹\VSProject\MapGenerator\temp")
import analyze_isopack5 as A
cells=A.load_map(r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261002_205302.map")[0]
for q in [(109,111),(110,111),(109,112),(108,111),(109,110)]:
    c=cells.get(q)
    if c:
        print("%s tile=%d Height=%d Level=%d Slope=%d Land=%d Pass=%d"%(
            q,c["tile"],c["height"],c["level"],c["slope"],c["land"],c.get("pass",-1)))
    else:
        print(q,"缺")
# 该格有没有地形/覆盖
p=r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261002_205302.map"
raw=open(p,"rb").read().decode("latin-1")
def sec(n):
    o=[];on=False
    for ln in raw.splitlines():
        s=ln.strip()
        if s.startswith("["): on=(s==n);continue
        if on and "=" in s:o.append(s)
    return o
print("\nTerrain对象(标准编码 x=%1000) 落点=109,111 附近:")
for s in sec("[Terrain]"):
    k,v=s.split("=");kk=int(k);x,y=kk%1000,kk//1000
    if max(abs(x-109),abs(y-111))<=1: print("  ",(x,y),v)
# Overlay 段需要单独解，看该格 overlay index
print("\n(OverlayPack 是二进制段，下面看 cells 解析是否带overlay)")
print("keys:",list(c for c in list(cells.values())[0].keys()))