# -*- coding: utf-8 -*-
p=r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261002_195435.map"
raw=open(p,"rb").read().decode("latin-1")
def sec(n):
    o=[];on=False
    for ln in raw.splitlines():
        s=ln.strip()
        if s.startswith("["): on=(s==n);continue
        if on and "=" in s:o.append(s)
    return o
print("=== [Waypoints] 原始 ===")
for s in sec("[Waypoints]")[:6]:
    k,v=s.split("="); vv=int(v)
    print("  %s=%s  A(x%%1000,y//1000)=(%d,%d)  B(x//1000,y%%1000)=(%d,%d)"
          %(k,v,vv%1000,vv//1000,vv//1000,vv%1000))
print("=== [Terrain] 前8 ===")
for s in sec("[Terrain]")[:8]:
    k,v=s.split("="); kk=int(k)
    print("  %s=%s  A(%d,%d)  B(%d,%d)"
          %(k,v,kk%1000,kk//1000,kk//1000,kk%1000))