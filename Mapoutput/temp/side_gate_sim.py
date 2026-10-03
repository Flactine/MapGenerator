# -*- coding: utf-8 -*-
# 离线验证侧向等高门控：对比 PlaceCliffs(刻前) 与 CarveRamps7(刻后)
import io, os
base=r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput"
def load(stem):
    d={}
    with io.open(os.path.join(base,stem+".isopack5.txt"),"r",encoding="utf-8",errors="replace") as fp:
        for line in fp:
            p=line.split()
            if len(p)<12: continue
            try: x=int(p[0]);y=int(p[1])
            except: continue
            d[(x,y)]=dict(t=int(p[2]),L=int(p[8]),sl=int(p[10]))
    return d
old=load("20261002_212051_PlaceCliffs")
new=load("20261002_212051_CarveRegionRamps7")
# rampBase 起点：快照里 r00..r19 是 29..48
RAMP0=29
SIDE={1:(-1,-1),5:(-1,-1), 2:(1,1),7:(1,1), 3:(-1,1),10:(-1,1), 4:(1,-1),8:(1,-1)}
# 新坡格 = 刻前非坡(sl0或非ramp瓦)、刻后是 rampBase 29..48
hits=[]
nnew=0
for (x,y),nc in new.items():
    t=nc["t"]
    if not (RAMP0<=t<=RAMP0+19): continue
    oc=old.get((x,y))
    if oc and RAMP0<=oc["t"]<=RAMP0+19: continue   # 原本就是坡
    nnew+=1
    slope=t-RAMP0+1
    if slope not in SIDE: continue
    dx,dy=SIDE[slope]
    for step in (1,2):
        qx,qy=x+dx*step,y+dy*step
        oq=old.get((qx,qy)); nq=new.get((qx,qy))
        if not oq or not nq: continue
        # 刻前是纯高地顶面(slope0, 等高)，刻后仍是未被动过的纯高地顶面
        if (oq["sl"]==0 and nq["sl"]==0 and oq["L"]==nq["L"]
            and nq["L"]==nc["L"]+1):   # 坡顶层 L=owner-1，旁边 L=owner
            hits.append((x,y,slope,step,(qx,qy),nq["L"]))
print("新刻坡格总数:",nnew)
print("侧向命中(应取消)条数:",len(set((h[0],h[1]) for h in hits)))
for h in hits:
    print("  坡格(%d,%d) R%d 侧向%d格 -> 等高高地(%d,%d) L%d"%(
        h[0],h[1],h[2],h[3],h[4][0],h[4][1],h[5]))