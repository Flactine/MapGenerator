#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Find every reference in a PE to an address range, then disassemble around.

    python find_refs.py <exe> <va_lo> <va_hi>

Scans every section's raw bytes for little-endian 4-byte addresses inside
[va_lo, va_hi). Reports each hit's VA and the referenced target.
"""
import struct
import sys


def main():
    path = sys.argv[1]
    lo = int(sys.argv[2], 0)
    hi = int(sys.argv[3], 0)
    data = open(path, "rb").read()
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    nsec = struct.unpack_from("<H", data, pe + 6)[0]
    optsz = struct.unpack_from("<H", data, pe + 20)[0]
    imagebase = struct.unpack_from("<I", data, pe + 24 + 28)[0]
    sec0 = pe + 24 + optsz
    for i in range(nsec):
        s = sec0 + i * 40
        name = data[s:s + 8].rstrip(b"\0")
        vsz, va, rsz, raw = struct.unpack_from("<IIII", data, s + 8)
        blob = data[raw:raw + rsz]
        hits = []
        for off in range(0, len(blob) - 3):
            val = struct.unpack_from("<I", blob, off)[0]
            if lo <= val < hi:
                hits.append((off, val))
        if hits:
            print("section %s VA 0x%X raw 0x%X, %d refs" % (
                name.decode(errors="replace"), imagebase + va, raw, len(hits)))
            for off, val in hits:
                print("   at VA 0x%X (file 0x%X) -> 0x%X"
                      % (imagebase + va + off, raw + off, val))


main()
