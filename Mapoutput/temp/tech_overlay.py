# -*- coding: utf-8 -*-
# 检查 rmg_20261003_121340.yrm 的科技建筑地基格(及外圈2格)上有没有 overlay。
# OverlayPack/OverlayDataPack 是 Westwood format80(LCW)：每段头 4 字节
# (U24 压缩长 + 0x20)，32 段每段解压出 8192 字节。
import base64, re, struct

p = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261003_121340.yrm"
raw = open(p, "rb").read()

def section_b64(name):
    m = re.search(("\\[%s\\]" % name).encode(), raw)
    s = m.end()
    e = raw.find(b"[", s)
    # 每行形如 "1=base64..."，必须先剥掉键名前缀再拼接。
    body = b""
    for ln in raw[s:e].splitlines():
        i = ln.find(b"=")
        if i >= 0:
            body += ln[i+1:]
    return base64.b64decode(body)

def decode80(src):
    out = bytearray()
    i = 0
    while i < len(src):
        b0 = src[i]; i += 1
        if not (b0 & 0x80):
            count = (b0 >> 4) + 3
            off = ((b0 & 0x0f) << 8) | src[i]; i += 1
            for _ in range(count):
                out.append(out[len(out)-off] if off <= len(out) else 0)
        else:
            c = b0 & 0x3f
            if not (b0 & 0x40):
                if c == 0:
                    break
                out += src[i:i+c]; i += c
            else:
                w = src[i] | (src[i+1] << 8); i += 2
                if c < 0x3e:
                    for _ in range(c + 3):
                        out.append(out[len(out)-w] if w <= len(out) else 0)
                elif c == 0x3e:
                    v = src[i]; i += 1
                    out += bytes([v]) * w
                else:
                    off = src[i] | (src[i+1] << 8); i += 2
                    for _ in range(w):
                        out.append(out[len(out)-off] if off <= len(out) else 0)
    return out

def decode80pack(name):
    blob = section_b64(name)
    data = b""
    pos = 0
    while pos + 4 <= len(blob):
        si = blob[pos] | (blob[pos+1] << 8) | (blob[pos+2] << 16)
        tag = blob[pos+3]
        assert tag == 0x20, (name, pos, tag)
        data += bytes(decode80(blob[pos+4:pos+4+si]))
        pos += 4 + si
    return data

ov = decode80pack("OverlayPack")
ovd = decode80pack("OverlayDataPack")
print("OverlayPack len", len(ov), "OverlayDataPack len", len(ovd))

def g(grid, x, y):
    i = x + 512 * y
    return grid[i] if 0 <= i < len(grid) else None

blds = [("CAAIRP",109,106,3,3), ("CAOILD",93,54,2,2),
        ("CAPOWR",91,121,2,2), ("CATHOSP",47,56,6,4)]
for name, x0, y0, w, h in blds:
    print("===", name, w, "x", h, "@", (x0, y0))
    for row in range(-2, h+2):
        line = ""
        for col in range(-2, w+2):
            x, y = x0+col, y0+row
            v = g(ov, x, y)
            inside = (0 <= col < w and 0 <= row < h)
            if v is None:
                line += "  ?? "
            elif v == 0xFF:
                line += " [..]" if inside else "   . "
            else:
                line += (" [%02X]" % v) if inside else ("  %02X " % v)
        print(line)
    hits = []
    for r in range(h):
        for c in range(w):
            v = g(ov, x0+c, y0+r)
            if v not in (None, 0xFF):
                hits.append((x0+c, y0+r, v, g(ovd, x0+c, y0+r)))
    print("FOUNDATION overlay hits:", hits)
