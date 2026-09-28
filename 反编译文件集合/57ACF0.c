// ============================================================================
// sub_57ACF0  --  遍3/4 水岸瓦片选择
// 地址: 0x57ACF0   签名: bool __fastcall sub_57ACF0(int a1, int a2, CellClass *a3, int n2, int a5, char a6)
//   a1 = 备用（存入 v38[1]，未使用）
//   a2 = n2 = 遍号：1 = 第一遍，2 = 第二遍
//   a3 = CellClass* 当前格
//   n2 = 同上（遍号）
//   a5 = genCode（生成代号）
//   a6 = flag（各调用点均传 0）
// 返回: a3 != 0（落瓦片是否被否决）；早退路径返回 1
//
// 要点:
//   1) v6 = sub_598030(0, 5)  → **每格消耗一次 RNG**，取值 0..5。
//   2) v9 = sub_57B210(cell, n2==2 ? 1 : 0)；v9 == 0 → return 1。
//   3) 分两支:
//      A. n2 == 2（第二遍）：只看 v9 的四种角位组合
//         0xA0&0xA0 → 0x11&0x11 → n12 = (v8&1)+23
//                              否则     → n12 = (v9&1) ? 21 : 30
//         0x82&0x82 → 0x44&0x44 → n12 = (v8&1)+15
//                              否则     → n12 = (v9&4) ? 14 : 22
//         0x0A&0x0A → 0x11&0x11 → n12 = (v8&1)+7
//                              否则     → n12 = (v9&1) ? 13 : 6
//         0x28&0x28 → 0x44&0x44 → n12 = (v8&1)+31
//                              否则     → n12 = (v9&4) ? 5 : 29
//      B. n2 == 1（第一遍）：按单边位分别处理，沿边扫描计数 v38[0]，
//         再结合奇偶/相邻位决定 n12；未命中时落到 LABEL_61 的兜底分支
//         （(v10&1)→+35 / (v10&4)→+33 / (v10&0x10)→+39 / (v10&0x40)→+37）。
//         各边映射:
//           bit 0x02 → 邻格 4(+X) 与 2(-Y) 方向扫描，n12 = 12 或 |v8%3|+9
//           bit 0x20 → 邻格 4(+X) 与 6(-X) 方向扫描，n12 = 28 或 v8%3+25
//           bit 0x08 → 邻格 2(+Y) 与 4(+X) 方向扫描，n12 = 4  或 v8%3+1
//           bit 0x80 → 邻格 2(+Y) 与 0(-Y) 方向扫描，n12 = 20 或 v8%3+17
//   4) 命中后 LABEL_71:
//        - MouseClass::CurrentBuildingType = IsometricTileTypeClass::Array
//          [dword_ABAD28-1][n12]（取第 n12 个水岸瓦片对象）
//        - 由 word_ABDB64[2*n12] / word_ABDB66[2*n12] 得到该瓦片的 X/Y 偏移，
//          加到当前格坐标上，得目标格 v38[0]
//        - sub_4A91B0 做显示坐标换算
//        - n2 == 1 → sub_57B440(0, 0, Level, a5, &a3, a6)
//          n2 == 2 → sub_57B440(dword_ABAD28, dword_ABAD28+41, Level, a5, &a3, a6)
//   5) n12 <= 0 时直接 return 1。
// ============================================================================

bool __fastcall sub_57ACF0(int a1, int a2, CellClass *a3, int n2, int a5, char a6)
{
  int v6; // eax
  int n2_1; // edi
  int v8; // ebp
  int v9; // eax
  char v10; // bl
  int n12_1; // ebp
  int n12; // eax
  CellClass *NeighbourCell; // esi
  CellClass *v14; // edi
  char v15; // al
  CellClass *v16; // esi
  CellClass *v17; // edi
  char v18; // al
  CellClass *v19; // esi
  CellClass *v20; // edi
  char v21; // al
  CellClass *v22; // esi
  CellClass *v23; // edi
  char v24; // al
  CellClass *v25; // esi
  CellStruct MapCoords; // ecx
  __int16 v27; // dx
  __int16 v28; // ax
  bool v30; // [esp+13h] [ebp-Dh]
  bool v31; // [esp+13h] [ebp-Dh]
  bool v32; // [esp+13h] [ebp-Dh]
  bool v33; // [esp+13h] [ebp-Dh]
  bool v34; // [esp+13h] [ebp-Dh]
  bool v35; // [esp+13h] [ebp-Dh]
  bool v36; // [esp+13h] [ebp-Dh]
  bool v37; // [esp+13h] [ebp-Dh]
  _DWORD v38[2]; // [esp+14h] [ebp-Ch] BYREF
  CellStruct v39; // [esp+1Ch] [ebp-4h] BYREF

  v38[1] = a1; /*0x57ad00*/
  v6 = sub_598030(0, 5); /*0x57ad04*/
  n2_1 = n2; /*0x57ad09*/
  v8 = v6; /*0x57ad0d*/
  if ( n2 == 2 ) /*0x57ad12*/
    v9 = sub_57B210(a3, 1); /*0x57ad1b*/
  else
    v9 = sub_57B210(a3, 0); /*0x57ad26*/
  v10 = v9; /*0x57ad2b*/
  if ( !v9 ) /*0x57ad2f*/
    return 1; /*0x57ad2f*/
  if ( n2_1 != 2 ) /*0x57ad38*/
  {
    if ( (v9 & 2) != 0 ) /*0x57ae12*/
    {
      v38[0] = 1; /*0x57ae1e*/
      NeighbourCell = CellClass::GetNeighbourCell(a3, 4); /*0x57ae2b*/
      v14 = CellClass::GetNeighbourCell(NeighbourCell, 2); /*0x57ae38*/
      v30 = sub_485060(NeighbourCell) == 0; /*0x57ae43*/
      v15 = sub_485060(v14); /*0x57ae48*/
      if ( v30 ) /*0x57ae53*/
      {
        do /*0x57ae93*/
        {
          if ( !v15 ) /*0x57ae57*/
            break; /*0x57ae57*/
          ++v38[0]; /*0x57ae62*/
          NeighbourCell = CellClass::GetNeighbourCell(NeighbourCell, 4); /*0x57ae6f*/
          v14 = CellClass::GetNeighbourCell(v14, 4); /*0x57ae78*/
          v31 = sub_485060(NeighbourCell) == 0; /*0x57ae83*/
          v15 = sub_485060(v14); /*0x57ae88*/
        }
        while ( v31 ); /*0x57ae93*/
      }
      if ( (v38[0] & 1) != 0 && v10 >= 0 || (v10 & 4) == 0 || (v10 & 0x18) != 0 ) /*0x57aeb3*/
      {
        n12 = 12; /*0x57aea1*/
        goto LABEL_71; /*0x57aea6*/
      }
      n12 = abs32(v8 % 3) + 9; /*0x57aec6*/
    }
    else if ( (v9 & 0x20) != 0 ) /*0x57aed1*/
    {
      v38[0] = 1; /*0x57aedd*/
      v16 = CellClass::GetNeighbourCell(a3, 4); /*0x57aeea*/
      v17 = CellClass::GetNeighbourCell(v16, 6); /*0x57aef7*/
      v32 = sub_485060(v16) == 0; /*0x57af02*/
      v18 = sub_485060(v17); /*0x57af07*/
      if ( v32 ) /*0x57af12*/
      {
        do /*0x57af52*/
        {
          if ( !v18 ) /*0x57af16*/
            break; /*0x57af16*/
          ++v38[0]; /*0x57af21*/
          v16 = CellClass::GetNeighbourCell(v16, 4); /*0x57af2e*/
          v17 = CellClass::GetNeighbourCell(v17, 4); /*0x57af37*/
          v33 = sub_485060(v16) == 0; /*0x57af42*/
          v18 = sub_485060(v17); /*0x57af47*/
        }
        while ( v33 ); /*0x57af52*/
      }
      if ( (v38[0] & 1) != 0 && v10 >= 0 || (v10 & 0x10) == 0 || (v10 & 0xC) != 0 ) /*0x57af72*/
      {
        n12 = 28; /*0x57af60*/
        goto LABEL_71; /*0x57af65*/
      }
      n12 = v8 % 3 + 25; /*0x57af80*/
    }
    else if ( (v9 & 8) != 0 ) /*0x57af8b*/
    {
      v38[0] = 1; /*0x57af97*/
      v19 = CellClass::GetNeighbourCell(a3, 2); /*0x57afa4*/
      v20 = CellClass::GetNeighbourCell(v19, 4); /*0x57afb1*/
      v34 = sub_485060(v19) == 0; /*0x57afbc*/
      v21 = sub_485060(v20); /*0x57afc1*/
      if ( v34 ) /*0x57afcc*/
      {
        do /*0x57b00c*/
        {
          if ( !v21 ) /*0x57afd0*/
            break; /*0x57afd0*/
          ++v38[0]; /*0x57afdb*/
          v19 = CellClass::GetNeighbourCell(v19, 2); /*0x57afe8*/
          v20 = CellClass::GetNeighbourCell(v20, 2); /*0x57aff1*/
          v35 = sub_485060(v19) == 0; /*0x57affc*/
          v21 = sub_485060(v20); /*0x57b001*/
        }
        while ( v35 ); /*0x57b00c*/
      }
      if ( (v38[0] & 1) != 0 || (v10 & 4) == 0 || (v10 & 3) != 0 ) /*0x57b027*/
      {
        n12 = 4; /*0x57b015*/
        goto LABEL_71; /*0x57b01a*/
      }
      n12 = v8 % 3 + 1; /*0x57b035*/
    }
    else
    {
      if ( (v9 & 0x80u) == 0 ) /*0x57b03e*/
      {
LABEL_61:
        if ( (v10 & 1) != 0 ) /*0x57b0f0*/
        {
          n12_1 = (v8 & 1) + 35; /*0x57b0f5*/
        }
        else if ( (v10 & 4) != 0 ) /*0x57b0fd*/
        {
          n12_1 = (v8 & 1) + 33; /*0x57b102*/
        }
        else if ( (v10 & 0x10) != 0 ) /*0x57b10a*/
        {
          n12_1 = (v8 & 1) + 39; /*0x57b10f*/
        }
        else
        {
          if ( (v10 & 0x40) == 0 ) /*0x57b117*/
            return 1; /*0x57b117*/
          n12_1 = (v8 & 1) + 37; /*0x57b120*/
        }
        goto LABEL_69; /*0x57b0f8*/
      }
      v38[0] = 1; /*0x57b04a*/
      v22 = CellClass::GetNeighbourCell(a3, 2); /*0x57b057*/
      v23 = CellClass::GetNeighbourCell(v22, 0); /*0x57b064*/
      v36 = sub_485060(v22) == 0; /*0x57b06f*/
      v24 = sub_485060(v23); /*0x57b074*/
      if ( v36 ) /*0x57b07f*/
      {
        do /*0x57b0bf*/
        {
          if ( !v24 ) /*0x57b083*/
            break; /*0x57b083*/
          ++v38[0]; /*0x57b08e*/
          v22 = CellClass::GetNeighbourCell(v22, 2); /*0x57b09b*/
          v23 = CellClass::GetNeighbourCell(v23, 2); /*0x57b0a4*/
          v37 = sub_485060(v22) == 0; /*0x57b0af*/
          v24 = sub_485060(v23); /*0x57b0b4*/
        }
        while ( v37 ); /*0x57b0bf*/
      }
      if ( (v38[0] & 1) != 0 || (v10 & 1) == 0 || (v10 & 6) != 0 ) /*0x57b0d7*/
      {
        n12 = 20; /*0x57b0c8*/
        goto LABEL_71; /*0x57b0cd*/
      }
      n12 = v8 % 3 + 17; /*0x57b0e5*/
    }
    if ( n12 != -1 ) /*0x57b0eb*/
      goto LABEL_70; /*0x57b0eb*/
    goto LABEL_61; /*0x57b0eb*/
  }
  if ( (v9 & 0xA0) == 0xA0 )
  {
    if ( (v9 & 0x11) == 0x11 ) /*0x57ad50*/
    {
      n12_1 = (v8 & 1) + 23; /*0x57ad55*/
LABEL_69:
      n12 = n12_1; /*0x57b123*/
LABEL_70:
      if ( n12 <= 0 ) /*0x57b127*/
        return 1; /*0x57b127*/
      goto LABEL_71; /*0x57b127*/
    }
    n12 = (v9 & 1) != 0 ? 21 : 30;
  }
  else if ( (v9 & 0x82) == 0x82 )
  {
    if ( (v9 & 0x44) == 0x44 ) /*0x57ad86*/
    {
      n12_1 = (v8 & 1) + 15; /*0x57ad8b*/
      goto LABEL_69; /*0x57ad8e*/
    }
    n12 = (v9 & 4) != 0 ? 14 : 22;
  }
  else if ( (v9 & 0xA) == 0xA )
  {
    if ( (v9 & 0x11) == 0x11 ) /*0x57adb8*/
    {
      n12_1 = (v8 & 1) + 7; /*0x57adbd*/
      goto LABEL_69; /*0x57adc0*/
    }
    n12 = (v9 & 1) != 0 ? 13 : 6;
  }
  else
  {
    if ( (v9 & 0x28) != 0x28 ) /*0x57ade1*/
      return 1; /*0x57ade1*/
    if ( (v9 & 0x44) == 0x44 ) /*0x57adee*/
    {
      n12_1 = (v8 & 1) + 31; /*0x57adf3*/
      goto LABEL_69; /*0x57adf6*/
    }
    n12 = (v9 & 4) != 0 ? 5 : 29;
  }
LABEL_71:
  v25 = a3; /*0x57b12d*/
  MouseClass::Instance.CurrentBuildingType = *(&IsometricTileTypeClass::Array.Items[dword_ABAD28 - 1] + n12); /*0x57b143*/
  MapCoords = a3->MapCoords; /*0x57b149*/
  v27 = word_ABDB64[2 * n12]; /*0x57b14c*/
  v28 = word_ABDB66[2 * n12]; /*0x57b154*/
  LOWORD(a3) = MapCoords.X + v27; /*0x57b168*/
  HIWORD(a3) = MapCoords.Y + v28; /*0x57b16d*/
  v38[0] = a3; /*0x57b17e*/
  sub_4A91B0(&MouseClass::Instance, &v39, v38); /*0x57b189*/
  LOBYTE(a3) = 1; /*0x57b192*/
  if ( n2 == 1 ) /*0x57b19a*/
  {
    sub_57B440(0, 0, v25->Level, a5, &a3, a6); /*0x57b1b7*/
  }
  else
  {
    if ( n2 != 2 ) /*0x57b1bc*/
      return 1; /*0x57b1bc*/
    sub_57B440(dword_ABAD28, dword_ABAD28 + 41, v25->Level, a5, &a3, a6); /*0x57b1e3*/
  }
  return a3 != 0; /*0x57b1ee*/
}