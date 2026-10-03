# -*- coding: utf-8 -*-
# 全图 diff：sqrt 修复前后 lakeStartA 水格集合
import io, os
base = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput"
def water(fn):
    s=set()
    with io.open(os.path.join(base,fn),"r",encoding="utf-8",errors="replace") as fp:
        for line in fp:
            p=line.split()
            if len(p)<12: continue
            try: x=int(p[0]); y=int(p[1])
            except Exception: continue
            if 314<=int(p[2])<=327: s.add((x,y))
    return s
old=water("20261002_165759_lakeStartA.isopack5.txt")
new=water("20261002_173626_lakeStartA.isopack5.txt")
new2=water("20261002_173625_lakeStartA.isopack5.txt")
print("旧湖水格 %d, 新(173626) %d, 另一张(173625) %d" % (len(old),len(new),len(new2)))
print("173626 vs 旧: 新增 %d, 消失 %d" % (len(new-old), len(old-new)))
print("173625 vs 旧: 新增 %d, 消失 %d" % (len(new2-old), len(old-new2)))