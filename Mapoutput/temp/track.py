# -*- coding: utf-8 -*-
# 逐阶段追踪尖角 (50,51) 及周边 4 格的 tile 变化
import io, os
base = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput"
stages = [
    ("lakeStartA(铺前)", "20261002_165759_lakeStartA.isopack5.txt"),
    ("FloodFill后",      "20261002_165759_FloodFill.isopack5.txt"),
    ("CleanupTile后",    "20261002_165759_CleanupTile.isopack5.txt"),
    ("Bends后",          "20261002_165759_FillStaircaseBends.isopack5.txt"),
    ("SelectShoreTile1", "20261002_165759_SelectShoreTile.isopack5.txt"),
    ("SelectShoreTile2", "20261002_165759_SelectShoreTile2.isopack5.txt"),
]
watch = [(50,51),(49,50),(49,51),(48,50),(48,51),(49,49),(50,50),(50,52),(51,51),(52,51)]

def load(fn):
    d = {}
    with io.open(os.path.join(base, fn), "r", encoding="utf-8", errors="replace") as fp:
        for line in fp:
            p = line.split()
            if len(p) < 12: continue
            try: x = int(p[0]); y = int(p[1])
            except Exception: continue
            d[(x,y)] = int(p[2])
    return d

Ds = [(nm, load(fn)) for nm, fn in stages]
hdr = "格子      " + "".join("%-16s" % nm for nm,_ in Ds)
print(hdr)
for q in watch:
    row = "%-10s" % str(q)
    for _, d in Ds:
        t = d.get(q)
        row += "%-16s" % ("水" if (t is not None and 314<=t<=327)
                          else ("0占位" if t==0 else str(t)))
    print(row)