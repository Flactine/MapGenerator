# -*- coding: utf-8 -*-
# 统计最终图上的"对角擦水"构型：
#   A 型：陆地格正交 4 邻全陆，但对角邻有水（水在 2x2 的一个角，1水3陆）
#   B 型：陆地格正交 4 邻中 >=3 个水（1陆3水的陆尖角）
# 水判据：tile 314..327
import io, os, sys, collections
base = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput"
name = sys.argv[1]
cells = {}
tiles = {}
with io.open(os.path.join(base, name), "r", encoding="utf-8", errors="replace") as fp:
    for line in fp:
        p = line.split()
        if len(p) < 12: continue
        try: x = int(p[0]); y = int(p[1])
        except Exception: continue
        t = int(p[2])
        cells[(x, y)] = (314 <= t <= 327)
        tiles[(x, y)] = t

D = [(-1,-1),(0,-1),(1,-1),(-1,0),(1,0),(-1,1),(0,1),(1,1)]
A = []   # 仅对角擦水的陆格
B = []   # 三/四面环水的陆尖角
for (x, y), isw in cells.items():
    if isw: continue
    vals = []
    ok = True
    for dx, dy in D:
        v = cells.get((x+dx, y+dy))
        if v is None:
            ok = False; break
        vals.append(v)
    if not ok: continue
    nw, n, ne, w, e, sw, s, se = vals
    orth = sum([n, s, e, w])
    diag = [("NE",ne),("SE",se),("SW",sw),("NW",nw)]
    dwater = [z[0] for z in diag if z[1]]
    if orth == 0 and dwater:
        A.append((x, y, dwater, tiles[(x,y)]))
    if orth >= 3:
        B.append((x, y, orth, dwater, tiles[(x,y)]))

print("A 型(仅对角擦水的陆格): %d" % len(A))
buck = collections.Counter(tuple(sorted(a[2])) for a in A)
for k, c in buck.most_common():
    print("   对角水方向 %s : %d" % (k, c))
print("明细(前 60):")
for x, y, dw, t in sorted(A, key=lambda a:(a[1],a[0]))[:60]:
    print("   (%d,%d) %s t=%d" % (x, y, "/".join(dw), t))
print()
print("B 型(正交>=3面环水的陆尖角): %d" % len(B))
for x, y, orth, dw, t in sorted(B, key=lambda a:(a[1],a[0]))[:40]:
    print("   (%d,%d) orth水=%d 对角=%s t=%d" % (x, y, orth, "/".join(dw), t))