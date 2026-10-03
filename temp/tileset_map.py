#!/usr/bin/env python3
"""Map an absolute tile index back to the temperat.ini tile set it came from.

The engine numbers tiles by walking [TileSetNNNN] sections in ascending section
number and accumulating TilesInSet - the same walk MapGenRiver.cpp does with
RunningTotal::Start.  That makes each [General] index (RoughTile, GreenTile,
MMRampBase, ...) an absolute base, and every engine tile index a base + offset.

Usage:  python tileset_map.py <temperat.ini> [tile ...]
"""

import re
import sys


def load(path):
    cur = None
    name = {}
    fname = {}
    tiles = {}
    order = []
    with open(path, "r", encoding="latin-1") as fh:
        for line in fh:
            s = line.strip()
            m = re.match(r"(?i)\[tileset0*(\d+)\]$", s)
            if m:
                cur = int(m.group(1))
                order.append(cur)
                name[cur] = ""
                fname[cur] = ""
                tiles[cur] = 0
                continue
            if cur is None:
                continue
            low = s.lower()
            if low.startswith("setname"):
                name[cur] = s.split("=", 1)[1].strip()
            elif low.startswith("filename"):
                fname[cur] = s.split("=", 1)[1].strip()
            elif low.startswith("tilesinset"):
                try:
                    tiles[cur] = int(s.split("=", 1)[1].strip())
                except ValueError:
                    pass
    order = sorted(set(order))
    out = []
    cum = 0
    for i in order:
        out.append((i, name[i], fname[i], tiles[i], cum))
        cum += tiles[i]
    return out, cum


def main():
    path = sys.argv[1]
    table, total = load(path)

    print("%4s %-26s %-22s %5s %6s" % ("sec", "SetName", "FileName", "n", "base"))
    for sec, name, fname, n, base in table:
        print("%4d %-26s %-22s %5d %6d" % (sec, name[:26], fname[:22], n, base))
    print("TOTAL tiles: %d" % total)

    for want in sys.argv[2:]:
        t = int(want, 0)
        hit = None
        for sec, name, fname, n, base in table:
            if base <= t < base + n:
                hit = (sec, name, fname, t - base, n, base)
                break
        if hit is None:
            print("tile %d: outside every set" % t)
        else:
            print("tile %d -> section %d %s (%s) offset %d of %d, base %d"
                  % (t, hit[0], hit[1], hit[2], hit[3], hit[4], hit[5]))


if __name__ == "__main__":
    main()
