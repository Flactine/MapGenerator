#!/usr/bin/env python3
"""Dump the per-sub-cell record headers of a tile's .tem plus how much of each
sub-cell's graphics is the magenta transparency key.

    python tem_info.py <tile> [<tile> ...]

For each sub-cell: index, footprint (col,row), record header (x, y, len,
z-offset), the number of magenta-key pixels (0xF81F-ish: r==63 and b==63) and
how many pixels are opaque art.
"""
import os
import sys

sys.path.insert(0, ".")
from tmp_render import Tmp, tile_file, load_pal, TILE_DIR

PAL = load_pal()


def main():
    for arg in sys.argv[1:]:
        tile = int(arg)
        name = tile_file(tile)
        path = os.path.join(TILE_DIR, name)
        if not os.path.isfile(path):
            print("tile %d: missing %s" % (tile, path))
            continue
        tmp = Tmp(path)
        print("tile %d = %s   block %dx%d  iw=%d ih=%d"
              % (tile, name, tmp.bw, tmp.bh, tmp.iw, tmp.ih))
        for i in range(tmp.bw * tmp.bh):
            col, row = i % tmp.bw, i // tmp.bw
            off = tmp.idx[i]
            if off == 0:
                print("   sub %d (c%d r%d): EMPTY record" % (i, col, row))
                continue
            hx = tmp._i32(off)
            hy = tmp._i32(off + 4)
            hlen = tmp._i32(off + 8)
            hz = tmp._i32(off + 12)
            img = tmp.data[off + 52:off + 52 + 900]
            key = 0
            other = 0
            for v in img:
                if PAL[v] == (255, 0, 255):
                    key += 1
                else:
                    other += 1
            print("   sub %d (c%d r%d): header xy=(%d,%d) len=%d z=%d"
                  "  key=%d art=%d" % (i, col, row, hx, hy, hlen, hz, key, other))
        print()


if __name__ == "__main__":
    main()
