# -*- coding: utf-8 -*-
# 在 SelectShoreTile 阶段快照上验证拦截判据
import io, os, glob
base = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput"
def load(fn):
    d={}
    with io.open(os.path.join(base,fn),"r",encoding="utf-8",errors="replace") as fp:
        for line in fp:
            p=line.split()
            if len(p)<12: continue
            try: x=int(p[0]); y=int(p[1])
            except Exception: continue
            d[(x,y)]=int(p[2])
    return d
# 最新一轮的 SelectShoreTile 快照(pass1 之后)
f1=sorted(glob.glob(os.path.join(base,"2026*_SelectShoreTile.isopack5.txt")),key=os.path.getmtime)[-1]
T=load(os.path.basename(f1))
print("快照:", os.path.basename(f1))
def w(x,y):
    t=T.get((x,y))
    return None if t is None else (314<=t<=327)
def orth_water(x,y):
    return [dn for dn,(dx,dy) in (("N",(0,-1)),("E",(1,0)),("S",(0,1)),("W",(-1,0)))
            if w(x+dx,y+dy) is True]
# 两处触发与2x2覆盖（n12/朝向: 38 NW off0,0; 40 SW off0,-1）
cases = [
    ("第一处 (48,50) n12=38 NW", (48,50), (0,0)),
    ("第二处 (110,66) n12=40 SW", (110,66), (0,-1)),
]
for name,(cx,cy),(ox,oy) in cases:
    print(name)
    hit=False
    for gy in range(cy+oy, cy+oy+2):
        for gx in range(cx+ox, cx+ox+2):
            ow=orth_water(gx,gy)
            t=T.get((gx,gy))
            print("   覆盖格(%d,%d) t=%s 正交深水=%s" % (gx,gy,t,ow or "无"))
            if ow: hit=True
    print("   => 判据%s拦截" % ("会" if hit else "不会"))
    print()