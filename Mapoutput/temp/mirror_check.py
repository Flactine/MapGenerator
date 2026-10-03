# -*- coding: utf-8 -*-
# 实证雷达 PNG 是否左右镜像：
# 读 PNG 找红色出生点像素簇中心，与 FA2 公式预测的 (px,py) 比较；
# 再计算"镜像预测"(pwidth-1-px')，看哪个吻合。
import struct, zlib

png = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\radar_preview.png"
data = open(png, "rb").read()
assert data[:8] == b"\x89PNG\r\n\x1a\n"
pos = 8
width = height = bitdepth = colortype = interlace = 0
idat = b""
while pos < len(data):
    ln = struct.unpack(">I", data[pos:pos+4])[0]
    typ = data[pos+4:pos+8]
    body = data[pos+8:pos+8+ln]
    if typ == b"IHDR":
        width, height, bitdepth, colortype = struct.unpack(">IIBB", body[:10])
        interlace = body[12]
    elif typ == b"IDAT":
        idat += body
    pos += 12 + ln
print("PNG", width, height, "depth", bitdepth, "colorType", colortype, "interlace", interlace)
raw = zlib.decompress(idat)
ch = {0:1,2:3,3:1,4:2,6:4}[colortype]
bpp = ch
stride = width*bpp
# unfilter
out = bytearray()
prev = bytearray(stride)
i = 0
for y in range(height):
    ft = raw[i]; i += 1
    line = bytearray(raw[i:i+stride]); i += stride
    if ft == 1:
        for x in range(bpp, stride):
            line[x] = (line[x] + line[x-bpp]) & 255
    elif ft == 2:
        for x in range(stride):
            line[x] = (line[x] + prev[x]) & 255
    elif ft == 3:
        for x in range(stride):
            a = line[x-bpp] if x >= bpp else 0
            line[x] = (line[x] + ((a + prev[x]) >> 1)) & 255
    elif ft == 4:
            for x in range(stride):
                a = line[x-bpp] if x >= bpp else 0
                b = prev[x]
                c = prev[x-bpp] if x >= bpp else 0
                pp = a + b - c
                pa, pb, pc = abs(pp-a), abs(pp-b), abs(pp-c)
                pr = a if (pa <= pb and pa <= pc) else (b if pb <= pc else c)
                line[x] = (line[x] + pr) & 255
    out += line
    prev = line

def px(x, y):
    o = y*stride + x*bpp
    if colortype == 6:
        return out[o], out[o+1], out[o+2]      # R,G,B
    if colortype == 2:
        return out[o], out[o+1], out[o+2]
    return (out[o],)*3

# 红像素
reds = [(x,y) for y in range(height) for x in range(width)
        if px(x,y)[0] > 180 and px(x,y)[1] < 80 and px(x,y)[2] < 80]
print("red pixels:", len(reds))
# 聚类（简单：按坐标连通）
seen = set()
clusters = []
for r in reds:
    if r in seen: continue
    stk=[r]; seen.add(r); comp=[]
    while stk:
        cx,cy=stk.pop(); comp.append((cx,cy))
        for dx in(-1,0,1):
            for dy in(-1,0,1):
                n=(cx+dx,cy+dy)
                if n in reds and n not in seen:
                    seen.add(n); stk.append(n)
    clusters.append(comp)
clusters.sort(key=len, reverse=True)
centers = [(sum(c[0] for c in cl)/len(cl), sum(c[1] for c in cl)/len(cl), len(cl))
           for cl in clusters[:8]]
print("red cluster centers (x,y,n):")
for c in centers: print("  %.1f %.1f n=%d" % c)

# 预测
W, H = 124, 132
pts = [(243,133),(18,129),(132,21),(129,215),(146,118),(75,75),(85,157),(191,181)]
print("FA2 predicted (px,py) and mirrored-x prediction:")
pred = []
for X,Y in pts:
    pxx = W + Y - X
    pyy = (X + Y)//2 - W//2
    pred.append((pxx,pyy))
    print("  (%d,%d) -> (%d,%d)   mirror=(%d,%d)" % (X,Y,pxx,pyy, 2*W-1-pxx, pyy))
