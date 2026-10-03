# -*- coding: utf-8 -*-
# 模拟"单格对角台阶展平"：
#   A 型陆格：正交4邻全陆、对角恰有水。
#   以 SE 水角 W=(x+1,y+1) 为例，与其正交的 E=(x+1,y)、S=(x,y+1) 皆陆：
#     - 块外 (x+2,y+1) 水 -> 凿 E（右列变2格水，岸线取垂直走向）
#     - 块外 (x+1,y+2) 水 -> 凿 S（下行变2格水，岸线取水平走向）
#     - 两者皆水 -> 按固定优先序凿 S（不引随机）
#     - 两者皆陆 -> 水角为孤立单格水 -> 反向填掉 W（水->陆）
#   四个对角方向对称。批量收集统一改，再扫一遍确认不产生新型、不连锁。
import io, os, sys
base = r"d:\新建文件夹\VSProject\MapGenerator\Mapoutput"
name = sys.argv[1]
water = set()
allc = set()
with io.open(os.path.join(base, name), "r", encoding="utf-8", errors="replace") as fp:
    for line in fp:
        p = line.split()
        if len(p) < 12: continue
        try: x = int(p[0]); y = int(p[1])
        except Exception: continue
        allc.add((x, y))
        if 314 <= int(p[2]) <= 327:
            water.add((x, y))

# 方向表：角位 -> (水角相对A, 两个正交贴边陆格相对A, 块外延续水的探查点->应凿格)
# 返回改动列表 (坐标, '凿'/'填')
def plan(ws):
    chg = []
    used = set()
    for (x, y) in allc:
        if (x, y) in ws:
            continue
        orth = [(0,-1),(1,0),(0,1),(-1,0)]
        if any(((x+dx,y+dy) not in allc) for dx,dy in orth):
            continue
        if any((x+dx,y+dy) in ws for dx,dy in orth):
            continue   # 正交有水，不是 A 型
        # 四个对角： (角名, d角, d边1, d边2, 探1, 凿1, 探2, 凿2)
        cands = [
            ("SE", (1,1),  (1,0),(0,1),  (2,1),(1,0),  (1,2),(0,1)),
            ("SW", (-1,1), (-1,0),(0,1), (-2,1),(-1,0),( -1,2),(0,1)),
            ("NE", (1,-1), (1,0),(0,-1), (2,-1),(1,0),  (1,-2),(0,-1)),
            ("NW", (-1,-1),(-1,0),(0,-1),(-2,-1),(-1,0),( -1,-2),(0,-1)),
        ]
        hits = [c for c in cands if (x+c[1][0], y+c[1][1]) in ws]
        if len(hits) != 1:
            continue   # 只处理恰好一个对角水的单格台阶
        nm, dc, de, ds, q1, ce, q2, cs = hits[0]
        tip = (x+dc[0], y+dc[1])
        e1 = (x+ce[0], y+ce[1]); e2 = (x+cs[0], y+cs[1])
        ext1 = (x+q1[0], y+q1[1]) in ws
        ext2 = (x+q2[0], y+q2[1]) in ws
        if ext1 and ext2:
            target, kind = e2, "凿"
        elif ext2:
            target, kind = e2, "凿"
        elif ext1:
            target, kind = e1, "凿"
        else:
            target, kind = tip, "填"
        if target not in used:
            used.add(target)
            chg.append((target, kind, (x,y), nm))
    return chg

changes = plan(water)
# 应用：凿=加入水，填=移出水
newws = set(water)
for (xy, kind, a, nm) in changes:
    if kind == "凿": newws.add(xy)
    else: newws.discard(xy)

# 改后再扫 A 型
def a_count(ws):
    n = 0; lst=[]
    for (x,y) in allc:
        if (x,y) in ws: continue
        orth=[(0,-1),(1,0),(0,1),(-1,0)]; diag=[(-1,-1),(1,-1),(-1,1),(1,1)]
        if any(((x+dx,y+dy) not in allc) for dx,dy in orth+diag): continue
        if any((x+dx,y+dy) in ws for dx,dy in orth): continue
        if any((x+dx,y+dy) in ws for dx,dy in diag): n+=1; lst.append((x,y))
    return n, lst

before, _ = a_count(water)
after, rem = a_count(newws)
nz = sum(1 for c in changes if c[1]=="凿"); nt = sum(1 for c in changes if c[1]=="填")
print("A 型格: 改前 %d -> 改后 %d (残余 %s)" % (before, after, rem[:20]))
print("总改动 %d 格：凿水 %d，填水 %d" % (len(changes), nz, nt))

# 用户点的 5 格附近
watch = [(49,49),(48,51),(49,51),(49,50),(111,65)]
print()
for (wx,wy) in watch:
    near = [c for c in changes if abs(c[0][0]-wx)<=3 and abs(c[0][1]-wy)<=3]
    print("(%d,%d) 附近改动:" % (wx,wy))
    for xy, kind, a, nm in sorted(near, key=lambda c:(c[0][1],c[0][0])):
        print("   %s %s  (消除 A 格 %s 的 %s 角台阶)" % (kind, xy, a, nm))