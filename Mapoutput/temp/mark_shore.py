# -*- coding: utf-8 -*-
# 在最终图上标出所有"存活到最后的 n12=37/38/39/40 拐角片"
# 数据链：rmg_diag.log 落片记录(cell,n12,off) -> kShoreFootprints 几何算覆盖
#         -> 与最终 isopack5 快照比对 tile==88+n12 判定存活
# 输出：shore_check_<原文件名>.map（原 Waypoints 0/1 出生点保留，100 起追加）
import io, os, re, sys, shutil

base = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput"
stem = sys.argv[1]                       # 如 rmg_20261002_155735
snap = os.path.join(base, stem + ".isopack5.txt")
srcmap = os.path.join(base, stem + ".map")
outmap = os.path.join(base, "shore_check_" + stem + ".map")

# 42 个 shore 片几何（与 MapGenRiver.cpp kShoreFootprints 一致）
FP = [
 (2,2,0xF),(2,2,0xF),(2,2,0xF),(1,2,0x3),(2,3,0x3F),(2,3,0x3F),
 (2,2,0xF),(2,2,0xF),(2,2,0xF),(2,2,0xF),(2,2,0xF),(2,1,0x3),
 (3,2,0x3F),(3,2,0x3F),(2,2,0xF),(2,2,0xF),(2,2,0xF),(2,2,0xF),
 (2,2,0xF),(1,2,0x3),(2,3,0x3F),(2,3,0x3F),(2,2,0xF),(2,2,0xF),
 (2,2,0xF),(2,2,0xF),(2,2,0xF),(2,1,0x3),(3,2,0x3F),(3,2,0x3F),
 (2,2,0xF),(2,2,0xF),(2,2,0xF),(2,2,0xF),(2,2,0xF),(2,2,0xF),
 (2,2,0xF),(2,2,0xF),(2,2,0xF),(2,2,0xF),(6,4,0xFFFFCE),
 (9,5,0x1FEFF7FC380C),
]

def cover(n12, cx, cy, ox, oy):
    w, h, m = FP[n12 - 1]
    out = []
    for r in range(h):
        for ccol in range(w):
            if (m >> (r * w + ccol)) & 1:
                out.append((cx + ox + ccol, cy + oy + r))
    return out

# 1) 最终快照
tile = {}
with io.open(snap, "r", encoding="utf-8", errors="replace") as fp:
    for line in fp:
        p = line.split()
        if len(p) < 12: continue
        try: x = int(p[0]); y = int(p[1])
        except Exception: continue
        tile[(x, y)] = int(p[2])

# 2) 日志中的落片记录
pat = re.compile(r"SHORE mode=(\d) g=\d+ cell=\((\d+),(\d+)\) mask=0x([0-9A-Fa-f]+) "
                 r"n12=(\d+) off=\((-?\d+),(-?\d+)\) placed=(\d)")
records = []
with io.open(os.path.join(base, "rmg_diag.log"), "r", encoding="utf-8",
             errors="replace") as fp:
    for line in fp:
        m = pat.search(line)
        if not m: continue
        mode = int(m.group(1)); x = int(m.group(2)); y = int(m.group(3))
        mask = int(m.group(4), 16); n12 = int(m.group(5))
        ox = int(m.group(6)); oy = int(m.group(7)); placed = int(m.group(8))
        if n12 in (37, 38, 39, 40) and placed:
            records.append((mode, x, y, mask, n12, ox, oy))

# 3) 存活判定：覆盖格中最终 tile == 88+n12 的格子
pieces = []
for mode, x, y, mask, n12, ox, oy in records:
    cells = cover(n12, x, y, ox, oy)
    alive = [q for q in cells if tile.get(q) == 88 + n12]
    if alive:
        pieces.append(dict(mode=mode, trig=(x, y), n12=n12, mask=mask,
                           off=(ox, oy), alive=alive, allc=cells))

# 4) 排除用户已标的 5 格所在片
user = [(48, 51), (49, 51), (49, 50), (49, 49), (111, 65)]
excluded, kept = [], []
for pc in pieces:
    if any(q in pc["allc"] for q in user):
        excluded.append(pc)
    else:
        kept.append(pc)

# 存活格去重（不同片可能覆盖同格）
used = set()
wp = []          # (编号, x, y, 片描述)
nxt = 100
report = []
for pc in sorted(kept, key=lambda d: (d["trig"][1], d["trig"][0])):
    mark = [q for q in pc["alive"] if q not in used]
    if not mark:
        continue
    base_no = nxt
    for q in sorted(mark, key=lambda q: (q[1], q[0])):
        wp.append((nxt, q[0], q[1]))
        used.add(q)
        nxt += 1
    t = pc["trig"]
    report.append((base_no, nxt - 1, pc["n12"], t,
                   len(pc["alive"]), len(pc["allc"]), pc["mask"], mark))

# 5) 写入新 map（原文件 ANSI 字节，插入纯 ASCII 行）
raw = open(srcmap, "rb").read().decode("latin-1")
lines = raw.split("\n")
out_lines = []
inserted = False
for ln in lines:
    out_lines.append(ln)
    if not inserted and ln.strip() == "1=115054":
        for no, x, y in wp:
            out_lines.append("%d=%d" % (no, x + 1000 * y))
        inserted = True
assert inserted, "没找到 Waypoints 插入点"
open(outmap, "wb").write("\n".join(out_lines).encode("latin-1"))

print("日志中 37/38/39/40 落片记录: %d, 最终存活片: %d"
      % (len(records), len(pieces)))
print("排除(覆盖你已标5格的片) %d 片:" % len(excluded))
for pc in excluded:
    print("   n12=%d 触发%s 存活格%s"
          % (pc["n12"], pc["trig"], pc["alive"]))
print()
print("其余候选片 %d 个，路径点编号 %d..%d：" % (len(report), 100, nxt - 1))
print("编号区间      片号  触发格    存活/总  mask   标记格")
for a, b, n12, t, na, nt, mask, mark in report:
    rng = ("%d" % a) if a == b else ("%d-%d" % (a, b))
    print("  %-9s  %-3d %-9s %2d/%-2d   0x%02X   %s"
          % (rng, n12, t, na, nt, mask, mark))
print()
print("输出文件:", outmap)