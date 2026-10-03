import io, os, sys
base = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput"

def load(name):
    cells = {}
    with io.open(os.path.join(base, name), "r", encoding="utf-8", errors="replace") as fp:
        for line in fp:
            p = line.split()
            if len(p) < 12:
                continue
            try:
                x = int(p[0]); y = int(p[1])
            except Exception:
                continue
            cells[(x, y)] = (int(p[2]), int(p[8]), int(p[10]))
    return cells

def cls(t):
    if t == 0: return '.'
    if 29 <= t <= 43: return 'r'
    if 384 <= t <= 403: return 'p'
    if 49 <= t <= 88: return 'c'
    return '?'

name = sys.argv[1]
x0, x1, y0, y1 = [int(v) for v in sys.argv[2:6]]
c = load(name)

print("      " + "".join("%2d" % ((x // 10) % 10) for x in range(x0, x1 + 1)))
print("      " + "".join("%2d" % (x % 10) for x in range(x0, x1 + 1)))
for y in range(y0, y1 + 1):
    row = []
    for x in range(x0, x1 + 1):
        v = c.get((x, y))
        if v is None:
            row.append("..")
        else:
            lvl = v[1]
            ch = '4' if lvl == 4 else ('8' if lvl == 8 else 'X')
            row.append(ch + cls(v[0]))
    print("y=%-4d" % y + "".join(row))
print()
print("legend: first char = Level (4/8/X), second = tile class (. placeholder, r ramp-base 29-43, p slope-set-piece 384-403, c cliff 49-88)")