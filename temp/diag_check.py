#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Verify the inner-corner slot-34 selection in the LAST run section of
cliff_diag.txt (everything appended after `base_lines` lines).

Usage: python diag_check.py [base_lines]
"""
import re
import sys

base = int(sys.argv[1]) if len(sys.argv) > 1 else 0
lines = open("temp/cliff_diag.txt", encoding="utf-8", errors="replace").read().splitlines()
seg = lines[base:]
pat = re.compile(r"SELECT \((\d+),(\d+)\) slot=(\d+).*mask=0x([0-9A-Fa-f]+)")

tot = 0
hit34 = 0
wrong = 0
samples = []
all_selects = 0
for ln in seg:
    m = pat.search(ln)
    if not m:
        continue
    all_selects += 1
    mask = int(m.group(4), 16)
    slot = int(m.group(3))
    # (mask & 0xA0)==0xA0 with the W bit (0x20) clear: with the old port the
    # "eastMask < 0" test was dead, so these always went to 9/10/11.
    if (mask & 0xA0) == 0xA0 and (mask & 0x20) == 0:
        tot += 1
        if slot == 34:
            hit34 += 1
        if slot in (9, 10, 11):
            wrong += 1
        if len(samples) < 12:
            samples.append("(%s,%s) slot=%d mask=0x%02X"
                           % (m.group(1), m.group(2), slot, mask))

print("section lines: %d, SELECTs: %d" % (len(seg), all_selects))
print("inner-corner pattern: %d  slot34: %d  wrong(9/10/11): %d"
      % (tot, hit34, wrong))
for s in samples:
    print("   " + s)
