#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Summarise RAMP-PAIR diagnostics per run section in rmg_diag.log."""
import re
import collections

lines = open("rmg_diag.log", encoding="utf-8", errors="replace").read().splitlines()
starts = [i for i, ln in enumerate(lines) if "MAP BODY START" in ln]
if not starts:
    starts = [0]
starts.append(len(lines))

for si in range(len(starts) - 1):
    seg = lines[starts[si]:starts[si + 1]]
    gate = None
    pairs = []
    cur = None
    for ln in seg:
        m = re.search(r"RAMP-PAIR-START .* roll=(\d+) gate=(\d+)", ln)
        if m:
            cur = {"roll": int(m.group(1)), "gate": int(m.group(2))}
            gate = cur["gate"]
        m = re.search(r"RAMP-PAIR-END .* want=(\d+) carved=(\d+) attempts=(\d+)", ln)
        if m and cur is not None:
            cur.update(want=int(m.group(1)), carved=int(m.group(2)),
                       attempts=int(m.group(3)))
            pairs.append(cur)
            cur = None
    if not pairs:
        continue
    wantc = collections.Counter(p["want"] for p in pairs)
    carv0 = sum(1 for p in pairs if p["carved"] == 0)
    att100 = sum(1 for p in pairs if p["attempts"] >= 100)
    total_carved = sum(p["carved"] for p in pairs)
    print("run#%d gate=%d pairs=%d wantDist=%s carvedTotal=%d pairsWithZero=%d hit100attempts=%d"
          % (si, gate, len(pairs), dict(sorted(wantc.items())),
             total_carved, carv0, att100))
    for p in pairs:
        if p["carved"] == 0 or p["want"] > 1:
            print("   roll=%2d want=%d carved=%d attempts=%d"
                  % (p["roll"], p["want"], p["carved"], p["attempts"]))
