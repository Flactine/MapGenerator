#!/usr/bin/env python3
"""Show the region the user tagged with tag 01000001, cell by cell.

    python analyze_tag.py <map> [tag]

Prints, for the union window of the tagged cells, a symbolic map of the tiles
so the shore segment can be read directly:

    .      placeholder 0xFFFF (never stamped)
    clr    Clear 0
    rbNN   RampBase  29..48   (NN = tile-28 = slope pattern)
    cfNN   CliffSet  49..88
    SNN    shore piece 89..130 (NN = n12)
    ruff   Ruff 131
    clatNN 132..147
    wcNN   WaterCliff 148..175
    ~~~    Water 314..327
    sand   Sandy 418
    dlatNN 419..434
    platNN 463..478
    G      Green 493
    glatNN 494..509
    RNN    Rmpfx 510..521  (NN = tile-509)
    pave   534
    T<hex> anything else

Each cell is printed as "<sym>/<Height>" so partial stamping is visible.
Tagged cells are wrapped in [ ].
"""
import sys

sys.path.insert(0, ".")
import analyze_isopack5 as A


def sym(t):
    if t == 0xFFFF:
        return "."
    if t == 0:
        return "clr"
    if 29 <= t <= 48:
        return "rb%02d" % (t - 28)
    if 49 <= t <= 88:
        return "cf%02d" % (t - 48)
    if 89 <= t <= 130:
        return "S%02d" % (t - 88)
    if t == 131:
        return "ruff"
    if 132 <= t <= 147:
        return "clat%02d" % (t - 131)
    if 148 <= t <= 175:
        return "wc%02d" % (t - 147)
    if 314 <= t <= 327:
        return "~~~"
    if t == 418:
        return "sand"
    if 419 <= t <= 434:
        return "dlat%02d" % (t - 418)
    if 463 <= t <= 478:
        return "plat%02d" % (t - 462)
    if t == 493:
        return "G"
    if 494 <= t <= 509:
        return "glat%02d" % (t - 493)
    if 510 <= t <= 521:
        return "R%02d" % (t - 509)
    if t == 534:
        return "pave"
    return "T%X" % t


def read_tags(path):
    """[CellTags] key = y*1000+x, value = 8 hex digits."""
    tags = {}
    inside = False
    with open(path, "r", encoding="utf-8", errors="replace") as fh:
        for line in fh:
            s = line.strip()
            if s.startswith("["):
                inside = s.lower() == "[celltags]"
                continue
            if not inside or not s or s.startswith(";"):
                continue
            if "=" not in s:
                continue
            k, v = s.split("=", 1)
            try:
                tags[int(k.strip())] = v.strip()
            except ValueError:
                pass
    return tags


def main():
    path = sys.argv[1]
    want = sys.argv[2].lower() if len(sys.argv) > 2 else "01000001"
    cells, _s, _n = A.load_map(path)
    tags = read_tags(path)

    hit = {}
    for k, v in tags.items():
        if v.lower().lstrip("0") == want.lstrip("0") or v.lower() == want:
            hit[(k % 1000, k // 1000)] = v
    print("tag %s : %d cells" % (want, len(hit)))
    xs = sorted(p[0] for p in hit)
    ys = sorted(p[1] for p in hit)
    print("X %d..%d   Y %d..%d" % (min(xs), max(xs), min(ys), max(ys)))
    print("cells: %s" % sorted(hit))

    x0, x1 = min(xs) - 8, max(xs) + 8
    y0, y1 = min(ys) - 5, max(ys) + 5
    print()
    print("window X %d..%d  Y %d..%d   (cell = sym/Height)" % (x0, x1, y0, y1))
    print(" " * 8 + "".join("%9d" % x for x in range(x0, x1 + 1)))
    for y in range(y0, y1 + 1):
        row = "y=%5d " % y
        for x in range(x0, x1 + 1):
            c = cells.get((x, y))
            if c is None:
                row += "        ."
                continue
            s = "%s/%d" % (sym(c["tile"]), c["height"])
            row += ("%9s" % ("[" + s + "]")) if (x, y) in hit else ("%9s" % s)
        print(row)


main()
