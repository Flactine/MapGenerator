#!/usr/bin/env python3
"""Isometric family-colour render of a .map, so the coast can be eyeballed.

    python render_families.py <map> <out.png> [x0 x1 y0 y1] [tag]

Colours (per cell, whole diamond):
    water      314..327  deep blue
    shore       89..130  sand
    Green 493            green
    glat       494..509  light green
    sand       418       pale sand
    dlat       419..434  tan
    ruff       131       olive
    clat       132..147  green-ish
    plat       463..478  grey-brown
    RampBase    29..48   grey
    Rmpfx      510..521  grey
    CliffSet    49..88   dark grey
    Clear 0              grass
    0xFFFF               MAGENTA  <- never stamped, must not appear near water
Tagged cells are outlined bright red.
"""
import sys
import zlib
import struct

sys.path.insert(0, ".")
import analyze_isopack5 as A

HALF_W = int(__import__("os").environ.get("FAM_HALF_W", "5"))
HALF_H = int(__import__("os").environ.get("FAM_HALF_H", "3"))


def colour(t):
    if t == 0xFFFF:
        return (255, 0, 255)
    if 314 <= t <= 327:
        return (30, 60, 170)
    if 89 <= t <= 130:
        return (235, 215, 150)
    if t == 493:
        return (80, 140, 60)
    if 494 <= t <= 509:
        return (120, 175, 85)
    if t == 418:
        return (240, 230, 185)
    if 419 <= t <= 434:
        return (205, 185, 110)
    if t == 131:
        return (150, 140, 110)
    if 132 <= t <= 147:
        return (150, 180, 105)
    if 463 <= t <= 478:
        return (175, 165, 125)
    if 29 <= t <= 48:
        return (165, 160, 145)
    if 510 <= t <= 521:
        return (150, 145, 135)
    if 49 <= t <= 88:
        return (105, 105, 110)
    if t == 0:
        return (105, 165, 85)
    return (200, 120, 30)


def read_tags(path):
    tags = {}
    inside = False
    with open(path, "r", encoding="utf-8", errors="replace") as fh:
        for line in fh:
            s = line.strip()
            if s.startswith("["):
                inside = s.lower() == "[celltags]"
                continue
            if not inside or not s or "=" in s and False:
                continue
            if "=" in s:
                k, v = s.split("=", 1)
                try:
                    tags[int(k)] = v.strip()
                except ValueError:
                    pass
    return tags


def write_png(path, w, h, rgb):
    raw = bytearray()
    for y in range(h):
        raw.append(0)
        raw += rgb[y * w * 3:(y + 1) * w * 3]

    def chunk(tag, data):
        c = struct.pack(">I", len(data)) + tag + data
        return c + struct.pack(">I", zlib.crc32(tag + data) & 0xFFFFFFFF)

    png = b"\x89PNG\r\n\x1a\n"
    png += chunk(b"IHDR", struct.pack(">IIBBBBB", w, h, 8, 2, 0, 0, 0))
    png += chunk(b"IDAT", zlib.compress(bytes(raw), 6))
    png += chunk(b"IEND", b"")
    open(path, "wb").write(png)


def load_partial(cells):
    """Cells of a shore piece that is NOT fully stamped -> red set.

    A piece is one tile index over its whole footprint with Height = col + row*w.
    We blob 8-connected same-tile shore cells and check the height set."""
    import os
    from collections import Counter
    FOOT = {}
    for k in range(1, 41):
        FOOT[k] = (2, 2)
    for k in (4, 20):
        FOOT[k] = (1, 2)
    for k in (12, 28):
        FOOT[k] = (2, 1)
    for k in (5, 6, 21, 22):
        FOOT[k] = (2, 3)
    for k in (13, 14, 29, 30):
        FOOT[k] = (3, 2)
    FOOT[41] = (6, 4)
    FOOT[42] = (9, 5)

    shore = {p: c for p, c in cells.items() if 89 <= c["tile"] <= 130}
    seen = set()
    bad = set()
    ok = set()
    for p in sorted(shore):
        if p in seen:
            continue
        t = shore[p]["tile"]
        blob = []
        stack = [p]
        seen.add(p)
        while stack:
            q = stack.pop()
            blob.append(q)
            for dx, dy in ((1, 0), (1, 1), (0, 1), (-1, 1), (-1, 0), (-1, -1),
                           (0, -1), (1, -1)):
                r = (q[0] + dx, q[1] + dy)
                if r not in seen and r in shore and shore[r]["tile"] == t:
                    seen.add(r)
                    stack.append(r)
        w, h = FOOT[t - 89 + 1]
        got = set(shore[q]["height"] for q in blob)
        (ok if got == set(range(w * h)) else bad).update(blob)
    return bad, ok


def main():
    path, out = sys.argv[1], sys.argv[2]
    box = None
    if len(sys.argv) > 6:
        box = [int(v) for v in sys.argv[3:7]]
    cells, _s, _n = A.load_map(path)

    if box:
        x0, x1, y0, y1 = box
    else:
        xs = [p[0] for p in cells]
        ys = [p[1] for p in cells]
        x0, x1, y0, y1 = min(xs), max(xs), min(ys), max(ys)

    tags = read_tags(path) if len(sys.argv) > 7 else {}
    want = sys.argv[7] if len(sys.argv) > 7 else None

    sx = [(x - y) for x in range(x0, x1 + 1) for y in (y0, y1)]
    W = (x1 - x0 + y1 - y0 + 2) * HALF_W
    Hh = (x1 - x0 + y1 - y0 + 2) * HALF_H
    ox = (y1 - y0) * HALF_W
    px = bytearray(b"\x20" * (W * Hh * 3))

    def put(x, y, c):
        if 0 <= x < W and 0 <= y < Hh:
            i = (y * W + x) * 3
            px[i:i + 3] = bytes(c)

    order = sorted(cells.items(), key=lambda kv: (kv[0][0] + kv[0][1]))
    import os
    partial = os.environ.get("FAM_PIECE") == "1"
    bad, ok = load_partial(cells) if partial else (set(), set())
    for (x, y), c in order:
        if not (x0 <= x <= x1 and y0 <= y <= y1):
            continue
        cx = (x - x0 - (y - y0)) * HALF_W + ox
        cy = (x - x0 + (y - y0)) * HALF_H
        col = colour(c["tile"])
        if partial and 89 <= c["tile"] <= 130:
            col = (255, 40, 40) if (x, y) in bad else (255, 235, 0)
        for dy in range(-HALF_H, HALF_H + 1):
            half = HALF_W - int(abs(dy) * HALF_W / HALF_H)
            for dx in range(-half, half + 1):
                put(cx + dx, cy + dy, col)
        if tags and (y * 1000 + x) in tags and tags[y * 1000 + x].lower() == want:
            for dy in range(-HALF_H, HALF_H + 1):
                half = HALF_W - int(abs(dy) * HALF_W / HALF_H)
                put(cx - half, cy + dy, (255, 0, 0))
                put(cx + half, cy + dy, (255, 0, 0))
            for dx in range(-HALF_W, HALF_W + 1):
                put(cx + dx, cy - HALF_H, (255, 0, 0))
                put(cx + dx, cy + HALF_H, (255, 0, 0))

    write_png(out, W, Hh, px)
    print("wrote %s  %dx%d  box X%d..%d Y%d..%d" % (out, W, Hh, x0, x1, y0, y1))


main()
