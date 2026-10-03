#!/usr/bin/env python3
"""Scan the RA2 mixes for palette / temperate tile entries."""
import os
import sys
sys.path.insert(0, ".")
import mix_tool as M

SIGS = ["ra2.mix", "ra2md.mix", "temperat.mix", "isotemp.mix", "isotemmd.mix",
        "isogen.mix", "snow.mix", "snowmd.mix"]

GMD_CANDIDATES = [
    r"D:\Ra2\global mix database.dat",
    r"D:\新建文件夹\VSProject\CCmix\test_files\global mix database.dat",
]


def find_gmd():
    for p in GMD_CANDIDATES:
        if os.path.isfile(p):
            return p
    return None


def main():
    pat = sys.argv[1].lower() if len(sys.argv) > 1 else "pal"
    gmd = None
    gp = find_gmd()
    if gp:
        gmd = M.load_gmd(gp)
        print("gmd:", gp)
    for s in SIGS:
        p = os.path.join(r"D:\Ra2", s)
        if not os.path.isfile(p):
            continue
        try:
            mix = M.Mix(p)
            table = mix.names(gmd)
            hits = sorted({n for n in table.values() if pat in n.lower()})
            print("%-16s %d entries, %d name hits" % (s, len(mix.entries), len(hits)))
            for n in hits[:80]:
                print("     ", n)
        except Exception as e:
            print("%-16s error %s" % (s, e))


main()
