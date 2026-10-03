# -*- coding: utf-8 -*-
# 在"铺岸片前"快照上查关键格，并统计病态构型
import io, os
base = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput"
pre = os.path.join(base, "20261002_165759_lakeStartA.isopack5.txt")
D = {}
with io.open(pre, "r", encoding="utf-8", errors="replace") as fp:
    for line in fp:
        p = line.split()
        if len(p) < 12: continue
        try: x = int(p[0]); y = int(p[1])
        except Exception: continue
        D[(x,y)] = (int(p[2]), int(p[8]), int(p[9]), int(p[11]))

def isw(q):
    v = D.get(q)
    return None if v is None else (314 <= v[0] <= 327)

print("=== 关键格精确查询（铺前 lakeStartA）===")
for q in [(49,49),(49,50),(49,51),(50,50),(50,51),(50,52),(51,51),(48,50),(48,51)]:
    v = D.get(q)
    print("   %s tile=%s L=%s LT=%s P=%s" % (q,
          v[0] if v else "缺", v[1] if v else "-",
          v[2] if v else "-", v[3] if v else "-"))

print()
print("=== 铺前：正交 3~4 面环水的陆地尖角格 ===")
spikes = []
for (x,y), v in D.items():
    if 314 <= v[0] <= 327: continue
    n,s,e,w = isw((x,y-1)),isw((x,y+1)),isw((x+1,y)),isw((x-1,y))
    if None in (n,s,e,w): continue
    cnt = sum([n,s,e,w])
    if cnt >= 3:
        spikes.append((x,y,cnt))
for x,y,c in sorted(spikes, key=lambda q:(q[1],q[0])):
    print("   (%d,%d) 正交水 %d 面  N=%s E=%s S=%s W=%s tile=%d"
          % (x,y,c, isw((x,y-1)),isw((x+1,y)),isw((x,y+1)),isw((x-1,y)),
             D[(x,y)][0]))
print("共 %d 个" % len(spikes))

print()
print("=== 铺前：1 格宽陆桥（东西皆水 或 南北皆水）的陆格 ===")
bridges = []
for (x,y), v in D.items():
    if 314 <= v[0] <= 327: continue
    n,s,e,w = isw((x,y-1)),isw((x,y+1)),isw((x+1,y)),isw((x-1,y))
    if None in (n,s,e,w): continue
    if (e and w) or (n and s):
        bridges.append((x,y, "EW" if e and w else "", "NS" if n and s else ""))
near = [b for b in bridges if 44 <= b[0] <= 54 and 45 <= b[1] <= 55]
print("全图 %d 个，病灶区域(x44-54,y45-55)内:" % len(bridges))
for b in sorted(near, key=lambda q:(q[1],q[0])):
    print("   ", b)