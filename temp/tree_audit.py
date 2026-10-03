#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""统计最终 map 里 TREE 树坐标所在格的瓦片类型 + 出生点距离"""
import glob, os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import analyze_isopack5 as A

p = sorted(glob.glob(r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_*.map"),
           key=os.path.getmtime)[-1]
print("地图:", os.path.basename(p))
cells = A.load_map(p)[0]

# 读文本段（map 是压缩? analyze 已解 IsoMapPack5；Terrain/Waypoints 段需另读）
raw = open(p, "rb").read()
# 直接用 analyze 的解码结果之外，单独抓文本：map 可能整体未压缩? 试探
txt = None
for enc in ("latin-1",):
    try:
        t = raw.decode(enc)
        if "[Terrain]" in t or "[Waypoints]" in t:
            txt = t; break
    except Exception:
        pass
if txt is None:
    import zlib
    # 退化为打印：analyze_isopack5 是否已暴露文本
    print("未在明文找到段，查看 loader 能力")
    sys.exit(0)

def section(name):
    out=[]
    lines=txt.splitlines()
    on=False
    for ln in lines:
        s=ln.strip()
        if s.startswith("["):
            on = (s==name)
            continue
        if on and "=" in s:
            out.append(s)
    return out

trees=[]
for ln in section("[Terrain]"):
    key,_,val=ln.partition("=")
    if "TREE" in val:
        v=int(key)
        # [Terrain] key = X*1000 + Y（与 Waypoints 的 X+1000*Y 相反）
        trees.append((v//1000, v%1000, val))
wps=[int(ln.split("=")[1]) for ln in section("[Waypoints]") if ln.split("=")[0] in ("0","1")]
starts=[(v%1000, v//1000) for v in wps]
print("树总数:", len(trees), " 出生点:", starts)

def fam(t):
    if t==0 or t==0xFFFF: return "占位"
    if 29<=t<=48: return "坡基"
    if 49<=t<=88: return "悬崖"
    if 89<=t<=130: return "岸"
    if 314<=t<=327: return "水"
    if 384<=t<=393: return "崖坡"
    if 510<=t<=521: return "坡"
    if 493<=t<=509: return "LAT"
    if 1<=t<=28: return "地形"
    return "其它%d"%t
from collections import Counter
c=Counter()
bad=[]
for x,y,nm in trees:
    cell=cells.get((x,y))
    t=cell["tile"] if cell else -1
    f=fam(t); c[f]+=1
    if f in ("水","悬崖","崖坡","坡","坡基"):
        bad.append((x,y,nm,t,f))
print("树所在格瓦片族分布:", dict(c))
print("落在水/坡/崖的树 %d 棵:" % len(bad))
for b in bad[:40]:
    print("   (%d,%d) %s t=%d [%s]" % b)
# 出生点距离
near=[]
for x,y,nm in trees:
    for sx,sy in starts:
        d=max(abs(x-sx),abs(y-sy))
        if d<=4:
            near.append((x,y,nm,d)); break
print("出生点切比雪夫距离<=4 的树 %d 棵:" % len(near))
for q in near[:40]:
    print("   ", q)