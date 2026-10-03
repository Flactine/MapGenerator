# -*- coding: utf-8 -*-
# 查询若干格的 tile/Level/LandType/Passability
import io, os, sys
base = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput"
name = sys.argv[1]
want = [tuple(int(v) for v in a.split(",")) for a in sys.argv[2:]]
cells = {}
with io.open(os.path.join(base, name), "r", encoding="utf-8", errors="replace") as fp:
    for line in fp:
        p = line.split()
        if len(p) < 12: continue
        try: x = int(p[0]); y = int(p[1])
        except Exception: continue
        cells[(x, y)] = (int(p[2]), int(p[8]), int(p[9]), int(p[11]))
for (x, y) in want:
    v = cells.get((x, y))
    print("(%d,%d) -> %s" % (x, y, "缺" if v is None else "t=%d L=%d LT=%d P=%d" % v))