# -*- coding: utf-8 -*-
import base64, sys
sys.path.insert(0,r"d:\新建文件夹\VSProject\MapGenerator\temp")
import analyze_isopack5 as A
p=r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261002_205302.map"
def decode(name):
    b64=A._section(p,name)
    raw=base64.b64decode(b64+"="*(-len(b64)%4))
    data=bytearray();pos=0;nsec=0
    while pos+4<=len(raw):
        si=raw[pos]|(raw[pos+1]<<8); so=raw[pos+2]|(raw[pos+3]<<8)
        if si==0: break
        data+=A.lzo1x_decompress(bytes(raw[pos+4:pos+4+si]),so)
        pos+=4+si;nsec+=1
    return bytes(data),nsec
ov,ns=decode("OverlayPack")
print("OverlayPack 段数",ns,"解压长度",len(ov))
def g(x,y):
    i=x+512*y; return ov[i] if i<len(ov) else None
for q in [(109,111),(110,111),(108,111),(109,110),(109,112),(110,112),(111,111)]:
    print(q,"overlay=",g(*q))
sx,sy=110,112
bad=[(x,y,g(x,y)) for y in range(sy-4,sy+6) for x in range(sx-4,sx+6)
     if g(x,y) not in (None,0xFF)]
print("出生点0 10x10 内 overlay 非空:",len(bad),bad[:40])