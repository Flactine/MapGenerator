# -*- coding: utf-8 -*-
# 解析 temperatmd.ini 的 [TileSetNNNN]，累计每个瓦片绝对编号->家族名，并打印指定区间的映射
import io, os, re, sys

ini = r"d:\新建文件夹\VSProject\MapGenerator\x64\Debug\temperatmd.ini"
txt = io.open(ini, "r", encoding="latin-1").read()

sets = {}
for m in re.finditer(r"\[TileSet(\d{4})\](.*?)(?=\n\[|\Z)", txt, re.S):
    sec = int(m.group(1))
    body = m.group(2)
    name = ""
    nm = re.search(r"^\s*SetName\s*=\s*(.*)$", body, re.M)
    if nm:
        name = nm.group(1).strip()
    tm = re.search(r"^\s*TilesInSet\s*=\s*(\d+)", body, re.M)
    tiles = int(tm.group(1)) if tm else 0
    sets[sec] = (name, tiles)

cum = 0
base = {}
for sec in sorted(sets):
    name, tiles = sets[sec]
    base[sec] = (cum, tiles, name)
    cum += tiles

# General 里各节号
general = {}
gm = re.search(r"\[General\](.*?)(?=\n\[|\Z)", txt, re.S)
if gm:
    for line in gm.group(1).splitlines():
        if "=" in line:
            k, v = line.split("=", 1)
            try:
                general[k.strip()] = int(v.strip())
            except ValueError:
                pass

if len(sys.argv) > 1 and sys.argv[1] == "dump":
    for sec in sorted(sets):
        c, t, n = base[sec]
        print("TileSet%04d  base=%-5d tiles=%-3d  %s" % (sec, c, t, n))
    sys.exit(0)

# 给定绝对编号，找家族
def fam(tile):
    for sec in sorted(sets):
        c, t, n = base[sec]
        if c <= tile < c + t:
            return "TileSet%04d(%s)+%d" % (sec, n, tile - c)
    return "?"

for v in sys.argv[1:]:
    print("%s -> %s" % (v, fam(int(v))))