#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Disassemble one function of a PE.  python disasm_fn.py <exe> <va_start> [va_end]"""
import struct
import sys

import capstone


def main():
    path = sys.argv[1]
    start = int(sys.argv[2], 0)
    end = int(sys.argv[3], 0) if len(sys.argv) > 3 else start + 0x600
    data = open(path, "rb").read()
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    nsec = struct.unpack_from("<H", data, pe + 6)[0]
    optsz = struct.unpack_from("<H", data, pe + 20)[0]
    sec0 = pe + 24 + optsz
    imagebase = struct.unpack_from("<I", data, pe + 24 + 28)[0]
    fo = None
    for i in range(nsec):
        s = sec0 + i * 40
        name = data[s:s + 8].rstrip(b"\0")
        vsz, va, rsz, raw = struct.unpack_from("<IIII", data, s + 8)
        if imagebase + va <= start < imagebase + va + max(vsz, rsz):
            fo = raw + (start - (imagebase + va))
            secname = name
            break
    if fo is None:
        print("VA not found in sections")
        return
    size = min(end - start, len(data) - fo)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = False
    print("section %s fileoff 0x%X size %d" % (secname.decode(errors="replace"),
                                              fo, size))
    for ins in md.disasm(data[fo:fo + size], start):
        print("0x%X: %-10s %s %s" % (ins.address, ins.bytes.hex(),
                                     ins.mnemonic, ins.op_str))
        if len(sys.argv) > 3 and ins.address >= end - 1:
            break


main()
