# -*- coding: utf-8 -*-
files = [
    r"d:\新建文件夹\VSProject\MapGenerator\MapGenerator\MapGenMaking.cpp",
    r"d:\新建文件夹\VSProject\MapGenerator\MapGenerator\MapGenMakingSub.cpp",
    r"d:\新建文件夹\VSProject\MapGenerator\MapGenerator\MapGen.cpp",
]
tag = "// [SNAPSHOT-OFF] "
for p in files:
    raw = open(p, "rb").read()
    bom = raw[:3] == b"\xef\xbb\xbf"
    text = raw.decode("utf-8-sig")
    n = text.count(tag)
    text = text.replace(tag, "")
    out = text.encode("utf-8")
    if bom:
        out = b"\xef\xbb\xbf" + out
    open(p, "wb").write(out)
    print("%-22s 恢复 %d 行" % (p.split("\\")[-1], n))