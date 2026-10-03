# -*- coding: utf-8 -*-
# 关键验证：[Structures] field3/field4 两种坐标解释，哪个位置是平地？
# 若 field4/field3 解释下地基在坡上，而 field3/field4 解释下平整，
# 则工程写盘 X/Y 反了，FA2/游戏把建筑放到了镜像的坡位。
path = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput\rmg_20261003_143645.isopack5.txt"
cells = {}
for line in open(path, encoding="utf-8", errors="replace"):
    if line.startswith(";"): continue
    p = line.split()
    if len(p) < 12: continue
    cells[(int(p[0]), int(p[1]))] = {
        "tile": int(p[2]), "L": int(p[8]), "slope": int(p[10]), "pass": int(p[11]) }

# (name, field3, field4, w, h)
blds = [("CAOUTP",110,66,4,3),("CAMACH",48,60,3,3),("CAAIRP",98,49,3,3),("CAOILD",50,86,2,2)]

def survey(x0,y0,w,h,tag):
    bad=[]; levels=set()
    for y in range(y0,y0+h):
        for x in range(x0,x0+w):
            c=cells.get((x,y))
            if c is None: bad.append((x,y,"MISS")); continue
            levels.add(c["L"])
            if c["slope"]!=0 or c["tile"] not in (0,0xFFFF):
                bad.append((x,y,c["tile"],c["L"],c["slope"],c["pass"]))
    print("  %-22s anchor=(%d,%d) levels=%s bad=%d %s" % (tag,x0,y0,sorted(levels),len(bad),bad[:6]))

for n,f3,f4,w,h in blds:
    print(n)
    survey(f4,f3,w,h,"A: X=field4,Y=field3")
    survey(f3,f4,w,h,"B: X=field3,Y=field4")
