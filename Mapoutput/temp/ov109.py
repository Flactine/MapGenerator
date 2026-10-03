# -*- coding: utf-8 -*-
# 解 OverlayPack(format80,32段x8192) 查 (109,111) 及出生区 overlay
import re
p=r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261002_205302.map"
raw=open(p,"rb").read()
# 文件是文本(含二进制pack段但整体latin1)，抓 [OverlayPack] 到下一段
m=re.search(rb"\[OverlayPack\]\r?\n",raw)
start=m.end()
end=raw.find(b"[",start)
packtext=raw[start:end].strip().replace(b"\r",b"").replace(b"\n",b"")
pack=bytes.fromhex(packtext.decode("ascii"))

def dec80(data):
    out=bytearray();i=0
    while i<len(data):
        c=data[i];i+=1
        if c==0: continue
        if c<0x80:
            n=(c&0x3f)+1
            if c&0x40:
                out.extend(data[i:i+n]);i+=n
            else:
                out.extend([data[i]]*n);i+=1
        elif c<0xC0:
            # copy/run 复合
            n=(c&0x3f)+1
            out.extend([data[i]]*n);i+=1
        else:
            n=(c&0x3f)+1
            if c&0x40:
                out.extend(data[i:i+n]);i+=n
            else:
                out.extend([data[i]]*n);i+=1
    return bytes(out)
ov=dec80(pack)
print("解压长度",len(ov))
def ovget(x,y):
    idx=x+512*y
    return ov[idx] if idx<len(ov) else None
for q in [(109,111),(110,111),(109,112),(108,111),(110,112)]:
    print(q,"overlay index =",ovget(*q))
# 出生点0 10x10 内非 FF overlay
sx,sy=110,112
print("\n出生点0 外扩4(10x10 x%d..%d y%d..%d) 内非0xFF overlay:"%(sx-4,sx+5,sy-4,sy+5))
cnt=0
for y in range(sy-4,sy+6):
    for x in range(sx-4,sx+6):
        v=ovget(x,y)
        if v not in (None,0xFF):
            print("   (%d,%d)=%d"%(x,y,v));cnt+=1
print("共",cnt)