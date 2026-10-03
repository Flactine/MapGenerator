#!/usr/bin/env python3
"""Walk the nested mixes of the RA2/YR archives looking for .pal entries."""
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


def resolve(mix, g):
    best = None
    for game in ("ra2", "ra", "ts", "td"):
        mix.game = game
        t = mix.names(g)
        got = sum(1 for i, _, _ in mix.entries if (i & 0xFFFFFFFF) in t)
        if best is None or got > best[0]:
            best = (got, game, t)
    mix.game = best[1]
    return best[2], best[0]


def walk(path, depth, g, results, blob_holder):
    try:
        mix = M.Mix(path)
    except Exception as e:
        return
    t, got = resolve(mix, g)
    label = os.path.basename(path)
    for ident, off, size in sorted(mix.entries, key=lambda e: e[1]):
        name = mix.label(ident, t)
        low = name.lower()
        if low.endswith(".pal"):
            results.append((label, name, size, mix.raw(off, size)))
        elif depth > 0 and (low.endswith(".mix") or low.endswith(".mmx")):
            try:
                tmp = os.path.join(r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\paltmp",
                                   "_w.mix")
                with open(tmp, "wb") as fh:
                    fh.write(mix.raw(off, size))
                walk(tmp, depth - 1, g, results, blob_holder)
            except Exception:
                pass


def main():
    g = gmd()
    results = []
    for s in ("ra2.mix", "ra2md.mix"):
        walk(os.path.join(r"D:\Ra2", s), 2, g, results, None)
    print("pals found: %d" % len(results))
    want = sys.argv[1].lower() if len(sys.argv) > 1 else None
    outdir = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\paltmp"
    for owner, name, size, data in results:
        print("  %-22s %-24s %8d" % (owner, name, size))
        if want and want in name.lower():
            out = os.path.join(outdir, name)
            with open(out, "wb") as fh:
                fh.write(data)
            print("      -> %s" % out)



main()
