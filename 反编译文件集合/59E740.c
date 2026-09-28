// sub_59E740 @ 0x59E740 (full body, IDA MCP) - river-mouth delta fan

char __thiscall sub_59E740(_DWORD *this, int a2, __int16 *a3, __int16 *a4, int a5, char *a6, double *a7, double *a8)
{
  CellStruct pMapCoord__20; // ecx
  int n12_1; // edi
  int n12; // esi
  int X_10; // eax
  int Y_1; // edx
  int v13; // ebp
  int n512_3; // ebp
  int v15; // edx
  int X_11; // eax
  int v17; // ebp
  int v18; // edx
  int v19; // ebp
  CellStruct pMapCoord__23; // eax
  int v21; // edx
  int X_7; // edx
  CellStruct pMapCoord__24; // eax
  int v24; // ebp
  int n512_2; // ebp
  __int16 X; // dx
  int MapCoords_10; // edi
  int v28; // eax
  int X_2; // esi
  int X_1; // ebx
  int v31; // edx
  CellClass *CellAt_MapCrd; // eax
  int X_3; // ebp
  int v35; // ecx
  unsigned int n5; // eax
  int IsoTileTypeIndex; // esi
  unsigned int n3; // eax
  __int16 X_4; // si
  char v40; // cl
  int v41; // edi
  CellClass *i; // eax
  CellStruct MapCoords; // edx
  int v44; // ecx
  int v45; // ecx
  CellStruct MapCoords_11; // ebp
  int v47; // eax
  unsigned int n5_1; // eax
  int IsoTileTypeIndex_1; // esi
  unsigned int n3_1; // eax
  __int16 X_6; // si
  __int16 n8_6; // si
  Level *Level_1; // ebx
  _DWORD *this_3; // edi
  __int16 v55; // ax
  int v56; // edi
  int v57; // ecx
  int v58; // esi
  CellClass *v59; // eax
  int v60; // esi
  CellClass *v61; // eax
  int n8_9; // esi
  int n8_7; // edi
  int n8_8; // ebp
  int n8_14; // ebx
  Level *Level_3; // edi
  IsometricTileTypeClass *CurrentBuildingType_1; // eax
  _DWORD *this_5; // esi
  CellClass *v69; // eax
  __int16 v70; // dx
  int j; // esi
  CellClass *v72; // eax
  __int16 v73; // ax
  int v74; // edx
  int v75; // ecx
  int v76; // esi
  CellClass *v77; // eax
  int v78; // edi
  CellClass *v79; // eax
  int n8_17; // esi
  int n8_15; // edi
  _DWORD *this_6; // ebp
  int n8_16; // ebx
  Level *Level_2; // edi
  _DWORD *this_4; // ebx
  __int16 n8_10; // si
  CellStruct pMapCoord__11; // ebp
  int v88; // esi
  int v89; // ecx
  int v90; // edx
  CellClass *v91; // eax
  int v92; // edx
  CellClass *v93; // eax
  int n8_13; // esi
  int n8_11; // ebx
  int n8_12; // ebp
  Level *Level; // ebx
  _DWORD *this_2; // ebp
  int n8_2; // edi
  __int16 v100; // si
  IsometricTileTypeClass *CurrentBuildingType; // edx
  int v102; // edi
  int v103; // esi
  CellClass *v104; // eax
  int v105; // ecx
  int v106; // eax
  int v107; // edx
  CellClass *v108; // eax
  int v109; // esi
  CellClass *v110; // eax
  int n8_5; // esi
  int n8_3; // edi
  int n8_4; // ebp
  __int16 v114; // dx
  CellStruct pMapCoord__2; // [esp+10h] [ebp-118h] BYREF
  char v116; // [esp+17h] [ebp-111h] BYREF
  CellStruct pMapCoord__6; // [esp+18h] [ebp-110h] BYREF
  CellStruct pMapCoord__1; // [esp+20h] [ebp-108h] BYREF
  __int16 v119[4]; // [esp+24h] [ebp-104h] BYREF
  CellStruct MapCoords_1; // [esp+2Ch] [ebp-FCh]
  CellStruct pMapCoord_; // [esp+34h] [ebp-F4h] BYREF
  char v122; // [esp+3Bh] [ebp-EDh]
  int v123; // [esp+3Ch] [ebp-ECh] BYREF
  _DWORD *this_1; // [esp+40h] [ebp-E8h]
  __int16 v125; // [esp+48h] [ebp-E0h]
  __int16 v126; // [esp+4Ah] [ebp-DEh]
  CellStruct MapCoords_9; // [esp+50h] [ebp-D8h]
  CellStruct pMapCoord__22; // [esp+54h] [ebp-D4h]
  int n8_1; // [esp+58h] [ebp-D0h]
  int n8; // [esp+5Ch] [ebp-CCh]
  int X_9; // [esp+60h] [ebp-C8h]
  CellStruct pMapCoord__21; // [esp+64h] [ebp-C4h]
  int n4_1; // [esp+68h] [ebp-C0h]
  int n4; // [esp+6Ch] [ebp-BCh]
  int X_5; // [esp+70h] [ebp-B8h] BYREF
  int Y; // [esp+74h] [ebp-B4h]
  int n512; // [esp+78h] [ebp-B0h]
  int n512_1; // [esp+7Ch] [ebp-ACh]
  __int64 v139; // [esp+80h] [ebp-A8h] BYREF
  __int64 X_8; // [esp+88h] [ebp-A0h] BYREF
  CellStruct MapCoords_8; // [esp+98h] [ebp-90h] BYREF
  CellStruct MapCoords_3; // [esp+9Ch] [ebp-8Ch] BYREF
  CellStruct pMapCoord__16; // [esp+A0h] [ebp-88h] BYREF
  CellStruct MapCoords_4; // [esp+A4h] [ebp-84h] BYREF
  CellStruct pMapCoord__19; // [esp+A8h] [ebp-80h] BYREF
  CellStruct MapCoords_5; // [esp+ACh] [ebp-7Ch] BYREF
  CellStruct pMapCoord__10; // [esp+B0h] [ebp-78h] BYREF
  CellStruct MapCoords_6; // [esp+B4h] [ebp-74h] BYREF
  CellStruct pMapCoord__12; // [esp+B8h] [ebp-70h] BYREF
  CellStruct MapCoords_7; // [esp+BCh] [ebp-6Ch] BYREF
  CellStruct pMapCoord__7; // [esp+C0h] [ebp-68h] BYREF
  CellStruct pMapCoord__3; // [esp+C4h] [ebp-64h] BYREF
  CellStruct pMapCoord__18; // [esp+C8h] [ebp-60h] BYREF
  CellStruct pMapCoord__17; // [esp+CCh] [ebp-5Ch] BYREF
  CellStruct pMapCoord__4; // [esp+D0h] [ebp-58h] BYREF
  CellStruct pMapCoord__8; // [esp+D4h] [ebp-54h] BYREF
  CellStruct MapCoords_2; // [esp+D8h] [ebp-50h] BYREF
  CellStruct pMapCoord__13; // [esp+DCh] [ebp-4Ch] BYREF
  CellStruct pMapCoord__5; // [esp+E0h] [ebp-48h] BYREF
  CellStruct pMapCoord__14; // [esp+E4h] [ebp-44h] BYREF
  CellStruct pMapCoord__9; // [esp+E8h] [ebp-40h] BYREF
  int pMapCoord__15; // [esp+ECh] [ebp-3Ch] BYREF
  CellStruct v163; // [esp+F0h] [ebp-38h] BYREF
  CellStruct v164; // [esp+F4h] [ebp-34h] BYREF
  CellStruct v165; // [esp+F8h] [ebp-30h] BYREF
  CellStruct v166; // [esp+FCh] [ebp-2Ch] BYREF
  CellStruct v167; // [esp+100h] [ebp-28h] BYREF
  CellStruct v168; // [esp+104h] [ebp-24h] BYREF
  CellStruct v169; // [esp+108h] [ebp-20h] BYREF
  CellStruct v170; // [esp+10Ch] [ebp-1Ch] BYREF
  CellStruct v171; // [esp+110h] [ebp-18h] BYREF
  CellStruct v172; // [esp+114h] [ebp-14h] BYREF
  CellStruct v173; // [esp+118h] [ebp-10h] BYREF
  CellStruct v174; // [esp+11Ch] [ebp-Ch] BYREF
  CellStruct v175; // [esp+120h] [ebp-8h] BYREF
  CellStruct v176; // [esp+124h] [ebp-4h] BYREF

  this_1 = this; /*0x59e750*/
  *a6 = 0; /*0x59e754*/
  pMapCoord__20 = 0; /*0x59e761*/
  n12_1 = 0; /*0x59e763*/
  n12 = 0; /*0x59e765*/
  LODWORD(X_8) = 0; /*0x59e76a*/
  X_9 = 0; /*0x59e771*/
  pMapCoord__21 = 0; /*0x59e775*/
  n4_1 = 0; /*0x59e779*/
  n4 = 0; /*0x59e77d*/
  MapCoords_9 = 0; /*0x59e781*/
  pMapCoord__22 = 0; /*0x59e785*/
  n8_1 = 0; /*0x59e789*/
  n8 = 0; /*0x59e78d*/
  X_5 = 0; /*0x59e791*/
  Y = 0; /*0x59e795*/
  n512 = 0; /*0x59e799*/
  n512_1 = 0; /*0x59e79d*/
  switch ( a5 ) /*0x59e7a7*/
  {
    case 0: /*0x59e7a7*/
      X_10 = *a3; /*0x59e7bc*/
      Y_1 = a3[1]; /*0x59e7c2*/
      v13 = *a4 - X_10; /*0x59e7c6*/
      pMapCoord__20 = (Y_1 - 12); /*0x59e7cb*/
      Y_1 -= 4; /*0x59e7ce*/
      n12_1 = v13 + 5; /*0x59e7d1*/
      LODWORD(X_8) = X_10 - 2; /*0x59e7d5*/
      n4_1 = v13 + 1; /*0x59e7de*/
      n4 = 4; /*0x59e7e7*/
      n8 = 8; /*0x59e7f0*/
      n8_1 = v13 + 1; /*0x59e7f8*/
      X_5 = 0; /*0x59e803*/
      n512_3 = 512 - Y_1; /*0x59e807*/
      pMapCoord__21 = Y_1; /*0x59e80e*/
      Y = Y_1; /*0x59e812*/
      LOWORD(v123) = X_10; /*0x59e816*/
      HIWORD(v123) = Y_1; /*0x59e81b*/
      v15 = v123; /*0x59e820*/
      n12 = 12; /*0x59e824*/
      X_9 = X_10; /*0x59e829*/
      MapCoords_9 = X_10; /*0x59e82d*/
      pMapCoord__22 = pMapCoord__20; /*0x59e831*/
      n512 = 512; /*0x59e835*/
      n512_1 = n512_3; /*0x59e839*/
      goto LABEL_6; /*0x59e83d*/
    case 2: /*0x59e7a7*/
      n12_1 = 12; /*0x59e8dc*/
      v19 = *a3; /*0x59e8e1*/
      pMapCoord__23 = a3[1]; /*0x59e8e4*/
      v21 = a4[1] - *&pMapCoord__23; /*0x59e8ef*/
      LODWORD(X_8) = v19 + 1; /*0x59e8f1*/
      pMapCoord__20 = (*&pMapCoord__23 - 2); /*0x59e8f8*/
      n12 = v21 + 5; /*0x59e8fb*/
      n4 = v21 + 1; /*0x59e904*/
      X_9 = v19 + 1; /*0x59e908*/
      n4_1 = 4; /*0x59e911*/
      n8 = v21 + 1; /*0x59e918*/
      pMapCoord__21 = pMapCoord__23; /*0x59e923*/
      pMapCoord__22 = pMapCoord__23; /*0x59e927*/
      n8_1 = 8; /*0x59e92b*/
      X_5 = 0; /*0x59e92f*/
      Y = 0; /*0x59e933*/
      LOWORD(v123) = v19 + 5; /*0x59e937*/
      HIWORD(v123) = pMapCoord__23.X; /*0x59e93c*/
      MapCoords_9 = (v19 + 5); /*0x59e94d*/
      n512 = v19 + 4; /*0x59e951*/
      n512_1 = 512; /*0x59e955*/
      break; /*0x59e95d*/
    case 4: /*0x59e7a7*/
      n12 = 12; /*0x59e850*/
      X_11 = *a4; /*0x59e855*/
      v17 = a4[1]; /*0x59e85b*/
      v18 = *a3 - X_11; /*0x59e85f*/
      pMapCoord__20 = (v17 + 1); /*0x59e864*/
      LODWORD(X_8) = X_11 - 2; /*0x59e867*/
      n12_1 = v18 + 5; /*0x59e86e*/
      n4_1 = v18 + 1; /*0x59e872*/
      n8_1 = v18 + 1; /*0x59e876*/
      n8 = 8; /*0x59e887*/
      X_9 = X_11; /*0x59e88b*/
      n4 = 4; /*0x59e88f*/
      MapCoords_9 = X_11; /*0x59e893*/
      pMapCoord__22 = (v17 + 5); /*0x59e897*/
      LOWORD(v123) = X_11; /*0x59e89d*/
      HIWORD(v123) = v17 + 1; /*0x59e8a2*/
      pMapCoord__21 = (v17 + 1); /*0x59e8b1*/
      X_5 = 0; /*0x59e8b5*/
      Y = 0; /*0x59e8b9*/
      n512 = 512; /*0x59e8bd*/
      n512_1 = v17 + 4; /*0x59e8c1*/
      break; /*0x59e8c9*/
    case 6: /*0x59e7a7*/
      n12_1 = 12; /*0x59e970*/
      X_7 = *a4; /*0x59e975*/
      pMapCoord__24 = a4[1]; /*0x59e978*/
      v24 = a3[1] - *&pMapCoord__24; /*0x59e983*/
      MapCoords_1 = (X_7 - 12); /*0x59e985*/
      LODWORD(X_8) = X_7 - 12; /*0x59e989*/
      n12 = v24 + 5; /*0x59e995*/
      X_7 -= 4; /*0x59e998*/
      n4_1 = 4; /*0x59e99b*/
      n4 = v24 + 1; /*0x59e9a4*/
      MapCoords_9 = MapCoords_1; /*0x59e9a8*/
      n8 = v24 + 1; /*0x59e9ac*/
      n8_1 = 8; /*0x59e9ba*/
      n512_2 = 512 - X_7; /*0x59e9be*/
      Y = 0; /*0x59e9c2*/
      X_9 = X_7; /*0x59e9cb*/
      X_5 = X_7; /*0x59e9cf*/
      LOWORD(v123) = X_7; /*0x59e9d3*/
      HIWORD(v123) = pMapCoord__24.X; /*0x59e9d8*/
      v15 = v123; /*0x59e9dd*/
      pMapCoord__20 = (*&pMapCoord__24 - 2); /*0x59e9e1*/
      pMapCoord__21 = pMapCoord__24; /*0x59e9e4*/
      pMapCoord__22 = pMapCoord__24; /*0x59e9e8*/
      n512 = n512_2; /*0x59e9ec*/
      n512_1 = 512; /*0x59e9f0*/
LABEL_6:
      v123 = v15; /*0x59e9f4*/
      break; /*0x59e9f4*/
    default:
      break;
  }
  X = pMapCoord__20.X; /*0x59e9fa*/
  pMapCoord__6 = pMapCoord__20; /*0x59ea00*/
  pMapCoord__2 = (*&pMapCoord__20 + n12); /*0x59ea04*/
  if ( *&pMapCoord__20 >= *&pMapCoord__20 + n12 ) /*0x59ea08*/
  {
    v28 = dword_ABED04; /*0x59eacd*/
  }
  else
  {
    MapCoords_10 = X_8 + n12_1; /*0x59ea15*/
    v28 = dword_ABED04; /*0x59ea17*/
    MapCoords_1 = MapCoords_10; /*0x59ea1c*/
    do /*0x59eab7*/
    {
      X_2 = X_8; /*0x59ea20*/
      if ( X_8 < MapCoords_10 ) /*0x59ea29*/
      {
        X_1 = X; /*0x59ea2b*/
        do /*0x59ea31*/
        {
          v31 = X_1 + X_2; /*0x59ea31*/
          if ( v31 > v28 && X_2 - X_1 < v28 && X_1 - X_2 < v28 && v31 <= dword_ABED08 ) /*0x59ea4e*/
          {
            if ( !dword_ABED10 ) /*0x59ea58*/
              return 1; /*0x59ea58*/
            if ( *(dword_ABED10 + 20 * X_2 + 20 * dword_89C2DC * X_1 + 14) ) /*0x59ea6b*/
              return 1; /*0x59ea6b*/
            pMapCoord_.X = X_2; /*0x59ea80*/
            pMapCoord_.Y = pMapCoord__6.X; /*0x59ea85*/
            CellAt_MapCrd = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord_); /*0x59ea8a*/
            if ( !sub_486380(CellAt_MapCrd) ) /*0x59ea91*/
              return 1; /*0x59eaca*/
            v28 = dword_ABED04; /*0x59ea9a*/
          }
          MapCoords_10 = MapCoords_1; /*0x59ea9f*/
          ++X_2; /*0x59eaa3*/
        }
        while ( X_2 < *&MapCoords_1 ); /*0x59ea31*/
      }
      X = pMapCoord__6.X + 1; /*0x59eaa8*/
      ++*&pMapCoord__6; /*0x59eab3*/
    }
    while ( *&pMapCoord__6 < *&pMapCoord__2 ); /*0x59eab7*/
  }
  pMapCoord__6 = pMapCoord__21; /*0x59eadc*/
  MapCoords_1 = (*&pMapCoord__21 + n4); /*0x59eae2*/
  if ( *&pMapCoord__21 < *&pMapCoord__21 + n4 ) /*0x59eae6*/
  {
    pMapCoord__2 = (X_9 + n4_1); /*0x59eaf6*/
    do /*0x59ec43*/
    {
      for ( X_3 = X_9; X_3 < *&pMapCoord__2; ++X_3 ) /*0x59eb04*/
      {
        v35 = X_3 + pMapCoord__6.X; /*0x59eb12*/
        if ( v35 > v28 && X_3 - pMapCoord__6.X < v28 && pMapCoord__6.X - X_3 < v28 && v35 <= dword_ABED08 ) /*0x59eb42*/
        {
          do /*0x59eb77*/
          {
            X_8 = Randomizer::Random(&dword_ABE890); /*0x59eb54*/
            n5 = Game::F2I64(X_8 * 0.000000001396983862248478); /*0x59eb6f*/
          }
          while ( n5 > 5 ); /*0x59eb77*/
          pMapCoord_.Y = pMapCoord__6.X; /*0x59eb84*/
          IsoTileTypeIndex = n5 + nIdx; /*0x59eb8d*/
          pMapCoord_.X = X_3; /*0x59eb96*/
          MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord_)->IsoTileTypeIndex = IsoTileTypeIndex; /*0x59eba0*/
          do /*0x59ebd6*/
          {
            v139 = Randomizer::Random(&dword_ABE890); /*0x59ebad*/
            n3 = Game::F2I64(v139 * 9.31322574832319e-10); /*0x59ebcc*/
          }
          while ( n3 > 3 ); /*0x59ebd6*/
          X_4 = pMapCoord__6.X; /*0x59ebd8*/
          pMapCoord__1.X = X_3; /*0x59ebe6*/
          pMapCoord__1.Y = pMapCoord__6.X; /*0x59ebeb*/
          MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord__1)->Height = n3; /*0x59ebf5*/
          if ( dword_ABED10 ) /*0x59ec03*/
            *(dword_ABED10 + 20 * X_3 + 20 * dword_89C2DC * X_4 + 14) = a2; /*0x59ec1e*/
          v28 = dword_ABED04; /*0x59ec22*/
        }
      }
      ++*&pMapCoord__6; /*0x59ec3f*/
    }
    while ( *&pMapCoord__6 < *&MapCoords_1 ); /*0x59ec43*/
  }
  v40 = sub_5A08D0(this_1, &X_5, this_1[194], 0.003, &X_5, &v123, 0); /*0x59ec6a*/
  if ( v40 ) /*0x59ec6e*/
  {
    v122 = sub_57A0C0(this_1[194], 0); /*0x59ec8d*/
    if ( v122 ) /*0x59ec91*/
    {
      v122 = sub_5A0160(this_1[194], 2, X_5, Y, n512, n512_1, 0, 0); /*0x59ecd5*/
      if ( v122 ) /*0x59ecd9*/
      {
        v41 = this_1[194]; /*0x59ece3*/
        sub_578350(&MouseClass::Instance); /*0x59ecee*/
        for ( i = MapClass::CellIteratorNext(&MouseClass::Instance); /*0x59ecff*/
              i;
              i = MapClass::CellIteratorNext(&MouseClass::Instance) )
        {
          MapCoords = i->MapCoords; /*0x59ed07*/
          MapCoords_1 = MapCoords; /*0x59ed0c*/
          if ( dword_ABED10 ) /*0x59ed10*/
            v44 = *(dword_ABED10 + 20 * MapCoords.X + 20 * dword_89C2DC * MapCoords_1.Y + 14); /*0x59ed2e*/
          else
            v44 = -1; /*0x59ed12*/
          if ( v44 == v41 ) /*0x59ed34*/
            i->Level += 4; /*0x59ed36*/
        }
        pMapCoord__6 = pMapCoord__22; /*0x59ed53*/
        MapCoords_1 = (n8 + *&pMapCoord__22); /*0x59ed5c*/
        if ( *&pMapCoord__22 < n8 + *&pMapCoord__22 ) /*0x59ed60*/
        {
          v45 = dword_ABED04; /*0x59ed70*/
          pMapCoord__1 = (*&MapCoords_9 + n8_1); /*0x59ed76*/
          do /*0x59eec4*/
          {
            for ( MapCoords_11 = MapCoords_9; *&MapCoords_11 < *&pMapCoord__1; ++*&MapCoords_11 ) /*0x59ed84*/
            {
              v47 = MapCoords_11.X + pMapCoord__6.X; /*0x59ed92*/
              if ( v47 > v45 /*0x59edc2*/
                && MapCoords_11.X - pMapCoord__6.X < v45
                && pMapCoord__6.X - MapCoords_11.X < v45
                && v47 <= dword_ABED08 )
              {
                do /*0x59edf7*/
                {
                  X_8 = Randomizer::Random(&dword_ABE890); /*0x59edd4*/
                  n5_1 = Game::F2I64(X_8 * 0.000000001396983862248478); /*0x59edef*/
                }
                while ( n5_1 > 5 ); /*0x59edf7*/
                pMapCoord__2.Y = pMapCoord__6.X; /*0x59ee04*/
                IsoTileTypeIndex_1 = n5_1 + nIdx; /*0x59ee0d*/
                pMapCoord__2.X = MapCoords_11.X; /*0x59ee16*/
                MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord__2)->IsoTileTypeIndex = IsoTileTypeIndex_1; /*0x59ee20*/
                do /*0x59ee56*/
                {
                  v139 = Randomizer::Random(&dword_ABE890); /*0x59ee2d*/
                  n3_1 = Game::F2I64(v139 * 9.31322574832319e-10); /*0x59ee4c*/
                }
                while ( n3_1 > 3 ); /*0x59ee56*/
                X_6 = pMapCoord__6.X; /*0x59ee58*/
                pMapCoord_.X = MapCoords_11.X; /*0x59ee66*/
                pMapCoord_.Y = pMapCoord__6.X; /*0x59ee6b*/
                MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord_)->Height = n3_1; /*0x59ee75*/
                if ( dword_ABED10 ) /*0x59ee83*/
                  *(dword_ABED10 + 20 * MapCoords_11.X + 20 * dword_89C2DC * X_6 + 14) = a2; /*0x59ee9e*/
                v45 = dword_ABED04; /*0x59eea2*/
              }
            }
            ++*&pMapCoord__6; /*0x59eec0*/
          }
          while ( *&pMapCoord__6 < *&MapCoords_1 ); /*0x59eec4*/
        }
        v116 = 1; /*0x59eed1*/
        switch ( a5 ) /*0x59eee1*/
        {
          case 0: /*0x59eee1*/
            pMapCoord__6.Y = pMapCoord__21.X - 2; /*0x59fb4d*/
            pMapCoord__6.X = X_9 - 2; /*0x59fb60*/
            MapCoords_1.X = X_9 - 2; /*0x59fb65*/
            MapCoords_1.Y = pMapCoord__21.X - 4; /*0x59fb6a*/
            MapCoords_2 = MapCoords_1; /*0x59fb79*/
            Level = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &MapCoords_2)->Level; /*0x59fb85*/
            MouseClass::Instance.CurrentBuildingType = IsometricTileTypeClass::Array.Items[nIdx_3]; /*0x59fba5*/
            sub_4A91B0(&MouseClass::Instance, &v164, &pMapCoord__6); /*0x59fbb2*/
            this_2 = this_1; /*0x59fbb7*/
            sub_57B440(0, 0x10000, Level, this_1[194], &v116, 0); /*0x59fbd6*/
            n8_2 = n8_1; /*0x59fbdb*/
            v100 = n8_1 + 2; /*0x59fbea*/
            CurrentBuildingType = IsometricTileTypeClass::Array.Items[nIdx_3 + 3]; /*0x59fbed*/
            v119[0] = n8_1 + 2; /*0x59fbf5*/
            MouseClass::Instance.CurrentBuildingType = CurrentBuildingType; /*0x59fbfe*/
            MapCoords_1.Y = pMapCoord__6.Y; /*0x59fc0b*/
            MapCoords_1.X = pMapCoord__6.X + n8_1 + 2; /*0x59fc10*/
            MapCoords_3 = MapCoords_1; /*0x59fc2e*/
            sub_4A91B0(&MouseClass::Instance, &v166, &MapCoords_3); /*0x59fc35*/
            sub_57B440(0, 0x10000, Level, this_2[194], &v116, 0); /*0x59fc55*/
            MapCoords_1.Y = pMapCoord__6.Y; /*0x59fc64*/
            MapCoords_1.X = pMapCoord__6.X + 1; /*0x59fc69*/
            MapCoords_4 = MapCoords_1; /*0x59fc79*/
            MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &MapCoords_4)->IsoTileTypeIndex = 0xFFFF; /*0x59fc8b*/
            v119[0] = v100; /*0x59fc9b*/
            MapCoords_1.Y = pMapCoord__6.Y; /*0x59fca6*/
            MapCoords_1.X = pMapCoord__6.X + v100; /*0x59fcab*/
            MapCoords_5 = MapCoords_1; /*0x59fcbb*/
            v102 = n8_2 + 2; /*0x59fccd*/
            v103 = 0; /*0x59fcd0*/
            for ( MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &MapCoords_5)->IsoTileTypeIndex = 0xFFFF; /*0x59fcdb*/
                  v103 < v102;
                  v104->Level -= 4 )
            {
              v119[0] = v103 + 1; /*0x59fce4*/
              MapCoords_1.X = pMapCoord__6.X + v103 + 1; /*0x59fcf4*/
              MapCoords_1.Y = pMapCoord__6.Y; /*0x59fd00*/
              MapCoords_6 = MapCoords_1; /*0x59fd0f*/
              v104 = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &MapCoords_6); /*0x59fd16*/
              ++v103; /*0x59fd29*/
            }
            MapCoords_1.Y = pMapCoord__6.Y + 1; /*0x59fd3c*/
            MapCoords_1.X = pMapCoord__6.X - 1; /*0x59fd41*/
            pMapCoord_ = MapCoords_1; /*0x59fd4a*/
            MapCoords_1.Y = pMapCoord__6.Y + 1; /*0x59fd55*/
            v119[0] = n8_1 + 4; /*0x59fd5a*/
            v105 = (pMapCoord__6.X - 1); /*0x59fd65*/
            v106 = (pMapCoord__6.Y + 1); /*0x59fd68*/
            MapCoords_1.X = pMapCoord__6.X + n8_1 + 4; /*0x59fd6b*/
            pMapCoord__1 = MapCoords_1; /*0x59fd74*/
            v107 = dword_ABED04; /*0x59fd78*/
            if ( v106 + v105 > dword_ABED04 /*0x59fda5*/
              && v105 - v106 < dword_ABED04
              && v106 - v105 < dword_ABED04
              && v106 + v105 <= dword_ABED08 )
            {
              MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord_)->IsoTileTypeIndex = 0xFFFF; /*0x59fdba*/
              v108 = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord_); /*0x59fdc7*/
              v108->Level += 4; /*0x59fddf*/
              MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord_)->Height = 0; /*0x59fdeb*/
              if ( dword_ABED10 ) /*0x59fdfa*/
                *(dword_ABED10 + 20 * pMapCoord_.X + 20 * dword_89C2DC * pMapCoord_.Y + 14) = this_2[194]; /*0x59fe1b*/
              v107 = dword_ABED04; /*0x59fe1f*/
            }
            v109 = pMapCoord__1.Y + pMapCoord__1.X; /*0x59fe2f*/
            if ( v109 > v107 /*0x59fe56*/
              && pMapCoord__1.X - pMapCoord__1.Y < v107
              && pMapCoord__1.Y - pMapCoord__1.X < v107
              && v109 <= dword_ABED08 )
            {
              MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord__1)->IsoTileTypeIndex = 0xFFFF; /*0x59fe6b*/
              v110 = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord__1); /*0x59fe78*/
              v110->Level += 4; /*0x59fe90*/
              MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord__1)->Height = 0; /*0x59fe9c*/
              if ( dword_ABED10 ) /*0x59feab*/
                *(dword_ABED10 + 20 * pMapCoord__1.X + 20 * dword_89C2DC * pMapCoord__1.Y + 14) = this_2[194]; /*0x59fecc*/
            }
            n8_5 = 0; /*0x59fed4*/
            if ( n8_1 > 0 ) /*0x59fed8*/
            {
              n8_3 = n8_1; /*0x59fede*/
              n8_4 = n8_1; /*0x59fee0*/
              do /*0x59ffce*/
              {
                v114 = n8_5 + 2; /*0x59fef9*/
                if ( n8_3 % 2 ) /*0x59fef8*/
                {
                  v119[0] = n8_5 + 2; /*0x59fefe*/
                  MapCoords_1.X = pMapCoord__6.X + v114; /*0x59ff0a*/
                  MapCoords_1.Y = pMapCoord__6.Y + 1; /*0x59ff16*/
                  MapCoords_7 = MapCoords_1; /*0x59ff2d*/
                  sub_4A91B0(&MouseClass::Instance, &v139, &MapCoords_7); /*0x59ff34*/
                  ++n8_5; /*0x59ff44*/
                  --n8_3; /*0x59ff45*/
                  MouseClass::Instance.CurrentBuildingType = IsometricTileTypeClass::Array.Items[nIdx_3 + 1]; /*0x59ff4a*/
                }
                else
                {
                  v125 = n8_5 + 2; /*0x59ff52*/
                  pMapCoord__2.X = pMapCoord__6.X + v114; /*0x59ff5e*/
                  pMapCoord__2.Y = pMapCoord__6.Y + 1; /*0x59ff6a*/
                  pMapCoord__3 = pMapCoord__2; /*0x59ff81*/
                  sub_4A91B0(&MouseClass::Instance, &X_8, &pMapCoord__3); /*0x59ff88*/
                  n8_5 += 2; /*0x59ff98*/
                  n8_3 -= 2; /*0x59ff9b*/
                  MouseClass::Instance.CurrentBuildingType = IsometricTileTypeClass::Array.Items[nIdx_3 + 2]; /*0x59ffa2*/
                }
                sub_57B440(0, 0x10000, Level, this_1[194], &v116, 0); /*0x59ffc7*/
              }
              while ( n8_5 < n8_4 ); /*0x59ffce*/
            }
            break; /*0x59ffce*/
          case 2: /*0x59eee1*/
            n8_6 = n8; /*0x59eeec*/
            v119[0] = MapCoords_9.X; /*0x59eef4*/
            pMapCoord__2.X = MapCoords_9.X + 2; /*0x59eeff*/
            v119[1] = n8 + pMapCoord__22.X; /*0x59ef0b*/
            pMapCoord__2.Y = n8 + pMapCoord__22.X; /*0x59ef10*/
            pMapCoord__4 = pMapCoord__2; /*0x59ef1f*/
            Level_1 = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord__4)->Level; /*0x59ef2b*/
            MouseClass::Instance.CurrentBuildingType = IsometricTileTypeClass::Array.Items[nIdx_0]; /*0x59ef4b*/
            sub_4A91B0(&MouseClass::Instance, &v168, v119); /*0x59ef58*/
            this_3 = this_1; /*0x59ef5d*/
            sub_57B440(0, 0x10000, Level_1, this_1[194], &v116, 0); /*0x59ef7c*/
            MouseClass::Instance.CurrentBuildingType = IsometricTileTypeClass::Array.Items[nIdx_0 + 3]; /*0x59ef98*/
            v126 = n8_6 + 2; /*0x59efa2*/
            pMapCoord__2.X = v119[0]; /*0x59efab*/
            pMapCoord__2.Y = v119[1] - (n8_6 + 2); /*0x59efb9*/
            pMapCoord__5 = pMapCoord__2; /*0x59efd0*/
            sub_4A91B0(&MouseClass::Instance, &v163, &pMapCoord__5); /*0x59efd7*/
            sub_57B440(0, 0x10000, Level_1, this_3[194], &v116, 0); /*0x59eff7*/
            v55 = v119[1]; /*0x59effc*/
            v126 = n8_6 + 3; /*0x59f010*/
            pMapCoord__2.X = v119[0]; /*0x59f015*/
            pMapCoord__1 = (*v119 + 0x20000); /*0x59f01e*/
            pMapCoord__2.Y = v119[1] - (n8_6 + 3); /*0x59f02f*/
            v56 = dword_ABED04; /*0x59f038*/
            v57 = (v119[1] + 2); /*0x59f041*/
            pMapCoord__6 = pMapCoord__2; /*0x59f044*/
            v58 = v57 + v119[0]; /*0x59f048*/
            if ( v58 > dword_ABED04 /*0x59f06f*/
              && v119[0] - v57 < dword_ABED04
              && v57 - v119[0] < dword_ABED04
              && v58 <= dword_ABED08 )
            {
              MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord__1)->IsoTileTypeIndex = 0xFFFF; /*0x59f084*/
              v59 = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord__1); /*0x59f095*/
              v59->Level += 4; /*0x59f0a8*/
              MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord__1)->Height = 0; /*0x59f0b9*/
              if ( dword_ABED10 ) /*0x59f0c8*/
                *(dword_ABED10 + 20 * pMapCoord__1.X + 20 * dword_89C2DC * pMapCoord__1.Y + 14) = this_1[194]; /*0x59f0ed*/
              v56 = dword_ABED04; /*0x59f0f1*/
              v55 = v119[1]; /*0x59f0f7*/
            }
            v60 = pMapCoord__6.Y + pMapCoord__6.X; /*0x59f105*/
            if ( v60 > v56 /*0x59f12c*/
              && pMapCoord__6.X - pMapCoord__6.Y < v56
              && pMapCoord__6.Y - pMapCoord__6.X < v56
              && v60 <= dword_ABED08 )
            {
              MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord__6)->IsoTileTypeIndex = 0xFFFF; /*0x59f145*/
              v61 = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord__6); /*0x59f152*/
              v61->Level += 4; /*0x59f16a*/
              MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord__6)->Height = 0; /*0x59f176*/
              if ( dword_ABED10 ) /*0x59f185*/
                *(dword_ABED10 + 20 * pMapCoord__6.X + 20 * dword_89C2DC * pMapCoord__6.Y + 14) = this_1[194]; /*0x59f1aa*/
              v55 = v119[1]; /*0x59f1ae*/
            }
            n8_9 = 0; /*0x59f1b6*/
            if ( n8 > 0 ) /*0x59f1ba*/
            {
              n8_7 = n8; /*0x59f1c0*/
              n8_8 = n8; /*0x59f1c2*/
              while ( 1 ) /*0x59f1d8*/
              {
                if ( n8_7 % 2 ) /*0x59f1d8*/
                {
                  v126 = n8_9 + 1; /*0x59f1e3*/
                  pMapCoord__2.X = v119[0]; /*0x59f1ee*/
                  pMapCoord__2.Y = v55 - (n8_9 + 1); /*0x59f1f3*/
                  pMapCoord__7 = pMapCoord__2; /*0x59f211*/
                  sub_4A91B0(&MouseClass::Instance, &v170, &pMapCoord__7); /*0x59f218*/
                  ++n8_9; /*0x59f228*/
                  --n8_7; /*0x59f229*/
                  MouseClass::Instance.CurrentBuildingType = IsometricTileTypeClass::Array.Items[nIdx_0 + 1]; /*0x59f22e*/
                }
                else
                {
                  MapCoords_1.Y = n8_9 + 2; /*0x59f23e*/
                  pMapCoord_.X = v119[0]; /*0x59f249*/
                  pMapCoord_.Y = v55 - (n8_9 + 2); /*0x59f24e*/
                  pMapCoord__8 = pMapCoord_; /*0x59f26c*/
                  sub_4A91B0(&MouseClass::Instance, &v172, &pMapCoord__8); /*0x59f273*/
                  n8_9 += 2; /*0x59f283*/
                  n8_7 -= 2; /*0x59f286*/
                  MouseClass::Instance.CurrentBuildingType = IsometricTileTypeClass::Array.Items[nIdx_0 + 2]; /*0x59f28d*/
                }
                sub_57B440(0, 0x10000, Level_1, this_1[194], &v116, 0); /*0x59f2b2*/
                if ( n8_9 >= n8_8 ) /*0x59f2b9*/
                  break; /*0x59f2b9*/
                v55 = v119[1]; /*0x59f1c6*/
              }
            }
            break; /*0x59f1c6*/
          case 4: /*0x59eee1*/
            pMapCoord__6.Y = pMapCoord__22.X; /*0x59f784*/
            pMapCoord__2.Y = pMapCoord__22.X + 2; /*0x59f78f*/
            pMapCoord__6.X = MapCoords_9.X - 2; /*0x59f79b*/
            pMapCoord__2.X = MapCoords_9.X - 2; /*0x59f7a0*/
            pMapCoord__9 = pMapCoord__2; /*0x59f7af*/
            Level_2 = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord__9)->Level; /*0x59f7bb*/
            MouseClass::Instance.CurrentBuildingType = IsometricTileTypeClass::Array.Items[nIdx_2]; /*0x59f7db*/
            sub_4A91B0(&MouseClass::Instance, &v167, &pMapCoord__6); /*0x59f7e8*/
            this_4 = this_1; /*0x59f7ed*/
            sub_57B440(0, 0x10000, Level_2, this_1[194], &v116, 0); /*0x59f80c*/
            n8_10 = n8_1; /*0x59f81c*/
            MouseClass::Instance.CurrentBuildingType = IsometricTileTypeClass::Array.Items[nIdx_2 + 3]; /*0x59f82b*/
            MapCoords_1.X = n8_1 + 2; /*0x59f831*/
            pMapCoord__2.X = pMapCoord__6.X + n8_1 + 2; /*0x59f841*/
            pMapCoord__2.Y = pMapCoord__6.Y; /*0x59f846*/
            pMapCoord__10 = pMapCoord__2; /*0x59f85d*/
            sub_4A91B0(&MouseClass::Instance, &v175, &pMapCoord__10); /*0x59f86b*/
            sub_57B440(0, 0x10000, Level_2, this_4[194], &v116, 0); /*0x59f88b*/
            pMapCoord__2.Y = pMapCoord__6.Y; /*0x59f89c*/
            MapCoords_1.X = n8_10 + 4; /*0x59f8a1*/
            pMapCoord__2.X = pMapCoord__6.X - 1; /*0x59f8af*/
            pMapCoord__11 = pMapCoord__2; /*0x59f8b4*/
            pMapCoord__2.X = pMapCoord__6.X + n8_10 + 4; /*0x59f8b8*/
            pMapCoord_ = pMapCoord__11; /*0x59f8c6*/
            v88 = dword_ABED04; /*0x59f8ca*/
            pMapCoord__1 = pMapCoord__2; /*0x59f8d0*/
            v89 = (pMapCoord__6.X - 1); /*0x59f8d4*/
            v90 = pMapCoord__6.Y + v89; /*0x59f8da*/
            if ( v90 > dword_ABED04 /*0x59f901*/
              && v89 - pMapCoord__6.Y < dword_ABED04
              && pMapCoord__6.Y - v89 < dword_ABED04
              && v90 <= dword_ABED08 )
            {
              MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord_)->IsoTileTypeIndex = 0xFFFF; /*0x59f912*/
              v91 = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord_); /*0x59f923*/
              v91->Level += 4; /*0x59f936*/
              MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord_)->Height = 0; /*0x59f947*/
              if ( dword_ABED10 ) /*0x59f956*/
                *(dword_ABED10 + 20 * pMapCoord_.X + 20 * dword_89C2DC * pMapCoord_.Y + 14) = this_4[194]; /*0x59f977*/
              v88 = dword_ABED04; /*0x59f97b*/
            }
            v92 = pMapCoord__1.Y + pMapCoord__1.X; /*0x59f98b*/
            if ( v92 > v88 /*0x59f9b2*/
              && pMapCoord__1.X - pMapCoord__1.Y < v88
              && pMapCoord__1.Y - pMapCoord__1.X < v88
              && v92 <= dword_ABED08 )
            {
              MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord__1)->IsoTileTypeIndex = 0xFFFF; /*0x59f9c7*/
              v93 = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord__1); /*0x59f9d4*/
              v93->Level += 4; /*0x59f9ec*/
              MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord__1)->Height = 0; /*0x59f9f8*/
              if ( dword_ABED10 ) /*0x59fa07*/
                *(dword_ABED10 + 20 * pMapCoord__1.X + 20 * dword_89C2DC * pMapCoord__1.Y + 14) = this_4[194]; /*0x59fa28*/
            }
            n8_13 = 0; /*0x59fa30*/
            if ( n8_1 > 0 ) /*0x59fa34*/
            {
              n8_11 = n8_1; /*0x59fa3a*/
              n8_12 = n8_1; /*0x59fa3c*/
              do /*0x59fb34*/
              {
                if ( n8_11 % 2 ) /*0x59fa4b*/
                {
                  v125 = n8_13 + 2; /*0x59fa55*/
                  pMapCoord__2.X = n8_13 + 2 + pMapCoord__6.X; /*0x59fa65*/
                  pMapCoord__2.Y = pMapCoord__6.Y; /*0x59fa6a*/
                  pMapCoord__12 = pMapCoord__2; /*0x59fa88*/
                  sub_4A91B0(&MouseClass::Instance, &v169, &pMapCoord__12); /*0x59fa8f*/
                  ++n8_13; /*0x59fa9f*/
                  --n8_11; /*0x59faa0*/
                  MouseClass::Instance.CurrentBuildingType = IsometricTileTypeClass::Array.Items[nIdx_2 + 1]; /*0x59faa5*/
                }
                else
                {
                  v119[0] = n8_13 + 2; /*0x59fab4*/
                  MapCoords_1.X = n8_13 + 2 + pMapCoord__6.X; /*0x59fac4*/
                  MapCoords_1.Y = pMapCoord__6.Y; /*0x59fac9*/
                  MapCoords_8 = MapCoords_1; /*0x59fae7*/
                  sub_4A91B0(&MouseClass::Instance, &v173, &MapCoords_8); /*0x59faee*/
                  n8_13 += 2; /*0x59fafe*/
                  n8_11 -= 2; /*0x59fb01*/
                  MouseClass::Instance.CurrentBuildingType = IsometricTileTypeClass::Array.Items[nIdx_2 + 2]; /*0x59fb08*/
                }
                sub_57B440(0, 0x10000, Level_2, this_1[194], &v116, 0); /*0x59fb2d*/
              }
              while ( n8_13 < n8_12 ); /*0x59fb34*/
            }
            break; /*0x59fb34*/
          case 6: /*0x59eee1*/
            n8_14 = n8; /*0x59f2c8*/
            v119[0] = X_9 - 2; /*0x59f2d5*/
            v119[1] = n8 + pMapCoord__22.X; /*0x59f2da*/
            pMapCoord__2.Y = n8 + pMapCoord__22.X; /*0x59f2e6*/
            pMapCoord__2.X = X_9 - 4; /*0x59f2eb*/
            pMapCoord__13 = pMapCoord__2; /*0x59f301*/
            Level_3 = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord__13)->Level; /*0x59f319*/
            CurrentBuildingType_1 = IsometricTileTypeClass::Array.Items[nIdx_1]; /*0x59f320*/
            MapCoords_1 = Level_3; /*0x59f335*/
            MouseClass::Instance.CurrentBuildingType = CurrentBuildingType_1; /*0x59f339*/
            sub_4A91B0(&MouseClass::Instance, &v174, v119); /*0x59f33e*/
            this_5 = this_1; /*0x59f343*/
            sub_57B440(0, 0x10000, Level_3, this_1[194], &v116, 0); /*0x59f362*/
            MouseClass::Instance.CurrentBuildingType = IsometricTileTypeClass::Array.Items[nIdx_1 + 3]; /*0x59f37e*/
            v126 = n8_14 + 2; /*0x59f388*/
            pMapCoord__2.X = v119[0]; /*0x59f38d*/
            pMapCoord__2.Y = v119[1] - (n8_14 + 2); /*0x59f39f*/
            pMapCoord__14 = pMapCoord__2; /*0x59f3b6*/
            sub_4A91B0(&MouseClass::Instance, &v176, &pMapCoord__14); /*0x59f3bd*/
            sub_57B440(0, 0x10000, Level_3, this_5[194], &v116, 0); /*0x59f3dd*/
            pMapCoord__2 = (*v119 - 0x10000); /*0x59f3f8*/
            pMapCoord__15 = *v119 - 0x10000; /*0x59f407*/
            v69 = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord__15); /*0x59f40e*/
            v70 = n8_1 + 2; /*0x59f41c*/
            v69->IsoTileTypeIndex = 0xFFFF; /*0x59f41f*/
            v126 = v70; /*0x59f427*/
            pMapCoord__2.X = v119[0]; /*0x59f436*/
            pMapCoord__2.Y = v119[1] + v70; /*0x59f43b*/
            pMapCoord__16 = pMapCoord__2; /*0x59f44b*/
            MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord__16)->IsoTileTypeIndex = 0xFFFF; /*0x59f45d*/
            for ( j = 0; j < n8_14 + 2; v72->Level -= 4 ) /*0x59f467*/
            {
              pMapCoord__2.X = v119[0]; /*0x59f474*/
              pMapCoord__2.Y = v119[1] - j; /*0x59f479*/
              pMapCoord__17 = pMapCoord__2; /*0x59f489*/
              v72 = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord__17); /*0x59f496*/
              ++j; /*0x59f4a9*/
            }
            v73 = v119[1]; /*0x59f4b7*/
            pMapCoord__2.X = v119[0] + 1; /*0x59f4bb*/
            pMapCoord__2.Y = v119[1] + 2; /*0x59f4c3*/
            pMapCoord__1 = pMapCoord__2; /*0x59f4cc*/
            v126 = n8_14 + 3; /*0x59f4d3*/
            pMapCoord__2.X = v119[0] + 1; /*0x59f4de*/
            pMapCoord__2.Y = v119[1] - (n8_14 + 3); /*0x59f4e5*/
            pMapCoord__6 = pMapCoord__2; /*0x59f4ee*/
            v74 = (v119[0] + 1); /*0x59f4f2*/
            v75 = (v119[1] + 2); /*0x59f4f5*/
            v76 = dword_ABED04; /*0x59f4f8*/
            if ( v75 + v74 > dword_ABED04 /*0x59f525*/
              && v74 - v75 < dword_ABED04
              && v75 - v74 < dword_ABED04
              && v75 + v74 <= dword_ABED08 )
            {
              MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord__1)->IsoTileTypeIndex = 0xFFFF; /*0x59f53e*/
              v77 = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord__1); /*0x59f54b*/
              v77->Level += 4; /*0x59f563*/
              MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord__1)->Height = 0; /*0x59f56f*/
              if ( dword_ABED10 ) /*0x59f57e*/
                *(dword_ABED10 + 20 * pMapCoord__1.X + 20 * dword_89C2DC * pMapCoord__1.Y + 14) = this_1[194]; /*0x59f5a3*/
              v76 = dword_ABED04; /*0x59f5a7*/
              v73 = v119[1]; /*0x59f5ad*/
            }
            v78 = pMapCoord__6.Y + pMapCoord__6.X; /*0x59f5bb*/
            if ( v78 > v76 /*0x59f5e2*/
              && pMapCoord__6.X - pMapCoord__6.Y < v76
              && pMapCoord__6.Y - pMapCoord__6.X < v76
              && v78 <= dword_ABED08 )
            {
              MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord__6)->IsoTileTypeIndex = 0xFFFF; /*0x59f5fb*/
              v79 = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord__6); /*0x59f608*/
              v79->Level += 4; /*0x59f620*/
              MapClass::GetCellAt_MapCrd(&MouseClass::Instance, &pMapCoord__6)->Height = 0; /*0x59f62c*/
              if ( dword_ABED10 ) /*0x59f63b*/
                *(dword_ABED10 + 20 * pMapCoord__6.X + 20 * dword_89C2DC * pMapCoord__6.Y + 14) = this_1[194]; /*0x59f660*/
              v73 = v119[1]; /*0x59f664*/
            }
            n8_17 = 0; /*0x59f668*/
            if ( n8_14 > 0 ) /*0x59f66c*/
            {
              n8_15 = n8; /*0x59f672*/
              this_6 = this_1; /*0x59f676*/
              n8_16 = n8; /*0x59f67a*/
              while ( 1 ) /*0x59f690*/
              {
                if ( n8_15 % 2 ) /*0x59f690*/
                {
                  v126 = n8_17 + 1; /*0x59f69a*/
                  pMapCoord__2.Y = v73 - (n8_17 + 1); /*0x59f6a6*/
                  pMapCoord__2.X = v119[0] + 1; /*0x59f6ab*/
                  pMapCoord__18 = pMapCoord__2; /*0x59f6c9*/
                  sub_4A91B0(&MouseClass::Instance, &v165, &pMapCoord__18); /*0x59f6d0*/
                  ++n8_17; /*0x59f6e0*/
                  --n8_15; /*0x59f6e1*/
                  MouseClass::Instance.CurrentBuildingType = IsometricTileTypeClass::Array.Items[nIdx_1 + 1]; /*0x59f6e6*/
                }
                else
                {
                  HIWORD(this_1) = n8_17 + 2; /*0x59f6f5*/
                  pMapCoord_.Y = v73 - (n8_17 + 2); /*0x59f701*/
                  pMapCoord_.X = v119[0] + 1; /*0x59f706*/
                  pMapCoord__19 = pMapCoord_; /*0x59f724*/
                  sub_4A91B0(&MouseClass::Instance, &v171, &pMapCoord__19); /*0x59f72b*/
                  n8_17 += 2; /*0x59f73b*/
                  n8_15 -= 2; /*0x59f73e*/
                  MouseClass::Instance.CurrentBuildingType = IsometricTileTypeClass::Array.Items[nIdx_1 + 2]; /*0x59f745*/
                }
                sub_57B440(0, 0x10000, MapCoords_1.X, this_6[194], &v116, 0); /*0x59f76a*/
                if ( n8_17 >= n8_16 ) /*0x59f771*/
                  break; /*0x59f771*/
                v73 = v119[1]; /*0x59f67e*/
              }
            }
            break; /*0x59f67e*/
          default:
            break;
        }
      }
    }
    v40 = v122; /*0x59ffd4*/
  }
  X_5 = 0; /*0x59ffe4*/
  Y = 12; /*0x59ffea*/
  n512 = 0; /*0x59ffee*/
  n512_1 = -12; /*0x59fff2*/
  X_9 = -12; /*0x59fff6*/
  pMapCoord__21 = 0; /*0x59fffa*/
  n4_1 = 12; /*0x59fffe*/
  n4 = 0; /*0x5a0002*/
  if ( v40 ) /*0x5a0006*/
  {
    *a7 = *(&X_5 + a5 / 2) + *a7; /*0x5a0024*/
    *a8 = *(&X_9 + a5 / 2) + *a8; /*0x5a0033*/
  }
  *a6 = v40; /*0x5a003f*/
  return v40; /*0x59eac0*/
}