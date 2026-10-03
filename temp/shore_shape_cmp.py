#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""形状级对照：NW 拐角片(t125/126)2x2 块周围的深水掩码
病灶块 (48,50) 移植图；在原版 6 图全部 t125/126 块上取同款掩码，
看原版是否出现相同水形。深水=tile314..327。"""
import glob, os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import analyze_isopack5 as A

def load(p):
    c = A.load_map(p)[0]
    return {k: (314 <= v["tile"] <= 327) for k, v in c.items()}, \
           {k: v["tile"] for k, v in c.items()}

def ring_sig(W, bx, by):
    # 以 2x2 块中心为原点，块外两圈(切比雪夫距 1..2)深水掩码，24 bit
    # 块四格 (bx,by)(bx+1,by)(bx,by+1)(bx+1,by+1)
    bits = []
    for r in (1, 2):
        for dy in range(-r, r+1):
            for dx in range(-r, r+1):
                if max(abs(dx),abs(dy)) != r:
                    continue
                # 相对块左上偏移
                gx, gy = bx+dx+(1 if dx>0 else 0), by+dy+(1 if dy>0 else 0)
                bits.append(1 if W.get((gx,gy)) else 0)
    return tuple(bits)

def blocks(W, T):
    out=[]
    for (x,y),t in T.items():
        if t not in (125,126): continue
        for ox,oy in ((0,0),(-1,0),(0,-1),(-1,-1)):
            bx,by=x+ox,y+oy
            q=[T.get((bx,by)),T.get((bx+1,by)),T.get((bx,by+1)),T.get((bx+1,by+1))]
            if all(v==t for v in q):
                out.append(((bx,by),t))
    return list(set(out))

# 病灶
Wp,Tp = load(r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261002_173632.map")
sick = ring_sig(Wp,48,50)
print("病灶块(48,50) 块外两圈深水掩码(1=深水):")
for r in (1,2):
    row=[sick[[ (1,2)].index(r)*0 ] ] if False else None
# 打印两圈示意
idx=0
for r in (1,2):
    print(" 距%d:"%r)
    for dy in range(-r,r+1):
        line=[]
        for dx in range(-r,r+1):
            if max(abs(dx),abs(dy))!=r:
                line.append("  "); continue
            line.append("~ " if sick[idx] else ". "); idx+=1
        print("   "+"".join(line))

print()
same=0; total=0; near=[]
for p in sorted(glob.glob(r"D:\新建文件夹\Ra2\Map.20261001-*.yrm")):
    W,T = load(p)
    for (bx,by),t in blocks(W,T):
        sig=ring_sig(W,bx,by)
        total+=1
        if sig==sick: same+=1
        # 距离=掩码不同位数
        d=sum(a!=b for a,b in zip(sig,sick))
        near.append((d,os.path.basename(p)[:18],(bx,by),t))
near.sort()
print("原版 t125/126 块总数=%d, 与病灶掩码完全相同: %d" % (total,same))
print("最接近的 8 个(汉明距, 文件, 位置, 片号):")
for d,f,xy,t in near[:8]:
    print("   距%-2d %s %s t%d" % (d,f,xy,t))