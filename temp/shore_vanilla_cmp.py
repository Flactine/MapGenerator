#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""原版 yrm vs 移植图：2x2 拐角岸片(shore33..40 = tile121..128)构型统计
判据：2x2 四格同属一个拐角片号(t121..128 同值)，
      数其中"正交邻水(tile314..327)"的格数。
病灶移植块：4 格里 0~1 格邻正边水 = 片基本盖在内陆。"""
import glob, os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import analyze_isopack5 as A

def isw(t): return 314 <= t <= 327

def analyze(path):
    cells = A.load_map(path)[0]
    T = {k: v["tile"] for k, v in cells.items()}
    blocks = {}   # (左上, 片号) -> 邻水格数
    for (x, y), t in T.items():
        if not (121 <= t <= 128):
            continue
        for ox, oy in ((0,0),(-1,0),(0,-1),(-1,-1)):
            bx, by = x+ox, y+oy
            q = [T.get((bx, by)), T.get((bx+1, by)),
                 T.get((bx, by+1)), T.get((bx+1, by+1))]
            if all(v == t for v in q):
                key = ((bx, by), t)
                nwater = 0
                detail = []
                for gx, gy in ((bx,by),(bx+1,by),(bx,by+1),(bx+1,by+1)):
                    orth = [T.get((gx,y2)) for y2 in (gy-1,gy+1)]
                    orth += [T.get((x2,gy)) for x2 in (gx-1,gx+1)]
                    hit = any(v is not None and isw(v) for v in orth)
                    nwater += hit
                    detail.append(hit)
                blocks[key] = (nwater, detail)
    return blocks

def report(tag, paths):
    print("="*70)
    print(tag)
    total_inland = 0
    for p in paths:
        b = analyze(p)
        from collections import Counter
        hist = Counter(v[0] for v in b.values())
        bad = {k: v for k, v in b.items() if v[0] <= 1}
        total_inland += len(bad)
        print("  %s" % os.path.basename(p))
        print("    拐角2x2块数=%d  邻水格数分布(0/1/2/3/4): %s  <=1格邻水: %d"
              % (len(b), dict(sorted(hist.items())), len(bad)))
        for (xy, t), (nw, det) in sorted(bad.items())[:12]:
            print("       t%-3d 左上%s 邻水格数=%d %s" % (t, xy, nw, det))
    print("  >>> %s 共 %d 个'拐角片几乎全在内陆'块" % (tag, total_inland))

van = sorted(glob.glob(r"D:\新建文件夹\Ra2\Map.20261001-*.yrm"))
report("原版 gamemd 山地图", van)
ports = sorted(glob.glob(r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261002_1*.map"))[-3:]
report("移植图(最近3张)", ports)