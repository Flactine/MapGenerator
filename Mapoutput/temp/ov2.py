# -*- coding: utf-8 -*-
import base64, re, struct, sys
sys.path.insert(0,r"d:\新建文件夹\VSProject\MapGenerator\temp")
import analyze_isopack5 as A
p=r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261002_205302.map"
raw=open(p,"rb").read()
def section_b64(name):
    m=re.search(("\\[%s\\]"%name).encode(),raw)
    s=m.end()
    # 读到下一个 [Section]
    e=raw.find(b"[",s)
    body=b"".join(raw[s:e].split())
    return base64.b64decode(body)
def decode(name):
    blob=section_b64(name); data=b"";pos=0
    while pos+4<=len(blob):
        si,so=struct.unpack("<HH",blob[pos:pos+4])
        data+=A.lzo1x_decompress(bytes(blob[pos+4:pos+4+si]),so)
        pos+=4+si
    return data
ov=decode("OverlayPack")
print("OverlayPack 长度",len(ov))
def g(x,y):
    i=x+512*y
    return ov[i] if i<len(ov) else None
for q in [(109,111),(110,111),(108,111),(109,110),(109,112),(110,112)]:
    print(q,"overlay=",g(*q))
sx,sy=110,112
bad=[]
for y in range(sy-4,sy+6):
    for x in range(sx-4,sx+6):
        v=g(x,y)
        if v is not None and v!=0xFF: bad.append((x,y,v))
print("出生点0 10x10 内 overlay 非空:",len(bad),bad[:30])