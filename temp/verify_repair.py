#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Verify the post-cliff repair from a captured rplog.

Groups CLIFF-SEL with the CLIFF-STAMP / CLIFF-SKIP / CLIFF-ABORT lines of the
same piece, then checks every blocked group was handled by CLIFF-REPAIR lines:
 - east-column-2x2 groups: origin + south-foot rewritten to t56 (C8);
 - otherwise every surviving (stamped) cell rewritten to a 1x1 tile
   (t82 wall, t60..t62 foot).
Also lists the B-scan fills (t0 foot-row cells).
"""
import glob
import os
import re
import sys

TEMP = os.path.dirname(os.path.abspath(__file__))
SEL = re.compile(r"CLIFF-SEL \((-?\d+),(-?\d+)\) slot=(\d+)")
STAMP = re.compile(r"CLIFF-STAMP \((-?\d+),(-?\d+)\).* h=(\d+) newL=(\d+)")
FAIL = re.compile(r"CLIFF-(?:SKIP|ABORT) \((-?\d+),(-?\d+)\).* h=(\d+)")
REPAIR = re.compile(r"CLIFF-REPAIR \((-?\d+),(-?\d+)\) t(\d+)/h(\d+) -> t(\d+)/h(\d+)")


def analyze(path):
    groups = []          # (ox,oy,slot, stamped[(x,y,h,L)], blocked[h])
    cur = None
    repairs = {}         # (x,y) -> (newTile, newH)
    for line in open(path, errors="replace"):
        m = SEL.search(line)
        if m:
            cur = (int(m.group(1)), int(m.group(2)), int(m.group(3)), [], [])
            groups.append(cur)
            continue
        m = FAIL.search(line)
        if m and cur is not None:
            cur[4].append(int(m.group(3)))
            continue
        m = STAMP.search(line)
        if m and cur is not None:
            cur[3].append((int(m.group(1)), int(m.group(2)),
                           int(m.group(3)), int(m.group(4))))
            continue
        m = REPAIR.search(line)
        if m:
            key = (int(m.group(1)), int(m.group(2)))
            repairs[key] = (int(m.group(5)), int(m.group(6)))

    damaged = [g for g in groups if g[4]]
    issues = []
    fixed = 0
    for ox, oy, slot, stamped, blocked in damaged:
        bm = set(blocked)
        surviving = [(x, y, h, L) for x, y, h, L in stamped]
        if slot in (4, 5, 6, 7) and bm == {1, 3}:
            need = {(ox, oy): (56, 0), (ox, oy + 1): (56, 1)}
            for xy, nv in need.items():
                if repairs.get(xy) != nv:
                    issues.append("C8 group (%d,%d) slot%d missing %s->%s got %s"
                                 % (ox, oy, slot, xy, nv, repairs.get(xy)))
            fixed += 1
            continue
        for x, y, h, L in surviving:
            want_hi = 82
            want_lo_set = {60, 61, 62}
            got = repairs.get((x, y))
            if L >= 7:
                if got != (want_hi, 0):
                    issues.append("wall (%d,%d) slot%d -> got %s want (82,0)"
                                 % (x, y, slot, got))
            else:
                if got is None or got[0] not in want_lo_set or got[1] != 0:
                    issues.append("foot (%d,%d) slot%d -> got %s want 60-62/h0"
                                 % (x, y, slot, got))
        fixed += 1
    return len(groups), len(damaged), fixed, len(repairs), issues


def main():
    paths = sorted(glob.glob(os.path.join(TEMP, sys.argv[1]))) \
        if len(sys.argv) > 1 else sorted(glob.glob(os.path.join(TEMP, "rplog_*.txt")))
    tot_dmg = tot_fix = tot_fill = 0
    for p in paths:
        n, dmg, fixed, nrep, issues = analyze(p)
        if dmg or nrep:
            print("%s pieces=%d damaged=%d repairedGroups=%d repairWrites=%d"
                  % (os.path.basename(p), n, dmg, fixed, nrep))
            for it in issues[:8]:
                print("    !! " + it)
        tot_dmg += dmg
        tot_fix += fixed
        tot_fill += nrep
    print("TOTAL damaged groups=%d repaired=%d repair cell writes=%d over %d logs"
          % (tot_dmg, tot_fix, tot_fill, len(paths)))


if __name__ == "__main__":
    main()
