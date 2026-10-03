# -*- coding: utf-8 -*-
# 新图两张 lakeStartA 病灶区 + 最终图瓦片
import io, os
base = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput"
def load(fn):
    d={}
    with io.open(os.path.join(base,fn),"r",encoding="utf-8",errors="replace") as fp:
        for line in fp:
            p=line.split()
            if len(p)<12: continue
            try: x=int(p[0]); y=int(p[1])
            except Exception: continue
            d[(x,y)]=(int(p[2]),int(p[8]),int(p[9]),int(p[11]))
    return d
LA1=load("20261002_173625_lakeStartA.isopack5.txt")
LA2=load("20261002_173626_lakeStartA.isopack5.txt")
print("=== 两张新 lakeStartA 关键格 ===")
for q in [(50,51),(51,51),(50,50),(50,52),(52,51),(49,49),(49,50),(49,51),(48,50),(48,51)]:
    a=LA1.get(q); b=LA2.get(q)
    def f(v):
        if v is None: return "缺"
        return ("水" if 314<=v[0]<=327 else ("0" if v[0]==0 else str(v[0])))
    print("   %-9s 173625:%-4s 173626:%-4s" % (q,f(a),f(b)))

# 最终图
import glob
fin=sorted(glob.glob(os.path.join(base,"rmg_*.isopack5.txt")),key=os.path.getmtime)[-1]
print()
print("最终图:", os.path.basename(fin))
F=load(fin)
for q in [(49,49),(49,50),(49,51),(48,50),(48,51),(50,51),(51,51),(111,65),(110,65),(110,66)]:
    v=F.get(q)
    print("   %-9s %s" % (q, ("缺" if v is None else "t=%d L=%d LT=%d P=%d"%v)))