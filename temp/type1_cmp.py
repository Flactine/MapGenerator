#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""第一处型：单角对角岸格 a，其 2x2 拐角片朝 +X/+Y 展开时，
展开侧一整列/行的被盖格自己贴着一堵正交深水墙（直边岸），拐角片绿边
够不着 -> 无解。
NW 水(片朝SE): (a+1,0)(a+1,1) 两格 E 邻皆深水
NE 水(片朝SW,off0,0 实际盖 y..y+1): (a,1)(a+1,1) S 邻皆深水
SW 水(片朝NE): (a+1,0)(a+1,1) ... 对称
SE 水: ...
a 要求正交全陆、仅该单角深水。深水=314..327。"""
import glob, os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import analyze_isopack5 as A
def load(p):
    c=A.load_map(p)[0]
    return {k:(314<=v["tile"]<=327) for k,v in c.items()}
def w(W,q):
    v=W.get(q); return v is True

def find(W):
    hits=[]
    for (x,y),water in W.items():
        if water: continue
        N,E,S,We=(w(W,(x,y-1)),w(W,(x+1,y)),w(W,(x,y+1)),w(W,(x-1,y)))
        if N or E or S or We: continue
        nw,ne,sw,se=w(W,(x-1,y-1)),w(W,(x+1,y-1)),w(W,(x-1,y+1)),w(W,(x+1,y+1))
        # 仅单角
        corners=[("NW",nw),("NE",ne),("SW",sw),("SE",se)]
        if sum(c for _,c in corners)!=1: continue
        name=[n for n,c in corners if c][0]
        # 展开侧整列/整行贴深水墙
        ok=False
        if name=="NW":   # 片朝SE，东列两格 E 水
            ok = w(W,(x+2,y)) and w(W,(x+2,y+1))
        elif name=="NE": # 片南行两格 S 水
            ok = w(W,(x,y+2)) and w(W,(x+1,y+2))
        elif name=="SW": # 片东列... SW水在(x-1,y+1)，片朝NE，东列两格 E 水
            ok = w(W,(x+2,y)) and w(W,(x+2,y+1))
        elif name=="SE": # 片北行两格 N 水
            ok = w(W,(x,y-2)) and w(W,(x+1,y-2))
        if ok: hits.append(((x,y),name))
    return hits

print("=== 第一处型（拐角片整列盖直边岸）===")
for p in sorted(glob.glob(r"D:\新建文件夹\Ra2\Map.20261001-*.yrm")):
    h=find(load(p)); print("  原版 %-22s %d %s" % (os.path.basename(p)[:22],len(h),h[:8]))
for p in sorted(glob.glob(r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_2026100*.map"))[-4:]:
    h=find(load(p)); print("  移植 %-22s %d %s" % (os.path.basename(p)[:22],len(h),h[:10]))