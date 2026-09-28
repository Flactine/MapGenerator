// ============================================================================
// helpers.c  --  SmoothWaterBody 调用树中的小工具函数合集
//
// 包含:
//   sub_58C2A0   WorkCell 二维访问器（按菱形坐标 x, y）
//   sub_58C2C0   WorkCell 线性访问器（按序号 i）
//   sub_58BDC0   WorkCell 构造（80 字节清零 + data[16]=-1 + byte74=1）
//   sub_5A00C0   读 WorkCell data[14]（生成代号）
//   sub_5A0090   写 WorkCell data[14]
//   sub_485060   "该格是否为水瓦片"判定
//   sub_486380   "该格是否为占位瓦片"判定（0 或 0xFFFF）
//   sub_598030   RandomFloatRange（消耗全局 RNG）
//   MapClass::GetCellAt_MapCrd   按坐标取格（越界返回 InvalidCell）
//   CellClass::GetNeighbourCell  取 8 邻格
// ============================================================================


// ----------------------------------------------------------------------------
// sub_58C2A0  --  WorkCell 二维访问器
//   返回 dword_ABED10 + 80*x + 80*workSide*y
//   this 指向 CellStruct { int16 X; int16 Y; }
// ----------------------------------------------------------------------------
char *__thiscall sub_58C2A0(__int16 *this)
{
  return dword_ABED10 + 80 * *this + 80 * dword_89C2DC * this[1]; /*0x58c2be*/
}


// ----------------------------------------------------------------------------
// sub_58C2C0  --  WorkCell 线性访问器
//   返回 dword_ABED10 + 80*i
// ----------------------------------------------------------------------------
char *__fastcall sub_58C2C0(int a1)
{
  return dword_ABED10 + 80 * a1; /*0x58c2ce*/
}


// ----------------------------------------------------------------------------
// sub_58BDC0  --  WorkCell 构造（单格初始化）
//   this[0..15] = 0，this[16] = -1（处理标记），byte68..73 = 0，
//   byte74 = 1（有效标志），byte75 = 0
//   注: 反编译里 *(this+68) 等是字节偏移写法，this 为 _DWORD*，
//       故 (this+68) 实为第 68 个字节。
// ----------------------------------------------------------------------------
_DWORD *__thiscall sub_58BDC0(_DWORD *this)
{
  _DWORD *result; // eax

  result = this; /*0x58bdc0*/
  this[2] = 0; /*0x58bdc4*/
  this[4] = 0; /*0x58bdc7*/
  this[6] = 0; /*0x58bdca*/
  this[8] = 0; /*0x58bdcd*/
  this[10] = 0; /*0x58bdd0*/
  this[12] = 0; /*0x58bdd3*/
  *this = 0; /*0x58bdd6*/
  *(this + 1) = 0; /*0x58bdd9*/
  this[3] = 0; /*0x58bddd*/
  this[5] = 0; /*0x58bde0*/
  this[7] = 0; /*0x58bde3*/
  this[9] = 0; /*0x58bde6*/
  this[11] = 0; /*0x58bde9*/
  this[13] = 0; /*0x58bdec*/
  this[14] = 0; /*0x58bdef*/
  this[15] = 0; /*0x58bdf2*/
  this[16] = -1; /*0x58bdf5*/
  *(this + 68) = 0; /*0x58bdfc*/
  *(this + 69) = 0; /*0x58bdff*/
  *(this + 70) = 0; /*0x58be02*/
  *(this + 71) = 0; /*0x58be05*/
  *(this + 72) = 0; /*0x58be08*/
  *(this + 73) = 0; /*0x58be0b*/
  *(this + 74) = 1; /*0x58be0e*/
  *(this + 75) = 0; /*0x58be12*/
  return result; /*0x58be15*/
}


// ----------------------------------------------------------------------------
// sub_5A00C0  --  读该格 WorkCell 的生成代号 (data[14]，字节偏移 56)
//   工作数组为空时返回 -1
// ----------------------------------------------------------------------------
int __stdcall sub_5A00C0(int *p_n8)
{
  if ( dword_ABED10 ) /*0x5a00c8*/
    return *(dword_ABED10 + 20 * *p_n8 + 20 * dword_89C2DC * *(p_n8 + 1) + 14); /*0x5a00ea*/
  else
    return -1; /*0x5a00ca*/
}


// ----------------------------------------------------------------------------
// sub_5A0090  --  写该格 WorkCell 的生成代号 (字节偏移 56)
// ----------------------------------------------------------------------------
int __stdcall sub_5A0090(int *p_n8, int a2)
{
  int result; // eax

  if ( dword_ABED10 ) /*0x5a0098*/
  {
    result = 80 * (*p_n8 + dword_89C2DC * *(p_n8 + 1)); /*0x5a00b5*/
    *(dword_ABED10 + result + 56) = a2; /*0x5a00b8*/
  }
  return result; /*0x5a00bc*/
}


// ----------------------------------------------------------------------------
// sub_485060  --  该格是否为水瓦片
//   返回 IsoTileTypeIndex ∈ [nIdx, nIdx + 14)
//   注: 此函数用的是 this[14]（即 CellClass 偏移 56 处的 int），
//       在 CellClass 上偏移 56 即 IsoTileTypeIndex。
// ----------------------------------------------------------------------------
BOOL __thiscall sub_485060(_DWORD *this)
{
  int nIdx; // eax

  nIdx = this[14]; /*0x485060*/
  return nIdx >= ::nIdx && nIdx < ::nIdx + 14; /*0x485079*/
}


// ----------------------------------------------------------------------------
// sub_486380  --  该格是否为占位瓦片（0 或 0xFFFF）
// ----------------------------------------------------------------------------
bool __thiscall sub_486380(_DWORD *this)
{
  int n0xFFFF; // eax

  n0xFFFF = this[14]; /*0x486380*/
  return n0xFFFF == 0xFFFF || !n0xFFFF; /*0x486390*/
}


// ----------------------------------------------------------------------------
// sub_598030  --  RandomFloatRange(lo, hi)
//   取 [lo, hi] 内整数，浮点缩放 + 上界拒绝采样，消耗全局 RNG
//   注: 项目内对应 R250Random::RandomFloatRange
// ----------------------------------------------------------------------------
__int64 __fastcall sub_598030(int a1, unsigned int a2)
{
  double v3; // st7
  __int64 result; // rax
  __int64 v5; // [esp+8h] [ebp-18h]
  __int64 v6; // [esp+8h] [ebp-18h]
  double v7; // [esp+18h] [ebp-8h]

  v5 = a2 - a1 + 1; /*0x59803e*/
  v3 = v5; /*0x598046*/
  LODWORD(v5) = a1; /*0x59804a*/
  v7 = v5; /*0x59805a*/
  do /*0x598089*/
  {
    v6 = Randomizer::Random(&dword_ABE890); /*0x598068*/
    result = Game::F2I64(v6 * v3 * 2.328306437080797e-10 + v7); /*0x598082*/
  }
  while ( result > a2 ); /*0x598089*/
  return result; /*0x59808b*/
}


// ----------------------------------------------------------------------------
// MapClass::GetCellAt_MapCrd  --  按坐标取格
//   线性索引 = X + (Y << 9)；越界或空槽返回 MapClass::InvalidCell
// ----------------------------------------------------------------------------
CellClass *__thiscall MapClass::GetCellAt_MapCrd(MapClass *this_pMap, CellStruct *pMapCoord)
{
  unsigned int idx; // eax
  CellClass *p_MapClass::InvalidCell; // eax

  idx = pMapCoord->X + (pMapCoord->Y << 9); /*0x5657af*/
  if ( idx >= 0x40000 || (p_MapClass::InvalidCell = this_pMap->Cells.Items[idx]) == 0 ) /*0x5657c6*/
  {
    p_MapClass::InvalidCell = &MapClass::InvalidCell; /*0x5657ca*/
    MapClass::InvalidCell.MapCoords = *pMapCoord; /*0x5657cf*/
  }
  return p_MapClass::InvalidCell; /*0x5657b1*/
}


// ----------------------------------------------------------------------------
// CellClass::GetNeighbourCell  --  取 8 邻格
//   nFacingType < 8 时用 Neighbours[nFacingType & 7] 偏移当前坐标，
//   否则原样返回自身
// ----------------------------------------------------------------------------
CellClass *__thiscall CellClass::GetNeighbourCell(CellClass *this, int nFacingType)
{
  CellClass *this_1; // eax
  __int16 v3; // ax
  CellStruct MapCoords; // [esp+0h] [ebp-4h]

  this_1 = this; /*0x481815*/
  if ( nFacingType < 8 ) /*0x48181a*/
  {
    MapCoords = this->MapCoords; /*0x481822*/
    v3 = MapCoords.Y + Neighbours[nFacingType & 7].Y; /*0x481839*/
    LOWORD(nFacingType) = MapCoords.X + Neighbours[nFacingType & 7].X; /*0x481841*/
    HIWORD(nFacingType) = v3; /*0x48184a*/
    return MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &nFacingType); /*0x48185d*/
  }
  return this_1; /*0x481863*/
}