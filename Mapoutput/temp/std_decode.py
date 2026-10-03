# -*- coding: utf-8 -*-
# 用引擎统一编码 key=Y*1000+X (x=%1000,y=//1000) 重解 Terrain
import sys
sys.path.insert(0,r"d:\新建文件夹\VSProject\MapGenerator\temp")
import analyze_isopack5 as A
p=r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261002_195435.map"
cells=A.load_map(p)[0]
raw=open(p,"rb").read().decode("latin-1")
def sec(n):
    o=[];on=False
    for ln in raw.splitlines():
        s=ln.strip()
        if s.startswith("["): on=(s==n);continue
        if on and "=" in s:o.append(s)
    return o
trees=[]
for s in sec("[Terrain]"):
    k,v=s.split("=")
    if v[:4]=="TREE" and v[4].isdigit():
        kk=int(k); trees.append((kk%1000,kk//1000,v))   # 标准: x=%1000
def kind(t):
    if t in (0,0xFFFF): return "空地"
    if 314<=t<=327: return "水"
    if 49<=t<=88: return "悬崖"
    if 148<=t<=175: return "水崖"
    if 89<=t<=130: return "岸"
    if 29<=t<=48 or 384<=t<=393 or 510<=t<=521: return "坡"
    if 131<=t<=147 or 493<=t<=509: return "绿LAT"
    return "t%d"%t
from collections import Counter
print("标准解码后 树所在格分布:",dict(Counter(kind(cells.get(q,{}).get("tile",-1)) for q in trees)))
bad=[(x,y,nm,cells[(x,y)]["tile"]) for x,y,nm in trees if (x,y) in cells and kind(cells[(x,y)]["tile"]) in ("水","悬崖","水崖")]
print("落在水/崖的树:",len(bad))
for b in bad[:30]: print("   ",b)
print("\n路径点2/3 (30,58-59) 切比雪夫<=6 的树:")
for x,y,nm in sorted(trees,key=lambda q:(q[1],q[0])):
    if max(abs(x-30),abs(y-58))<=6 or max(abs(x-30),abs(y-59))<=6:
        c=cells.get((x,y)); print("   (%d,%d) %s [%s]"%(x,y,nm,kind(c["tile"]) if c else "缺"))