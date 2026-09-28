// ============================================================================
// sub_59C920 @ 0x59C920  (full body, IDA MCP / Hex-Rays; /*0xNNNN*/ marks kept)
//
// RandomMapGenerator::GenerateLake - standalone lake generation.
// Call sites:
//   sub_59C580 lake stage  (0x59c5fb, up to 10 tries, random start point)
//   river-exit phase       (0x59e22c, seeded with the river-mouth cell)
//
// Direct callees (subordinate tree):
//   sub_578350      CellIterator reset             -> 578290_578350_CellIterator.c
//   sub_5A0410      water-body expand / relabel    -> 5A0410.c
//   sub_486380      placeholder-tile test (0/FFFF) -> helpers.c
//   sub_5AD870      min-heap sift-down             -> 5AD870.c
//   sub_5A0160      ExpandWaterBody                -> MapGenRiver.cpp (implemented)
//   sub_57A0C0      SmoothWaterBody                -> MapGenRiver.cpp (implemented)
//   sub_5980C0      Gaussian sampler               -> sub_5980C0.dcomp.c
//   Randomizer::Random / Game::F2I64 / YRMath::sqrt / operator new|delete
//
// Globals touched:
//   dword_ABED10  WorkCell array (80 bytes/cell), dword_89C2DC = workSide
//   dword_ABED04  W' (diamond reject lo), dword_ABED08 = W'+2H'
//   this[193]     usedWaterCells, this[194] = generation code
//   this[19]      waterAmount, this[96]/this[97] = W / H size coeffs
//   nIdx          WaterSet base tile index, IsoTileTypeIndex_29 = "water 29"
// ============================================================================

char __thiscall sub_59C920(_DWORD *this, _WORD *a2)
{
  int v3; // eax
  int n75; // eax
  int n100_1; // edi
  int n100; // esi
  void *v7; // eax
  void *v8; // esi
  int n100_2; // eax
  void *v10; // eax
  int v11; // ecx
  int v12; // eax
  CellClass *i; // eax
  _WORD *v14; // ecx
  int v15; // edi
  int v16; // eax
  int v17; // ecx
  int v18; // edx
  int *v19; // ecx
  int v20; // eax
  bool v21; // zf
  unsigned int v22; // ebx
  unsigned int v23; // eax
  __int16 v24; // di
  unsigned int v25; // ebx
  unsigned int v26; // eax
  __int16 v27; // cx
  __int16 v28; // ax
  CellClass *CellAt_MapCrd; // eax
  int v31; // eax
  int v32; // ecx
  double v33; // st7
  int n76_3; // eax
  int v35; // ecx
  int v36; // eax
  _DWORD *v37; // edi
  unsigned int v38; // ecx
  unsigned int v39; // edx
  int v40; // ebx
  unsigned int v41; // eax
  int n200_1; // ecx
  int v43; // eax
  CellStruct *n200_3; // edi
  _DWORD *v45; // edx
  CellClass *v46; // eax
  char *v47; // edx
  float *v48; // ebx
  int v49; // ecx
  __int16 v50; // ax
  int v51; // ecx
  char *v52; // edi
  CellClass *v53; // eax
  __int16 Height_1; // ax
  int v55; // edx
  float *v56; // edi
  unsigned int v57; // ecx
  unsigned int v58; // edx
  unsigned int v59; // eax
  int v60; // edi
  int v61; // eax
  int n200_2; // edi
  int v63; // eax
  CellStruct *pMapCoord; // edi
  CellClass *v65; // ebx
  char *v66; // edi
  int v67; // eax
  _DWORD *v68; // edi
  CellClass *j; // eax
  int v70; // ecx
  int IsoTileTypeIndex; // ecx
  int v72; // esi
  CellClass *k; // eax
  char *v74; // ecx
  char v75; // [esp+1Bh] [ebp-5Dh]
  int pMapCoord_; // [esp+20h] [ebp-58h] BYREF
  __int64 n76_4; // [esp+24h] [ebp-54h]
  int n200; // [esp+2Ch] [ebp-4Ch]
  void *Block; // [esp+30h] [ebp-48h]
  __int64 Height; // [esp+34h] [ebp-44h] BYREF
  __int64 v82; // [esp+3Ch] [ebp-3Ch]
  __int64 Width; // [esp+44h] [ebp-34h]
  int n76; // [esp+4Ch] [ebp-2Ch]
  double n76_1; // [esp+50h] [ebp-28h]
  double n76_2; // [esp+58h] [ebp-20h]
  double v87; // [esp+60h] [ebp-18h]
  double v88; // [esp+68h] [ebp-10h]
  double v89; // [esp+70h] [ebp-8h]

  v3 = this[19]; /*0x59c92e*/
  v75 = 1; /*0x59c937*/
  LODWORD(n76_2) = v3; /*0x59c93c*/
  if ( v3 ) /*0x59c940*/
    v3 = Game::F2I64(this[97] * this[96] * SLODWORD(n76_2) * 0.008 + 100.0); /*0x59c95e*/
  n75 = v3 - this[193]; /*0x59c963*/
  LODWORD(n76_1) = n75; /*0x59c96c*/
  if ( n75 <= 75 ) /*0x59c970*/
    return 0; /*0x59c970*/
  n100_1 = 2 * n75 + 2; /*0x59c976*/
  n100 = n100_1; /*0x59c97d*/
  if ( n100_1 <= 100 ) /*0x59c97f*/
    n100 = 100; /*0x59c981*/
  v7 = operator new(8 * n100); /*0x59c98e*/
  if ( v7 ) /*0x59c998*/
  {
    Block = v7; /*0x59c99b*/
    LODWORD(v88) = n100 - 1; /*0x59c99f*/
  }
  else
  {
    Block = 0; /*0x59c9a5*/
  }
  v8 = operator new(0x14u); /*0x59c9b4*/
  if ( v8 ) /*0x59c9bb*/
  {
    n100_2 = n100_1; /*0x59c9c0*/
    if ( n100_1 <= 100 ) /*0x59c9c2*/
      n100_2 = 100; /*0x59c9c4*/
    *(v8 + 3) = 0; /*0x59c9d3*/
    *(v8 + 4) = -1; /*0x59c9d6*/
    *v8 = 0; /*0x59c9dd*/
    *(v8 + 1) = n100_2; /*0x59c9df*/
    v10 = operator new(4 * n100_2 + 4); /*0x59c9e2*/
    v11 = *(v8 + 1); /*0x59c9e7*/
    *(v8 + 2) = v10; /*0x59c9ea*/
    v12 = 0; /*0x59c9f0*/
    if ( v11 >= 0 ) /*0x59c9f4*/
    {
      do /*0x59ca03*/
      {
        ++v12; /*0x59c9f9*/
        *(*(v8 + 2) + 4 * v12 - 4) = 0; /*0x59c9fa*/
      }
      while ( v12 <= *(v8 + 1) ); /*0x59ca03*/
    }
  }
  else
  {
    v8 = 0; /*0x59ca07*/
  }
  sub_578350(&MouseClass::Instance); /*0x59ca10*/
  for ( i = MapClass::CellIteratorNext(&MouseClass::Instance); i; i = MapClass::CellIteratorNext(&MouseClass::Instance) ) /*0x59ca21*/
  {
    LODWORD(n76_2) = i->MapCoords; /*0x59ca26*/
    *(dword_ABED10 + 20 * SLOWORD(n76_2) + 20 * dword_89C2DC * SWORD1(n76_2) + 15) = 0; /*0x59ca4b*/
  }
  v14 = a2; /*0x59ca5e*/
  v15 = dword_89C2DC * dword_89C2DC; /*0x59ca61*/
  if ( *a2 || a2[1] ) /*0x59ca6e*/
  {
    if ( v15 > 0 ) /*0x59cc83*/
    {
      v31 = 0; /*0x59cc89*/
      do /*0x59cc9a*/
      {
        v31 += 80; /*0x59cc91*/
        --v15; /*0x59cc94*/
        *(dword_ABED10 + v31 - 12) = 1; /*0x59cc95*/
      }
      while ( v15 ); /*0x59cc9a*/
    }
  }
  else
  {
    if ( v15 > 0 ) /*0x59ca7b*/
    {
      v16 = 0; /*0x59ca7d*/
      v17 = dword_89C2DC * dword_89C2DC; /*0x59ca7f*/
      do /*0x59ca90*/
      {
        v16 += 80; /*0x59ca87*/
        --v17; /*0x59ca8a*/
        *(dword_ABED10 + v16 - 12) = 0; /*0x59ca8b*/
      }
      while ( v17 ); /*0x59ca90*/
    }
    sub_5A0410(0, 2, -2); /*0x59ca9a*/
    if ( v15 > 0 ) /*0x59caa1*/
    {
      v18 = 0; /*0x59caa3*/
      do /*0x59cada*/
      {
        v19 = (dword_ABED10 + v18 + 56); /*0x59caaa*/
        v20 = *v19; /*0x59caae*/
        if ( !*v19 || v20 == this[194] ) /*0x59cabc*/
        {
          *(dword_ABED10 + v18 + 68) = 1; /*0x59cad1*/
        }
        else if ( v20 == -2 ) /*0x59cac1*/
        {
          *v19 = 0; /*0x59cac3*/
        }
        v18 += 80; /*0x59cad6*/
        --v15; /*0x59cad9*/
      }
      while ( v15 ); /*0x59cada*/
    }
    v14 = a2; /*0x59cadc*/
  }
  v21 = *v14 == 0; /*0x59cadf*/
  n200 = 0; /*0x59cae3*/
  if ( v21 && !v14[1] ) /*0x59caf1*/
  {
    while ( 1 ) /*0x59cb09*/
    {
      v22 = MouseClass::Instance.MapRect.Width - 1; /*0x59cb09*/
      Width = MouseClass::Instance.MapRect.Width; /*0x59cb0f*/
      v89 = MouseClass::Instance.MapRect.Width; /*0x59cb17*/
      do /*0x59cb48*/
      {
        v82 = Randomizer::Random(&dword_ABE890); /*0x59cb25*/
        v23 = Game::F2I64(v82 * v89 * 2.328306437080797e-10); /*0x59cb3f*/
        v24 = v23; /*0x59cb44*/
      }
      while ( v23 > v22 ); /*0x59cb48*/
      v25 = MouseClass::Instance.MapRect.Height - 1; /*0x59cb58*/
      Height = MouseClass::Instance.MapRect.Height; /*0x59cb5e*/
      v89 = MouseClass::Instance.MapRect.Height; /*0x59cb66*/
      do /*0x59cb95*/
      {
        n76_4 = Randomizer::Random(&dword_ABE890); /*0x59cb74*/
        v26 = Game::F2I64(n76_4 * v89 * 2.328306437080797e-10); /*0x59cb8e*/
      }
      while ( v26 > v25 ); /*0x59cb95*/
      WORD1(v87) = -v24; /*0x59cba2*/
      WORD1(n76_2) = MouseClass::Instance.MapRect.Width; /*0x59cbab*/
      LOWORD(v88) = v24 + 1; /*0x59cbb7*/
      WORD1(v88) = LOWORD(MouseClass::Instance.MapRect.Width) - v24; /*0x59cbbc*/
      v27 = v26 + v24 + 1; /*0x59cbc9*/
      v28 = LOWORD(MouseClass::Instance.MapRect.Width) - v24 + v26; /*0x59cbcb*/
      LOWORD(n76) = v27; /*0x59cbcd*/
      HIWORD(n76) = v28; /*0x59cbd2*/
      pMapCoord_ = n76; /*0x59cbdb*/
      if ( ++n200 >= 200 ) /*0x59cbee*/
        return 0; /*0x59cbee*/
      if ( dword_ABED10 ) /*0x59cbfc*/
      {
        if ( !*(dword_ABED10 + 20 * v27 + 20 * dword_89C2DC * v28 + 14) ) /*0x59cc17*/
        {
          CellAt_MapCrd = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord_); /*0x59cc2d*/
          if ( sub_486380(CellAt_MapCrd) ) /*0x59cc34*/
          {
            if ( *(dword_ABED10 + 80 * pMapCoord_ + 80 * dword_89C2DC * SHIWORD(pMapCoord_) + 68) ) /*0x59cc60*/
            {
              if ( n200 < 200 ) /*0x59cc74*/
                goto LABEL_50; /*0x59cc74*/
              return 0; /*0x59cc7e*/
            }
          }
        }
      }
    }
  }
  pMapCoord_ = *v14; /*0x59cca3*/
LABEL_50:
  v32 = LODWORD(n76_1); /*0x59cca7*/
  LODWORD(n76_4) = 0; /*0x59ccb0*/
  n76 = 76; /*0x59ccb4*/
  if ( SLODWORD(n76_1) >= 76 ) /*0x59ccbc*/
    n76 = LODWORD(n76_1); /*0x59ccbe*/
  n76_1 = n76; /*0x59cccd*/
  v88 = (v32 / 6); /*0x59cce7*/
  LODWORD(n76_2) = v32 / 3; /*0x59ccf2*/
  v87 = (v32 / 3); /*0x59ccfa*/
  if ( v87 - v88 > n76_1 || v87 + v88 < 75.0 ) /*0x59cd20*/
  {
    v88 = (n76_1 - 75.0) * 0.5; /*0x59cd32*/
    v87 = v88 + 75.0; /*0x59cd3c*/
  }
  do /*0x59cd70*/
  {
    do /*0x59cd61*/
    {
      v33 = sub_5980C0(&byte_ABDFB8); /*0x59cd45*/
      n76_2 = v33 * v88 + v87; /*0x59cd52*/
    }
    while ( n76_2 < 75.0 ); /*0x59cd61*/
  }
  while ( n76_2 > n76_1 ); /*0x59cd70*/
  n76_3 = Game::F2I64(n76_2); /*0x59cd76*/
  v35 = *v8; /*0x59cd7b*/
  n76 = n76_3; /*0x59cd7d*/
  v36 = 0; /*0x59cd81*/
  if ( v35 >= 0 ) /*0x59cd85*/
  {
    do /*0x59cd93*/
    {
      ++v36; /*0x59cd8a*/
      *(*(v8 + 2) + 4 * v36 - 4) = 0; /*0x59cd8b*/
    }
    while ( v36 <= *v8 ); /*0x59cd93*/
  }
  v37 = Block; /*0x59cd95*/
  *v8 = 0; /*0x59cd99*/
  LODWORD(v82) = 1; /*0x59cd9f*/
  *v37 = pMapCoord_; /*0x59cda7*/
  v37[1] = 0; /*0x59cda9*/
  *(dword_ABED10 + 20 * pMapCoord_ + 20 * dword_89C2DC * SHIWORD(pMapCoord_) + 15) = this[194]; /*0x59cdd4*/
  v38 = *v8 + 1; /*0x59cddd*/
  LODWORD(n76_2) = v37[1]; /*0x59cde0*/
  v39 = v38 >> 1; /*0x59cde7*/
  if ( v38 < *(v8 + 1) ) /*0x59cdeb*/
  {
    for ( ; v38 > 1; v39 >>= 1 ) /*0x59cdf0*/
    {
      v40 = *(v8 + 2); /*0x59cdf2*/
      if ( *(*(v40 + 4 * v39) + 4) <= *&n76_2 ) /*0x59ce04*/
        break; /*0x59ce04*/
      *(v40 + 4 * v38) = *(v40 + 4 * v39); /*0x59ce09*/
      v38 = v39; /*0x59ce0c*/
    }
    *(*(v8 + 2) + 4 * v38) = v37; /*0x59ce18*/
    v41 = *(v8 + 3); /*0x59ce1d*/
    ++*v8; /*0x59ce23*/
    if ( v37 > v41 ) /*0x59ce25*/
      *(v8 + 3) = v37; /*0x59ce27*/
    if ( v37 < *(v8 + 4) ) /*0x59ce2d*/
      *(v8 + 4) = v37; /*0x59ce2f*/
  }
  n200_1 = *v8; /*0x59ce32*/
  if ( *v8 ) /*0x59ce32*/
  {
    v43 = *(v8 + 2); /*0x59ce38*/
    n200_3 = *(v43 + 4); /*0x59ce40*/
    *(v43 + 4) = *(v43 + 4 * n200_1); /*0x59ce43*/
    *(*(v8 + 2) + 4 * (*v8)--) = 0; /*0x59ce4b*/
    sub_5AD870(v8, 1); /*0x59ce59*/
    n200_1 = n200_3; /*0x59ce5e*/
  }
  n200 = n200_1; /*0x59ce64*/
  if ( n76 > 0 ) /*0x59ce6a*/
  {
    v45 = dword_ABED10; /*0x59ce70*/
    while ( n200_1 && v75 ) /*0x59ce84*/
    {
      if ( v45 ) /*0x59ce98*/
        v45[20 * *n200_1 + 14 + 20 * dword_89C2DC * *(n200_1 + 2)] = this[194]; /*0x59ceba*/
      v46 = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, n200_1); /*0x59cec4*/
      v47 = Block; /*0x59cecf*/
      v46->IsoTileTypeIndex = nIdx; /*0x59ced3*/
      v46->Height = 0; /*0x59ced6*/
      LODWORD(Width) = 0; /*0x59cee1*/
      v48 = &v47[8 * v82]; /*0x59cee9*/
      do /*0x59d0f8*/
      {
        v49 = Width & 7; /*0x59cef4*/
        v50 = Neighbours[v49].X + *n200; /*0x59cf00*/
        LOWORD(v49) = Neighbours[v49].Y; /*0x59cf0f*/
        LOWORD(n76_1) = v50; /*0x59cf13*/
        WORD1(n76_1) = *(n200 + 2) + v49; /*0x59cf1c*/
        LODWORD(Height) = LODWORD(n76_1); /*0x59cf25*/
        v51 = SWORD1(n76_1) + v50; /*0x59cf2f*/
        if ( v51 > dword_ABED04 /*0x59cf60*/
          && v50 - SWORD1(n76_1) < dword_ABED04
          && SWORD1(n76_1) - v50 < dword_ABED04
          && v51 <= dword_ABED08 )
        {
          v52 = dword_ABED10 + 80 * v50 + 80 * dword_89C2DC * SWORD1(n76_1); /*0x59cf7b*/
          if ( *(v52 + 14) /*0x59cfb9*/
            || *(v52 + 15) == this[194]
            || (v53 = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &Height), !sub_486380(v53))
            || !v52[68] )
          {
            v60 = *(v52 + 14); /*0x59d0d2*/
            if ( v60 && v60 != this[194] ) /*0x59d0e3*/
              v75 = 0; /*0x59d0e5*/
          }
          else
          {
            Height_1 = Height; /*0x59cfc4*/
            v55 = SWORD1(Height); /*0x59cfcb*/
            *v48 = Height; /*0x59cfd0*/
            LODWORD(n76_2) = (pMapCoord_ - Height_1) * (pMapCoord_ - Height_1) /*0x59cfef*/
                           + (SHIWORD(pMapCoord_) - v55) * (SHIWORD(pMapCoord_) - v55);
            *&n76_2 = YRMath::sqrt(SLODWORD(n76_2)); /*0x59cfff*/
            *&v89 = Randomizer::Random(&dword_ABE890); /*0x59d010*/
            LODWORD(v82) = v82 + 1; /*0x59d035*/
            v48[1] = 10.0 * (*&v89 * 2.328306437080797e-10) + *&n76_2 * 0.5 - n76_4 * 0.02; /*0x59d053*/
            *(v52 + 15) = this[194]; /*0x59d05c*/
            v56 = v48; /*0x59d061*/
            v48 += 2; /*0x59d063*/
            v57 = *v8 + 1; /*0x59d066*/
            LODWORD(n76_2) = v48; /*0x59d067*/
            *&v87 = v56[1]; /*0x59d070*/
            v58 = v57 >> 1; /*0x59d077*/
            if ( v57 < *(v8 + 1) ) /*0x59d07d*/
            {
              for ( ; v57 > 1; v58 >>= 1 ) /*0x59d082*/
              {
                LODWORD(v88) = *(*(v8 + 2) + 4 * v58); /*0x59d08a*/
                if ( *(LODWORD(v88) + 4) <= *&v87 ) /*0x59d09a*/
                  break; /*0x59d09a*/
                *(*(v8 + 2) + 4 * v57) = LODWORD(v88); /*0x59d0a3*/
                v48 = LODWORD(n76_2); /*0x59d0a6*/
                v57 = v58; /*0x59d0aa*/
              }
              *(*(v8 + 2) + 4 * v57) = v56; /*0x59d0b6*/
              v59 = *(v8 + 3); /*0x59d0bb*/
              ++*v8; /*0x59d0c1*/
              if ( v56 > v59 ) /*0x59d0c3*/
                *(v8 + 3) = v56; /*0x59d0c5*/
              if ( v56 < *(v8 + 4) ) /*0x59d0cb*/
                *(v8 + 4) = v56; /*0x59d0cd*/
            }
          }
        }
        LODWORD(Width) = Width + 2; /*0x59d0f4*/
      }
      while ( Width < 8 ); /*0x59d0f8*/
      LODWORD(n76_4) = n76_4 + 1; /*0x59d103*/
      if ( *v8 ) /*0x59d107*/
      {
        v61 = *(v8 + 2); /*0x59d113*/
        n200_2 = *(v61 + 4); /*0x59d11b*/
        *(v61 + 4) = *(v61 + 4 * *v8); /*0x59d11e*/
        *(*(v8 + 2) + 4 * (*v8)--) = 0; /*0x59d126*/
        sub_5AD870(v8, 1); /*0x59d134*/
        n200 = n200_2; /*0x59d139*/
      }
      else
      {
        n200 = 0; /*0x59d10d*/
      }
      if ( n76_4 >= n76 ) /*0x59d147*/
        break; /*0x59d147*/
      v45 = dword_ABED10; /*0x59ce78*/
      n200_1 = n200; /*0x59ce7e*/
    }
  }
  if ( *v8 ) /*0x59d14d*/
  {
    v63 = *(v8 + 2); /*0x59d157*/
    pMapCoord = *(v63 + 4); /*0x59d15f*/
    *(v63 + 4) = *(v63 + 4 * *v8); /*0x59d162*/
    *(*(v8 + 2) + 4 * (*v8)--) = 0; /*0x59d16a*/
    sub_5AD870(v8, 1); /*0x59d178*/
    if ( pMapCoord ) /*0x59d17f*/
    {
      while ( v75 ) /*0x59d18b*/
      {
        v65 = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, pMapCoord); /*0x59d19c*/
        v66 = dword_ABED10 + 80 * pMapCoord->X + 80 * dword_89C2DC * pMapCoord->Y; /*0x59d1ba*/
        if ( !*(v66 + 14) && sub_486380(v65) && v66[68] ) /*0x59d1ce*/
        {
          v65->IsoTileTypeIndex = nIdx; /*0x59d1de*/
          v65->Height = 0; /*0x59d1e1*/
          *(v66 + 14) = this[194]; /*0x59d1ee*/
        }
        else
        {
          v75 = 0; /*0x59d1f3*/
        }
        if ( *v8 ) /*0x59d1f8*/
        {
          v67 = *(v8 + 2); /*0x59d202*/
          pMapCoord = *(v67 + 4); /*0x59d20a*/
          *(v67 + 4) = *(v67 + 4 * *v8); /*0x59d20d*/
          *(*(v8 + 2) + 4 * (*v8)--) = 0; /*0x59d215*/
          sub_5AD870(v8, 1); /*0x59d223*/
        }
        else
        {
          pMapCoord = 0; /*0x59d1fe*/
        }
        LODWORD(n76_4) = n76_4 + 1; /*0x59d22f*/
        if ( !pMapCoord ) /*0x59d233*/
          goto LABEL_113; /*0x59d233*/
      }
      goto LABEL_121; /*0x59d18b*/
    }
  }
LABEL_113:
  if ( !v75 ) /*0x59d23f*/
  {
LABEL_121:
    v68 = this; /*0x59d296*/
    goto LABEL_122; /*0x59d296*/
  }
  if ( n76_4 <= 75 || n76_4 <= n76 / 4 ) /*0x59d259*/
  {
    v75 = 0; /*0x59d291*/
    goto LABEL_121; /*0x59d291*/
  }
  v75 = 1; /*0x59d25e*/
  if ( *a2 || a2[1] ) /*0x59d269*/
  {
    v68 = this; /*0x59d2e6*/
LABEL_127:
    if ( !*a2 && !a2[1] ) /*0x59d2f0*/
    {
      v68 = this; /*0x59d316*/
      v75 = sub_5A0160(this[194], 1, 0, 0, 512, 512, 0, 0); /*0x59d32a*/
      if ( v75 ) /*0x59d32e*/
      {
        LODWORD(v88) = this[194]; /*0x59d33f*/
        sub_578350(&MouseClass::Instance); /*0x59d343*/
        for ( j = MapClass::CellIteratorNext(&MouseClass::Instance); /*0x59d354*/
              j;
              j = MapClass::CellIteratorNext(&MouseClass::Instance) )
        {
          if ( dword_ABED10 ) /*0x59d35e*/
            v70 = *(dword_ABED10 + 20 * j->MapCoords.X + 20 * dword_89C2DC * j->MapCoords.Y + 14); /*0x59d37c*/
          else
            v70 = -1; /*0x59d360*/
          if ( v70 == LODWORD(v88) ) /*0x59d384*/
          {
            IsoTileTypeIndex = j->IsoTileTypeIndex; /*0x59d386*/
            if ( !IsoTileTypeIndex || IsoTileTypeIndex == 0xFFFF ) /*0x59d393*/
              j->IsoTileTypeIndex = IsoTileTypeIndex_29; /*0x59d39b*/
          }
        }
        v75 = 1; /*0x59d3ac*/
      }
    }
    goto LABEL_122; /*0x59d3b1*/
  }
  v68 = this; /*0x59d270*/
  v75 = sub_57A0C0(this[194], 0); /*0x59d289*/
  if ( v75 ) /*0x59d28d*/
    goto LABEL_127; /*0x59d28d*/
LABEL_122:
  if ( v8 ) /*0x59d29c*/
  {
    operator delete(*(v8 + 2)); /*0x59d2a2*/
    operator delete(v8); /*0x59d2a8*/
  }
  operator delete(Block); /*0x59d2b5*/
  if ( v75 ) /*0x59d2c3*/
  {
    v68[193] += n76_4; /*0x59d2d5*/
    return 1; /*0x59d2e3*/
  }
  v72 = v68[194]; /*0x59d3b6*/
  sub_578350(&MouseClass::Instance); /*0x59d3c1*/
  for ( k = MapClass::CellIteratorNext(&MouseClass::Instance); k; k = MapClass::CellIteratorNext(&MouseClass::Instance) ) /*0x59d3d4*/
  {
    LODWORD(v88) = k->MapCoords; /*0x59d3d9*/
    v74 = dword_ABED10 + 80 * SLOWORD(v88) + 80 * dword_89C2DC * SWORD1(v88); /*0x59d3fa*/
    if ( *(v74 + 14) == v72 ) /*0x59d3ff*/
    {
      *(v74 + 14) = 0; /*0x59d401*/
      v74[75] = 0; /*0x59d404*/
      k->IsoTileTypeIndex = 0; /*0x59d408*/
      k->Height = 0; /*0x59d40b*/
      k->Level = v68[195]; /*0x59d418*/
    }
  }
  return 0; /*0x59cc78*/
}
