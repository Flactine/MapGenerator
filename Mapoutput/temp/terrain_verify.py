# -*- coding: utf-8 -*-
# 只验证、不下结论：
# (1) 工程 .map 里 [Terrain] 打包键 key=X+1000Y 的实际落点地形
# (2) [Waypoints] 0..n 打包键的落点地形（出生点应是 Passable 平地）
# 对每个键同时给"当前写法"和"转置写法"两种解释的格数据，由事实判断。
import sys
path = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261003_143645.isopack5.txt"
import re

# dump: X Y tile bMapData bSubTile bHeight bMapData2 H L land slope pass
cells = {}
for line in open(path, encoding="utf-8", errors="replace"):
    if line.startswith(";"): continue
    p = line.split()
    if len(p) < 12: continue
    cells[(int(p[0]), int(p[1]))] = (int(p[2]), int(p[8]), int(p[10]), int(p[11]))

def terrain_objects(mapf):
    out=[]; sec=""
    for l in open(mapf, encoding="utf-8", errors="replace"):
        l=l.rstrip("\n")
        if l.startswith("["): sec=l; continue
        if sec=="[Terrain]" and "=" in l:
            k,v=l.split("=",1)
            out.append((int(k), v))
    return out

def waypoint_keys(mapf):
    out=[]; sec=""
    for l in open(mapf, encoding="utf-8", errors="replace"):
        l=l.rstrip("\n")
        if l.startswith("["): sec=l; continue
        if sec=="[Waypoints]" and "=" in l:
            k,v=l.split("=",1)
            try:
                out.append((int(k), int(v)))
            except ValueError:
                pass
    return out

mapf = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261003_143645.map"

def desc(x,y):
    c = cells.get((x,y))
    if c is None: return "MISSING/no-record"
    t,L,s,pa = c
    return "tile=%d L=%d slope=%d pass=%d" % (t,L,s,pa)

print("===== [Terrain]  (key 按 X+1000Y 打包；PosToXY: x=key%%1000,y=key//1000) =====")
to = terrain_objects(mapf)
print("count:", len(to))
flatA=flatB=0
for k,v in to[:20]:
    x, y = k % 1000, k // 1000          # 当前写法的 (X,Y)
    da = desc(x,y); db = desc(y,x)
    print("%-8s key=%-6d -> A(X=%d,Y=%d): %-34s | B(X=%d,Y=%d): %s"
          % (v, k, x,y,da, y,x,db))

print()
print("===== [Waypoints] =====")
wp = waypoint_keys(mapf)
print("count:", len(wp), "first keys:", [k for k,_ in wp][:12])
for k,pack in wp[:10]:
    x, y = pack % 1000, pack // 1000
    print("wp%-3d pack=%-6d -> A(X=%d,Y=%d): %-34s | B(X=%d,Y=%d): %s"
          % (k, pack, x,y,desc(x,y), y,x,desc(y,x)))
