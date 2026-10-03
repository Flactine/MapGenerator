# -*- coding: utf-8 -*-
# 模拟 FillNarrowWaterChannels：快照上把"某正交轴两侧皆陆"的水格填成陆地，再统计残余
import io, os, sys

base = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput"
name = sys.argv[1]

cells = {}
with io.open(os.path.join(base, name), "r", encoding="utf-8", errors="replace") as fp:
    for line in fp:
        p = line.split()
        if len(p) < 12: continue
        try: x = int(p[0]); y = int(p[1])
        except Exception: continue
        cells[(x, y)] = int(p[2])

water = set((x, y) for (x, y), t in cells.items() if 314 <= t <= 327)

def pinched(ws, x, y):
    W = (x - 1, y) in ws; E = (x + 1, y) in ws
    N = (x, y - 1) in ws; S = (x, y + 1) in ws
    # 只统计四邻都在图内（图内 4 邻一定存在，因为菱形内部；边界格跳过）
    for q in ((x-1,y),(x+1,y),(x,y-1),(x,y+1)):
        if q not in cells:
            return False
    return (not W and not E) or (not N and not S)

allfill = set()
ws = set(water)
for it in range(1, 9):
    fill = set(c for c in ws if pinched(ws, *c))
    if not fill:
        break
    allfill |= fill
    ws -= fill
    print("第%d遍: 命中 %d, 剩水 %d" % (it, len(fill), len(ws)))
resid = set(c for c in ws if pinched(ws, *c))
print("原水格=%d  累计填充=%d  最终水格=%d  残余窄水=%d" % (len(water), len(allfill), len(ws), len(resid)))
print("残余:", sorted(resid, key=lambda p: (p[1], p[0])))
print("路径点一带(x40-56,y44-58)填充:", sorted([p for p in allfill if 40 <= p[0] <= 56 and 44 <= p[1] <= 58], key=lambda p: (p[1], p[0])))