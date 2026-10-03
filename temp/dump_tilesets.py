#!/usr/bin/env python3
"""Print the running tile index of each [General] tile-family key.

Mirrors RandomMapGenerator::LoadTheaterTiles: walk [TileSetNNNN] in numeric
order accumulating TilesInSet, and snapshot the running total at the start of
the section named by the key.  Usage: python dump_tilesets.py <theater.ini>
"""
import re
import sys

path = sys.argv[1]
lines = open(path, encoding="latin-1").read().splitlines()

general = {}
cur = None
sets = []
for l in lines:
    s = l.strip()
    if s.startswith("[") and s.endswith("]"):
        cur = s[1:-1]
        if re.match(r"^TileSet\d+$", cur):
            sets.append([int(cur[7:]), cur, 0, ""])
        continue
    if "=" not in s:
        continue
    k, v = s.split("=", 1)
    k = k.strip()
    v = v.strip()
    if cur == "General":
        general[k] = v
    elif cur and cur.startswith("TileSet"):
        if k == "TilesInSet":
            try:
                sets[-1][2] = int(v)
            except ValueError:
                pass
        elif k in ("FileName", "Name", "TileSetName"):
            sets[-1][3] = v.rstrip()

sets.sort(key=lambda x: x[0])
run = 0
info = {}
for num, name, tiles, names in sets:
    info[num] = (run, tiles, names)
    run += tiles

keys = ["ClearTile", "RoughTile", "ClearToRoughLat", "SandTile", "ClearToSandLat",
        "GreenTile", "ClearToGreenLat", "PaveTile", "ClearToPaveLat",
        "RampBase", "RampSmooth", "ShorePieces", "WaterSet", "CliffSet",
        "WaterCliffs", "DestroyableCliffs", "WaterfallEast", "WaterfallWest",
        "WaterfallSouth", "WaterfallNorth", "BridgeSet", "WoodBridgeSet",
        "CliffRamps", "WaterCaves", "MiscPaveTile", "HeightBase", "BlackTile"]

for k in keys:
    v = general.get(k)
    if v is None:
        print("%-20s missing" % k)
        continue
    sec = int(v)
    st, tl, nm = info.get(sec, (None, None, None))
    print("%-20s sec=%-4s start=%-5s tiles=%-4s %s" % (k, sec, st, tl, nm))
print("total tiles:", run)