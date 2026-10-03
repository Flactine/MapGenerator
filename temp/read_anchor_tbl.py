#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Read the cliff anchor-offset pair table at VA 0xABDDA4 (40 x/y int16
pairs, used by sub_579620 as word_ABDDA4[2*k]/word_ABDDA6[2*k])."""
import struct

EXE = r"D:\Ra2\gamemd.exe"
VA = 0xABDDA4
NPair = 42

d = open(EXE, "rb").read()
pe = struct.unpack_from("<I", d, 0x3C)[0]
assert d[pe:pe+4] == b"PE\0\0"
coff = pe + 4
nsec = struct.unpack_from("<H", d, coff + 2)[0]
opt_size = struct.unpack_from("<H", d, coff + 16)[0]
image_base = struct.unpack_from("<I", d, coff + 20 + 28)[0]
sec0 = coff + 20 + opt_size
print("image base 0x%X sections %d" % (image_base, nsec))
rva_target = VA - image_base
file_off = None
for i in range(nsec):
    o = sec0 + i * 40
    name = d[o:o+8].rstrip(b"\0").decode("latin1")
    vsize, vaddr, rsize, raddr = struct.unpack_from("<IIII", d, o + 8)
    print("  %-8s VA=0x%X vsize=0x%X raw=0x%X rsize=0x%X" % (name, image_base+vaddr, vsize, raddr, rsize))
    if vaddr <= rva_target < vaddr + max(vsize, rsize):
        file_off = raddr + (rva_target - vaddr)
assert file_off is not None, "VA not mapped"
print("file offset 0x%X" % file_off)
print("slot  dx  dy")
for k in range(1, NPair + 1):
    dx, dy = struct.unpack_from("<hh", d, file_off + 4 * (k - 1))
    print("%3d  %4d %4d" % (k, dx, dy))
