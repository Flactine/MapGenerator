// ============================================================================
// 578290_578350_CellIterator.c  --  菱形格子迭代器
//
//   sub_578350   复位（MapClass::CellIteratorReset）
//   MapClass::CellIteratorNext   推进并返回当前格
//
// 迭代顺序: 对角线 s = x+y 递增；每条对角线上 x 递增 / y 递减。
//           首个返回格为 (1, W')。
//           终止条件: 槽位为 nullptr（菱形之外）。
//
// 项目内对应: MapGen.h 中的 CellIterator::Reset / CellIterator::Next
// ============================================================================


// ----------------------------------------------------------------------------
// sub_578350  --  迭代器复位
//   NextX = 1, NextY = Width, CurrentY = Width-1,
//   NextCell = &Cells.Items[512*Width + 1]
// ----------------------------------------------------------------------------
CellClass *__thiscall sub_578350(MouseClass *this)
{
  int Width; // eax
  CellClass *CellIterator_NextCell; // eax

  Width = this->MapRect.Width; /*0x578350*/
  this->CellIterator_NextX = 1; /*0x578356*/
  this->CellIterator_NextY = Width; /*0x578360*/
  this->CellIterator_CurrentY = Width - 1; /*0x578369*/
  CellIterator_NextCell = &this->Cells.Items[512 * Width + 1]; /*0x578378*/
  this->CellIterator_NextCell = CellIterator_NextCell; /*0x57837c*/
  return CellIterator_NextCell; /*0x578382*/
}


// ----------------------------------------------------------------------------
// MapClass::CellIteratorNext  --  推进迭代器
//   CurrentY != 0: 沿当前对角线走一步
//       NextY -= 1; NextX += 1; CurrentY -= 1; NextCell -= 511
//   CurrentY == 0: 换到下一条对角线
//       交换 NextX/NextY，按 (NextY - Width + NextX - 1) & 1 的奇偶选择
//       对角线上剩余的推进次数（Width-1 或 Width-2），
//       NextCell = &Cells.Items[NextX + (NextY << 9)]
//   返回 *NextCell（旧槽位），为 nullptr 表示迭代结束
// ----------------------------------------------------------------------------
CellClass *__thiscall MapClass::CellIteratorNext(DisplayClass *this)
{
  int CellIterator_CurrentY; // eax
  CellClass **CellIterator_NextCell; // ebp
  int CellIterator_NextY; // edx
  int CellIterator_NextY_1; // edx
  int CellIterator_NextX; // eax
  int Width; // esi
  int CellIterator_CurrentY_1; // esi
  int CellIterator_NextX_1; // edx
  int v10; // eax

  CellIterator_CurrentY = this->CellIterator_CurrentY; /*0x578290*/
  CellIterator_NextCell = this->CellIterator_NextCell; /*0x578297*/
  if ( CellIterator_CurrentY ) /*0x5782a0*/
  {
    CellIterator_NextY = this->CellIterator_NextY - 1; /*0x5782af*/
    ++this->CellIterator_NextX; /*0x5782b1*/
    this->CellIterator_CurrentY = CellIterator_CurrentY - 1; /*0x5782b7*/
    this->CellIterator_NextY = CellIterator_NextY; /*0x5782c3*/
    this->CellIterator_NextCell = (CellIterator_NextCell - 511); /*0x5782c9*/
    return *CellIterator_NextCell; /*0x5782cf*/
  }
  else
  {
    CellIterator_NextY_1 = this->CellIterator_NextY; /*0x5782d5*/
    CellIterator_NextX = this->CellIterator_NextX; /*0x5782db*/
    Width = this->MapRect.Width; /*0x5782e1*/
    this->CellIterator_NextX = CellIterator_NextY_1; /*0x5782e8*/
    this->CellIterator_NextY = CellIterator_NextX; /*0x5782f2*/
    if ( ((CellIterator_NextY_1 - Width + CellIterator_NextX - 1) & 1) != 0 ) /*0x5782ff*/
    {
      CellIterator_CurrentY_1 = Width - 1; /*0x578302*/
      this->CellIterator_NextY = CellIterator_NextX + 1; /*0x578303*/
    }
    else
    {
      CellIterator_CurrentY_1 = Width - 2; /*0x57830c*/
      this->CellIterator_NextX = CellIterator_NextY_1 + 1; /*0x57830f*/
    }
    CellIterator_NextX_1 = this->CellIterator_NextX; /*0x57831b*/
    v10 = this->CellIterator_NextY << 9; /*0x578321*/
    this->CellIterator_CurrentY = CellIterator_CurrentY_1; /*0x578324*/
    this->CellIterator_NextCell = (&this->Cells.Items[CellIterator_NextX_1] + v10); /*0x578337*/
    return *CellIterator_NextCell; /*0x57833d*/
  }
}