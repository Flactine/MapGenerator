// ============================================================================
// sub_57B210  --  瓦片邻接掩码计算（核心判定）
// 地址: 0x57B210   签名: int __thiscall sub_57B210(_DWORD *this, int a2, int a3)
//   this = CellClass*（IDA 显示为 _DWORD*）
//   a2   = 传入坐标打包（低16=X，高16=Y），实际取 *(a2+36) 即 cell->MapCoords
//   a3   = 模式: 0 = 常规连通掩码；1 = 反向掩码；2 = 返回瓦片形态码
// 返回: 掩码 / 形态码 / 0
//
// 要点:
//   - 菱形四条件判定（W' < x+y <= W'+2H' 且 |x-y| < W'），越界返回 0。
//   - a3 == 1 时，若该格瓦片已在 [nIdx, nIdx+14) 内，返回 0。
//   - a3 == 0 时，若 sub_486380(cell)（瓦片为 0 或 0xFFFF）为假则返回 0。
//   - 读 WorkCell +74 有效标志，为 0 返回 0。
//   - 读 WorkCell +64 处理标记: >= 0 时直接返回该值（已缓存）。
//   - 否则按 8 邻（用 Cells.Items 线性索引 ±1 / ±2 / ±510 / ±512）
//     逐位构造掩码 n64:
//         bit 0x40 / 0x80 / 0x01 / 0x20 / 0x02 / 0x10 / 0x08 / 0x04
//      判定规则: 邻格非空且 sub_485060(邻格)（是水）→ 置位；
//                或邻格为空且 v32（本格 sub_485060）为真 → 置位。
//   - v32 = sub_485060(a2)（本格是否水瓦片）。
// ============================================================================

int __thiscall sub_57B210(_DWORD *this, int a2, int a3)
{
  int nIdx; // ebx
  int v5; // esi
  int IsoTileTypeIndex; // eax
  int result; // eax
  int nIdx_1; // eax
  int v9; // eax
  int v10; // edx
  int v11; // esi
  int v12; // ecx
  _DWORD *v13; // esi
  char v14; // bl
  int n64; // edi
  int v16; // ecx
  _DWORD *v17; // esi
  int v18; // ecx
  _DWORD *v19; // esi
  int v20; // ecx
  _DWORD *v21; // esi
  int v22; // ecx
  _DWORD *v23; // esi
  int v24; // ecx
  _DWORD *v25; // esi
  int v26; // ecx
  _DWORD *v27; // esi
  int v28; // ecx
  _DWORD *v29; // esi
  int nIdx_2; // [esp+18h] [ebp-8h]
  char v32; // [esp+24h] [ebp+4h]

  nIdx = ::nIdx; /*0x57b214*/
  v5 = *(a2 + 36); /*0x57b224*/
  nIdx_2 = ::nIdx + 14; /*0x57b239*/
  v32 = sub_485060(a2); /*0x57b248*/
  IsoTileTypeIndex = SHIWORD(v5) + v5; /*0x57b254*/
  if ( IsoTileTypeIndex <= IsoTileTypeIndex_0 /*0x57b271*/
    || v5 - SHIWORD(v5) >= IsoTileTypeIndex_0
    || SHIWORD(v5) - v5 >= IsoTileTypeIndex_0
    || IsoTileTypeIndex > IsoTileTypeIndex_1 )
  {
    return 0; /*0x57b27c*/
  }
  if ( a3 ) /*0x57b285*/
  {
    if ( a3 == 1 ) /*0x57b2a1*/
    {
      nIdx_1 = *(a2 + 56); /*0x57b2a3*/
      if ( nIdx_1 >= nIdx && nIdx_1 < nIdx_2 ) /*0x57b2ae*/
        return 0; /*0x57b2b9*/
    }
  }
  else if ( !sub_486380(a2) ) /*0x57b289*/
  {
    return 0; /*0x57b29b*/
  }
  a3 = *(a2 + 36); /*0x57b2c3*/
  v9 = sub_58C2A0(&a3); /*0x57b2c7*/
  if ( !*(v9 + 74) ) /*0x57b2cc*/
    return 0; /*0x57b2d6*/
  result = *(v9 + 64); /*0x57b2df*/
  if ( result < 0 ) /*0x57b2e4*/
  {
    v10 = this[79]; /*0x57b2f1*/
    v11 = v5 + (SHIWORD(v5) << 9); /*0x57b2f7*/
    v12 = *(v10 + 4 * v11 - 2052); /*0x57b2f9*/
    v13 = (v10 + 4 * v11 - 2052); /*0x57b300*/
    if ( v12 && sub_485060(v12) ) /*0x57b30b*/
    {
      v14 = v32; /*0x57b328*/
      n64 = 64; /*0x57b32c*/
    }
    else if ( *v13 ) /*0x57b314*/
    {
      n64 = 0; /*0x57b333*/
      v14 = v32; /*0x57b337*/
    }
    else
    {
      v14 = v32; /*0x57b319*/
      if ( v32 ) /*0x57b31f*/
        n64 = 64; /*0x57b321*/
      else
        n64 = 0; /*0x57b33d*/
    }
    v16 = v13[1]; /*0x57b341*/
    v17 = v13 + 1; /*0x57b344*/
    if ( v16 && sub_485060(v16) || !*v17 && v14 ) /*0x57b35b*/
      n64 |= 0x80u; /*0x57b35d*/
    v18 = v17[1]; /*0x57b363*/
    v19 = v17 + 1; /*0x57b366*/
    if ( v18 && sub_485060(v18) || !*v19 && v14 ) /*0x57b37d*/
      n64 |= 1u; /*0x57b37f*/
    v20 = v19[510]; /*0x57b382*/
    v21 = v19 + 510; /*0x57b388*/
    if ( v20 && sub_485060(v20) || !*v21 && v14 ) /*0x57b3a2*/
      n64 |= 0x20u; /*0x57b3a4*/
    v22 = v21[2]; /*0x57b3a7*/
    v23 = v21 + 2; /*0x57b3aa*/
    if ( v22 && sub_485060(v22) || !*v23 && v14 ) /*0x57b3c1*/
      n64 |= 2u; /*0x57b3c3*/
    v24 = v23[510]; /*0x57b3c6*/
    v25 = v23 + 510; /*0x57b3cc*/
    if ( v24 && sub_485060(v24) || !*v25 && v14 ) /*0x57b3e6*/
      n64 |= 0x10u; /*0x57b3e8*/
    v26 = v25[1]; /*0x57b3eb*/
    v27 = v25 + 1; /*0x57b3ee*/
    if ( v26 && sub_485060(v26) || !*v27 && v14 ) /*0x57b405*/
      n64 |= 8u; /*0x57b407*/
    v28 = v27[1]; /*0x57b40a*/
    v29 = v27 + 1; /*0x57b40d*/
    if ( v28 && sub_485060(v28) || !*v29 && v14 ) /*0x57b424*/
      return n64 | 4; /*0x57b426*/
    return n64; /*0x57b429*/
  }
  return result; /*0x57b273*/
}