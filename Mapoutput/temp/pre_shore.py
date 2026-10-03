# -*- coding: utf-8 -*-
# 铺岸片前(FillStaircaseBends 快照)五处构型：水~ 陆占位. 其它数字
import io, os, glob
base = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput"
f=sorted(glob.glob(os.path.join(base,"2026*_FillStaircaseBends.isopack5.txt")),key=os.path.getmtime)[-1]
T={}
with io.open(f,"r",encoding="utf-8",errors="replace") as fp:
    for line in fp:
        p=line.split()
        if len(p)<12: continue
        try: x=int(p[0]); y=int(p[1])
        except Exception: continue
        T[(x,y)]=int(p[2])
print("快照:", os.path.basename(f))
def s(t):
    if t is None: return " #"
    if t==0: return " ."
    if 314<=t<=327: return " ~"
    return "%3d"%t
def draw(x0,x1,y0,y1,title):
    print("--- %s  (%d..%d,%d..%d) ---" % (title,x0,x1,y0,y1))
    print("     "+"".join("%-4d"%x for x in range(x0,x1+1)))
    for y in range(y0,y1+1):
        print("y%-3d "%y+"".join("%-4s"%s(T.get((x,y))) for x in range(x0,x1+1)))
draw(45,53,46,54,"第一处 (49,49-51)")
draw(106,115,61,69,"第二处 (111,65)")

# 统计铺前"1格宽陆"占位格：东西皆水 或 南北皆水
def w(q):
    t=T.get(q); return None if t is None else (314<=t<=327)
spit=[]
for (x,y),t in T.items():
    if t==0 or (89<=t<=130):
        pass
    if 314<=t<=327: continue
    W,E,N,S = w((x-1,y)),w((x+1,y)),w((x,y-1)),w((x,y+1))
    if None in (W,E,N,S): continue
    if (W and E) or (N and S):
        spit.append((x,y,"EW" if W and E else "","NS" if N and S else "",t))
print()
print("铺前 1格宽陆格(占位/其它陆, 轴向对穿深水) 全图 %d 个:" % len(spit))
for x,y,a,b,t in sorted(spit,key=lambda q:(q[1],q[0])):
    if (44<=x<=54 and 45<=y<=55) or (106<=x<=115 and 60<=y<=70):
        print("   (%d,%d) %s%s t=%d" % (x,y,a,b,t))