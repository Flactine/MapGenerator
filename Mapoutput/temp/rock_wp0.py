# -*- coding: utf-8 -*-
import sys
sys.path.insert(0,r"d:\新建文件夹\VSProject\MapGenerator\temp")
import analyze_isopack5 as A
p=r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261002_205302.map"
cells=A.load_map(p)[0]
raw=open(p,"rb").read().decode("latin-1")
def sec(n):
    o=[];on=False
    for ln in raw.splitlines():
        s=ln.strip()
        if s.startswith("["): on=(s==n);continue
        if on and "=" in s:o.append(s)
    return o
wp={}
for s in sec("[Waypoints]"):
    k,v=s.split("="); vv=int(v); wp[int(k)]=(vv%1000,vv//1000)
print("出生点:",{k:wp[k] for k in sorted(wp)[:4]})
sx,sy=wp[0]
print("出生点0=(%d,%d)"%(sx,sy))
print("\n出生点0 周围 5x5 (x%d..%d y%d..%d):"%(sx-2,sx+2,sy-2,sy+2))
for y in range(sy-2,sy+3):
    row=[]
    for x in range(sx-2,sx+3):
        c=cells.get((x,y))
        t=c["tile"] if c else -1
        if t in (0,0xFFFF): s=" .. "
        elif 314<=t<=327: s=" ~%02d"%(t-314)
        elif 49<=t<=88: s=" C%02d"%(t-49)
        elif 89<=t<=130: s=" o%02d"%(t-89)
        elif 29<=t<=48: s=" r%02d"%(t-29)
        elif 131<=t<=147: s=" g%02d"%(t-131)
        elif 148<=t<=175: s=" W%02d"%(t-148)
        else: s="%4d"%t
        row.append(s)
    print("  y%-3d %s"%(y," ".join(row)))
print("        "+" ".join("x%-3d"%x for x in range(sx-2,sx+3)))
# 上面一格(sy-1)的原始瓦片号
up=cells.get((sx,sy-1))
print("\n正上格(%d,%d): tile=%s Level=%s slope=%s"%(sx,sy-1,
      up["tile"] if up else "缺", up["level"] if up else "?",
      up["slope"] if up else "?"))
# 附近 Terrain 对象（标准编码 x=key%1000）
print("\n附近 [Terrain] 对象:")
for s in sec("[Terrain]"):
    k,v=s.split("="); kk=int(k); x,y=kk%1000,kk//1000
    if max(abs(x-sx),abs(y-sy))<=4:
        print("   (%d,%d) %s"%(x,y,v))