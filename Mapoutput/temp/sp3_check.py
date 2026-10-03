# -*- coding: utf-8 -*-
path = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261003_185613.isopack5.txt"
cells = {}
for line in open(path, encoding="utf-8", errors="replace"):
    if line.startswith(";"): continue
    p = line.split()
    if len(p) < 12: continue
    cells[(int(p[0]), int(p[1]))] = dict(t=int(p[2]), H=int(p[7]), L=int(p[8]), land=int(p[9]), s=int(p[10]), pa=int(p[11]))

pts = [("pt0",131,241),("pt1",129,18),("pt2",240,129),("pt3",137,114),
       ("pt4",63,84),("pt5",187,185),("pt6",98,180),("pt7",194,83)]
R=4
for n,x0,y0 in pts:
    print("="*86)
    print("%s anchor=(%d,%d)" % (n,x0,y0))
    for y in range(y0-R,y0+R+1):
        row="y%-3d "%y
        for x in range(x0-R,x0+R+1):
            c=cells.get((x,y))
            if c is None: row+="  MISS  "; continue
            tag = "[%4d/L%02d/s%02d/p%d]" % (c["t"],c["L"],c["s"],c["pa"]) if (x,y)==(x0,y0) else " %4d/L%02d/s%02d  " % (c["t"],c["L"],c["s"])
            row+=tag
        print(row)
