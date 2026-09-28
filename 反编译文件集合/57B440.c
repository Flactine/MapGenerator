// ============================================================================
// sub_57B440  --  把选中的水岸瓦片真正铺到格子上
// 地址: 0x57B440
// 签名: char __stdcall sub_57B440(int IsoTileTypeIndex_1, int IsoTileTypeIndex_2,
//                                 char a3, int a4, _BYTE *a5, char a6)
//   IsoTileTypeIndex_1 / _2 = 允许覆盖的瓦片号下/上界
//       遍3 调用: (0, 0)
//       遍4 调用: (dword_ABAD28, dword_ABAD28 + 41)
//   a3   = 基准 Level
//   a4   = genCode（生成代号）
//   a5   = 输出标志（被否决时置 0）
//   a6   = flag（非 0 时强制 a4 = 0）
// 返回: 1 = 正常；0 = 失败
//
// 要点:
//   - 入口校验 MouseClass::CurrentBuildingType 必须是 Isotile 类型，
//     否则返回 0；取不到图像也返回 0。
//   - 按 CurrentBuildingType 的"尺寸"（W × H，来自 IsometricTileTypeClass）
//     双层循环遍历建筑覆盖的每一格:
//       * 计算目标格坐标 = CurrentFoundation_CenterCell + (v32, v30)
//       * 菱形范围过滤，越界跳过
//       * 从图像数据取出该格的瓦片号 v35，为 0 跳过
//       * v17 = sub_5A00C0(&p_n8)（该格现有生成代号）
//       * 依 a6 / a4 / 现有代号 / sub_486380 / dword_82A7F4 / dword_82A89C
//         决定是否否决（*a5 = 0 并 return 0），否则:
//           sub_5A0090(&p_n8, 代号)  回写代号
//           若 sub_486380 或现有瓦片在 [上界, 下界] 内:
//               瓦片 = 目标瓦片号；Height = Height；Level = a3 + 偏移
//   - 另有两个兜底分支调用 sub_4865B0 / sub_578D80 / sub_4863D0，
//     命中则 *a5 = 0。
// ============================================================================

char __stdcall sub_57B440(int IsoTileTypeIndex_1, int IsoTileTypeIndex_2, char a3, int a4, _BYTE *a5, char a6)
{
  ObjectTypeClass *CurrentBuildingType; // ebp
  int Width; // edi
  int v8; // ecx
  __int16 v9; // ax
  int v10; // ecx
  int v11; // eax
  int Width_1; // edx
  unsigned int n0x40000; // eax
  CellClass *p_MapClass::InvalidCell; // esi
  int Height; // ebx
  int v16; // ebp
  int v17; // eax
  int v18; // edi
  int n41_2; // eax
  int n41_3; // ecx
  __int64 v21; // rax
  int n3; // eax
  int n41; // edi
  int n41_1; // ebp
  int IsoTileTypeIndex; // eax
  int v26; // ecx
  int v28; // eax
  ObjectTypeClass *CurrentBuildingType_1; // [esp+10h] [ebp-1Ch]
  int v30; // [esp+14h] [ebp-18h]
  int p_n8; // [esp+18h] [ebp-14h] BYREF
  int v32; // [esp+1Ch] [ebp-10h]
  int p_n8_1; // [esp+20h] [ebp-Ch]
  SHPStruct *v34; // [esp+24h] [ebp-8h]
  int v35; // [esp+28h] [ebp-4h]

  if ( MouseClass::Instance.CurrentBuildingType->WhatAmI(MouseClass::Instance.CurrentBuildingType) != AbstractType_IsotileType ) /*0x57b455*/
    return 0; /*0x57b455*/
  if ( a6 ) /*0x57b461*/
    a4 = 0; /*0x57b463*/
  CurrentBuildingType = MouseClass::Instance.CurrentBuildingType; /*0x57b46b*/
  CurrentBuildingType_1 = MouseClass::Instance.CurrentBuildingType; /*0x57b473*/
  v34 = MouseClass::Instance.CurrentBuildingType->GetImage(MouseClass::Instance.CurrentBuildingType); /*0x57b482*/
  if ( !v34 ) /*0x57b486*/
    return 0; /*0x57b486*/
  v30 = 0; /*0x57b492*/
  if ( *&CurrentBuildingType[1].UINameLabel[23] <= 0 ) /*0x57b49c*/
    return 1; /*0x57b70e*/
  Width = MouseClass::Instance.MapRect.Width; /*0x57b4a2*/
  while ( 1 ) /*0x57b4a8*/
  {
    v8 = *&CurrentBuildingType[1].UINameLabel[19]; /*0x57b4a8*/
    v9 = 0; /*0x57b4ae*/
    v32 = 0; /*0x57b4b2*/
    if ( v8 > 0 ) /*0x57b4b6*/
      break; /*0x57b4b6*/
LABEL_39:
    if ( ++v30 >= *&CurrentBuildingType[1].UINameLabel[23] ) /*0x57b6a4*/
      return 1; /*0x57b6b3*/
  }
  while ( 1 ) /*0x57b4d0*/
  {
    LOWORD(p_n8_1) = v9 + MouseClass::Instance.CurrentFoundation_CenterCell.X; /*0x57b4d0*/
    v10 = (v9 + MouseClass::Instance.CurrentFoundation_CenterCell.X); /*0x57b4d5*/
    HIWORD(p_n8_1) = MouseClass::Instance.CurrentFoundation_CenterCell.Y + v30; /*0x57b4d8*/
    v11 = (MouseClass::Instance.CurrentFoundation_CenterCell.Y + v30); /*0x57b4e1*/
    p_n8 = p_n8_1; /*0x57b4e4*/
    Width_1 = v10 + v11; /*0x57b4e8*/
    if ( Width_1 <= Width /*0x57b516*/
      || v10 - v11 >= Width
      || v11 - v10 >= Width
      || Width_1 > Width + 2 * MouseClass::Instance.MapRect.Height )
    {
      goto LABEL_38; /*0x57b516*/
    }
    n0x40000 = v10 + (v11 << 9); /*0x57b51f*/
    if ( n0x40000 >= 0x40000 || (p_MapClass::InvalidCell = MouseClass::Instance.Cells.Items[n0x40000]) == 0 ) /*0x57b535*/
    {
      MapClass::InvalidCell.MapCoords = p_n8_1; /*0x57b537*/
      p_MapClass::InvalidCell = &MapClass::InvalidCell; /*0x57b53d*/
    }
    Height = v32 + v30 * *&CurrentBuildingType[1].UINameLabel[19]; /*0x57b555*/
    v35 = *(&v34[2].Type + Height); /*0x57b55d*/
    v16 = v35; /*0x57b557*/
    if ( v35 ) /*0x57b561*/
      break; /*0x57b561*/
LABEL_37:
    CurrentBuildingType = CurrentBuildingType_1; /*0x57b678*/
LABEL_38:
    v26 = *&CurrentBuildingType[1].UINameLabel[19]; /*0x57b67c*/
    v9 = ++v32; /*0x57b686*/
    if ( v32 >= v26 ) /*0x57b68d*/
      goto LABEL_39; /*0x57b68d*/
  }
  v17 = sub_5A00C0(&p_n8); /*0x57b571*/
  if ( a6 ) /*0x57b57c*/
  {
    v17 = 0; /*0x57b57e*/
LABEL_18:
    v18 = a4; /*0x57b580*/
    goto LABEL_19; /*0x57b580*/
  }
  if ( v17 <= 0 ) /*0x57b5e0*/
    goto LABEL_18; /*0x57b5e0*/
  v18 = a4; /*0x57b5e2*/
  if ( v17 == a4 ) /*0x57b5e8*/
    goto LABEL_20; /*0x57b5e8*/
  if ( a4 != -1 ) /*0x57b5ed*/
  {
    n41 = p_MapClass::InvalidCell->IsoTileTypeIndex - dword_ABAD28; /*0x57b603*/
    n41_1 = CurrentBuildingType_1[1].AbstractTypeClass::AbstractClass::IPersistStream::IPersist::IUnknown::__vftable /*0x57b605*/
          - dword_ABAD28;
    if ( !sub_486380(p_MapClass::InvalidCell) ) /*0x57b60e*/
    {
      if ( n41 < 0 || n41_1 < 0 || n41 > 41 || n41_1 > 41 || dword_82A7F4[n41] != dword_82A7F4[n41_1] ) /*0x57b703*/
      {
        *a5 = 0; /*0x57b718*/
        return 0; /*0x57b721*/
      }
      return 1; /*0x57b703*/
    }
    sub_5A0090(&p_n8, a4); /*0x57b623*/
    v16 = v35; /*0x57b628*/
    goto LABEL_32; /*0x57b628*/
  }
LABEL_19:
  if ( v17 == v18 ) /*0x57b586*/
  {
LABEL_20:
    n41_2 = p_MapClass::InvalidCell->IsoTileTypeIndex - dword_ABAD28; /*0x57b58c*/
    n41_3 = CurrentBuildingType_1[1].AbstractTypeClass::AbstractClass::IPersistStream::IPersist::IUnknown::__vftable /*0x57b5a1*/
          - dword_ABAD28;
    if ( n41_2 >= 0 && n41_3 >= 0 && n41_2 <= 41 && n41_3 <= 41 ) /*0x57b5b7*/
    {
      v21 = dword_82A89C[n41_2] - dword_82A89C[n41_3]; /*0x57b5c9*/
      n3 = (HIDWORD(v21) ^ v21) - HIDWORD(v21); /*0x57b5cc*/
      if ( n3 >= 3 && n3 <= 5 ) /*0x57b5d6*/
      {
        *a5 = 0; /*0x57b72b*/
        return 0; /*0x57b734*/
      }
    }
    goto LABEL_32; /*0x57b5d6*/
  }
  if ( !sub_486380(p_MapClass::InvalidCell) ) /*0x57b6bf*/
  {
    if ( v18 != -1 ) /*0x57b6d9*/
      goto LABEL_58; /*0x57b6d9*/
    goto LABEL_36; /*0x57b6d9*/
  }
  sub_5A0090(&p_n8, v18); /*0x57b6cc*/
LABEL_32:
  if ( sub_486380(p_MapClass::InvalidCell) /*0x57b64a*/
    || (IsoTileTypeIndex = p_MapClass::InvalidCell->IsoTileTypeIndex, IsoTileTypeIndex >= IsoTileTypeIndex_1)
    && IsoTileTypeIndex <= IsoTileTypeIndex_2 )
  {
    p_MapClass::InvalidCell->IsoTileTypeIndex = CurrentBuildingType_1[1].AbstractTypeClass::AbstractClass::IPersistStream::IPersist::IUnknown::__vftable; /*0x57b65e*/
    p_MapClass::InvalidCell->Height = Height; /*0x57b661*/
    p_MapClass::InvalidCell->Level = a3 + *(v16 + 40); /*0x57b66c*/
LABEL_36:
    Width = MouseClass::Instance.MapRect.Width; /*0x57b672*/
    goto LABEL_37; /*0x57b672*/
  }
  if ( sub_4865B0(p_MapClass::InvalidCell) /*0x57b774*/
    && sub_578D80(
         CurrentBuildingType_1[1].AbstractTypeClass::AbstractClass::IPersistStream::IPersist::IUnknown::__vftable,
         Height)
    || (v28 = CurrentBuildingType_1[1].AbstractTypeClass::AbstractClass::IPersistStream::IPersist::IUnknown::__vftable,
        v28 >= dword_ABAD28)
    && v28 < dword_ABAD28 + 42
    && sub_4863D0(p_MapClass::InvalidCell) )
  {
LABEL_58:
    *a5 = 0; /*0x57b77d*/
  }
  return 0; /*0x57b6aa*/
}