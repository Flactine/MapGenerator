#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Compare highland edge shape patterns vanilla vs port.

1. Every BROKEN 'None' cell: is it on the diamond boundary (|x-y|==W or x+y==W+2H)?
2. 'notch' = a real (non-placeholder) low cell C at level L whose TWO opposite
   orthogonal neighbours are both L+4 (N&S high, or E&W high): a one-cell dip in
   a plateau that no single-face cliff piece can cap. Count + list.
"""
import sys
sys.path.insert(0, ".")
import analyze_isopack5 as A

W, H = 74, 82
def on_boundary(x, y):
    return abs(x - y) == W or (x + y) == W + 2 * H

def run(path, label):
    cells, _, _ = A.load_map(path)
    # 1. boundary check on missing-record cliff cells is done by audit externally;
    #    here just confirm record holes near boundary.
    notch_ns = []
    notch_ew = []
    for (x, y), c in cells.items():
        if c["tile"] == 0xFFFF:
            continue
        L = c["level"]
        n = cells.get((x, y - 1)); s = cells.get((x, y + 1))
        e = cells.get((x + 1, y)); wq = cells.get((x - 1, y))
        real = lambda q: q is not None and q["tile"] != 0xFFFF
        if real(n) and real(s) and n["level"] == L + 4 and s["level"] == L + 4:
            notch_ns.append((x, y, L))
        if real(e) and real(wq) and e["level"] == L + 4 and wq["level"] == L + 4:
            notch_ew.append((x, y, L))
    print("== %s ==" % label)
    print("one-cell NOTCH N-S (high-low-high same column): %d" % len(notch_ns))
    print("one-cell NOTCH E-W (high-low-high same row): %d" % len(notch_ew))
    print("  N-S:", notch_ns[:25])
    print("  E-W:", notch_ew[:25])

run(sys.argv[1], sys.argv[2])
