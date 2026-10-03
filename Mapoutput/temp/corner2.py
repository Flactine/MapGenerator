# -*- coding: utf-8 -*-
# 1) 全图 t121..128（拐角片33..40）各片实际占多少格
# 2) 82 个"仅对角擦水"格里各片型分布
import io, os, sys, collections
base = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput"
name = sys.argv[1]
water = {}
tilec = collections.Counter()
with io.open(os.path.join(base, name), "r", encoding="utf-8", errors="replace") as fp:
    for line in fp:
        p = line.split()
        if len(p) < 12: continue
        try: x = int(p[0]); y = int(p[1])
        except Exception: continue
        t = int(p[2])
        tilec[t] += 1
        water[(x,y)] = (314 <= t <= 327)

# 82 个 A 型格
A = []
for (x,y), isw in water.items():
    if isw: continue
    nb=[(x,y-1),(x+1,y),(x,y+1),(x-1,y)]; dg=[(x-1,y-1),(x+1,y-1),(x-1,y+1),(x+1,y+1)]
    if any(q not in water for q in nb+dg): continue
    if any(water[q] for q in nb): continue
    if any(water[q] for q in dg): A.append((x,y))

atiles = collections.Counter()
for x,y in A:
    # 重新取 tile
    pass

# 重新读一遍拿 tile 映射
xy2t = {}
with io.open(os.path.join(base, name), "r", encoding="utf-8", errors="replace") as fp:
    for line in fp:
        p = line.split()
        if len(p) < 12: continue
        try: x = int(p[0]); y = int(p[1])
        except Exception: continue
        xy2t[(x,y)] = int(p[2])

print("=== 全图各拐角片实际占地格数（n12=33..40 对应 t121..128）===")
names = {121:"33 SE 2x2",122:"34 SE 2x2",123:"35 NE 2x2",124:"36 NE 2x2",
         125:"37 NW 2x2",126:"38 NW 2x2",127:"39 SW 9x5大片",128:"40 SW 6x4大片"}
for t in range(121,129):
    print("  t%-3d n12=%-2d %-14s 全图 %3d 格, 其中落在对角擦水格上 %2d 格"
          % (t, t-88, names[t], tilec.get(t,0),
             sum(1 for q in A if xy2t.get(q)==t)))

other = collections.Counter(xy2t[q] for q in A if not (121 <= xy2t[q] <= 128))
print()
print("82 个对角擦水格上其余片型（被别的片覆盖）:", dict(other))
print("对角擦水格合计:", len(A))