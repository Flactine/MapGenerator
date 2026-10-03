#!/usr/bin/env python3
"""Crop and nearest-neighbour scale a PNG written by tmp_render.py.

    python png_crop.py <in.png> <x0> <y0> <x1> <y1> <scale> <out.png>

Only the exact format tmp_render.py emits is supported (8-bit RGBA, filter 0
rows, single IDAT).
"""
import sys
import zlib


def read_png(path):
    d = open(path, "rb").read()
    assert d[:8] == b"\x89PNG\r\n\x1a\n"
    pos = 8
    idat = b""
    w = h = 0
    while pos < len(d):
        ln = int.from_bytes(d[pos:pos + 4], "big")
        tag = d[pos + 4:pos + 8]
        body = d[pos + 8:pos + 8 + ln]
        if tag == b"IHDR":
            w = int.from_bytes(body[0:4], "big")
            h = int.from_bytes(body[4:8], "big")
            assert body[8] == 8 and body[9] == 6, "expect 8-bit RGBA"
        elif tag == b"IDAT":
            idat += body
        pos += 12 + ln
    raw = zlib.decompress(idat)
    assert len(raw) == h * (1 + w * 4), (len(raw), h, w)
    rows = []
    for y in range(h):
        o = y * (1 + w * 4)
        assert raw[o] == 0, "unsupported filter %d" % raw[o]
        rows.append(raw[o + 1:o + 1 + w * 4])
    return w, h, rows


def main():
    src, x0, y0, x1, y1, scale, out = (sys.argv[1], int(sys.argv[2]), int(sys.argv[3]),
                                       int(sys.argv[4]), int(sys.argv[5]), int(sys.argv[6]),
                                       sys.argv[7])
    w, h, rows = read_png(src)
    x0 = max(0, x0); y0 = max(0, y0)
    x1 = min(w - 1, x1); y1 = min(h - 1, y1)
    cw = x1 - x0 + 1
    ch = y1 - y0 + 1
    ow = cw * scale
    oh = ch * scale
    raw = bytearray()
    for y in range(y0, y1 + 1):
        row = rows[y][x0 * 4:(x1 + 1) * 4]
        big = b"".join(row[k * 4:k * 4 + 4] * scale for k in range(cw))
        for _ in range(scale):
            raw.append(0)
            raw += big

    def chunk(tag, data):
        c = tag + data
        return (len(data).to_bytes(4, "big") + c +
                (zlib.crc32(c) & 0xFFFFFFFF).to_bytes(4, "big"))

    png = b"\x89PNG\r\n\x1a\n"
    png += chunk(b"IHDR", ow.to_bytes(4, "big") + oh.to_bytes(4, "big") + bytes([8, 6, 0, 0, 0]))
    png += chunk(b"IDAT", zlib.compress(bytes(raw), 6))
    png += chunk(b"IEND", b"")
    open(out, "wb").write(png)
    print("wrote %s (%dx%d from %d,%d..%d,%d x%d)" % (out, ow, oh, x0, y0, x1, y1, scale))


if __name__ == "__main__":
    main()
