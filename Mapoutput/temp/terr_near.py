# -*- coding: utf-8 -*-
p=r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261002_195435.map"
raw=open(p,"rb").read().decode("latin-1")
terr=[];on=False
for ln in raw.splitlines():
    s=ln.strip()
    if s.startswith("["): on=(s=="[Terrain]");continue
    if on and "=" in s: terr.append(s)
print("[Terrain] 总对象:",len(terr))
# 类型统计
from collections import Counter
import re
c=Counter(re.sub(r"\d+$","",v.split("=")[1].rstrip("0123456789")[:6]) for v in terr)
names=Counter(v.split("=")[1] for v in terr)
print("对象名分布:",dict(names))
# 路径点(30,58)(30,59)附近 key=X*1000+Y, X26..34 Y54..63
print("\n附近原始记录:")
for s in terr:
    k,v=s.split("="); kk=int(k); x,y=kk//1000,kk%1000
    if 25<=x<=35 and 53<=y<=64:
        print("   key=%s (%d,%d) = %s"%(k,x,y,v))