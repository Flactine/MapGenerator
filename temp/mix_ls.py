#!/usr/bin/env python3
"""List the direct entries of a mix and dump one by resolved name."""
import os
import sys
sys.path.insert(0, ".")
import mix_tool as M


def gmd():
    for p in (r"D:\Ra2\global mix database.dat",
              r"D:\新建文件夹\VSProject\CCmix\test_files\global mix database.dat"):
        if os.path.isfile(p):
            return M.load_gmd(p)
    return None


def main():
    path = sys.argv[1]
    want = sys.argv[2].lower() if len(sys.argv) > 2 else None
    outdir = sys.argv[3] if len(sys.argv) > 3 else None
    g = gmd()
    mix = M.Mix(path)
    best = None
    for game in ("ra2", "ra", "ts", "td"):
        mix.game = game
        t = mix.names(g)
        got = sum(1 for i, _, _ in mix.entries if (i & 0xFFFFFFFF) in t)
        if best is None or got > best[0]:
            best = (got, game, t)
    mix.game = best[1]
    table = best[2]
    print("game=%s resolved=%d/%d" % (best[1], best[0], len(mix.entries)))
    for ident, off, size in sorted(mix.entries, key=lambda e: e[1]):
        name = mix.label(ident, table)
        print("%-34s %10d" % (name, size))
        if want and outdir and want in name.lower():
            data = mix.raw(off, size)
            out = os.path.join(outdir, name)
            with open(out, "wb") as fh:
                fh.write(data)
            print("   -> %s (%d bytes)" % (out, len(data)))


main()
