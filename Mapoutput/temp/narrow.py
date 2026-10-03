# -*- coding: utf-8 -*-
# 在最终快照上统计"窄水格"(某正交轴两侧皆陆)与"窄陆格"(某正交轴两侧皆水)
import io, os, sys, collections

base = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput"
name = sys.argv[1]

cells = {}
with io.open(os.path.join(base, name), "r", encoding="utf-8", errors="replace") as fp:
    for line in fp:
        p = line.split()
        if len(p) < 12: continue
        try:
            x = int(p[0]); y = int(p[1])
        except Exception:
            continue
        cells[(x, y)] = int(p[2])

def water(x, y):
    v = cells.get((x, y))
    if v is None:
        return None          # 图外
    return 314 <= v <= 327

narrowW = []
narrowL = []
for (x, y), t in cells.items():
    w = water(x, y)
    if w is None:
        continue
    n = water(x, y - 1); s = water(x, y + 1)
    e = water(x + 1, y); wl = water(x - 1, y)
    if None in (n, s, e, wl):
        continue
    if w:
        if (wl is False and e is False) or (n is False and s is False):
            narrowW.append((x, y))
    else:
        if (wl is True and e is True) or (n is True and s is True):
            narrowL.append((x, y))

print("窄水格(1格宽水道): %d" % len(narrowW))
print("窄陆格(1格宽陆桥/沙嘴): %d" % len(narrowL))

def dump(tag, lst):
    print()
    print("=== %s 分布(按15x15桶) ===" % tag)
    buck = collections.Counter((x // 15 * 15, y // 15 * 15) for x, y in lst)
    for (bx, by), c in sorted(buck.items(), key=lambda kv: -kv[1])[:20]:
        print("  块(%3d,%3d)  x%d" % (bx, by, c))

dump("窄水格", narrowW)
dump("窄陆格", narrowL)

if len(sys.argv) > 2:
    x0, x1, y0, y1 = [int(v) for v in sys.argv[2:6]]
    print()
    print("=== 区域明细 (%d..%d,%d..%d) ===" % (x0, x1, y0, y1))
    print("窄水:", sorted([p for p in narrowW if x0 <= p[0] <= x1 and y0 <= p[1] <= y1], key=lambda p: (p[1], p[0])))
    print("窄陆:", sorted([p for p in narrowL if x0 <= p[0] <= x1 and y0 <= p[1] <= y1], key=lambda p: (p[1], p[0])))