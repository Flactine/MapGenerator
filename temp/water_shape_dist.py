#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""最终深水形状破碎度：原版 yrm vs 移植 map
深水 = tile 314..327（与美术帧无关的基础水瓦）
A. 2x2 陆块对角外皆深水（错台沙嘴）
B. 深水 1 格刺：深水格某正交轴两侧皆陆
C. 陆尖角：非深水格 正交>=3 面深水"""
import glob, os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import analyze_isopack5 as A

def load(p):
    c = A.load_map(p)[0]
    W={}
    for k,v in c.items():
        t=v["tile"]; W[k]=(314<=t<=327)
    return W

def stats(W):
    a=b=cc=0
    for (x,y),w in W.items():
        # 需要全部 8 邻在图内
        nb=[W.get((x+dx,y+dy)) for dx in(-1,0,1) for dy in(-1,0,1) if (dx,dy)!=(0,0)]
        if any(v is None for v in nb): continue
        n,s,e,west = W.get((x,y-1)),W.get((x,y+1)),W.get((x+1,y)),W.get((x-1,y))
        if w:
            if (west is False and e is False) or (n is False and s is False):
                b+=1
        else:
            if n and s and e and west: cc+=1
            orth=sum(bool(v) for v in (n,s,e,west))
            if orth>=3: cc+=0  # 上面四面已计；三面另计
            if orth==3: cc+=1
    # A 错台
    for (x,y),w in W.items():
        if w: continue
        blk=[(x,y),(x+1,y),(x,y+1),(x+1,y+1)]
        if any(q not in W or W[q] for q in blk): continue
        if (W.get((x-1,y-1)) and W.get((x+2,y+2))) or \
           (W.get((x+2,y-1)) and W.get((x-1,y+2))):
            a+=1
    return a,b,cc

print("%-22s %6s %6s %6s" % ("文件","错台块","水刺","陆尖角"))
for p in sorted(glob.glob(r"D:\新建文件夹\Ra2\Map.20261001-*.yrm")):
    a,b,c=stats(load(p))
    print("%-22s %6d %6d %6d" % (os.path.basename(p)[:22],a,b,c))
print("-"*46)
for p in sorted(glob.glob(r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_2026100*.map"))[-6:]:
    a,b,c=stats(load(p))
    print("%-22s %6d %6d %6d" % (os.path.basename(p)[:22],a,b,c))