# -*- coding: utf-8 -*-
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
            d[(x,y)]=(int(p[2]),int(p[8]),int(p[10]))
    return d
# 1) 全局 6->7 差异数
a=load("20261002_212051_CarveRegionRamps6")
b=load("20261002_212051_CarveRegionRamps7")
diff=[q for q in set(a)|set(b) if a.get(q)!=b.get(q)]
print("全局 6->7 差异格数:",len(diff))
xs=[q for q in diff if 80<=q[0]<=100 and 105<=q[1]<=125]
print("其中病灶区(80..100,105..125):",len(xs),sorted(xs))
# 2) 追溯 (95,114) r01 坡 何时出现：从 PlaceCliffs 往前比
import glob
stages=["20261002_212051_CarveRegionRamps5","20261002_212051_CarveRegionRamps6","20261002_212051_CarveRegionRamps7","20261002_212051_PlaceCliffs"]
prev=None
for st in ["20261002_212051_PlaceCliffs"]:
    pass
# 顺序应为 5,6,7,PlaceCliffs；逐个查 (95,114) 和 (92,116)
order=["20261002_212051_CarveRegionRamps5","20261002_212051_CarveRegionRamps6","20261002_212051_CarveRegionRamps7"]
for q in [(95,114),(92,116),(90,116),(91,116),(89,116)]:
    print(q, {st.split("Ramps")[1]: load(st).get(q) for st in order})