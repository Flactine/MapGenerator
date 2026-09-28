// ============================================================================
// 4A8BF0_4A91B0_DisplayClass.c  --  DisplayClass（MouseClass）相关辅助
//
//   sub_4A8BF0   入口清理：鼠标/建筑预览状态复位（sub_57A0C0 第一步调用）
//   sub_4A91B0   坐标换算：把目标格换算为显示层当前格（sub_57ACF0 LABEL_71 调用）
//
// 两者都操作 DisplayClass 的“建筑预览”状态（CurrentFoundation_CenterCell /
// _TopLeftOffset / _Data，偏移 +0x1174/+0x1178/+0x117C）。该状态不写 CellClass
// 的地形字段，只改 AltFlags（bit 0x2 = ContainsBuilding）与 UI 预览。
// 生成器自带一份等价状态（MapGen.h 的 FoundationPreviewState）并完整复刻了
// sub_4A8BF0 与 sub_4A95A0，不再是空实现。
// ============================================================================


// ----------------------------------------------------------------------------
// sub_4A8BF0  --  建筑预览/鼠标状态复位
//   this = DisplayClass*（&MouseClass::Instance）
//   src_1 = 建筑图像数据（sub_57A0C0 传 0）
//   传 0 时: 清 *(this+4476)（当前预览对象指针）并复位偏移 *(this+4472)
// ----------------------------------------------------------------------------
int __thiscall sub_4A8BF0(int this, const void *src_1)
{
  int result; // eax
  __int16 v4; // cx
  const void *src; // esi
  bool v6; // zf
  int v7; // eax
  __int16 src_2; // cx
  __int16 src_3; // [esp+8h] [ebp-8h] BYREF
  __int16 v10; // [esp+Ah] [ebp-6h]

  result = *(this + 4476); /*0x4a8bf7*/
  if ( result ) /*0x4a8bff*/
  {
    v4 = *(this + 4470) + *(this + 4474); /*0x4a8c16*/
    src_3 = *(this + 4468) + *(this + 4472); /*0x4a8c1f*/
    v10 = v4; /*0x4a8c24*/
    result = sub_4A95A0(&src_3, 0); /*0x4a8c38*/
  }
  src = src_1; /*0x4a8c3d*/
  v6 = src_1 == 0; /*0x4a8c47*/
  *(this + 4472) = dword_8A03F8; /*0x4a8c49*/
  if ( v6 ) /*0x4a8c4f*/
  {
    *(this + 4476) = 0; /*0x4a8d1f*/
  }
  else
  {
    if ( (byte_8A0618 & 1) == 0 ) /*0x4a8c5c*/
    {
      byte_8A0618 |= 1u; /*0x4a8c68*/
      atexit(nullsub_10); /*0x4a8c6e*/
    }
    qmemcpy(&dst_, src, 0x1E0u); /*0x4a8c85*/
    *(this + 4476) = &dst_; /*0x4a8c8f*/
    v7 = *sub_4A94F0(&src_1, &dst_); /*0x4a8c9e*/
    src_3 = v7 - 1; /*0x4a8ca6*/
    v10 = HIWORD(v7) - 1; /*0x4a8cab*/
    LOWORD(src_1) = (1 - v7) / 2; /*0x4a8cc4*/
    HIWORD(src_1) = (1 - HIWORD(v7)) / 2; /*0x4a8cd1*/
    src_2 = src_1; /*0x4a8cd6*/
    *(this + 4472) = src_1; /*0x4a8cda*/
    LOWORD(v7) = *(this + 4474) + *(this + 4470); /*0x4a8cee*/
    LOWORD(src_1) = src_2 + *(this + 4468); /*0x4a8cf8*/
    HIWORD(src_1) = v7; /*0x4a8cfd*/
    return sub_4A95A0(&src_1, 1); /*0x4a8d11*/
  }
  return result; /*0x4a8d17*/
}


// ----------------------------------------------------------------------------
// sub_4A91B0  --  目标格 → 显示层当前格换算
//   this = DisplayClass*，a2 = 输出 CellStruct*，p_src = 输入打包坐标*
//   返回 a2（换算后的格子坐标）
//
// 简化说明（复刻 SmoothWaterBody 时）:
//   sub_57ACF0 调用它只是为了把"水岸瓦片将落在的格"登记到 DisplayClass 的
//   当前格状态上，属于 UI 预览簿记，不改变 CellClass 数据。
//   若不需要像素级还原 UI，可直接跳过或空实现。
// ----------------------------------------------------------------------------
CellStruct *__thiscall sub_4A91B0(DisplayClass *this, CellStruct *a2, _DWORD *p_src)
{
  _DWORD *p_src_1; // ebp
  bool v4; // zf
  Point2D *v6; // eax
  int X; // edi
  int Y; // ebx
  Point2D *v9; // ecx
  int X_1; // eax
  int Y_1; // ecx
  Point2D *v12; // eax
  _DWORD *p_src_2; // eax
  Point2D *v14; // eax
  int Y_2; // ecx
  CellStruct *CurrentFoundation_Data; // eax
  CellStruct CurrentFoundation_CenterCell_1; // ecx
  CellStruct *result; // eax
  __int16 v19; // dx
  _WORD *v20; // eax
  __int16 v21; // dx
  CellStruct CurrentFoundation_CenterCell; // ebx
  __int16 v23; // ax
  __int16 v24; // ax
  __int16 v25; // cx
  CellStruct *CurrentFoundation_Data_1; // edx
  __int16 v27; // ax
  _DWORD *p_src_3; // [esp+10h] [ebp-14h] BYREF
  int X_2; // [esp+14h] [ebp-10h] BYREF
  int Y_3; // [esp+18h] [ebp-Ch]
  _BYTE v31[8]; // [esp+1Ch] [ebp-8h] BYREF

  p_src_1 = *p_src; /*0x4a91ba*/
  v4 = *p_src == ::p_src; /*0x4a91bd*/
  p_src = *p_src; /*0x4a91c6*/
  if ( v4 && HIWORD(p_src) == HIWORD(::p_src) ) /*0x4a91dc*/
  {
    v6 = WWMouseClass::Instance->GetCoords(WWMouseClass::Instance, &X_2); /*0x4a91ef*/
    X = DSurface::ViewBounds.X; /*0x4a91f2*/
    Y = DSurface::ViewBounds.Y; /*0x4a91f8*/
    v9 = v6; /*0x4a91fe*/
    X_1 = v6->X; /*0x4a9200*/
    Y_1 = v9->Y; /*0x4a9204*/
    if ( X_1 < DSurface::ViewBounds.X /*0x4a9223*/
      || X_1 >= DSurface::ViewBounds.X + DSurface::ViewBounds.Width
      || Y_1 < DSurface::ViewBounds.Y
      || Y_1 >= DSurface::ViewBounds.Y + DSurface::ViewBounds.Height )
    {
      v14 = WWMouseClass::Instance->GetCoords(WWMouseClass::Instance, v31); /*0x4a9284*/
      Y_2 = v14->Y; /*0x4a9292*/
      X_2 = v14->X - X; /*0x4a9295*/
      Y_3 = Y_2 - Y; /*0x4a929f*/
      p_src_1 = *sub_6D6590(&p_src, &X_2); /*0x4a92af*/
    }
    else
    {
      v12 = WWMouseClass::Instance->GetCoords(WWMouseClass::Instance, v31); /*0x4a9232*/
      X_2 = v12->X; /*0x4a9237*/
      Y_3 = v12->Y; /*0x4a924d*/
      p_src_2 = *sub_653760(&p_src_3, &X_2); /*0x4a9256*/
      p_src_3 = p_src_2; /*0x4a925f*/
      if ( p_src_2 == ::p_src ) /*0x4a9263*/
        goto LABEL_11; /*0x4a9263*/
      p_src_1 = p_src_2; /*0x4a9273*/
    }
    p_src = p_src_1; /*0x4a92b1*/
  }
LABEL_11:
  CurrentFoundation_Data = this->CurrentFoundation_Data; /*0x4a92b5*/
  if ( CurrentFoundation_Data ) /*0x4a92bd*/
  {
    if ( !Unsorted::ArmageddonMode ) /*0x4a92e3*/
    {
      v19 = HIWORD(p_src) + this->CurrentFoundation_TopLeftOffset.Y; /*0x4a92f3*/
      LOWORD(p_src_3) = p_src_1 + this->CurrentFoundation_TopLeftOffset.X; /*0x4a92fb*/
      HIWORD(p_src_3) = v19; /*0x4a9301*/
      v20 = sub_6DA360(&X_2, &p_src_3, CurrentFoundation_Data); /*0x4a931e*/
      v21 = v20[1] - this->CurrentFoundation_TopLeftOffset.Y; /*0x4a9331*/
      LOWORD(p_src) = *v20 - this->CurrentFoundation_TopLeftOffset.X; /*0x4a9338*/
      HIWORD(p_src) = v21; /*0x4a933d*/
      p_src_1 = p_src; /*0x4a9342*/
    }
    v4 = p_src_1 == this->CurrentFoundation_CenterCell.X; /*0x4a9346*/
    p_src = p_src_1; /*0x4a934d*/
    if ( v4 && HIWORD(p_src_1) == this->CurrentFoundation_CenterCell.Y ) /*0x4a935f*/
    {
      result = a2; /*0x4a9361*/
      *a2 = p_src_1; /*0x4a9367*/
    }
    else
    {
      CurrentFoundation_CenterCell = this->CurrentFoundation_CenterCell; /*0x4a9377*/
      if ( this->CurrentFoundation_Data ) /*0x4a9371*/
      {
        if ( p_src_1 != *&this->CurrentFoundation_CenterCell && *&this->CurrentFoundation_CenterCell != ::p_src ) /*0x4a93a0*/
        {
          v23 = this->CurrentFoundation_CenterCell.Y + this->CurrentFoundation_TopLeftOffset.Y; /*0x4a93c7*/
          LOWORD(p_src) = this->CurrentFoundation_CenterCell.X + this->CurrentFoundation_TopLeftOffset.X; /*0x4a93d0*/
          HIWORD(p_src) = v23; /*0x4a93d5*/
          sub_4A95A0(&p_src, 0); /*0x4a93e9*/
        }
        if ( p_src_1 != ::p_src ) /*0x4a93f5*/
        {
          v24 = this->CurrentFoundation_TopLeftOffset.X + p_src_1; /*0x4a940a*/
          HIWORD(p_src) = HIWORD(p_src_1) + this->CurrentFoundation_TopLeftOffset.Y; /*0x4a9414*/
          LOWORD(p_src) = v24; /*0x4a941b*/
          sub_4A95A0(&p_src, 1); /*0x4a942f*/
        }
      }
      this->CurrentFoundation_CenterCell = p_src_1; /*0x4a9434*/
      v25 = this->CurrentFoundation_TopLeftOffset.X + p_src_1; /*0x4a944b*/
      HIWORD(p_src) = this->CurrentFoundation_CenterCell.Y + this->CurrentFoundation_TopLeftOffset.Y; /*0x4a9452*/
      CurrentFoundation_Data_1 = this->CurrentFoundation_Data; /*0x4a9457*/
      LOWORD(p_src) = v25; /*0x4a945d*/
      this->CurrentFoundation_InAdjacent = sub_4A8EB0( /*0x4a9485*/
                                             this->CurrentBuildingType,
                                             this->CurrentBuildingTypeArrayIndex,
                                             CurrentFoundation_Data_1,
                                             &p_src);
      v27 = this->CurrentFoundation_TopLeftOffset.Y + this->CurrentFoundation_CenterCell.Y; /*0x4a94a0*/
      LOWORD(p_src) = this->CurrentFoundation_CenterCell.X + this->CurrentFoundation_TopLeftOffset.X; /*0x4a94a7*/
      HIWORD(p_src) = v27; /*0x4a94b0*/
      this->CurrentFoundation_NoShrouded = sub_4A9070( /*0x4a94da*/
                                             this->CurrentBuildingType,
                                             this->CurrentBuildingTypeArrayIndex,
                                             this->CurrentFoundation_Data,
                                             &p_src);
      result = a2; /*0x4a94e0*/
      *a2 = CurrentFoundation_CenterCell; /*0x4a94e6*/
    }
  }
  else
  {
    CurrentFoundation_CenterCell_1 = this->CurrentFoundation_CenterCell; /*0x4a92bf*/
    result = a2; /*0x4a92c5*/
    this->CurrentFoundation_CenterCell = p_src_1; /*0x4a92c9*/
    *a2 = CurrentFoundation_CenterCell_1; /*0x4a92d2*/
  }
  return result; /*0x4a92cf*/
}