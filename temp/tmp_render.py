#!/usr/bin/env python3
"""Render a window of a .map using the real theater TMP tiles.

    python tmp_render.py <map> <x0> <x1> <y0> <y1> <out.png>

TMP (RA2) layout, per ModEnc + the TS format doc:
    file header : int32 blockW, blockH, blockImageW(=60), blockImageH(=30)
    index       : blockW*blockH int32 offsets
    cell record : 52-byte image header (x, y, unknown1[3], x_extra, y_extra,
                  cx_extra, cy_extra, unknown2[4])
                  + 900 bytes  normal graphics (opaque pixels only)
                  + 900 bytes  Z data
The 900 = 4*(1+..+15) + 4*(14+..+1), i.e. rows 0..14 grow by 4 px from 4 to 60,
rows 15..28 shrink by 4 px from 56 down to 4.  Row 29 is empty.
"""
import os
import sys
import zlib

sys.path.insert(0, ".")
import analyze_isopack5 as A

TILE_DIR = r"d:\新建文件夹\VSProject\MapGenerator\Tile资源\温和"
PAL_PATH = os.path.join(os.path.dirname(os.path.abspath(__file__)), "paltmp", "isotem.pal")

SET_BASE = {  # tile-set number -> (first absolute tile index, filename prefix)
    12: (89, "shore", 42),
    13: (131, "ruff", 1),
    14: (132, "clat", 16),
    21: (314, "water", 14),
    33: (418, "sand", 1),
    41: (493, "green", 1),
    42: (494, "glat", 16),
}


def load_pal():
    """Westwood .pal stores 6-bit channels; expand to 8 bit."""
    d = open(PAL_PATH, "rb").read()
    return [tuple(((v << 2) | (v >> 4)) & 0xFF for v in d[i * 3:i * 3 + 3])
            for i in range(256)]


def tile_file(tile):
    """absolute tile index -> .tem file, or None."""
    for _set, (base, prefix, count) in SET_BASE.items():
        if base <= tile < base + count:
            return "%s%02d.tem" % (prefix, tile - base + 1)
    return None


class Tmp(object):
    def __init__(self, path):
        d = open(path, "rb").read()
        self.bw = int.from_bytes(d[0:4], "little")
        self.bh = int.from_bytes(d[4:8], "little")
        self.iw = int.from_bytes(d[8:12], "little")
        self.ih = int.from_bytes(d[12:16], "little")
        n = self.bw * self.bh
        self.idx = [int.from_bytes(d[16 + 4 * i:20 + 4 * i], "little")
                    for i in range(n)]
        self.data = d

    def image(self, i):
        """i-th cell -> (x, y, rows) with rows a list of (row, x, bytes).

        The image block holds only the opaque pixels of the isometric diamond,
        walked exactly like the TS-format reference draw loop: the row band
        grows by 4 px from 4 to iw, then shrinks by 4 px back down.
        """
        off = self.idx[i]
        if off == 0:
            return None
        x = self._i32(off)
        y = self._i32(off + 4)
        img = self.data[off + 52:off + 52 + 900]
        rows = []
        r = 0
        px = 0
        sx = self.iw // 2
        for row in range(self.ih):
            if row < 15:
                px += 4
                sx -= 2
            else:
                px -= 4
                sx += 2
            if px <= 0 or sx < 0 or sx + px > self.iw:
                continue
            rows.append((row, sx, img[r:r + px]))
            r += px
        return x, y, rows


    def _i32(self, off):
        v = int.from_bytes(self.data[off:off + 4], "little")
        return v - (1 << 32) if v & 0x80000000 else v


CACHE = {}


def get_tmp(name):
    if name not in CACHE:
        p = os.path.join(TILE_DIR, name)
        CACHE[name] = Tmp(p) if os.path.isfile(p) else None
    return CACHE[name]


def main():
    path, x0, x1, y0, y1, out = (sys.argv[1], int(sys.argv[2]), int(sys.argv[3]),
                                 int(sys.argv[4]), int(sys.argv[5]), sys.argv[6])
    cells, _s, _n = A.load_map(path)
    pal = load_pal()

    cw, ch = 60, 30
    xs = [x for x in range(x0, x1 + 1)]
    ys = [y for y in range(y0, y1 + 1)]
    minx = min(x - y for x in xs for y in ys) * (cw // 2)
    miny = min(x + y for x in xs for y in ys) * (ch // 2)
    W = (max(x - y for x in xs for y in ys) - min(x - y for x in xs for y in ys)) * (cw // 2) + cw
    H = (max(x + y for x in xs for y in ys) - min(x + y for x in xs for y in ys)) * (ch // 2) + ch
    buf = bytearray(W * H * 4)          # RGBA

    order = sorted(((x, y) for x in xs for y in ys), key=lambda c: c[0] + c[1])
    stats = {}
    for (x, y) in order:
        c = cells.get((x, y))
        if c is None:
            continue
        tile = c["tile"]
        if tile == 65535:
            stats["placeholder"] = stats.get("placeholder", 0) + 1
            continue
        name = tile_file(tile)
        if not name:
            stats["unmapped %d" % tile] = stats.get("unmapped %d" % tile, 0) + 1
            continue
        tmp = get_tmp(name)
        if tmp is None:
            stats["missing " + name] = stats.get("missing " + name, 0) + 1
            continue
        sub = c["bSubTile"]
        if sub >= len(tmp.idx):
            stats["subrange " + name] = stats.get("subrange " + name, 0) + 1
            sub = 0
        im = tmp.image(sub)
        if im is None:
            stats["emptycell %s[%d]" % (name, sub)] = \
                stats.get("emptycell %s[%d]" % (name, sub), 0) + 1
            continue
        _ox, _oy, rows = im
        # The TMP header x/y of a sub-cell already equals its diagonal offset
        # inside the footprint ((col-row)*30, (col+row)*15) - and the map stores
        # that sub-cell at its own (x, y), so the position below already carries
        # it.  Adding the header values again shifts every multi-cell piece.
        sx0 = (x - y) * (cw // 2) - minx
        sy0 = (x + y) * (ch // 2) - miny
        for row, sx, data in rows:
            dy = sy0 + row
            if dy < 0 or dy >= H:
                continue
            for k, v in enumerate(data):
                dx = sx0 + sx + k
                if dx < 0 or dx >= W:
                    continue
                r, g, b = pal[v]
                o = (dy * W + dx) * 4
                buf[o] = r
                buf[o + 1] = g
                buf[o + 2] = b
                buf[o + 3] = 255

    write_png(out, W, H, buf)
    print("wrote %s (%dx%d)" % (out, W, H))
    if stats:
        print("unmapped tiles:", sorted(stats.items())[:20])


def write_png(path, w, h, rgba):
    raw = bytearray()
    for y in range(h):
        raw.append(0)
        raw += rgba[y * w * 4:(y + 1) * w * 4]

    def chunk(tag, data):
        c = tag + data
        return (len(data).to_bytes(4, "big") + c +
                (zlib.crc32(c) & 0xFFFFFFFF).to_bytes(4, "big"))

    png = b"\x89PNG\r\n\x1a\n"
    png += chunk(b"IHDR", w.to_bytes(4, "big") + h.to_bytes(4, "big") + bytes([8, 6, 0, 0, 0]))
    png += chunk(b"IDAT", zlib.compress(bytes(raw), 6))
    png += chunk(b"IEND", b"")
    open(path, "wb").write(png)


if __name__ == "__main__":
    main()
