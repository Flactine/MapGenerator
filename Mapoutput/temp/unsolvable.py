# -*- coding: utf-8 -*-
# 铺前快照客观判定：纯对角拐角片 2x2 覆盖的格中，若有格自己正交邻深水，
# 而该片绿边不朝该方向 -> 这片"盖得住格子、盖不住水边"=构型无解
import io, os, glob, sys
base = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput"
f = sys.argv[1] if len(sys.argv)>1 else \
    sorted(glob.glob(os.path.join(base,"2026*_FillStaircaseBends.isopack5.txt")),key=os.path.getmtime)[-1]
T={}
with io.open(f,"r",encoding="utf-8",errors="replace") as fp:
    for line in fp:
        p=line.split()
        if len(p)<12: continue
        try: x=int(p[0]); y=int(p[1])
        except Exception: continue
        T[(x,y)]=int(p[2])
def w(q):
    t=T.get(q); return None if t is None else (314<=t<=327)
def land0(q):   # mode0 认的占位陆
    return T.get(q)==0

# 8 邻掩码（仅对 tile==0 占位格，等同 mode0 水接触）
DIRS=[("NW",-1,-1,0x40),("N",0,-1,0x80),("NE",1,-1,0x01),("W",-1,0,0x20),
      ("E",1,0,0x02),("SW",-1,1,0x10),("S",0,1,0x08),("SE",1,1,0x04)]
def orth_water_dirs(x,y):
    return [dn for dn,dx,dy in (("N",0,-1),("E",1,0),("S",0,1),("W",-1,0))
            if w((x+dx,y+dy)) is True]

# 四个纯对角 -> (n12候选, 2x2相对触发格的覆盖格, 该片绿边朝向)
# off=(0,0)，片朝 +X/+Y 展开；拐角片绿边朝向 = 对角水方向
CORNER={0x01:("NE",35),0x04:("SE",33),0x10:("SW",39),0x40:("NW",37)}
hits=[]
for (x,y),t in T.items():
    if t!=0: continue
    mask=0
    for dn,dx,dy,b in DIRS:
        if w((x+dx,y+dy)) is True: mask|=b
    orth=mask&0xAA  # N S W E = 0x80,0x08,0x20,0x02
    diag=mask&0x55  # 四角
    if orth or not diag: continue
    if diag not in CORNER: continue   # 多角不取
    face,n12=CORNER[diag]
    # 2x2 覆盖（off0,0）
    cover=[(x,y),(x+1,y),(x,y+1),(x+1,y+1)]
    if not all(land0(q) or w(q) is False for q in cover):
        pass
    bad=[]
    for gx,gy in cover:
        ow=orth_water_dirs(gx,gy)
        # 该片绿边只在 face 方向；若该格正交水方向 != face 侧，则盖不住
        for d in ow:
            bad.append((gx,gy,d))
    if bad:
        hits.append((x,y,face,n12,cover,bad))

print("快照:", os.path.basename(f))
print("无解拐角触发 %d 处:" % len(hits))
for x,y,face,n12,cover,bad in sorted(hits,key=lambda h:(h[1],h[0])):
    print("  触发(%d,%d) 朝%s n12=%d/%d 覆盖%s" % (x,y,face,n12,n12+1,cover))
    for gx,gy,d in bad:
        print("      被盖格(%d,%d) 自己%s侧邻深水 <== 片绿边不朝这" % (gx,gy,d))