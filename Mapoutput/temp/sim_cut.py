#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""在铺岸水形(SelectShoreTile 快照，水瓦即铺岸面对的水)上，
对两处病灶逐格试凿(->水314)/填(->陆0)，复查两种判据在局部是否归零。"""
import io, os, glob
base=r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput"
f=sorted(glob.glob(os.path.join(base,"2026*_SelectShoreTile.isopack5.txt")),key=os.path.getmtime)[-1]
T={}
with io.open(f,"r",encoding="utf-8",errors="replace") as fp:
    for line in fp:
        p=line.split()
        if len(p)<12: continue
        try: x=int(p[0]);y=int(p[1])
        except: continue
        T[(x,y)]=int(p[2])
def iswater(t): return 314<=t<=327
def W(T,q):
    t=T.get(q); return False if t is None else iswater(t)

def type1(T,x0,x1,y0,y1):
    h=[]
    for x in range(x0,x1+1):
        for y in range(y0,y1+1):
            if W(T,(x,y)): continue
            if any(W(T,q) for q in ((x,y-1),(x+1,y),(x,y+1),(x-1,y))): continue
            cs={"NW":W(T,(x-1,y-1)),"NE":W(T,(x+1,y-1)),"SW":W(T,(x-1,y+1)),"SE":W(T,(x+1,y+1))}
            nm=[k for k,v in cs.items() if v]
            if len(nm)!=1: continue
            n=nm[0]
            ok=((n=="NW" and W(T,(x+2,y)) and W(T,(x+2,y+1))) or
                (n=="NE" and W(T,(x,y+2)) and W(T,(x+1,y+2))) or
                (n=="SW" and W(T,(x+2,y)) and W(T,(x+2,y+1))) or
                (n=="SE" and W(T,(x,y-2)) and W(T,(x+1,y-2))))
            if ok: h.append(((x,y),n))
    return h
def pinch(T,x0,x1,y0,y1):
    pr=set()
    for x in range(x0,x1+1):
        for y in range(y0,y1+1):
            if W(T,(x,y)): continue
            for bx,by,da,db in ((x+1,y-1,(x-1,y+1),(x+2,y-2)),
                               (x+1,y+1,(x-1,y-1),(x+2,y+2))):
                if not (x0<=bx<=x1 and y0<=by<=y1): continue
                if W(T,(bx,by)): continue
                if any(W(T,q) for q in ((x,y-1),(x+1,y),(x,y+1),(x-1,y))): continue
                if any(W(T,q) for q in ((bx,by-1),(bx+1,by),(bx,by+1),(bx-1,by))): continue
                if not(W(T,da) and W(T,db)): continue
                ad=[(x-1,y-1),(x+1,y-1),(x-1,y+1),(x+1,y+1)]
                bd=[(bx-1,by-1),(bx+1,by-1),(bx-1,by+1),(bx+1,by+1)]
                if sum(W(T,q) for q in ad)==1 and sum(W(T,q) for q in bd)==1:
                    pr.add(tuple(sorted([(x,y),(bx,by)])))
    return pr

def score(T):
    return (len(type1(T,44,54,45,55))+len(pinch(T,44,54,45,55)),
            len(type1(T,105,116,60,70))+len(pinch(T,105,116,60,70)))
print("文件:",os.path.basename(f)," 基线(第一处,第二处)冲突:",score(T))
def trial(tag,cell,val):
    t=dict(T); t[cell]=val
    print("  %-22s -> %s" % (tag,score(t)))
print("-- 第一处 (48,50) 候选 --")
for c in [(48,50),(49,50),(49,51),(48,51),(47,49),(50,50),(50,51)]:
    trial("凿%s->水"%str(c),c,314)
for c in [(47,49),(50,50),(50,51),(50,52)]:
    trial("填%s->陆"%str(c),c,0)
print("-- 第二处 (110,66)/(111,65) 候选 --")
for c in [(110,66),(111,65),(110,67),(112,65),(109,67),(112,64)]:
    trial("凿%s->水"%str(c),c,314)
for c in [(109,67),(112,64)]:
    trial("填%s->陆"%str(c),c,0)