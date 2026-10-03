# -*- coding: utf-8 -*-
import io,sys
sys.path.insert(0,r"d:\新建文件夹\VSProject\MapGenerator\temp")
import analyze_isopack5 as A
p=r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261002_195435.map"
cells=A.load_map(p)[0]
raw=open(p,"rb").read().decode("latin-1")
terr=[];on=False
for ln in raw.splitlines():
    s=ln.strip()
    if s.startswith("["): on=(s=="[Terrain]");continue
    if on and "=" in s: terr.append(s)
trees=[]
for s in terr:
    k,v=s.split("=")
    if v[:4]=="TREE" and v[4].isdigit():
        kk=int(k);trees.append((kk//1000,kk%1000,v))
for wx,wy,tag in ((30,59,"WP2"),(30,58,"WP3")):
    near=sorted(((max(abs(tx-wx),abs(ty-wy)),abs(tx-wx)+abs(ty-wy),tx,ty,nm) for tx,ty,nm in trees))[:8]
    print("=== 离%s(%d,%d)最近的树 ==="%(tag,wx,wy))
    for ch,md,tx,ty,nm in near:
        c=cells.get((tx,ty)); t=c["tile"] if c else -1
        if 314<=t<=327: kind="水"
        elif 49<=t<=88: kind="崖"
        elif 89<=t<=130: kind="岸"
        elif 29<=t<=48 or 384<=t<=393: kind="坡"
        elif 131<=t<=147 or 493<=t<=509: kind="绿LAT"
        else: kind="t%d"%t
        print("   (%d,%d) %s 切比雪夫距离%d 逻辑格[%s tile=%d]"%(tx,ty,nm,ch,kind,t))