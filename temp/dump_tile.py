#!/usr/bin/env python3
"""ASCII dump of one .tem tile cell, to verify the row-walk of the TMP image."""
import sys
sys.path.insert(0, ".")
import tmp_render as R

name = sys.argv[1]
cell = int(sys.argv[2]) if len(sys.argv) > 2 else 0
t = R.Tmp(r"d:\新建文件夹\VSProject\MapGenerator\Tile资源\温和\%s" % name)
print(name, "blocks", t.bw, t.bh, "img", t.iw, t.ih, "idx", t.idx)
res = t.image(cell)
if res is None:
    print("empty cell")
    sys.exit()
x, y, pix = res
print("x,y =", x, y)
for row in range(t.ih):
    r = pix[row * t.iw:(row + 1) * t.iw]
    print("%2d " % row + "".join("." if v == 255 else ("#" if v == 0 else str(v % 10))
                                 for v in r))
