// ============================================================================
// sub_5A0410 @ 0x5A0410  (full body, IDA MCP / Hex-Rays; /*0xNNNN*/ marks kept)
//
// Called from sub_59C920 (GenerateLake, 0x59ca9a) as the "pre-clean / relabel"
// pass over the whole work grid before lake seeding.
//
// Signature note: IDA prints the call inside sub_59C920 as
//   sub_5A0410(0, 2, -2)
// while the body is typed with 4 params (this, a2, n2, a4). The extra leading
// value is a __thiscall/ECX artefact - read it together with the body, not the
// call-site text.
//
// Direct callees:
//   sub_5A0700   BuildWaterRing (ring 0)      -> MapGenRiver.cpp (implemented)
//   sub_578350   CellIterator reset           -> 578290_578350_CellIterator.c
//   DynamicVectorClass<CellClass*>::Init     -> 42FCB0
//   operator new
//
// Globals touched:
//   dword_ABED10  WorkCell array (80 bytes/cell), dword_89C2DC = workSide
//   dword_ABED04  W' (diamond reject lo), dword_ABED08 = W'+2H'
//   Neighbours    @ 0x89F688 8-direction offset table
//   this[780]     base Level written back per cell
// ============================================================================

char __thiscall sub_5A0410(_DWORD *this, int a2, int n2, int a4)
{
  _DWORD *v4; // ebx
  int n2_1; // esi
  _DWORD *v6; // ebp
  CellClass *i; // eax
  int j; // esi
  CellStruct pMapCoord__1; // ecx
  CellClass *CellAt_MapCrd; // eax
  _DWORD *v11; // eax
  _DWORD *v12; // esi
  _DWORD *v13; // ebx
  int MapCoords_1; // eax
  int v15; // edi
  int v16; // edx
  char v17; // al
  int v18; // eax
  __int16 v19; // cx
  int v20; // eax
  int v21; // ecx
  char *v22; // esi
  int v23; // ecx
  int v24; // eax
  int v25; // eax
  int v26; // edx
  CellClass *k; // eax
  _DWORD *v29; // [esp+10h] [ebp-20h]
  int n2_2; // [esp+14h] [ebp-1Ch]
  CellStruct pMapCoord_; // [esp+18h] [ebp-18h] BYREF
  int v32; // [esp+1Ch] [ebp-14h]
  int v33; // [esp+20h] [ebp-10h]
  int n8; // [esp+24h] [ebp-Ch]
  int MapCoords; // [esp+28h] [ebp-8h]
  _DWORD *v36; // [esp+2Ch] [ebp-4h]

  v4 = this; /*0x5a041b*/
  v36 = this; /*0x5a041e*/
  n2_1 = n2; /*0x5a0427*/
  v6 = sub_5A0700(this, a2); /*0x5a042b*/
  v29 = v6; /*0x5a0430*/
  if ( n2 > 1 ) /*0x5a0434*/
  {
    sub_578350(&MouseClass::Instance); /*0x5a043b*/
    for ( i = MapClass::CellIteratorNext(&MouseClass::Instance); i; i = MapClass::CellIteratorNext(&MouseClass::Instance) ) /*0x5a044e*/
    {
      MapCoords = i->MapCoords; /*0x5a0453*/
      *(dword_ABED10 + 20 * MapCoords + 20 * dword_89C2DC * SHIWORD(MapCoords) + 15) = 0; /*0x5a0478*/
    }
  }
  n2_2 = 0; /*0x5a048b*/
  if ( n2 > 0 ) /*0x5a048f*/
  {
    do /*0x5a067e*/
    {
      for ( j = v6[4] - 1; j >= 0; CellAt_MapCrd->Level = *(v4 + 780) ) /*0x5a0499*/
      {
        pMapCoord__1 = *(v6[1] + 4 * j); /*0x5a04a6*/
        pMapCoord_ = pMapCoord__1; /*0x5a04a9*/
        if ( dword_ABED10 ) /*0x5a04ad*/
          *(dword_ABED10 + 20 * pMapCoord__1.X + 20 * dword_89C2DC * pMapCoord_.Y + 14) = a4; /*0x5a04ca*/
        CellAt_MapCrd = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord_); /*0x5a04d8*/
        CellAt_MapCrd->IsoTileTypeIndex = 0; /*0x5a04dd*/
        CellAt_MapCrd->Height = 0; /*0x5a04e0*/
        --j; /*0x5a04ed*/
      }
      if ( n2_2 < n2 - 1 ) /*0x5a0501*/
      {
        v11 = operator new(0x18u); /*0x5a0509*/
        v12 = v11; /*0x5a050e*/
        if ( v11 ) /*0x5a0515*/
        {
          DynamicVectorClass_TL_CellClass_PTR_TR_::Init(v11, 0, 0); /*0x5a051b*/
          *v12 = &DynamicVectorClass<Cell>::`vftable'; /*0x5a0520*/
          v12[5] = 10; /*0x5a0526*/
          v12[4] = 0; /*0x5a052d*/
          v13 = v12; /*0x5a0530*/
        }
        else
        {
          v13 = 0; /*0x5a0534*/
        }
        v13[5] = v6[4]; /*0x5a0539*/
        MapCoords_1 = v6[4] - 1; /*0x5a053f*/
        MapCoords = MapCoords_1; /*0x5a0540*/
        if ( MapCoords_1 >= 0 ) /*0x5a0544*/
        {
          v15 = dword_ABED04; /*0x5a054a*/
          do /*0x5a0650*/
          {
            v16 = *(v6[1] + 4 * MapCoords_1); /*0x5a0553*/
            v17 = 0; /*0x5a0556*/
            v32 = v16; /*0x5a0558*/
            for ( n8 = 0; n8 < 8; ++n8 ) /*0x5a055c*/
            {
              v18 = v17 & 7; /*0x5a0560*/
              v19 = HIWORD(v32) + Neighbours[v18].Y; /*0x5a057b*/
              LOWORD(v33) = v32 + Neighbours[v18].X; /*0x5a0580*/
              HIWORD(v33) = v19; /*0x5a0585*/
              v20 = v19; /*0x5a058d*/
              v21 = v19 + v33; /*0x5a0590*/
              if ( v21 > v15 && v33 - v20 < v15 && v20 - v33 < v15 && v21 <= dword_ABED08 ) /*0x5a05b9*/
              {
                v22 = dword_ABED10 + 80 * v33 + 80 * dword_89C2DC * v20; /*0x5a05d4*/
                if ( *(v22 + 14) == a2 ) /*0x5a05d9*/
                {
                  if ( *(v22 + 15) != n2_2 + 1 ) /*0x5a05e7*/
                  {
                    v23 = v13[2]; /*0x5a05e9*/
                    if ( v13[4] < v23 /*0x5a060e*/
                      || (*(v13 + 13) || !v23) && (v24 = v13[5], v24 > 0) && (*(*v13 + 8))(v13, v23 + v24, 0) )
                    {
                      v25 = v13[4]; /*0x5a0615*/
                      v26 = v13[1]; /*0x5a0618*/
                      v13[4] = v25 + 1; /*0x5a061e*/
                      *(v26 + 4 * v25) = v33; /*0x5a0625*/
                    }
                    *(v22 + 15) = n2_2 + 1; /*0x5a0628*/
                    v15 = dword_ABED04; /*0x5a062b*/
                  }
                  v6 = v29; /*0x5a0631*/
                }
              }
              v17 = n8 + 1; /*0x5a0639*/
            }
            MapCoords_1 = --MapCoords; /*0x5a064b*/
          }
          while ( MapCoords >= 0 ); /*0x5a0650*/
        }
        if ( v6 ) /*0x5a065a*/
          (**v6)(v6, 1); /*0x5a0663*/
        v29 = v13; /*0x5a0665*/
        v6 = v13; /*0x5a0669*/
        v4 = v36; /*0x5a066b*/
      }
      ++n2_2; /*0x5a067a*/
    }
    while ( n2_2 < n2 ); /*0x5a067e*/
    n2_1 = n2; /*0x5a0684*/
  }
  if ( v6 ) /*0x5a0688*/
    (**v6)(v6, 1); /*0x5a0691*/
  if ( n2_1 > 1 ) /*0x5a0696*/
  {
    sub_578350(&MouseClass::Instance); /*0x5a069d*/
    for ( k = MapClass::CellIteratorNext(&MouseClass::Instance); k; k = MapClass::CellIteratorNext(&MouseClass::Instance) ) /*0x5a06ae*/
      *(dword_ABED10 + 20 * *&k->MapCoords + 20 * dword_89C2DC * HIWORD(*&k->MapCoords) + 15) = 0; /*0x5a06d8*/
  }
  return 1; /*0x5a06e5*/
}
