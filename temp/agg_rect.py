#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Aggregate the new ramp-placement diagnostics per captured rplog:
 - B2-CONCAVE cells that stay high (L>=6) at stamp time
 - RECT rejection reason counts (vanilla-no / vanilla-tile / custom-2ring)
Read-only."""
import glob
import os
import re
import sys

TEMP = os.path.dirname(os.path.abspath(__file__))
pat = sys.argv[1] if len(sys.argv) > 1 else "rplog_rmg_20261001_14*.txt"

for f in sorted(glob.glob(os.path.join(TEMP, pat))):
    name = os.path.basename(f)[6:-4]
    no = tile = custom = 0
    conc_high = []
    for line in open(f, errors="replace"):
        if line.startswith("RECT-VANILLA-NO"):
            no += 1
        elif line.startswith("RECT-VANILLA-TILE"):
            tile += 1
        elif line.startswith("RECT-CUSTOM-2RING"):
            custom += 1
        elif line.startswith("B2-CONCAVE"):
            m = re.search(r"cell\((-?\d+),(-?\d+)\)\=L(\d+)/t(-?\d+) mark=(-?\d+)",
                          line)
            if m and int(m.group(3)) >= 6:
                conc_high.append((m.group(1), m.group(2), m.group(3),
                                  m.group(4), m.group(5)))
    print("%s reject(no=%d tile=%d CUSTOM2R=%d) B2concaveHigh=%d %s"
          % (name, no, tile, custom, len(conc_high), conc_high[:6]))
