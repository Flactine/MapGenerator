# -*- coding: utf-8 -*-
# 精确判据：2x2 方块四格全是陆地，但方块的"一对外对角"都是水：
#   方块左上=(x,y)，四格 (x,y)(x+1,y)(x,y+1)(x+1,y+1)
#   NW外对角=(x-1,y-1)   SE外对角=(x+2,y+2)   -> 对角线A
#   NE外对角=(x+2,y-1)   SW外对角=(x-1,y+2)   -> 对角线B
# 任一对角线两端皆水 = 岸线在 2x2 尺度上发生单格错台
import io, os, sys
base = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput"
name = sys.argv[1]
W = {}
T = {}
with io.open(os.path.join(base, name), "r", encoding="utf-8", errors="replace") as fp:
    for line in fp:
        p = line.split()
        if len(p) < 12: continue
        try: x = int(p[0]); y = int(p[1])
        except Exception: continue
        t = int(p[2])
        T[(x,y)] = t
        W[(x,y)] = (314 <= t <= 327)

hits = []   # (x,y, 对角线)
for (x,y) in W:
    block = [(x,y),(x+1,y),(x,y+1),(x+1,y+1)]
    if any(q not in W or W[q] for q in block):
        continue   # 四格必须都在图内且都是陆地
    nw, se = (x-1,y-1), (x+2,y+2)
    ne, sw = (x+2,y-1), (x-1,y+2)
    a = W.get(nw) is True and W.get(se) is True
    b = W.get(ne) is True and W.get(sw) is True
    if a or b:
        hits.append((x, y, "NW-SE" if a else "", "NE-SW" if b else ""))

print("命中 2x2 错台方块数:", len(hits))
cells = set()
for x,y,a,b in hits:
    print("  方块左上(%d,%d) %s%s  四格=%s 瓦片=%s"
          % (x, y, a, b,
             [(x,y),(x+1,y),(x,y+1),(x+1,y+1)],
             [T[q] for q in [(x,y),(x+1,y),(x,y+1),(x+1,y+1)]]))
    cells.update([(x,y),(x+1,y),(x,y+1),(x+1,y+1)])

user = [(48,51),(49,51),(49,50),(49,49),(111,65)]
print()
print("用户标的 5 格是否全部被覆盖:")
for q in user:
    print("   %s : %s  (t=%d)" % (q, "命中" if q in cells else "未命中", T.get(q,-1)))

# 我之前错标的 20 处方块中心（取每片 2x2 左上）
wrong20 = [(67,27),(69,29),(49,30),(56,35),(72,35),(65,39),(67,41),(55,42),
           (76,45),(79,48),(55,55),(77,55),(73,57),(112,56),(127,60),
           (129,63),(129,73),(111,74),(110,77),(109,84)]
hitblocks = set((x,y) for x,y,a,b in hits)
print()
print("之前错标的 20 处是否被新判据命中（应全部为否）:")
bad = [q for q in wrong20 if q in hitblocks]
print("   误命中:", bad if bad else "无，20 处全部排除")