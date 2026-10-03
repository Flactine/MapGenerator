# -*- coding: utf-8 -*-
# 按 1-based 行号区间删除（含两端），带内容校验，字节级回写不动编码
import sys
p = sys.argv[1]
a = int(sys.argv[2])
b = int(sys.argv[3])
data = open(p, "rb").read()
lines = data.split(b"\n")
print("首行:", lines[a - 1][:70])
print("末行:", repr(lines[b - 1]), "下一行:", lines[b][:70] if b < len(lines) else "<EOF>")
assert lines[a - 1].startswith(b"// ---"), "起始行不是注释分隔线"
assert lines[b - 1].strip() == b"", "结束行不是空行"
del lines[a - 1:b]
open(p, "wb").write(b"\n".join(lines))
print("已删除", b - a + 1, "行")