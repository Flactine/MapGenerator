# SmoothWaterBody（sub_57A0C0）反编译文件集合

本目录存放 `RandomMapGenerator::SmoothWaterBody` 所对应原函数 `sub_57A0C0`
及其全部下级函数的原始反编译（Hex-Rays 伪代码，保留 `/*0xNNNN*/` 地址标注）。

生成时间：2026-09-27
二进制：RA2/YR（gamemd.exe 基址 0x400000）
所有文件均为**原始反编译输出**，未做语义重写；仅文件头补充说明。

---

## 1. 调用树

```
sub_57A0C0  SmoothWaterBody                     四遍全图平滑，返回末遍结果
├─ sub_4A8BF0  鼠标/建筑预览清理（DisplayClass）         [仅一次，入口]
├─ sub_58BDC0  WorkCell 构造（80 字节清零，data[16]=-1，byte74=1）
├─ sub_58C2C0  WorkCell 线性访问器：base + 80*i
├─ MapClass::CellIteratorNext / sub_578350   菱形格子迭代器
│
├─ [遍1] sub_57A430  递归洪泛填充（水体裁剪）
│   ├─ sub_58C2A0   WorkCell 二维访问器：base + 80*x + 80*W'*y
│   ├─ sub_57B210   瓦片邻接掩码（核心判定）
│   │   ├─ sub_485060   该格是否为水瓦片（[nIdx, nIdx+14)）
│   │   ├─ sub_486380   该格是否为占位瓦片（0 或 0xFFFF）
│   │   └─ sub_58C2A0
│   ├─ sub_5A00C0   读 WorkCell data[14]（该格生成代号）
│   ├─ sub_5A0090   写 WorkCell data[14]
│   └─ CellClass::GetNeighbourCell  取 8 邻格（用 Neighbours 表）
│       └─ MapClass::GetCellAt_MapCrd
│
├─ [遍2] sub_57A320  瓦片清理（占位瓦片回收）
│   ├─ sub_57B210
│   ├─ sub_58C2A0
│   └─ CellClass::GetNeighbourCell
│
├─ [遍3] sub_57ACF0(x, 1, ...)  水岸瓦片选择（第一遍）
└─ [遍4] sub_57ACF0(x, 2, ...)  水岸瓦片选择（第二遍）
    ├─ sub_598030   RandomFloatRange(0,5)  → 随机外观序号
    ├─ sub_57B210
    ├─ CellClass::GetNeighbourCell
    ├─ sub_485060
    ├─ sub_4A91B0   DisplayClass 坐标换算（把目标格换算为屏幕格）
    └─ sub_57B440   实际落瓦片（sub_57B440 → sub_5A00C0 / sub_5A0090 /
                    sub_486380 / sub_4865B0 / sub_578D80 / sub_4863D0）

Neighbours 表初始化：sub_49F2F0（见 49F2F0_Neighbours.c）
```

---

## 2. 文件清单

| 文件 | 地址 | 符号 | 作用 |
|---|---|---|---|
| `57A0C0.c` | 0x57A0C0 | SmoothWaterBody | 主函数：分配工作数组 + 四遍扫描 |
| `57A430.c` | 0x57A430 | FloodFill | 遍1：递归洪泛，裁剪水体边界 |
| `57A320.c` | 0x57A320 | CleanupTile | 遍2：回收占位瓦片 |
| `57ACF0.c` | 0x57ACF0 | SelectShoreTile | 遍3/4：按邻接形态选水岸瓦片 |
| `57B210.c` | 0x57B210 | TileNeighbourMask | 由瓦片形态算出 8 向连通掩码 |
| `57B440.c` | 0x57B440 | PlaceShoreTile | 把选中瓦片真正铺到格子上 |
| `49F2F0_Neighbours.c` | 0x49F2F0 | Neighbours init | 8 邻方向表初值 |
| `helpers.c` | 多个 | 见文件头 | 其余小工具函数 |
| `578290_CellIteratorNext.c` | 0x578290 | CellIteratorNext | 菱形迭代器推进 |
| `578350_CellIteratorReset.c` | 0x578350 | CellIterator Reset | 菱形迭代器复位 |

---

## 3. 关键全局变量

| 地址 | 名称 | 含义 |
|---|---|---|
| 0xABED10 | dword_ABED10 | 工作数组基址（80 字节/格，惰性分配） |
| 0x89C2DC | dword_89C2DC | 工作数组边长 `workSide = W' + H' + 1` |
| 0xABED04 | IsoTileTypeIndex_0 | 菱形下界 `W'`（MapRect.Width） |
| 0xABED08 | IsoTileTypeIndex_1 | 菱形上界 `W' + 2H'` |
| 0xAA0738 | nIdx | 水瓦片基号（WaterSet 首瓦片） |
| 0x89F688 | Neighbours | 8 邻方向表（见下） |
| 0xABAD28 | dword_ABAD28 | 水岸修正瓦片基号（IsometricTileTypeClass::Array 起点） |
| 0xABDB64 / 0xABDB66 | word_ABDB64 / word_ABDB66 | 41 项水岸瓦片的 X / Y 偏移表 |

### Neighbours[8] 实际值（由 sub_49F2F0 写入）

| i | 原始 dword | (X, Y) |
|---|---|---|
| 0 | 0xFFFF0000 | (0, -1) |
| 1 | 0xFFFF0001 | (1, -1) |
| 2 | 0x00000001 | (1, 0) |
| 3 | 0x00010001 | (1, 1) |
| 4 | 0x00010000 | (0, 1) |
| 5 | 0x0001FFFF | (-1, 1) |
| 6 | 0x0000FFFF | (-1, 0) |
| 7 | 0xFFFFFFFF | (-1, -1) |

---

## 4. 工作数组（WorkCell）字段约定

| 偏移 | 字节 | 类型 | 含义 |
|---|---|---|---|
| +0 | 0..3 | int | MapCoords（低16=X，高16=Y） |
| +56 | 56..59 | int | 遍1/遍2 写入的"生成代号/中间标记" |
| +64 | 64..67 | int | **处理标记**：-1 = 未处理；>=0 = 已归入某水体 |
| +74 | 74 | byte | 有效标志（1 = 参与判定） |
| +76 | 76..79 | — | 未使用 |

访问器：
- 线性（按 X + W'·Y 之外的简单序号）：`base + 80*i`（sub_58C2C0）
- 二维（按菱形坐标 x, y）：`base + 80*x + 80*W'*y`（sub_58C2A0）

---

## 5. 四遍扫描的语义要点

1. **遍1（sub_57A430，递归洪泛）**
   - 入参 `(cell, a1=genCode, a2=flag)`。
   - 先把当前格的处理标记 `data[16]` 置为其 `sub_57B210(cell, 2)` 的结果。
   - 计算连通掩码 `n11 = sub_57B210(cell, 0)`；`n11 == 0` 直接返回。
   - 按位探测 ±1 / ±2 距离的邻格，判断是否需要"回退"（`v44`）。
   - 若掩码含 `0x88`、`0x22` 或 `v44`，则：
     - `sub_5A00C0` 取该格生成代号；若 `>0 && != a2 && !a1` 则**返回 0**（失败传播）。
     - 把该格瓦片设为 `nIdx`（水基瓦片），清 `+282`，写 `+56 = nIdx`。
     - `sub_5A0090` 回写代号。
     - 8 邻递归：邻格在处理标记置 -1 后递归调用自身。
   - 返回值 `1` = 成功；`0` = 撞上"外来水体"（不同代号），主函数借此中止后续遍。

2. **遍2（sub_57A320，清理）**
   - 仅对瓦片落在 `[nIdx, nIdx+12)` 的格生效。
   - 取 `sub_57B210(cell, 2)`，若属于 8 个特定编号之一
     （199/124/241/31/198/108/177/27），则该格瓦片置 `0xFFFF`、`Height=0`，
     并在 `MapCoords.X != 0` 时写 `+56 = a2`。
   - 再遍历 8 邻，把菱形范围内的邻格处理标记置 -1、并写其 `sub_57B210(...,2)`。

3. **遍3/4（sub_57ACF0，参数 n2 = 1 然后 2）**
   - 先 `sub_598030(0, 5)` 取随机数 `v8`（**消耗 RNG**）。
   - `v9 = sub_57B210(cell, n2==2 ? 1 : 0)`；`v9 == 0` 直接返回 1。
   - 按 `v9` 的位组合（0xA0/0x82/0x0A/0x28 四种角、0x20/0x02/0x08/0x80 四边）
     与沿边扫描计数 `v38[0]` 决定水岸瓦片编号 `n12`（0..41 区间）。
   - 命中后：把 `n12` 对应的瓦片对象写入 `MouseClass::CurrentBuildingType`，
     经 `sub_4A91B0` 换算屏幕坐标，最后 `sub_57B440` 落瓦片。
   - 返回 `a3 != 0`（`a3` 为落瓦片是否被否决）。

---

## 6. 与项目内 `MapGen.cpp` 的对应关系

`MapGen.cpp` 中 `SmoothWaterBody` 目前为**桩实现**（直接 return true）。
本文档集合即为其完整复刻依据。复刻时需注意：

- 四遍扫描共用同一个"失败标志" `j`：任一遍返回 0，后续遍的循环体在
  `if (!j) break;` 处立即跳出，但**仍会把四遍都走完**（每遍都是独立循环）。
  最终返回值是**最后一遍** `j` 的值。
- `sub_57ACF0` 每格都会消耗一次 RNG（`sub_598030(0,5)`），因此**遍3/4 的
  RNG 消耗次数 = 参与迭代的格子数 × 2**，复刻时必须逐格调用以保证序列一致。
- 遍3 与遍4 的区别仅在传给 `sub_57B210` 的第二参（1 / 0）与 `sub_57B440`
  的基号参数（`0,0` vs `dword_ABAD28, dword_ABAD28+41`）。