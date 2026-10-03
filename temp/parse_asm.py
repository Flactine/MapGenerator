#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import json, re, sys

raw = open(sys.argv[1], encoding="utf-8").read()
raw = raw.replace("\\u003e", ">").replace("\\u003c", "<")
outer = json.loads(raw) if raw.lstrip().startswith("[") else json.loads(
    raw[raw.index("["):raw.rindex("]") + 1])
text = outer[0]["text"] if isinstance(outer, list) else outer["text"]
inner = json.loads(text)
for ln in inner["asm"]["lines"]:
    print("%s  %s" % (ln["addr"], ln["instruction"]))
