# -*- coding: utf-8 -*-
import io, glob, os
p=sorted(glob.glob(r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_*.map"),key=os.path.getmtime)[-1]
import sys; sys.path.insert(0,r"d:\新建文件夹\VSProject\MapGenerator\temp")
import analyze_isopack5 as A
cells=A.load_map(p)[0]
raw=open(p,"rb").read().decode("latin-1")
def sec(n):
    o=[];on=False
    for ln in raw.splitlines():
        s=ln.strip()
        if s.startswith("["): on=(s==n);continue
        if on and "=" in s:o.append(s)
    return o
for ln in sec("[Terrain]"):
    k,_,v=ln.partition("=")
    if len(v)>=5 and v[:4]=="TREE" and v[4].isdigit():
        kk=int(k);x,y=kk//1000,kk%1000
        c=cells.get((x,y))
        if c and not (c["tile"] in (0,0xFFFF) or 29<=c["tile"]<=48 or 510<=c["tile"]<=521
                     or 384<=c["tile"]<=393 or 493<=c["tile"]<=509):
            # 非绿/非坡/非LAT 的都列出
            print("(%d,%d) %s tile=%d Level=%d slope=%d pass=%s"
                  %(x,y,v,c["tile"],c["level"],c["slope"],
                    c.get("pass","?")))