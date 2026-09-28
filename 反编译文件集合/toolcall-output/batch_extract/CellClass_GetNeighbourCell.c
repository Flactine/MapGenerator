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