#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""纯形状判据（不依赖占位，最终图可跑）：
背靠背对角夹 = 两个对角相邻非水格 a,b，
  a 仅某对角方向深水、b 仅其反向对角深水，且二者正交四邻皆非深水。
另含第一处构型：拐角盖直边格——纯对角占位岸格 a，其 2x2 片覆盖的
  对角格 g 自己有正交深水（直边岸格），且 g 与 a 对角相邻。
深水=314..327。"""
import glob, os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import analyze_isopack5 as A

def load(p):
    c=A.load_map(p)[0]
    return {k:(314<=v["tile"]<=327) for k,v in c.items()}

def ww(W,q):
    v=W.get(q); return v if v is not None else False

def diag_pinch(W):
    pairs=set()
    for (x,y),water in W.items():
        if water: continue
        # 两种对角相邻：a=(x,y), b 在 NE(x+1,y-1) 或 SE(x+1,y+1)
        for (bx,by,da,db) in (
            (x+1,y-1,(x-1,y+1),(x+2,y-2)),   # a-SW水, b-NE水
            (x+1,y+1,(x-1,y-1),(x+2,y+2)),   # a-NW水, b-SE水
        ):
            if W.get((bx,by)) is not False:   # b 必须是非水陆
                continue
            # a 正交全陆
            if any(ww(W,q) for q in ((x,y-1),(x+1,y),(x,y+1),(x-1,y))): continue
            # b 正交全陆
            if any(ww(W,q) for q in ((bx,by-1),(bx+1,by),(bx,by+1),(bx-1,by))): continue
            # a 仅 da 对角深水
            if not ww(W,da): continue
            # b 仅 db 对角深水
            if not ww(W,db): continue
            # a 其它三个对角不深水
            ad=[(x-1,y-1),(x+1,y-1),(x-1,y+1),(x+1,y+1)]
            bd=[(bx-1,by-1),(bx+1,by-1),(bx-1,by+1),(bx+1,by+1)]
            if sum(ww(W,q) for q in ad)!=1: continue
            if sum(ww(W,q) for q in bd)!=1: continue
            pairs.add(tuple(sorted([(x,y),(bx,by)])))
    return pairs

print("=== 背靠背对角夹（第二处型）===")
for p in sorted(glob.glob(r"D:\新建文件夹\Ra2\Map.20261001-*.yrm")):
    pr=diag_pinch(load(p))
    print("  原版 %-22s %d %s" % (os.path.basename(p)[:22], len(pr), sorted(pr)[:6]))
for p in sorted(glob.glob(r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_2026100*.map"))[-4:]:
    pr=diag_pinch(load(p))
    print("  移植 %-22s %d %s" % (os.path.basename(p)[:22], len(pr), sorted(pr)[:8]))