#!/usr/bin/env python3
"""
Analyze the *.isopack5.txt dump written by SaveMapFile.

Dump columns (one line per cell, tab separated, then " | hex"):
    X Y tile bMapData bSubTile bHeight bMapData2 = Height Level LandType SlopeIndex Passability

Reported here:
  * tile class census (placeholder / RampBase 29..48 / Ramp edge fixup 510..521 / other)
  * Level histogram
  * BOGUS RAMPS: a cell carries a ramp tile (or SlopeIndex != 0) while all of its
    eight neighbours sit on the SAME Level - i.e. a slope with no height step to
    bridge.  (The rule: two neighbour cells at the same level must not be joined
    by a ramp.)
  * for the bogus ramps, the histogram of neighbouring tile indices that are
    neither placeholder nor ramp - these are the "features" (cliff / shore /
    water family, etc.) the bad ramps cluster around.
  * ISOLATED PIT / BUMP: a cell whose Level differs by +-1 from every neighbour,
    listed separately.
Usage:  python analyze_isopack5.py <dump.txt> [<dump2.txt>]
"""

import base64
import sys
from collections import Counter, defaultdict

DIRS = [(0, -1), (1, -1), (1, 0), (1, 1), (0, 1), (-1, 1), (-1, 0), (-1, -1)]

PLACEHOLDER = 65535


def is_ramp_base(t):
    return 29 <= t <= 48


def is_ramp_smooth(t):
    return 510 <= t <= 521


def is_ramp(t):
    return is_ramp_base(t) or is_ramp_smooth(t)


def load(path):
    cells = {}
    with open(path, "r", encoding="utf-8", errors="replace") as fh:
        for line in fh:
            if line.startswith(";") or not line.strip():
                continue
            body = line.split("|")[0].split()
            if len(body) < 12:
                continue
            v = [int(tok) for tok in body[:12]]
            cells[(v[0], v[1])] = {
                "tile": v[2], "bSubTile": v[4], "bHeight": v[5],
                "height": v[7], "level": v[8], "land": v[9],
                "slope": v[10], "pass": v[11],
            }
    return cells


# ---------------------------------------------------------------------------
# Reading a real .map / .yrm
#
# [IsoMapPack5] is the base64 of one or more format-5 sections; each section is
# [uint16 size_in][uint16 size_out][size_in bytes of LZO1X], exactly what
# MapGenMapFile.cpp writes.  The port emits the uncompressed literal form, but
# the game's own writer really compresses, so a full LZO1X decompressor is
# needed to read a shipped map.
#
# Each decoded record is the 11 bytes of MapGenMapFile.cpp:
#   +0 int16 X  +2 int16 Y  +4 uint16 tile  +6 uint16 bMapData
#   +8 uint8 Height (+0x11A)  +9 uint8 Level (+0x11B)  +10 uint8 (+0x119)
# SlopeIndex (+0x11C) is NOT in the file, so it is recovered from the tile where
# that is possible: the RampBase family 29..48 is indexed by the pattern number
# (slope = tile - 28).  The 510..521 fixup family carries no slope information.
# ---------------------------------------------------------------------------

M2_MAX_OFFSET = 0x0800


def lzo1x_decompress(src, dst_len):
    """LZO1X decoder (a transliteration of lzo1x_decompress_safe).

    Raises ValueError when the stream runs off the end or does not produce
    exactly dst_len bytes - either means a broken decoder or a broken file."""
    out = bytearray()
    ip = 0
    n = len(src)

    def byte():
        nonlocal ip
        if ip >= n:
            raise ValueError("lzo: out of input at %d" % ip)
        v = src[ip]
        ip += 1
        return v

    def literals(cnt):
        nonlocal ip
        if ip + cnt > n:
            raise ValueError("lzo: literal run past the end of input")
        out.extend(src[ip:ip + cnt])
        ip += cnt

    def match(m_pos, length):
        if m_pos < 0:
            raise ValueError("lzo: negative match offset %d" % m_pos)
        for i in range(length):
            out.append(out[m_pos + i])

    t = byte()
    if t > 17:
        t -= 17
        if t < 4:
            literals(t)
            t = byte()
            state = "match"
        else:
            literals(t)
            state = "first_literal_run"
    else:
        state = "literal_run"

    while state != "eof":
        if state == "literal_run":
            if t >= 16:
                state = "match"
                continue
            if t == 0:
                while ip < n and src[ip] == 0:
                    t += 255
                    ip += 1
                t += 15 + byte()
            literals(t + 3)
            state = "first_literal_run"
            continue

        if state == "first_literal_run":
            t = byte()
            if t >= 16:
                state = "match"
                continue
            m_pos = len(out) - (1 + M2_MAX_OFFSET) - (t >> 2) - (byte() << 2)
            match(m_pos, 3)
            state = "match_done"
            continue

        if state == "match":
            if t >= 64:
                m_pos = len(out) - 1 - ((t >> 2) & 7) - (byte() << 3)
                ln = (t >> 5) + 1
            elif t >= 32:
                t &= 31
                if t == 0:
                    while ip < n and src[ip] == 0:
                        t += 255
                        ip += 1
                    t += 31 + byte()
                m_pos = len(out) - 1 - (src[ip] >> 2) - (src[ip + 1] << 6)
                ip += 2
                ln = t + 2
            elif t >= 16:
                m_pos = len(out) - ((t & 8) << 11)
                t &= 7
                if t == 0:
                    while ip < n and src[ip] == 0:
                        t += 255
                        ip += 1
                    t += 7 + byte()
                m_pos -= (src[ip] >> 2) + (src[ip + 1] << 6)
                ip += 2
                if m_pos == len(out):
                    state = "eof"
                    continue
                m_pos -= 0x4000
                ln = t + 2
            else:
                m_pos = len(out) - 1 - (t >> 2) - (byte() << 2)
                match(m_pos, 2)
                state = "match_done"
                continue
            match(m_pos, ln)
            state = "match_done"
            continue

        if state == "match_done":
            t = src[ip - 2] & 3
            if t == 0:
                t = byte()
                state = "literal_run"
            else:
                state = "match_next"
            continue

        if state == "match_next":
            literals(t)
            t = byte()
            state = "match"
            continue

    if len(out) != dst_len:
        raise ValueError("lzo: decoded %d bytes, expected %d" % (len(out), dst_len))
    return out


def _section(path, name):
    """The concatenated base64 of one numbered-key INI section."""
    parts = []
    inside = False
    want = "[" + name.lower() + "]"
    with open(path, "r", encoding="utf-8", errors="replace") as fh:
        for line in fh:
            s = line.strip()
            if s.startswith("["):
                inside = (s.lower() == want)
                continue
            if not inside or not s or s.startswith(";"):
                continue
            if "=" in s:
                s = s.split("=", 1)[1].strip()
            parts.append(s)
    return "".join(parts)


def load_map(path):
    """Decode [IsoMapPack5] of a .map / .yrm into the same dict `load` builds."""
    b64 = _section(path, "IsoMapPack5")
    if not b64:
        raise ValueError("no [IsoMapPack5] in %s" % path)
    raw = base64.b64decode(b64 + "=" * (-len(b64) % 4))

    data = bytearray()
    sections = []
    pos = 0
    while pos + 4 <= len(raw):
        size_in = raw[pos] | (raw[pos + 1] << 8)
        size_out = raw[pos + 2] | (raw[pos + 3] << 8)
        if size_in == 0:
            break
        if pos + 4 + size_in > len(raw):
            raise ValueError("section %d: size_in %d overruns the blob"
                             % (len(sections), size_in))
        sections.append((size_in, size_out))
        data += lzo1x_decompress(bytes(raw[pos + 4:pos + 4 + size_in]), size_out)
        pos += 4 + size_in

    cells = {}
    for i in range(len(data) // 11):
        r = data[i * 11:i * 11 + 11]
        x = int.from_bytes(r[0:2], "little", signed=True)
        y = int.from_bytes(r[2:4], "little", signed=True)
        tile = r[4] | (r[5] << 8)
        if is_ramp_base(tile):
            slope = tile - 28                      # RampBase:   tile = slope + 29 - 1
        elif is_ramp_smooth(tile):
            slope = (tile - 510) // 3 + 1          # RampSmooth: 4 slopes x 3 masks
        else:
            slope = 0
        cells[(x, y)] = {
            "tile": tile, "bSubTile": r[8], "bHeight": r[9],
            "height": r[8], "level": r[9], "land": -1,
            "slope": slope,
            "pass": -1,
        }
    return cells, sections, len(data)


# off_83FF18 (19 entries), corner order = e(x,y), e(x+1,y), e(x+1,y+1), e(x,y+1).
# index 0 is the "not a pattern" filler {-1,-1,-1,-1}; a flat cell (all four
# corners equal) is NOT in the table, so such a cell keeps its previous
# SlopeIndex / tile and only has its Level updated.
PAT = [
    [-1, -1, -1, -1], [0, 15, 15, 0], [0, 0, 15, 15], [15, 0, 0, 15],
    [15, 15, 0, 0], [0, 0, 15, 0], [0, 0, 0, 15], [15, 0, 0, 0],
    [0, 15, 0, 0], [0, 15, 15, 15], [15, 0, 15, 15], [15, 15, 0, 15],
    [15, 15, 15, 0], [0, 15, 30, 15], [15, 0, 15, 30], [30, 15, 0, 15],
    [15, 30, 15, 0], [0, 15, 0, 15], [15, 0, 15, 0],
]

# corner i of cell (x, y) is the grid point:
CORNER_AT = [(0, 0), (1, 0), (1, 1), (0, 1)]


def corner_consistency(cells):
    """Every grid point is shared by up to four cells; all of them must imply
    the same absolute elevation (Level * 15 + pattern offset).

    A boundary between cells whose Levels differ by 2 or more is a cliff: the
    jump is carried by the cliff tiles of the earlier stage and the cell that
    straddles it is skipped by the finalize pass on purpose, so such points are
    excluded.  What remains are points shared by cells that differ by at most
    one Level - there a ramp pattern has to make both sides meet, and a
    disagreement there is a real defect ("two cells that are level, or one step
    apart, that do not line up")."""
    grid = defaultdict(list)
    covered = 0
    for (x, y), c in cells.items():
        # 0xFFFF means "no tile of its own / covered by a multi-cell tile" (the
        # merge step's marker).  Its Level is a frame hint for that other tile,
        # not this cell's own corner height, so it cannot take part in the
        # corner arithmetic.
        if c["tile"] == PLACEHOLDER and c["slope"] == 0:
            covered += 1
            continue
        s = c["slope"]
        pat = PAT[s] if 1 <= s <= 18 else [0, 0, 0, 0]
        base = c["level"] * 15
        for i, (dx, dy) in enumerate(CORNER_AT):
            grid[(x + dx, y + dy)].append((base + pat[i], x, y, c["level"]))

    bad = []
    cliff = 0
    for g, lst in grid.items():
        if len(lst) < 2:
            continue
        lv = [l for _, _, _, l in lst]
        if max(lv) - min(lv) >= 2:
            cliff += 1
            continue
        vals = [v for v, _, _, _ in lst]
        if max(vals) != min(vals):
            bad.append((g, lst))
    deltas = Counter()
    for _, lst in bad:
        vals = [v for v, _, _, _ in lst]
        deltas[(max(vals) - min(vals)) // 15] += 1
    return grid, bad, deltas, cliff


def analyse(path):
    print("=" * 78)
    print("file : %s" % path)
    if path.lower().endswith((".map", ".yrm")):
        cells, sections, total = load_map(path)
        print("pack : %d section(s), %d bytes decoded -> %d records"
              % (len(sections), total, len(cells)))
    else:
        cells = load(path)
        print("cells: %d" % len(cells))
    if cells:
        xs = [p[0] for p in cells]
        ys = [p[1] for p in cells]
        print("bounds: X %d..%d  Y %d..%d" % (min(xs), max(xs), min(ys), max(ys)))

    # ---- census -----------------------------------------------------------
    cnt = Counter()
    for c in cells.values():
        t = c["tile"]
        if t == PLACEHOLDER:
            cnt["placeholder"] += 1
        elif is_ramp_base(t):
            cnt["rampBase"] += 1
        elif is_ramp_smooth(t):
            cnt["rampSmooth"] += 1
        else:
            cnt["other"] += 1
    print("census: placeholder=%d rampBase=%d rampSmooth=%d other=%d  (ramps=%d)"
          % (cnt["placeholder"], cnt["rampBase"], cnt["rampSmooth"], cnt["other"],
             cnt["rampBase"] + cnt["rampSmooth"]))

    # A cell that carries a slope pattern but no ramp tile is drawn flat by the
    # game while its height corners say otherwise - the height data and the
    # visible tile disagree.  (For a .map/.yrm the slope is only known where a
    # ramp tile names it, so these two counters are 0 there by construction.)
    no_tile = sum(1 for c in cells.values()
                  if c["tile"] == PLACEHOLDER and c["slope"] != 0)
    odd_tile = sum(1 for c in cells.values()
                   if c["tile"] != PLACEHOLDER and not is_ramp(c["tile"])
                   and c["slope"] != 0)
    print("sloped but no ramp tile: placeholder=%d  other-tile=%d" % (no_tile, odd_tile))

    lv = Counter(c["level"] for c in cells.values())
    print("level histogram: " + " ".join("%d:%d" % kv for kv in sorted(lv.items())))

    # ---- bogus ramps ------------------------------------------------------
    bogus = []
    feature_tiles = Counter()
    for (x, y), c in cells.items():
        if not (is_ramp(c["tile"]) or c["slope"] != 0):
            continue
        nbs = [(x + dx, y + dy) for dx, dy in DIRS]
        present = [cells[p] for p in nbs if p in cells]
        if len(present) < 8:
            continue                      # diamond border cell: not conclusive
        if any(n["level"] != c["level"] for n in present):
            continue                      # there IS a step: legitimately sloped
        bogus.append((x, y, c))
        for n in present:
            t = n["tile"]
            if t != PLACEHOLDER and not is_ramp(t):
                feature_tiles[t] += 1

    print("BOGUS RAMPS (ramp tile / slope!=0 but all 8 neighbours same Level): %d"
          % len(bogus))
    if bogus:
        rows = defaultdict(list)
        for x, y, _ in bogus:
            rows[y].append(x)
        shown = 0
        for y in sorted(rows):
            xs = sorted(rows[y])
            spans = []
            start = prev = xs[0]
            for v in xs[1:]:
                if v == prev + 1:
                    prev = v
                    continue
                spans.append((start, prev))
                start = prev = v
            spans.append((start, prev))
            print("   y=%3d  x: %s" % (y, " ".join(
                ("%d" % a) if a == b else ("%d-%d" % (a, b)) for a, b in spans)))
            shown += 1
            if shown >= 25:
                print("   ... (%d rows total)" % len(rows))
                break
        print("   bogus-ramp rows: %d" % len(rows))
        print("   neighbouring NON-placeholder NON-ramp tiles (top 15):")
        for t, n in feature_tiles.most_common(15):
            print("      tile %-6d x%d" % (t, n))

    # ---- isolated pits / bumps -------------------------------------------
    pits = bumps = 0
    for (x, y), c in cells.items():
        present = [cells[p] for p in
                   ((x + dx, y + dy) for dx, dy in DIRS) if p in cells]
        if len(present) < 8:
            continue
        d = [n["level"] - c["level"] for n in present]
        if all(v == 1 for v in d):
            pits += 1
        elif all(v == -1 for v in d):
            bumps += 1
    print("isolated pits (own Level 1 below every neighbour): %d" % pits)
    print("isolated bumps (own Level 1 above every neighbour): %d" % bumps)

    # ---- corner consistency ----------------------------------------------
    grid, bad, deltas, cliff = corner_consistency(cells)
    print("corner grid: %d points; %d cliff-boundaries (skipped), "
          "%d REAL disagreements" % (len(grid), cliff, len(bad)))
    if deltas:
        print("   disagreement size (levels): " +
              " ".join("%d:%d" % kv for kv in sorted(deltas.items())))
        rows = Counter(g[1] for g, _ in bad)
        shown = 0
        for y in sorted(rows):
            print("   y=%3d  %d bad corner(s)" % (y, rows[y]))
            shown += 1
            if shown >= 15:
                break
        g, lst = bad[0]
        print("   example corner %s: %s" % (g, sorted(lst)))

    # ---- tile census ------------------------------------------------------
    print("top tiles: " + " ".join("%d:%d" % kv for kv in
                                   Counter(c["tile"] for c in cells.values()).most_common(18)))
    return cells


def print_window(cells, cx, cy, r):
    print("window around (%d,%d), radius %d - cells shown as tile/level:" % (cx, cy, r))
    xs = range(cx - r, cx + r + 1)
    print("       " + "".join("%8d" % x for x in xs))
    for y in range(cy - r, cy + r + 1):
        row = "y=%4d " % y
        for x in xs:
            c = cells.get((x, y))
            row += "       ." if c is None else "%8s" % ("%d/%d" % (c["tile"], c["level"]))
        print(row)


def main():
    files = []
    win = None
    for a in sys.argv[1:]:
        if a.startswith("--win="):
            win = [int(v) for v in a[6:].split(",")]
        else:
            files.append(a)
    if not files:
        print(__doc__)
        return 1
    for f in files:
        cells = analyse(f)
        if win:
            print_window(cells, win[0], win[1], win[2])
    return 0


if __name__ == "__main__":
    sys.exit(main())