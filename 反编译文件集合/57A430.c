// ============================================================================
// sub_57A430  --  遍1 递归洪泛填充（水体边界裁剪）
// 地址: 0x57A430   签名: char __fastcall sub_57A430(int a1, int a2, int n8, int a4, int a5)
//   a1 = CellClass* 当前格
//   a2 = a4 = genCode（生成代号）
//   n8 = a5 = flag（各调用点均传 0）
// 返回: 1 = 正常；0 = 撞上"外来水体"（不同生成代号），用于中止后续遍
//
// 要点:
//   - 先把当前格 WorkCell data[16] (偏移64) 写为 sub_57B210(cell, 2)。
//   - 计算连通掩码 n11 = sub_57B210(cell, 0)；n11 <= 0 直接返回 1。
//   - 依掩码位探测 ±1 / ±2 邻格，累积"需回退"标志 v44。
//   - 掩码含 0x88 或 0x22，或 v44 置位时执行主体:
//       * 取该格生成代号（sub_5A00C0）；
//         若代号 > 0 且 != a4 且 a5 == 0 → return 0（污染，失败）。
//       * 瓦片置为水基瓦片 nIdx，清 +282，写 +56 = nIdx；
//       * 回写生成代号（sub_5A0090，flag 决定写入值）。
//       * 8 邻递归：邻格若在菱形范围内，先把其处理标记置 -1 再递归。
//   - 邻格坐标过滤使用菱形四条件（W' < x+y <= W'+2H' 且 |x-y| < W'）。
// ============================================================================

char __fastcall sub_57A430(int a1, int a2, int n8, int a4, int a5)
{
  int n8_1; // ebp
  int n8_2; // eax
  int v7; // esi
  int n11; // eax
  char n11_1; // bl
  unsigned int n0x40000; // eax
  CellClass *p_MapClass::InvalidCell; // eax
  unsigned int n0x40000_1; // eax
  CellClass *p_MapClass::InvalidCell_1; // eax
  char v14; // al
  unsigned int n0x40000_2; // eax
  CellClass *p_MapClass::InvalidCell_2; // eax
  char v17; // bl
  unsigned int n0x40000_3; // eax
  CellClass *p_MapClass::InvalidCell_3; // eax
  char v20; // al
  unsigned int n0x40000_4; // eax
  CellClass *p_MapClass::InvalidCell_4; // eax
  char v23; // bl
  unsigned int n0x40000_5; // eax
  CellClass *p_MapClass::InvalidCell_5; // eax
  char v26; // al
  unsigned int n0x40000_6; // eax
  CellClass *p_MapClass::InvalidCell_6; // eax
  char v29; // bl
  unsigned int n0x40000_7; // eax
  CellClass *p_MapClass::InvalidCell_7; // eax
  char v32; // al
  int v33; // eax
  int v34; // edx
  char v35; // cl
  int nIdx; // eax
  int nFacingType; // eax
  CellClass *NeighbourCell; // esi
  CellStruct MapCoords_4; // edx
  int v41; // edi
  int v42; // eax
  int v43; // edx
  char v44; // [esp+13h] [ebp-15h]
  CellStruct MapCoords; // [esp+14h] [ebp-14h]
  CellStruct MapCoords_1; // [esp+14h] [ebp-14h]
  CellStruct MapCoords_2; // [esp+14h] [ebp-14h]
  CellStruct MapCoords_3; // [esp+14h] [ebp-14h]
  int v49; // [esp+18h] [ebp-10h]
  int v50; // [esp+18h] [ebp-10h]
  _DWORD v51[3]; // [esp+1Ch] [ebp-Ch] BYREF

  n8_1 = n8; /*0x57a435*/
  n8_2 = *(n8 + 36); /*0x57a43d*/
  v51[2] = a1; /*0x57a444*/
  v44 = 0; /*0x57a448*/
  n8 = n8_2; /*0x57a44d*/
  v7 = sub_58C2A0(&n8); /*0x57a45b*/
  *(v7 + 64) = sub_57B210(n8_1, 2); /*0x57a467*/
  n11 = sub_57B210(n8_1, 0); /*0x57a46a*/
  n11_1 = n11; /*0x57a46f*/
  n8 = n11; /*0x57a473*/
  if ( n11 > 0 ) /*0x57a477*/
  {
    if ( n11 == 11 || n11 == 26 ) /*0x57a485*/
      v44 = 1; /*0x57a487*/
    if ( (n11 & 0xA0) == 0xA0 && (n11 & 0x11) == 0 /*0x57a4cb*/
      || (n11 & 0x82) == 0x82 && (n11 & 0x44) == 0
      || (n11 & 0xA) == 0xA && (n11 & 0x11) == 0
      || (n11 & 0x28) == 0x28 && (n11 & 0x44) == 0 )
    {
      v44 = 1; /*0x57a4cd*/
    }
    if ( (n11 & 0x20) != 0 ) /*0x57a4d5*/
    {
      v49 = *(n8_1 + 36); /*0x57a4de*/
      n0x40000 = (v49 + 1) + (SHIWORD(v49) << 9); /*0x57a4fd*/
      if ( n0x40000 >= 0x40000 || (p_MapClass::InvalidCell = MouseClass::Instance.Cells.Items[n0x40000]) == 0 ) /*0x57a513*/
      {
        p_MapClass::InvalidCell = &MapClass::InvalidCell; /*0x57a519*/
        MapCoords.X = v49 + 1; /*0x57a4ef*/
        MapCoords.Y = HIWORD(*(n8_1 + 36)); /*0x57a4ea*/
        MapClass::InvalidCell.MapCoords = MapCoords; /*0x57a51e*/
      }
      v51[0] = sub_57B210(p_MapClass::InvalidCell, 0); /*0x57a52e*/
      v50 = *(n8_1 + 36); /*0x57a535*/
      n0x40000_1 = (v50 + 2) + (SHIWORD(v50) << 9); /*0x57a554*/
      if ( n0x40000_1 >= 0x40000 || (p_MapClass::InvalidCell_1 = MouseClass::Instance.Cells.Items[n0x40000_1]) == 0 ) /*0x57a56a*/
      {
        MapCoords_1.X = v50 + 2; /*0x57a546*/
        MapCoords_1.Y = HIWORD(*(n8_1 + 36)); /*0x57a541*/
        MapClass::InvalidCell.MapCoords = MapCoords_1; /*0x57a570*/
        p_MapClass::InvalidCell_1 = &MapClass::InvalidCell; /*0x57a575*/
      }
      v14 = sub_57B210(p_MapClass::InvalidCell_1, 0); /*0x57a57f*/
      if ( (v51[0] & 2) != 0 || (v14 & 2) != 0 ) /*0x57a58d*/
        v44 = 1; /*0x57a58f*/
    }
    if ( (n11_1 & 2) != 0 ) /*0x57a597*/
    {
      v51[0] = *(n8_1 + 36); /*0x57a5a0*/
      MapCoords_2.Y = HIWORD(v51[0]); /*0x57a5ac*/
      n0x40000_2 = (LOWORD(v51[0]) - 1) + (SHIWORD(v51[0]) << 9); /*0x57a5bf*/
      if ( n0x40000_2 >= 0x40000 || (p_MapClass::InvalidCell_2 = MouseClass::Instance.Cells.Items[n0x40000_2]) == 0 ) /*0x57a5d5*/
      {
        MapCoords_2.X = LOWORD(v51[0]) - 1; /*0x57a5b1*/
        MapClass::InvalidCell.MapCoords = MapCoords_2; /*0x57a5db*/
        p_MapClass::InvalidCell_2 = &MapClass::InvalidCell; /*0x57a5e0*/
      }
      v17 = sub_57B210(p_MapClass::InvalidCell_2, 0); /*0x57a5ef*/
      v51[0] = *(n8_1 + 36); /*0x57a5f4*/
      MapCoords_3.Y = HIWORD(v51[0]); /*0x57a600*/
      n0x40000_3 = (LOWORD(v51[0]) - 2) + (SHIWORD(v51[0]) << 9); /*0x57a613*/
      if ( n0x40000_3 >= 0x40000 || (p_MapClass::InvalidCell_3 = MouseClass::Instance.Cells.Items[n0x40000_3]) == 0 ) /*0x57a629*/
      {
        MapCoords_3.X = LOWORD(v51[0]) - 2; /*0x57a605*/
        MapClass::InvalidCell.MapCoords = MapCoords_3; /*0x57a62f*/
        p_MapClass::InvalidCell_3 = &MapClass::InvalidCell; /*0x57a634*/
      }
      v20 = sub_57B210(p_MapClass::InvalidCell_3, 0); /*0x57a63e*/
      if ( (v17 & 0x20) != 0 || (v20 & 0x20) != 0 ) /*0x57a64a*/
        v44 = 1; /*0x57a64c*/
      n11_1 = n8; /*0x57a651*/
    }
    if ( (n11_1 & 8) != 0 ) /*0x57a658*/
    {
      v51[0] = *(n8_1 + 36); /*0x57a661*/
      n0x40000_4 = SLOWORD(v51[0]) + ((HIWORD(v51[0]) - 1) << 9); /*0x57a67f*/
      if ( n0x40000_4 >= 0x40000 || (p_MapClass::InvalidCell_4 = MouseClass::Instance.Cells.Items[n0x40000_4]) == 0 ) /*0x57a695*/
      {
        MapClass::InvalidCell.MapCoords = (v51[0] - 0x10000); /*0x57a69b*/
        p_MapClass::InvalidCell_4 = &MapClass::InvalidCell; /*0x57a6a0*/
      }
      v23 = sub_57B210(p_MapClass::InvalidCell_4, 0); /*0x57a6b2*/
      v51[0] = *(n8_1 + 36); /*0x57a6b4*/
      n0x40000_5 = SLOWORD(v51[0]) + ((HIWORD(v51[0]) - 2) << 9); /*0x57a6d2*/
      if ( n0x40000_5 >= 0x40000 || (p_MapClass::InvalidCell_5 = MouseClass::Instance.Cells.Items[n0x40000_5]) == 0 ) /*0x57a6e8*/
      {
        MapClass::InvalidCell.MapCoords = (v51[0] - 0x20000); /*0x57a6ee*/
        p_MapClass::InvalidCell_5 = &MapClass::InvalidCell; /*0x57a6f3*/
      }
      v26 = sub_57B210(p_MapClass::InvalidCell_5, 0); /*0x57a6fd*/
      if ( v23 < 0 || v26 < 0 ) /*0x57a709*/
        v44 = 1; /*0x57a70b*/
      n11_1 = n8; /*0x57a710*/
    }
    if ( n11_1 < 0 ) /*0x57a717*/
    {
      v51[0] = *(n8_1 + 36); /*0x57a720*/
      n0x40000_6 = SLOWORD(v51[0]) + ((HIWORD(v51[0]) + 1) << 9); /*0x57a73e*/
      if ( n0x40000_6 >= 0x40000 || (p_MapClass::InvalidCell_6 = MouseClass::Instance.Cells.Items[n0x40000_6]) == 0 ) /*0x57a754*/
      {
        MapClass::InvalidCell.MapCoords = (v51[0] + 0x10000); /*0x57a75a*/
        p_MapClass::InvalidCell_6 = &MapClass::InvalidCell; /*0x57a75f*/
      }
      v29 = sub_57B210(p_MapClass::InvalidCell_6, 0); /*0x57a771*/
      v51[0] = *(n8_1 + 36); /*0x57a773*/
      n0x40000_7 = SLOWORD(v51[0]) + ((HIWORD(v51[0]) + 2) << 9); /*0x57a791*/
      if ( n0x40000_7 >= 0x40000 || (p_MapClass::InvalidCell_7 = MouseClass::Instance.Cells.Items[n0x40000_7]) == 0 ) /*0x57a7a7*/
      {
        MapClass::InvalidCell.MapCoords = (v51[0] + 0x20000); /*0x57a7ad*/
        p_MapClass::InvalidCell_7 = &MapClass::InvalidCell; /*0x57a7b2*/
      }
      v32 = sub_57B210(p_MapClass::InvalidCell_7, 0); /*0x57a7bc*/
      if ( (v29 & 8) != 0 || (v32 & 8) != 0 ) /*0x57a7c8*/
        v44 = 1; /*0x57a7ca*/
      n11_1 = n8; /*0x57a7cf*/
    }
    if ( (n11_1 & 0x88) == 0x88 || (n11_1 & 0x22) == 0x22 || v44 ) /*0x57a7ee*/
    {
      n8 = *(n8_1 + 36); /*0x57a801*/
      v33 = sub_5A00C0(&n8); /*0x57a805*/
      v34 = a4; /*0x57a80a*/
      v35 = a5; /*0x57a80e*/
      if ( v33 > 0 && v33 != a4 && !a5 ) /*0x57a81c*/
        return 0; /*0x57a827*/
      nIdx = ::nIdx; /*0x57a82a*/
      *(n8_1 + 282) = 0; /*0x57a82f*/
      *(n8_1 + 56) = nIdx; /*0x57a838*/
      n8 = *(n8_1 + 36); /*0x57a846*/
      if ( v35 ) /*0x57a83b*/
        sub_5A0090(&n8, 0); /*0x57a84b*/
      else
        sub_5A0090(&n8, v34); /*0x57a85f*/
      nFacingType = 0; /*0x57a864*/
      for ( n8 = 0; n8 < 8; ++n8 ) /*0x57a866*/
      {
        NeighbourCell = CellClass::GetNeighbourCell(n8_1, nFacingType); /*0x57a872*/
        MapCoords_4 = NeighbourCell->MapCoords; /*0x57a87a*/
        v51[0] = MapCoords_4; /*0x57a87f*/
        v41 = MapCoords_4.Y + MapCoords_4.X; /*0x57a88b*/
        if ( v41 > dword_ABED04 /*0x57a8b0*/
          && SLOWORD(v51[0]) - SHIWORD(v51[0]) < dword_ABED04
          && SHIWORD(v51[0]) - SLOWORD(v51[0]) < dword_ABED04
          && v41 <= dword_ABED08 )
        {
          v51[0] = MapCoords_4; /*0x57a8b6*/
          v42 = sub_58C2A0(v51); /*0x57a8ba*/
          v43 = a5; /*0x57a8bf*/
          *(v42 + 64) = -1; /*0x57a8c7*/
          sub_57A430(NeighbourCell, a4, v43); /*0x57a8d5*/
        }
        nFacingType = n8 + 1; /*0x57a8de*/
      }
    }
  }
  return 1; /*0x57a81e*/
}