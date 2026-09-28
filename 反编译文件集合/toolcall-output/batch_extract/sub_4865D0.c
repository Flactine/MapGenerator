bool __thiscall sub_4865D0(_DWORD *this)
{
  int IsoTileTypeIndex; // eax

  IsoTileTypeIndex = this[14]; /*0x4865d0*/
  if ( IsoTileTypeIndex >= IsoTileTypeIndex_1 && IsoTileTypeIndex < IsoTileTypeIndex_1 + 42 ) /*0x4865e2*/
    return 1; /*0x4865e4*/
  return IsoTileTypeIndex >= nIdx && IsoTileTypeIndex < nIdx + 14 /*0x48663a*/
      || IsoTileTypeIndex >= IsoTileTypeIndex_2 && IsoTileTypeIndex < IsoTileTypeIndex_2 + 4
      || IsoTileTypeIndex >= IsoTileTypeIndex_3 && IsoTileTypeIndex < IsoTileTypeIndex_3 + 4
      || IsoTileTypeIndex >= IsoTileTypeIndex_4 && IsoTileTypeIndex < IsoTileTypeIndex_4 + 4
      || IsoTileTypeIndex >= IsoTileTypeIndex_5 && IsoTileTypeIndex < IsoTileTypeIndex_5 + 4;
}