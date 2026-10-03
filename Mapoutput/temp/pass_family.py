# -*- coding: utf-8 -*-
# 统计各类瓦片（平地占位/坡瓦/崖墙/岸片/水）在 Recalc 后的 Passability/SlopeIndex
import collections

path = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261003_121340.isopack5.txt"

# PassabilityType: 0 Passable,1 Crush,2 Destroyer,3 Beach,4 Water,5 Free,6 Impass,7 Outside
def fam(t):
    if t == 0 or t == 0xFFFF: return "placeholder/empty"
    if 49 <= t <= 88: return "CliffSet(49-88)"
    if 148 <= t <= 175: return "WaterCliffs(148-175)"
    if 314 <= t <= 327: return "Water(314-327)"
    if 384 <= t <= 393: return "CliffRamps(384-393)"
    if 510 <= t <= 521: return "HillRamp(510-521)"
    if 29 <= t <= 47: return "SlopeTiles(29-47)"
    if 489 <= t <= 509: return "CliffSetExt?(489-509)"
    return "other"

stat = collections.defaultdict(lambda: collections.Counter())
slope_on_diff1 = collections.Counter()
for line in open(path, encoding="utf-8", errors="replace"):
    if line.startswith(";"): continue
    p = line.split()
    if len(p) < 12: continue
    t, L, slope, pas = int(p[2]), int(p[8]), int(p[10]), int(p[11])
    stat[fam(t)]["pass%d" % pas] += 1
    stat[fam(t)]["n"] += 1
    if slope != 0: stat[fam(t)]["slope!=0"] += 1

for k in sorted(stat):
    print(k, dict(stat[k]))
