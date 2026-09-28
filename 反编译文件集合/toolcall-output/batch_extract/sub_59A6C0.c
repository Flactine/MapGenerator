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

  sub_578350(&MouseClass::Instance); /*0x59a6cc*/
  for ( i = MapClass::CellIteratorNext(&MouseClass::Instance); i; i = MapClass::CellIteratorNext(&MouseClass::Instance) ) /*0x59a6dd*/
    i->IsoTileTypeIndex = nIdx; /*0x59a6e5*/
  v3 = this[15]; /*0x59a6f6*/
  if ( v3 ) /*0x59a6fc*/
  {
    v4 = v3 - 1; /*0x59a6fe*/
    if ( v4 ) /*0x59a6ff*/
    {
      if ( v4 == 1 ) /*0x59a702*/
        sub_59B200(this); /*0x59a706*/
    }
    else
    {
      sub_59AFA0(this); /*0x59a70f*/
    }
  }
  else
  {
    sub_59AD10(this); /*0x59a718*/
  }
  sub_578350(&MouseClass::Instance); /*0x59a722*/
  for ( j = MapClass::CellIteratorNext(&MouseClass::Instance); j; j = MapClass::CellIteratorNext(&MouseClass::Instance) ) /*0x59a735*/
  {
    if ( j->IsoTileTypeIndex == nIdx ) /*0x59a741*/
    {
      v6 = 1; /*0x59a743*/
      for ( nFacingType = 0; nFacingType < 8; nFacingType += 2 ) /*0x59a745*/
      {
        NeighbourCell = CellClass::GetNeighbourCell(j, nFacingType); /*0x59a74a*/
        if ( !sub_486380(NeighbourCell) ) /*0x59a751*/
          v6 = 0; /*0x59a75a*/
      }
      if ( v6 ) /*0x59a766*/
        j->IsoTileTypeIndex = 0; /*0x59a768*/
    }
  }
  sub_57A0C0(0, 0); /*0x59a788*/
  if ( dword_ABED10 ) /*0x59a794*/
  {
    v9 = dword_89C2DC * dword_89C2DC; /*0x59a79c*/
    if ( dword_89C2DC * dword_89C2DC > 0 ) /*0x59a7a1*/
    {
      v10 = 0; /*0x59a7a3*/
      do /*0x59a7c0*/
      {
        *(dword_ABED10 + v10 + 56) = -1; /*0x59a7ae*/
        *(dword_ABED10 + v10 + 60) = -1; /*0x59a7b8*/
        v10 += 80; /*0x59a7bc*/
        --v9; /*0x59a7bf*/
      }
      while ( v9 ); /*0x59a7c0*/
    }
  }
  for ( k = dword_ABDFA0 - 1; k >= 0; --k ) /*0x59a7cc*/
  {
    v12 = *(dword_ABDF94 + k); /*0x59a7df*/
    if ( v12 ) /*0x59a7e4*/
    {
      if ( *v12 ) /*0x59a7ea*/
      {
        (***v12)(*v12, 1); /*0x59a7f4*/
        *v12 = 0; /*0x59a7f6*/
      }
      v19 = v12; /*0x59a808*/
      v13 = (*(dword_ABDF90 + 16))(&dword_ABDF90, &v19); /*0x59a80c*/
      if ( v13 != -1 && v13 < dword_ABDFA0 && v13 < --dword_ABDFA0 ) /*0x59a827*/
      {
        do /*0x59a83f*/
        {
          ++v13; /*0x59a82f*/
          *(dword_ABDF94 + v13 - 1) = *(dword_ABDF94 + v13); /*0x59a833*/
        }
        while ( v13 < dword_ABDFA0 ); /*0x59a83f*/
      }
      v14 = v12[11]; /*0x59a841*/
      v12[10] = &VectorClass<Cell>::`vftable'; /*0x59a844*/
      if ( v14 && *(v12 + 53) ) /*0x59a84b*/
      {
        operator delete(v14); /*0x59a853*/
        v12[11] = 0; /*0x59a85b*/
      }
      *(v12 + 53) = 0; /*0x59a85f*/
      v12[12] = 0; /*0x59a863*/
      operator delete(v12); /*0x59a866*/
    }
  }
  dword_ABED14 = 0; /*0x59a87a*/
  sub_578350(&MouseClass::Instance); /*0x59a884*/
  result = MapClass::CellIteratorNext(&MouseClass::Instance); /*0x59a88e*/
  for ( m = result; result; m = result ) /*0x59a897*/
  {
    if ( sub_4865B0(m) ) /*0x59a89b*/
    {
      for ( nFacingType_1 = 0; nFacingType_1 < 8; nFacingType_1 += 2 ) /*0x59a8a4*/
      {
        v18 = CellClass::GetNeighbourCell(m, nFacingType_1); /*0x59a8ae*/
        if ( sub_486380(v18) ) /*0x59a8b2*/
          v18->IsoTileTypeIndex = IsoTileTypeIndex_0; /*0x59a8c0*/
      }
    }
    result = MapClass::CellIteratorNext(&MouseClass::Instance); /*0x59a8d0*/
  }
  return result; /*0x59a8db*/
}