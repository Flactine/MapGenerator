# -*- coding: utf-8 -*-
p=r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261002_205302.map"
raw=open(p,"rb").read().decode("latin-1")
def sec(n):
    o=[];on=False
    for ln in raw.splitlines():
        s=ln.strip()
        if s.startswith("["): on=(s==n);continue
        if on and "=" in s:o.append(s)
    return o
from collections import Counter
names=Counter(v.split("=")[1] for v in sec("[Terrain]"))
print("全图 Terrain 对象种类:",dict(names))
print("\n出生点0(110,112) 半径8内全部对象:")
for s in sec("[Terrain]"):
    k,v=s.split("="); kk=int(k); x,y=kk%1000,kk//1000
    if max(abs(x-110),abs(y-112))<=8:
        print("   (%d,%d) %s"%(x,y,v))