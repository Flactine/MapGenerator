# -*- coding: utf-8 -*-
import io, os, glob
base = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput"
f1=sorted(glob.glob(os.path.join(base,"2026*_SelectShoreTile.isopack5.txt")),key=os.path.getmtime)[-1]
T={}
with io.open(f1,"r",encoding="utf-8",errors="replace") as fp:
    for line in fp:
        p=line.split()
        if len(p)<12: continue
        try: x=int(p[0]); y=int(p[1])
        except Exception: continue
        T[(x,y)]=int(p[2])
def s(t):
    if t is None: return "  #"
    if t==0: return "  ."
    if 314<=t<=327: return " ~ "
    if 89<=t<=130: return "%3d"%t
    return "   "
x0,x1,y0,y1=106,115,61,69
print("文件:", os.path.basename(f1))
print("     "+"".join("%-4d"%x for x in range(x0,x1+1)))
for y in range(y0,y1+1):
    print("y%-3d "%y + "".join("%-4s"%s(T.get((x,y))) for x in range(x0,x1+1)))