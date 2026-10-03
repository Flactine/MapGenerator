#!/usr/bin/env python3
"""Dump the TMP header (CellsInX / CellsInY) of the theater shore pieces.

TMP layout used by the port (MapGenRecalc.cpp ParseTmpInto):
    +0  int32 CellsInX     +4  int32 CellsInY
    +8  int32 cellWidth    +12 int32 cellHeight
    +16 int32 offset[CellsInX * CellsInY]

Compares the real art against kShoreFootprints in MapGenRiver.cpp - that table
is what PlaceIsoTile stamps, so a mismatch means the port occupies the wrong
number of map cells for that variant.
"""
import os
import re
import struct

ART = r"d:\新建文件夹\VSProject\MapGenerator\Tile资源\温和"

# kShoreFootprints, n12 = 1..42
TABLE = {
    1: (2, 2), 2: (2, 2), 3: (2, 2), 4: (1, 2), 5: (2, 3), 6: (2, 3),
    7: (2, 2), 8: (2, 2), 9: (2, 2), 10: (2, 2), 11: (2, 2), 12: (2, 1),
    13: (3, 2), 14: (3, 2), 15: (2, 2), 16: (2, 2), 17: (2, 2), 18: (2, 2),
    19: (2, 2), 20: (1, 2), 21: (2, 3), 22: (2, 3), 23: (2, 2), 24: (2, 2),
    25: (2, 2), 26: (2, 2), 27: (2, 2), 28: (2, 1), 29: (3, 2), 30: (3, 2),
    31: (2, 2), 32: (2, 2), 33: (2, 2), 34: (2, 2), 35: (2, 2), 36: (2, 2),
    37: (2, 2), 38: (2, 2), 39: (2, 2), 40: (2, 2), 41: (6, 4), 42: (9, 5),
}


def order(name):
    m = re.search(r"(\d+)\.tem$", name)
    return int(m.group(1)) if m else 0


files = [f for f in os.listdir(ART) if re.match(r"^shore\d+\.tem$", f, re.I)]
bad = 0
for name in sorted(files, key=order):
    k = order(name)
    data = open(os.path.join(ART, name), "rb").read()
    w, h = struct.unpack("<ii", data[:8])
    cw, ch = struct.unpack("<ii", data[8:16])
    tw, th = TABLE.get(k, (0, 0))
    mark = "" if (w, h) == (tw, th) else "   <== table says %dx%d" % (tw, th)
    if mark:
        bad += 1
    offs = struct.unpack("<%di" % (w * h), data[16:16 + 4 * w * h])
    frames = "".join("X" if o > 0 else "." for o in offs)
    print("%-14s art %2dx%-2d  table %2dx%-2d  cell %dx%-3d frames/row %s%s"
          % (name, w, h, tw, th, cw, ch,
             "/".join(frames[i * w:(i + 1) * w] for i in range(h)), mark))
print("mismatches: %d of %d" % (bad, len(files)))
