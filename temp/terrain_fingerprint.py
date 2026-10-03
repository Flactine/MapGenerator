#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Terrain fingerprint: level histogram, cliff counts for vanilla .yrm vs
ported .map whose land type is known from rplog_*.txt SPEC lines."""
import glob
import os
import re
import sys
from collections import Counter

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import analyze_isopack5 as A

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TEMP = os.path.dirname(os.path.abspath(__file__))


def landtype_of(mapname):
    p = os.path.join(TEMP, "rplog_" + mapname.replace(".map", "") + ".txt")
    if os.path.exists(p):
        with open(p, "r", errors="replace") as f:
            m = re.search(r"SPEC g=\d+ landType=(\d+)", f.read(2000))
            if m:
                return int(m.group(1))
    return None


rows = []
for p in sorted(glob.glob(os.path.join(ROOT, "Map.*.yrm"))) + \
        sorted(glob.glob(os.path.join(ROOT, "rmg_*.map"))):
    name = os.path.basename(p)
    cells = A.load_map(p)[0]
    lv = Counter(c["level"] for c in cells.values())
    cliff = sum(1 for c in cells.values() if 49 <= c["tile"] <= 88)
    cramp = sum(1 for c in cells.values() if 384 <= c["tile"] <= 393)
    lt = landtype_of(name)
    tag = ("t%d" % lt) if lt is not None else ("VANILLA" if name.endswith(".yrm") else "?")
    hist = " ".join("L%d=%d" % (k, lv.get(k, 0)) for k in sorted(lv))
    rows.append((tag, name, len(cells), cliff, cramp, hist))

for tag, name, n, cliff, cramp, hist in rows:
    print("%-7s %-34s cells=%-5d cliff=%-4d cliffRamp=%-4d %s"
          % (tag, name, n, cliff, cramp, hist))
