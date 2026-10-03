# -*- coding: utf-8 -*-
# 把 25 个错台方块(每块4格)全部写成路径点，编号 200 起，每块连续 4 号
import io, os, sys
base = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput"
stem = sys.argv[1]
snap = os.path.join(base, stem + ".isopack5.txt")
srcmap = os.path.join(base, stem + ".map")
outmap = os.path.join(base, "step25_" + stem + ".map")

W, T = {}, {}
with io.open(snap, "r", encoding="utf-8", errors="replace") as fp:
    for line in fp:
        p = line.split()
        if len(p) < 12: continue
        try: x = int(p[0]); y = int(p[1])
        except Exception: continue
        t = int(p[2]); T[(x,y)] = t; W[(x,y)] = (314 <= t <= 327)

hits = []
for (x,y) in W:
    block = [(x,y),(x+1,y),(x,y+1),(x+1,y+1)]
    if any(q not in W or W[q] for q in block): continue
    a = W.get((x-1,y-1)) is True and W.get((x+2,y+2)) is True
    b = W.get((x+2,y-1)) is True and W.get((x-1,y+2)) is True
    if a or b:
        hits.append((x, y, "NW-SE" if a else "NE-SW"))

hits.sort(key=lambda h: (h[1], h[0]))
wp, rows = [], []
no = 200
for i, (x, y, diag) in enumerate(hits):
    cells = [(x,y),(x+1,y),(x,y+1),(x+1,y+1)]
    lo, hi = no, no+3
    for cx, cy in cells:
        wp.append((no, cx, cy)); no += 1
    tiles = sorted(set(T[q] for q in cells))
    rows.append((i+1, "%d-%d" % (lo,hi), (x,y), diag, tiles))

raw = open(srcmap, "rb").read().decode("latin-1")
lines = raw.split("\n"); out, done = [], False
for ln in lines:
    out.append(ln)
    if not done and ln.strip() == "1=115054":
        for n, cx, cy in wp:
            out.append("%d=%d" % (n, cx + 1000*cy))
        done = True
open(outmap, "wb").write("\n".join(out).encode("latin-1"))

for i, rng, xy, diag, tiles in rows:
    mark = "  <== 你已确认错" if xy in ((48,50),(110,65)) else ""
    print("方块%2d  路径点%-8s 左上%-9s %s 瓦片%s%s"
          % (i, rng, xy, diag, tiles, mark))
print("\n文件:", outmap)