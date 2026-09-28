// ============================================================================
// 49F2F0_Neighbours.c  --  Neighbours[8] 方向表初始化
// 地址: 0x49F2F0   签名: int sub_49F2F0()
//
// 该函数在启动阶段写入全局 Neighbours[8]（0x89F688）与相邻的菱形边界全局。
// CellStruct 为两个 int16: { X, Y }，故每个 dword 即一个方向对。
//
// 还原后的表（CellClass::GetNeighbourCell 使用 Neighbours[nFacingType & 7]）:
//   [0] (0, -1)    [1] (1, -1)    [2] (1, 0)    [3] (1, 1)
//   [4] (0,  1)    [5] (-1, 1)    [6] (-1, 0)   [7] (-1, -1)
//
// 同函数还写入:
//   0xABED04 (IsoTileTypeIndex_0) = 0x1FFFF ??? —— 见下方说明
//   0xABED08 (IsoTileTypeIndex_1) = 0x10000 ???
// 注意: 该反编译中 IsoTileTypeIndex_0 / IsoTileTypeIndex_1 的写入点未在此函数
//       出现（此函数只写 Neighbours 及其紧邻的 0x89F68C..0x89F6A4 区间）。
//       菱形边界 W' / W'+2H' 是在地图尺寸计算阶段另行写入 0xABED04 / 0xABED08。
// ============================================================================

int sub_49F2F0()
{
  int result; // eax

  Neighbours[0] = -65536; /*0x49f305*/       // 0xFFFF0000 -> (0, -1)
  dword_89F68C = -65535; /*0x49f322*/        // 0xFFFF0001 -> (1, -1)
  stru_89F690 = 1; /*0x49f336*/              // 0x00000001 -> (1, 0)
  n65537_1 = 65537; /*0x49f34a*/             // 0x00010001 -> (1, 1)
  n0x1FFFF_1 = 0x1FFFF; /*0x49f375*/         // 0x0001FFFF -> (-1, 1)
  result = -1; /*0x49f384*/
  n0x10000_1 = 0x10000; /*0x49f388*/         // 0x00010000 -> (0, 1)
  pMapCrd = 0xFFFF; /*0x49f38e*/             // 0x0000FFFF -> (-1, 0)
  stru_89F6A4 = -1; /*0x49f394*/             // 0xFFFFFFFF -> (-1, -1)
  return result; /*0x49f39b*/
}

// 地址对应（IDA 将连续 8 个 CellStruct 拆成了带名字的 dword）:
//   0x89F688 Neighbours      [0]
//   0x89F68C dword_89F68C    [1]
//   0x89F690 stru_89F690     [2]
//   0x89F694 n65537_1        [3]
//   0x89F698 n0x10000_1      [4]
//   0x89F69C n0x1FFFF_1      [5]
//   0x89F6A0 pMapCrd         [6]
//   0x89F6A4 stru_89F6A4     [7]