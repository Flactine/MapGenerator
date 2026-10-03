#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Compare the vanilla flt_8610B4 atan table against the port's runtime
std::atan computation, float32 bit for bit."""
import json
import math
import struct

raw = open("atan.json", encoding="utf-8").read()
data = json.loads(raw)
blob = bytes(int(x, 16) for x in data["result"][0]["data"].split())
assert len(blob) == 4097 * 4, len(blob)

van = struct.unpack("<%df" % 4097, blob)

# step as stored at 0x8650B8
step_bits = 1019739780
step = struct.unpack("<f", struct.pack("<I", step_bits))[0]
print("step = %.18g  bits=0x%08X" % (step, step_bits))

diffs = []
maxulp = 0
for i in range(4097):
    port = struct.unpack("<f", struct.pack("<f", math.atan(i * step)))[0]
    a = struct.unpack("<I", struct.pack("<f", van[i]))[0]
    b = struct.unpack("<I", struct.pack("<f", port))[0]
    ulp = abs(a - b)
    if ulp:
        diffs.append((i, van[i], port, ulp))
    maxulp = max(maxulp, ulp)

print("entries differing (float32 ULP):", len(diffs), "maxULP=", maxulp)
for i, v, p, u in diffs[:15]:
    print("  i=%d van=%.9g(%08X) port=%.9g(%08X) ulp=%d"
          % (i, v, struct.unpack('<I', struct.pack('<f', v))[0],
             p, struct.unpack('<I', struct.pack('<f', p))[0], u))

# the saturation constant the port uses
port_pi2 = struct.unpack("<f", struct.pack("<f", math.pi / 2))[0]
print("port pi/2 f32 = %.9g  vanilla 1.5707964 = %.9g  eq=%s"
      % (port_pi2, 1.5707964, port_pi2 == 1.5707964))
print("table[4096] = %.9g" % van[4096])
