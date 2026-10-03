# -*- coding: utf-8 -*-
# 查 rmg_20261002_195435 路径点2/3 坐标，及附近树和格瓦片
import io, os, sys
sys.path.insert(0, r"d:\新建文件夹\VSProject\MapGenerator\temp")
import analyze_isopack5 as A
p=r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261002_195435.map"
cells=A.load_map(p)[0]
raw=open(p,"rb").read().decode("latin-1")
def sec(n):
    o=[];on=False
    for ln in raw.splitlines():
        s=ln.strip()
        if s.startswith("["): on=(s==n);continue
        if on and "=" in s:o.append(s)
    return o
print("=== 所有 Waypoints ===")
wp={}
for ln in sec("[Waypoints]"):
    k,_,v=ln.partition("="); wp[int(k)]=int(v)
    vv=int(v); print("  %s -> (%d,%d)"%(k,vv%1000,vv//1000))

# Terrain 树（key=X*1000+Y）
trees=[]
for ln in sec("[Terrain]"):
    k,_,v=ln.partition("=")
    if len(v)>=5 and v[:4]=="TREE" and v[4].isdigit():
        kk=int(k); trees.append((kk//1000,kk%1000,v))
print("树总数",len(trees))

for wpn in (2,3):
    if wpn not in wp: continue
    vv=wp[wpn]; wx,wy=vv%1000,vv//1000
    print("\n=== 路径点%d = (%d,%d) 周围 8 格 ==="%(wpn,wx,wy))
    for dy in range(-4,5):
        row=[]
        for dx in range(-4,5):
            x,y=wx+dx,wy+dy
            c=cells.get((x,y))
            if c is None: row.append("  ## ");continue
            t=c["tile"]
            if t==0 or t==0xFFFF: s=" .. "
            elif 314<=t<=327: s=" ~%02d"%(t-314)
            elif 49<=t<=88: s=" C%02d"%(t-49)
            elif 89<=t<=130: s=" o%02d"%(t-89)
            elif 29<=t<=48: s=" r%02d"%(t-29)
            elif 131<=t<=147: s=" g%02d"%(t-131)
            elif 384<=t<=393: s=" R%02d"%(t-384)
            else: s="%4d"%t
            # 标记该格有没有树
            has=any(tx==x and ty==y for tx,ty,_ in trees)
            row.append(("T"+s[1:] if has else s))
        print("  y%-3d %s"%(wy+dy," ".join(row)))
    print("        "+" ".join("x%-3d"%(wx+dx) for dx in range(-4,5)))
    # 列出该点附近所有树及瓦
    print("  附近树(切比雪夫<=5):")
    for tx,ty,nm in sorted(trees,key=lambda q:(q[1],q[0])):
        if max(abs(tx-wx),abs(ty-wy))<=5:
            c=cells.get((tx,ty))
            t=c["tile"] if c else -1
            kind="水" if 314<=t<=327 else ("悬崖" if 49<=t<=88 else
                 ("水崖" if 148<=t<=175 else ("坡" if (29<=t<=48 or 384<=t<=393 or 510<=t<=521) else "其它")))
            print("    (%d,%d) %s tile=%d [%s]"%(tx,ty,nm,t,kind))