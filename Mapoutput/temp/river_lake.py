# -*- coding: utf-8 -*-
# termRand(河主循环后,末端湖前) -> lakeStartA(末端湖后) 对比病灶区域
import io, os
base = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput"
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
A = load("20261002_165759_termRand.isopack5.txt")
B = load("20261002_165759_lakeStartA.isopack5.txt")

x0,x1,y0,y1 = 44,54,44,56
def s(t):
    if t is None: return "  #"
    if 314 <= t <= 327: return " ~ "
    return " . "
for y in range(y0,y1+1):
    print("y%-2d  河后:%s   | 湖后:%s" % (
        y,
        "".join(s(A.get((x,y))) for x in range(x0,x1+1)),
        "".join(s(B.get((x,y))) for x in range(x0,x1+1))))
print("     " + "".join("%-3d" % x for x in range(x0,x1+1)))

print()
print("termRand -> lakeStartA 发生 陆->水 的格:")
for y in range(y0-6,y1+6):
    for x in range(x0-6,x1+6):
        a, b = A.get((x,y)), B.get((x,y))
        if a is None or b is None: continue
        aw, bw = 314<=a<=327, 314<=b<=327
        if not aw and bw:
            print("   (%d,%d) t%d->水" % (x,y,a))
print("发生 水->陆 的格:")
for y in range(y0-6,y1+6):
    for x in range(x0-6,x1+6):
        a, b = A.get((x,y)), B.get((x,y))
        if a is None or b is None: continue
        aw, bw = 314<=a<=327, 314<=b<=327
        if aw and not bw:
            print("   (%d,%d) 水->t%d" % (x,y,b))