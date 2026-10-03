# -*- coding: utf-8 -*-
# 第二处病灶：离线模拟凿/填一格后，背靠背拐角冲突是否解除
# 冲突定义：两个纯对角岸格对角相邻、朝向相反(NW-SE 或 NE-SW)、选中的2x2片重叠
import io, os, glob, copy
base = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput"
f=sorted(glob.glob(os.path.join(base,"2026*_FillStaircaseBends.isopack5.txt")),key=os.path.getmtime)[-1]
T0={}
with io.open(f,"r",encoding="utf-8",errors="replace") as fp:
    for line in fp:
        p=line.split()
        if len(p)<12: continue
        try: x=int(p[0]); y=int(p[1])
        except Exception: continue
        T0[(x,y)]=int(p[2])
WAT=lambda t: 314<=t<=327
DIRS8=[(-1,-1,0x40),(0,-1,0x80),(1,-1,0x01),(-1,0,0x20),(1,0,0x02),(-1,1,0x10),(0,1,0x08),(1,1,0x04)]
def corner_triggers(T, x0,x1,y0,y1):
    """返回 {格:(朝向bit, 覆盖4格集)} 只计纯对角单角的占位陆格"""
    out={}
    for x in range(x0,x1+1):
        for y in range(y0,y1+1):
            if T.get((x,y))!=0: continue
            m=0
            for dx,dy,b in DIRS8:
                q=T.get((x+dx,y+dy))
                if q is not None and WAT(q): m|=b
            if m&0xAA: continue          # 有正交水，直边片，不算
            if m not in (0x01,0x04,0x10,0x40): continue
            out[(x,y)]=(m,{(x,y),(x+1,y),(x,y+1),(x+1,y+1)})
    return out
def conflicts(T):
    tr=corner_triggers(T,104,118,59,72)
    OPP={0x01:0x10,0x10:0x01,0x04:0x40,0x40:0x04}  # NE<->SW, SE<->NW
    bad=[]
    for (x,y),(m,cov) in tr.items():
        for dx,dy in ((1,-1),(-1,1),(1,1),(-1,-1)):
            q=(x+dx,y+dy)
            if q in tr:
                m2,cov2=tr[q]
                if m2==OPP[m] and cov & cov2:
                    pair=tuple(sorted([(x,y),q]))
                    if pair not in bad: bad.append(pair)
    return bad, tr

bad0,tr0=conflicts(T0)
print("原构型背靠背抢片对:", bad0)
for p in bad0:
    for q in p:
        if q in tr0: print("   ",q,hex(tr0[q][0]))

# 候选改动：水314(凿陆->用314)，陆0(填水->0)
cands=[("凿(110,66)->水",(110,66),314),("凿(111,65)->水",(111,65),314),
       ("凿两格(111,65)(110,66)",None,None),
       ("填(109,67)->陆",(109,67),0),("填(112,64)->陆",(112,64),0),
       ("填两水(109,67)(112,64)",None,None)]
for name,cell,val in cands:
    T=dict(T0)
    if cell: T[cell]=val
    else:
        if "凿两格" in name: T[(111,65)]=314; T[(110,66)]=314
        else: T[(109,67)]=0; T[(112,64)]=0
    bad,tr=conflicts(T)
    print("%-24s -> 抢片对 %d: %s" % (name,len(bad),bad))