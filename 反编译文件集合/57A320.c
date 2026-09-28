// ============================================================================
// sub_57A320  --  遍2 瓦片清理（占位瓦片回收）
// 地址: 0x57A320   签名: int __stdcall sub_57A320(CellClass *a1, int a2, CellStruct MapCoords_1)
//   a1 = CellClass* 当前格
//   a2 = genCode（生成代号）
//   MapCoords_1 = 传入的坐标（仅用其 .X 低 16 位做 X != 0 判定）
// 返回: 最后一次 sub_57B210(...,2) 的值（调用方忽略）
//
// 要点:
//   - 仅处理瓦片落在 [nIdx, nIdx+12) 的格。
//   - 取形态码 sub_57B210(cell, 2)；命中 8 个特定编号之一
//     （199 / 124 / 241 / 31 / 198 / 108 / 177 / 27）时:
//       * 该格瓦片置 0xFFFF（占位/多格覆盖标记），Height = 0；
//       * 若 MapCoords.X != 0，则 WorkCell +56 写 genCode。
//   - 随后遍历 8 邻格，把菱形范围内的邻格处理标记 data[16] (偏移64) 置 -1，
//     并再写一次其形态码。
//   - 菱形判定用 IsoTileTypeIndex_0 (=W') 与 IsoTileTypeIndex_1 (=W'+2H')。
// ============================================================================

int __stdcall sub_57A320(CellClass *a1, int a2, CellStruct MapCoords_1)
{
  CellClass *v3; // ebp
  int IsoTileTypeIndex; // eax
  int nFacingType; // ebx
  bool v6; // zf
  CellClass *NeighbourCell; // esi
  CellStruct MapCoords; // edx
  int IsoTileTypeIndex_1; // edi
  int v10; // edi

  v3 = a1; /*0x57a328*/
  IsoTileTypeIndex = a1->IsoTileTypeIndex; /*0x57a330*/
  if ( IsoTileTypeIndex >= nIdx && IsoTileTypeIndex < nIdx + 12 ) /*0x57a340*/
  {
    IsoTileTypeIndex = sub_57B210(a1, 2); /*0x57a349*/
    if ( IsoTileTypeIndex == 199 /*0x57a37c*/
      || IsoTileTypeIndex == 124
      || IsoTileTypeIndex == 241
      || IsoTileTypeIndex == 31
      || IsoTileTypeIndex == 198
      || IsoTileTypeIndex == 108
      || IsoTileTypeIndex == 177
      || IsoTileTypeIndex == 27 )
    {
      nFacingType = 0; /*0x57a387*/
      v6 = LOBYTE(MapCoords_1.X) == 0; /*0x57a38a*/
      a1->IsoTileTypeIndex = 0xFFFF; /*0x57a38d*/
      a1->Height = 0; /*0x57a394*/
      if ( !v6 ) /*0x57a39a*/
        *(sub_58C2A0(&a1->MapCoords) + 56) = a2; /*0x57a3a8*/
      do /*0x57a41e*/
      {
        NeighbourCell = CellClass::GetNeighbourCell(v3, nFacingType); /*0x57a3b3*/
        MapCoords = NeighbourCell->MapCoords; /*0x57a3b5*/
        MapCoords_1 = MapCoords; /*0x57a3ba*/
        IsoTileTypeIndex = MapCoords.Y; /*0x57a3c1*/
        IsoTileTypeIndex_1 = MapCoords.Y + MapCoords.X; /*0x57a3c6*/
        if ( IsoTileTypeIndex_1 > IsoTileTypeIndex_0 ) /*0x57a3cf*/
        {
          if ( MapCoords_1.X - MapCoords_1.Y < IsoTileTypeIndex_0 ) /*0x57a3db*/
          {
            IsoTileTypeIndex = MapCoords_1.Y - MapCoords_1.X; /*0x57a3dd*/
            if ( IsoTileTypeIndex < IsoTileTypeIndex_0 && IsoTileTypeIndex_1 <= ::IsoTileTypeIndex_1 ) /*0x57a3ef*/
            {
              MapCoords_1 = MapCoords; /*0x57a3f5*/
              v10 = sub_58C2A0(&MapCoords_1); /*0x57a402*/
              *(v10 + 64) = -1; /*0x57a407*/
              IsoTileTypeIndex = sub_57B210(NeighbourCell, 2); /*0x57a40e*/
              *(v10 + 64) = IsoTileTypeIndex; /*0x57a413*/
            }
          }
          v3 = a1; /*0x57a416*/
        }
        ++nFacingType; /*0x57a41a*/
      }
      while ( nFacingType < 8 ); /*0x57a41e*/
    }
  }
  return IsoTileTypeIndex; /*0x57a423*/
}