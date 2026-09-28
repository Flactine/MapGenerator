CellClass *__thiscall sub_59A6C0(int *this)
{
  CellClass *i; // eax
  int v3; // eax
  int v4; // eax
  CellClass *j; // edi
  char v6; // bl
  int nFacingType; // esi
  CellClass *NeighbourCell; // eax
  int v9; // ecx
  int v10; // eax
  int k; // ebx
  _DWORD *v12; // esi
  int v13; // eax
  void *v14; // eax
  CellClass *result; // eax
  CellClass *m; // ebp
  int nFacingType_1; // esi
  CellClass *v18; // edi
  _DWORD *v19; // [esp+10h] [ebp-4h] BYREF

  sub_578350(&MouseClass::Instance);
  for ( i = MapClass::CellIteratorNext(&MouseClass::Instance); i; i = MapClass::CellIteratorNext(&MouseClass::Instance) )
    i->IsoTileTypeIndex = nIdx;
  v3 = this[15];
  if ( v3 )
  {
    v4 = v3 - 1;
    if ( v4 )
    {
      if ( v4 == 1 )
        sub_59B200(this);
    }
    else
    {
      sub_59AFA0(this);
    }
  }
  else
  {
    sub_59AD10(this);
  }
  sub_578350(&MouseClass::Instance);
  for ( j = MapClass::CellIteratorNext(&MouseClass::Instance); j; j = MapClass::CellIteratorNext(&MouseClass::Instance) )
  {
    if ( j->IsoTileTypeIndex == nIdx )
    {
      v6 = 1;
      for ( nFacingType = 0; nFacingType < 8; nFacingType += 2 )
      {
        NeighbourCell = CellClass::GetNeighbourCell(j, nFacingType);
        if ( !sub_486380(NeighbourCell) )
          v6 = 0;
      }
      if ( v6 )
        j->IsoTileTypeIndex = 0;
    }
  }
  sub_57A0C0(0, 0);
  if ( dword_ABED10 )
  {
    v9 = dword_89C2DC * dword_89C2DC;
    if ( dword_89C2DC * dword_89C2DC > 0 )
    {
      v10 = 0;
      do
      {
        *(dword_ABED10 + v10 + 56) = -1;
        *(dword_ABED10 + v10 + 60) = -1;
        v10 += 80;
        --v9;
      }
      while ( v9 );
    }
  }
  for ( k = dword_ABDFA0 - 1; k >= 0; --k )
  {
    v12 = *(dword_ABDF94 + k);
    if ( v12 )
    {
      if ( *v12 )
      {
        (***v12)(*v12, 1);
        *v12 = 0;
      }
      v19 = v12;
      v13 = (*(dword_ABDF90 + 16))(&dword_ABDF90, &v19);
      if ( v13 != -1 && v13 < dword_ABDFA0 && v13 < --dword_ABDFA0 )
      {
        do
        {
          ++v13;
          *(dword_ABDF94 + v13 - 1) = *(dword_ABDF94 + v13);
        }
        while ( v13 < dword_ABDFA0 );
      }
      v14 = v12[11];
      v12[10] = &VectorClass<Cell>::`vftable';
      if ( v14 && *(v12 + 53) )
      {
        operator delete(v14);
        v12[11] = 0;
      }
      *(v12 + 53) = 0;
      v12[12] = 0;
      operator delete(v12);
    }
  }
  dword_ABED14 = 0;
  sub_578350(&MouseClass::Instance);
  result = MapClass::CellIteratorNext(&MouseClass::Instance);
  for ( m = result; result; m = result )
  {
    if ( sub_4865B0(m) )
    {
      for ( nFacingType_1 = 0; nFacingType_1 < 8; nFacingType_1 += 2 )
      {
        v18 = CellClass::GetNeighbourCell(m, nFacingType_1);
        if ( sub_486380(v18) )
          v18->IsoTileTypeIndex = IsoTileTypeIndex_0;
      }
    }
    result = MapClass::CellIteratorNext(&MouseClass::Instance);
  }
  return result;
}
