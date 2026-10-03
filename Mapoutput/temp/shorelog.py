# -*- coding: utf-8 -*-
# 从 rmg_diag.log 提取指定区域内的 SHORE-UNHANDLED / SHORE-IDLE 行，统计 mask
import io, re, sys, collections

log = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_diag.log"
x0, x1, y0, y1 = [int(v) for v in sys.argv[1:5]]

pat = re.compile(r"SHORE-(UNHANDLED|IDLE) mode=(\d) cell=\((\d+),(\d+)\)(?: mask=0x([0-9A-Fa-f]+))?(?: tile=(\d+))?(?: touch=0x([0-9A-Fa-f]+))?")

unh = collections.defaultdict(list)
idl = collections.defaultdict(list)
allmask = collections.Counter()

with io.open(log, "r", encoding="utf-8", errors="replace") as fp:
    for line in fp:
        m = pat.search(line)
        if not m:
            continue
        kind, mode, x, y = m.group(1), int(m.group(2)), int(m.group(3)), int(m.group(4))
        if kind == "UNHANDLED":
            allmask[(mode, m.group(5))] += 1
        if x0 <= x <= x1 and y0 <= y <= y1:
            tag = "U%d" % mode if kind == "UNHANDLED" else "I%d" % mode
            extra = ("mask=0x%s" % m.group(5)) if m.group(5) else ("touch=0x%s" % m.group(7))
            (unh if kind == "UNHANDLED" else idl)[tag].append((x, y, "t=%s" % m.group(6), extra))

print("=== 全图 SHORE-UNHANDLED (mode, mask) 计数 ===")
for (mode, mask), c in sorted(allmask.items(), key=lambda kv: -kv[1]):
    print("  mode=%d mask=0x%-3s  x%d" % (mode, mask, c))

print()
print("=== 区域 (%d..%d, %d..%d) 明细 ===" % (x0, x1, y0, y1))
for tag in ("U2", "U1", "I1", "I2"):
    src = unh if tag.startswith("U") else idl
    if tag in src:
        print("-- %s (%d) --" % (tag, len(src[tag])))
        for x, y, t, extra in sorted(src[tag], key=lambda r: (r[1], r[0])):
            print("   (%3d,%3d) %s %s" % (x, y, t, extra))