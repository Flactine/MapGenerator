#!/usr/bin/env python3
"""Colour-code a window by tile family (no TMP art needed) so the layout is
directly comparable with the in-game map editor.

    python cls_render.py <map> <x0> <x1> <y0> <y1> <out.png>
"""
import sys

sys.path.insert(0, ".")
import analyze_isopack5 as A
import tmp_render as R

CW, CH = 60, 30

COLOURS = {
    "cliff":  (225, 45, 45),
    "wcliff": (140, 20, 20),
    "rampC":  (255, 150, 0),    # CliffRamps 384..393
    "rampB":  (45, 90, 230),    # RampBase 29..48
    "rampS":  (0, 205, 205),    # RampSmooth 510..521
    "clear":  (40, 175, 40),
    "shore":  (235, 225, 70),
    "rough":  (150, 200, 80),
    "water":  (25, 45, 130),
    "green":  (110, 250, 110),
    "sandy":  (205, 175, 125),
    "other":  (170, 60, 200),
    "none":   (35, 35, 35),
    "gap":    (5, 5, 5),
}


def fam(t):
    if t == 65535:
        return "gap"
    if t in (0, 1):
        return "clear"
    if 29 <= t <= 48:
        return "rampB"
    if 510 <= t <= 521:
        return "rampS"
    if 49 <= t <= 88:
        return "cliff"
    if 148 <= t <= 175:
        return "wcliff"
    if 384 <= t <= 393:
        return "rampC"
    if 89 <= t <= 130:
        return "shore"
    if 131 <= t <= 147:
        return "rough"
    if 314 <= t <= 327:
        return "water"
    if 418 <= t <= 434:
        return "sandy"
    if 493 <= t <= 509:
        return "green"
    return "other"


def diamond_rows():
    out = []
    for r in range(CH):
        w = 4 * min(r + 1, CH - 1 - r)
        if w > 0:
            out.append((r, (CW - w) // 2, w))
    return out


def main():
    path, x0, x1, y0, y1, out = (sys.argv[1], int(sys.argv[2]), int(sys.argv[3]),
                                 int(sys.argv[4]), int(sys.argv[5]), sys.argv[6])
    cells, _s, _n = A.load_map(path)
    xs = list(range(x0, x1 + 1))
    ys = list(range(y0, y1 + 1))
    minx = min(x - y for x in xs for y in ys) * (CW // 2)
    miny = min(x + y for x in xs for y in ys) * (CH // 2)
    W = (max(x - y for x in xs for y in ys) - min(x - y for x in xs for y in ys)) * (CW // 2) + CW
    H = (max(x + y for x in xs for y in ys) - min(x + y for x in xs for y in ys)) * (CH // 2) + CH
    buf = bytearray(W * H * 4)

    def put(px, py, rgb):
        if 0 <= px < W and 0 <= py < H:
            o = (py * W + px) * 4
            buf[o], buf[o + 1], buf[o + 2], buf[o + 3] = rgb[0], rgb[1], rgb[2], 255

    rows = diamond_rows()
    order = sorted(((x, y) for x in xs for y in ys), key=lambda c: c[0] + c[1])
    for (x, y) in order:
        c = cells.get((x, y))
        f = "none" if c is None else fam(c["tile"])
        col = COLOURS[f]
        sx0 = (x - y) * (CW // 2) - minx
        sy0 = (x + y) * (CH // 2) - miny
        for r, xs_, w in rows:
            for k in range(w):
                put(sx0 + xs_ + k, sy0 + r, col)
        # outline
        for r, xs_, w in rows:
            put(sx0 + xs_, sy0 + r, (255, 255, 255))
            put(sx0 + xs_ + w - 1, sy0 + r, (255, 255, 255))
        put(sx0 + CW // 2, sy0, (255, 255, 255))
        put(sx0 + CW // 2, sy0 + CH - 1, (255, 255, 255))

    R.write_png(out, W, H, buf)
    print("wrote %s (%dx%d)" % (out, W, H))


main()