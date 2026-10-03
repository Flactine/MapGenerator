#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""模拟落盘前剪枝：水/真悬崖/0xFFFF 上的树删除；坡保留；
出生点 d<=2 全删、3<=d<=5 棋盘格(x+y偶)删一半。"""
import glob, os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import analyze_isopack5 as A
p = sorted(glob.glob(r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_*.map"),
           key=os.path.getmtime)[-1]
cells = A.load_map(p)[0]
raw = open(p,"rb").read().decode("latin-1")
def section(n):
    out=[];on=False
    for ln in raw.splitlines():
        s=ln.strip()
        if s.startswith("["): on=(s==n); continue
        if on and "=" in s: out.append(s)
    return out
trees=[]
for ln in section("[Terrain]"):
    k,_,v=ln.partition("=")
    if len(v)>=5 and v[:4]=="TREE" and v[4].isdigit():
        kk=int(k); trees.append((kk//1000,kk%1000,v))  # key=X*1000+Y
starts=[]
for ln in section("[Waypoints]"):
    if ln.split("=")[0] in ("0","1"):
        vv=int(ln.split("=")[1]); starts.append((vv%1000,vv//1000))

def blocking(t):
    if t==0xFFFF: return "覆盖空瓦"
    if 314<=t<=327: return "水"
    if 49<=t<=88: return "真悬崖"
    if 148<=t<=175: return "水崖"
    return None
KEEP_INNER=2; SPARSE_OUTER=5
removed_block=[]; removed_sp=[]; kept=0
for x,y,nm in trees:
    t=cells.get((x,y),{}).get("tile",-1)
    b=blocking(t)
    if b: removed_block.append((x,y,nm,t,b)); continue
    d=min(max(abs(x-sx),abs(y-sy)) for sx,sy in starts)
    if d<=KEEP_INNER:
        removed_sp.append((x,y,nm,d,"清空")); continue
    if d<=SPARSE_OUTER and ((x+y)&1)==0:
        removed_sp.append((x,y,nm,d,"棋盘稀疏")); continue
    kept+=1
from collections import Counter
print("树总数",len(trees))
print("因地形删除",len(removed_block),dict(Counter(z[4] for z in removed_block)))
for z in removed_block: print("   ",z)
print("因出生点删除",len(removed_sp))
for z in removed_sp: print("   ",z)
print("保留",kept)