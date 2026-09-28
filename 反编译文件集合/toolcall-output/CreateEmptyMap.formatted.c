
The MCP server responded with: [{"type":"text","text":"{\"addr\":\"0x565C10\",\"code\":\"void __thiscall MapClass::CreateEmptyMap(MapClass *this, int *a2, CellStruct jj, char a4, char a5)\
{\
  int Capacity; // edi\
  int Cell_Zero_Zero_3; // esi\
  __int16 v8; // si\
  int Width_1; // edx\
  int v10; // eax\
  int Width_2; // ecx\
  CellClass *v12; // eax\
  int Width_3; // eax\
  CellClass *v14; // esi\
  int v15; // ebp\
  CellStruct MapCoords; // eax\
  char *v17; // ecx\
  _WORD *v18; // eax\
  _WORD *v19; // eax\
  int v20; // eax\
  int v21; // ecx\
  int v22; // eax\
  int v23; // ecx\
  int v24; // ecx\
  int v25; // eax\
  int v26; // ecx\
  int v27; // eax\
  int v28; // ecx\
  int v29; // eax\
  int v30; // ecx\
  int v31; // eax\
  int v32; // ecx\
  int v33; // eax\
  int v34; // ecx\
  int v35; // eax\
  int v36; // ecx\
  int v37; // eax\
  int v38; // ecx\
  int v39; // eax\
  int v40; // ecx\
  int v41; // eax\
  int v42; // ecx\
  int v43; // eax\
  int v44; // ecx\
  int v45; // eax\
  int v46; // ecx\
  int Z; // ebp\
  int Width_4; // edx\
  int Right; // eax\
  int v50; // esi\
  int Width_6; // edx\
  int Width_5; // eax\
  int v53; // edi\
  CellClass *v54; // ecx\
  CellClass *v55; // eax\
  CellClass *v56; // ebp\
  int Width_7; // eax\
  int MapCoords_1; // ecx\
  int v59; // eax\
  int v60; // edx\
  int v61; // ebp\
  unsigned int n0x40000; // eax\
  CellClass *p_MapClass::InvalidCell_1; // eax\
  CellClass *p_MapClass::InvalidCell; // esi\
  CellStruct MapCoords_3; // ecx\
  unsigned __int16 *p_SensorsOfHouses; // eax\
  int v67; // ecx\
  unsigned __int16 *p_DisguiseSensorsOfHouses; // eax\
  int AltFlags; // eax\
  int AltFlags_1; // ecx\
  int AltFlags_2; // eax\
  int AltFlags_3; // ecx\
  CellFlags Flags; // ecx\
  int Flags_1; // eax\
  int Flags_2; // ecx\
  int Flags_3; // eax\
  int Flags_4; // ecx\
  int Flags_5; // eax\
  int Flags_6; // ecx\
  int Flags_7; // eax\
  int Flags_8; // ecx\
  int Flags_9; // eax\
  int Flags_10; // ecx\
  int Flags_11; // eax\
  int Flags_12; // ecx\
  int Flags_13; // eax\
  int Flags_14; // ecx\
  int Flags_15; // eax\
  int Flags_16; // ecx\
  int Flags_17; // eax\
  int Flags_18; // ecx\
  int Flags_19; // eax\
  int Flags_20; // ecx\
  int Flags_21; // eax\
  int Flags_22; // ecx\
  int Width_8; // eax\
  CellClass *i; // eax\
  CellStruct MapCoords_4; // ecx\
  int Width_9; // eax\
  int v100; // edx\
  int v101; // esi\
  CellClass *v102; // ecx\
  CellClass *v103; // eax\
  CellClass *v104; // eax\
  int n702; // esi\
  CellStruct *pFoundationData; // eax\
  CellStruct *FoundationMapCrd; // eax\
  int Count; // esi\
  CoordStruct *v109; // eax\
  int X_1; // edi\
  int Y_1; // ebp\
  _DWORD *v112; // esi\
  int X_2; // eax\
  CoordStruct *v114; // eax\
  int v115; // edx\
  int j; // esi\
  int Count_1; // eax\
  AnimClass *v118; // ecx\
  int Y_2; // edx\
  AnimClass_vtbl *v120; // eax\
  int Z_4; // esi\
  int Cell_Zero_Zero_1; // ebp\
  _WORD *k; // eax\
  int v124; // esi\
  int Width_10; // edx\
  int v126; // ecx\
  int v127; // ecx\
  int v128; // edi\
  CellClass **Items; // eax\
  CellClass *Width_11; // ecx\
  __int16 v131; // si\
  int Width_12; // edx\
  int v133; // eax\
  int Width_13; // ebp\
  int Width_14; // eax\
  CellClass *m; // eax\
  CellFlags Flags_23; // edx\
  int OverlayTypeIndex; // ecx\
  unsigned int v139; // edx\
  int Cell_Zero_Zero_2; // esi\
  char v141; // [esp+5h] [ebp-6Dh]\
  CoordStruct v142; // [esp+1Ah] [ebp-58h] BYREF\
  CoordStruct this_pCoord; // [esp+26h] [ebp-4Ch] BYREF\
  int v144; // [esp+32h] [ebp-40h]\
  CellStruct pMapCrd; // [esp+36h] [ebp-3Ch] BYREF\
  int n24; // [esp+3Ah] [ebp-38h]\
  CoordStruct Z_1; // [esp+42h] [ebp-30h] BYREF\
  int Z_3; // [esp+4Eh] [ebp-24h]\
  char Z_2[4]; // [esp+52h] [ebp-20h] BYREF\
  int Y; // [esp+56h] [ebp-1Ch]\
  int v151; // [esp+5Ah] [ebp-18h]\
  int Y_3; // [esp+5Eh] [ebp-14h]\
  int Width; // [esp+62h] [ebp-10h]\
  CellStruct Cell_Zero_Zero; // [esp+66h] [ebp-Ch]\
  int Cell_Zero_Zero_4; // [esp+6Eh] [ebp-4h] BYREF\
  _DWORD *pBuffer_; // [esp+72h] [ebp+0h] BYREF\
  int n24_1; // [esp+76h] [ebp+4h]\
  CellStruct MapCoords_2; // [esp+76h] [ebp+4h]\
  char X; // [esp+76h] [ebp+4h]\
\
  Width = this->MapRect.Width; /*0x565c24*/\
  Cell_Zero_Zero = Cell_Zero_Zero_0; /*0x565c2e*/\
  Capacity = 0; /*0x565c37*/\
  Cell_Zero_Zero_3 = 0; /*0x565c3d*/\
  Z_1.Z = 0; /*0x565c41*/\
  v151 = 0; /*0x565c45*/\
  for ( Y_3 = 2 * MouseClass::Instance.MapRect.Height + 8; Cell_Zero_Zero_3 < ::Cell_Zero_Zero_2; ++Cell_Zero_Zero_3 ) /*0x565c4d*/\
    (*(**(dword_A8E364 + Cell_Zero_Zero_3) + 292))(*(dword_A8E364 + Cell_Zero_Zero_3), 0); /*0x565c5b*/\
  if ( this->Cells.Capacity > 0 ) /*0x565c71*/\
  {\
    do /*0x565ce1*/\
    {\
      v8 = Capacity % 512; /*0x565c84*/\
      Width_1 = this->MapRect.Width; /*0x565c90*/\
      v10 = (Capacity / 512); /*0x565c9c*/\
      Width_2 = v8 + v10; /*0x565c9f*/\
      if ( Width_2 <= Width_1 /*0x565cbf*/\
        || v8 - v10 >= Width_1\
        || v10 - v8 >= Width_1\
        || Width_2 > Width_1 + 2 * this->MapRect.Height )\
      {\
        v12 = this->Cells.Items[Capacity]; /*0x565cc7*/\
        if ( v12 ) /*0x565ccc*/\
          v12->Level = jj.X; /*0x565cd2*/\
      }\
      ++Capacity; /*0x565cde*/\
    }\
    while ( Capacity < this->Cells.Capacity ); /*0x565ce1*/\
  }\
  Z_1.X = 0; /*0x565ce9*/\
  if ( !a2 ) /*0x565cef*/\
  {\
    Z_1.Y = operator new(328 * Y_3 * v151); /*0x565d0d*/\
    Y = Z_1.Y; /*0x565d11*/\
    Width_3 = this->MapRect.Width; /*0x565d15*/\
    this->CellIterator_NextX = 1; /*0x565d1b*/\
    this->CellIterator_NextY = Width_3; /*0x565d25*/\
    this->CellIterator_CurrentY = Width_3 - 1; /*0x565d31*/\
    this->CellIterator_NextCell = &this->Cells.Items[512 * Width_3 + 1]; /*0x565d46*/\
    v14 = MapClass::CellIteratorNext(this); /*0x565d51*/\
    Width = v14->MapCoords; /*0x565d58*/\
    if ( v14 ) /*0x565d5c*/\
    {\
      v15 = Z_1.Y + 40; /*0x565d66*/\
      do /*0x5662a6*/\
      {\
        sub_588C10(v14); /*0x565d6f*/\
        MapCoords = v14->MapCoords; /*0x565d74*/\
        n24 = 24; /*0x565d77*/\
        *(v15 - 4) = MapCoords; /*0x565d7f*/\
        *v15 = v14->FoggedObjects; /*0x565d85*/\
        *(v15 + 4) = v14->BridgeOwnerCell; /*0x565d8b*/\
        *(v15 + 8) = v14->unknown_30; /*0x565d91*/\
        *(v15 + 12) = v14->LightConvert; /*0x565d97*/\
        *(v15 + 16) = v14->IsoTileTypeIndex; /*0x565d9d*/\
        *(v15 + 20) = v14->AttachedTag; /*0x565da3*/\
        *(v15 + 24) = v14->Rubble; /*0x565da9*/\
        *(v15 + 28) = v14->OverlayTypeIndex; /*0x565daf*/\
        *(v15 + 32) = v14->SmudgeTypeIndex; /*0x565db5*/\
        *(v15 + 36) = v14->Passability; /*0x565dbb*/\
        *(v15 + 40) = v14->WallOwnerIndex; /*0x565dc1*/\
        *(v15 + 44) = v14->InfantryOwnerIndex; /*0x565dc7*/\
        *(v15 + 48) = v14->AltInfantryOwnerIndex; /*0x565dcd*/\
        *(v15 + 52) = v14->unknown_5C; /*0x565dd3*/\
        *(v15 + 56) = v14->unknown_60; /*0x565dd9*/\
        *(v15 + 60) = v14->RedrawFrame; /*0x565de2*/\
        *(v15 + 64) = v14->InViewportRect.X; /*0x565dea*/\
        *(v15 + 68) = v14->InViewportRect.Y; /*0x565def*/\
        *(v15 + 72) = v14->InViewportRect.Width; /*0x565df5*/\
        v17 = &v14->FoggedObjects - v15; /*0x565dfd*/\
        *(v15 + 76) = v14->InViewportRect.Height; /*0x565dff*/\
        *(v15 + 80) = v14->CloakedByHouses; /*0x565e05*/\
        v18 = (v15 + 84); /*0x565e08*/\
        do /*0x565e1e*/\
        {\
          *v18 = *(v18 + v17); /*0x565e0f*/\
          ++v18; /*0x565e16*/\
          --n24; /*0x565e1a*/\
        }\
        while ( n24 ); /*0x565e1e*/\
        v19 = (v15 + 132); /*0x565e20*/\
        n24 = 24; /*0x565e26*/\
        do /*0x565e41*/\
        {\
          *v19 = *&v17[v19]; /*0x565e32*/\
          ++v19; /*0x565e39*/\
          --n24; /*0x565e3d*/\
        }\
        while ( n24 ); /*0x565e41*/\
        *(v15 + 180) = v14->BaseSpacerOfHouses; /*0x565e49*/\
        *(v15 + 184) = v14->Jumpjet; /*0x565e55*/\
        *(v15 + 188) = v14->FirstObject; /*0x565e61*/\
        *(v15 + 192) = v14->AltObject; /*0x565e6d*/\
        *(v15 + 196) = v14->LandType; /*0x565e79*/\
        *(v15 + 200) = LODWORD(v14->RadLevel); /*0x565e85*/\
        *(v15 + 204) = HIDWORD(v14->RadLevel); /*0x565e91*/\
        *(v15 + 208) = v14->RadSite; /*0x565e9d*/\
        *(v15 + 212) = v14->PixelFX; /*0x565ea9*/\
        *(v15 + 216) = v14->OccupyHeightsCoveringMe; /*0x565eb5*/\
        *(v15 + 220) = v14->Intensity; /*0x565ec1*/\
        *(v15 + 224) = v14->Ambient; /*0x565ece*/\
        *(v15 + 226) = v14->Intensity_Normal; /*0x565edc*/\
        *(v15 + 228) = v14->Intensity_Terrain; /*0x565eea*/\
        *(v15 + 230) = v14->Color1_Blue; /*0x565ef8*/\
        *(v15 + 232) = v14->Color2_Red; /*0x565f06*/\
        *(v15 + 234) = v14->Color2_Green; /*0x565f14*/\
        *(v15 + 236) = v14->Color2_Blue; /*0x565f22*/\
        *(v15 + 238) = v14->TubeIndex; /*0x565f30*/\
        *(v15 + 240) = v14->unknown_118; /*0x565f3d*/\
        *(v15 + 241) = v14->IsIceGrowthAllowed; /*0x565f49*/\
        *(v15 + 242) = v14->Height; /*0x565f55*/\
        *(v15 + 243) = v14->Level; /*0x565f61*/\
        *(v15 + 244) = v14->SlopeIndex; /*0x565f6d*/\
        *(v15 + 245) = v14->unknown_11D; /*0x565f79*/\
        *(v15 + 246) = v14->OverlayData; /*0x565f85*/\
        *(v15 + 247) = v14->SmudgeData; /*0x565f91*/\
        *(v15 + 248) = v14->Visibility; /*0x565f9d*/\
        *(v15 + 249) = v14->Foggedness; /*0x565fa9*/\
        *(v15 + 250) = v14->BlockedNeighbours; /*0x565fb5*/\
        *(v15 + 252) = v14->OccupationFlags; /*0x565fc1*/\
        *(v15 + 256) = v14->AltOccupationFlags; /*0x565fcd*/\
        v20 = *(v15 + 260) ^ (v14->AltFlags ^ *(v15 + 260)) & 1; /*0x565fe6*/\
        *(v15 + 260) = v20; /*0x565fe8*/\
        v21 = v20 ^ (v14->AltFlags ^ v20) & 2; /*0x565ffb*/\
        *(v15 + 260) = v21; /*0x565ffd*/\
        v22 = v21 ^ (v14->AltFlags ^ v21) & 4; /*0x566010*/\
        *(v15 + 260) = v22; /*0x566012*/\
        v23 = v22 ^ (v14->AltFlags ^ v22) & 8; /*0x566025*/\
        *(v15 + 260) = v23; /*0x566027*/\
        *(v15 + 260) = v23 ^ (v14->AltFlags ^ v23) & 0x10; /*0x56603c*/\
        *(v15 + 264) = v14->ShroudCounter; /*0x566048*/\
        *(v15 + 268) = v14->GapsCoveringThisCell; /*0x566054*/\
        v24 = *(v15 + 280); /*0x566060*/\
        *(v15 + 272) = v14->VisibilityChanged; /*0x566066*/\
        *(v15 + 276) = v14->unknown_13C; /*0x566072*/\
        v25 = v24 ^ (v14->Flags ^ v24) & 1; /*0x566085*/\
        *(v15 + 280) = v25; /*0x566087*/\
        v26 = v25 ^ (v14->Flags ^ v25) & 2; /*0x56609a*/\
        *(v15 + 280) = v26; /*0x56609c*/\
        v27 = v26 ^ (v14->Flags ^ v26) & 4; /*0x5660af*/\
        *(v15 + 280) = v27; /*0x5660b1*/\
        v28 = v27 ^ (v14->Flags ^ v27) & 8; /*0x5660c4*/\
        *(v15 + 280) = v28; /*0x5660c6*/\
        v29 = v28 ^ (v14->Flags ^ v28) & 0x10; /*0x5660d9*/\
        *(v15 + 280) = v29; /*0x5660db*/\
        v30 = v29 ^ (v14->Flags ^ v29) & 0x20; /*0x5660ee*/\
        *(v15 + 280) = v30; /*0x5660f0*/\
        v31 = v30 ^ (v14->Flags ^ v30) & 0x40; /*0x566103*/\
        *(v15 + 280) = v31; /*0x566105*/\
        v32 = v31 ^ (v14->Flags ^ v31) & 0x80; /*0x56611b*/\
        *(v15 + 280) = v32; /*0x56611d*/\
        v33 = v32 ^ (v14->Flags ^ v32) & 0x100; /*0x566132*/\
        *(v15 + 280) = v33; /*0x566134*/\
        v34 = v33 ^ (v14->Flags ^ v33) & 0x200; /*0x56614a*/\
        *(v15 + 280) = v34; /*0x56614c*/\
        v35 = v34 ^ (v14->Flags ^ v34) & 0x400; /*0x566161*/\
        *(v15 + 280) = v35; /*0x566163*/\
        v36 = v35 ^ (v14->Flags ^ v35) & 0x800; /*0x566179*/\
        *(v15 + 280) = v36; /*0x56617b*/\
        v37 = v36 ^ (v14->Flags ^ v36) & 0x1000; /*0x566190*/\
        *(v15 + 280) = v37; /*0x566192*/\
        v38 = v37 ^ (v14->Flags ^ v37) & 0x2000; /*0x5661a8*/\
        *(v15 + 280) = v38; /*0x5661aa*/\
        v39 = v38 ^ (v14->Flags ^ v38) & 0x4000; /*0x5661bf*/\
        *(v15 + 280) = v39; /*0x5661c1*/\
        v40 = v39 ^ (v14->Flags ^ v39) & 0x8000; /*0x5661d7*/\
        *(v15 + 280) = v40; /*0x5661d9*/\
        v41 = v40 ^ (v14->Flags ^ v40) & 0x10000; /*0x5661ee*/\
        *(v15 + 280) = v41; /*0x5661f0*/\
        v42 = v41 ^ (v14->Flags ^ v41) & 0x20000; /*0x566206*/\
        *(v15 + 280) = v42; /*0x566208*/\
        v43 = v42 ^ (v14->Flags ^ v42) & 0x40000; /*0x56621d*/\
        *(v15 + 280) = v43; /*0x56621f*/\
        v44 = v43 ^ (v14->Flags ^ v43) & 0x80000; /*0x566235*/\
        *(v15 + 280) = v44; /*0x566237*/\
        v45 = v44 ^ (v14->Flags ^ v44) & 0x100000; /*0x56624c*/\
        *(v15 + 280) = v45; /*0x56624e*/\
        v46 = v45 ^ (v14->Flags ^ v45) & 0x200000; /*0x566264*/\
        *(v15 + 280) = v46; /*0x566266*/\
        *(v15 + 280) = v46 ^ (v14->Flags ^ v46) & 0x400000; /*0x566280*/\
        *(v15 + 4) = 0; /*0x566286*/\
        *(v15 + 8) = 0; /*0x56628b*/\
        v14 = MapClass::CellIteratorNext(this); /*0x566297*/\
        v15 += 328; /*0x56629a*/\
        ++Z_1.X; /*0x5662a2*/\
      }\
      while ( v14 ); /*0x5662a6*/\
    }\
  }\
  Z = 0; /*0x5662ba*/\
  this->MapRect = *pBuffer_; /*0x5662be*/\
  Width_4 = this->MapRect.Width; /*0x5662d2*/\
  this->MapRect.X = 0; /*0x5662d8*/\
  this->MapRect.Y = 0; /*0x5662e1*/\
  if ( Width_4 > 63 || this->MapRect.Height > 63 ) /*0x5662ef*/\
    n2_0 = 2; /*0x5662f1*/\
  ::Width = MouseClass::Instance.MapRect.Width; /*0x566306*/\
  Z_1.Z = 0; /*0x56630b*/\
  dword_ABED08 = MouseClass::Instance.MapRect.Width + 2 * MouseClass::Instance.MapRect.Height; /*0x566317*/\
  this->MapCoordBounds.Left = 1; /*0x56631c*/\
  this->MapCoordBounds.Top = 1; /*0x566322*/\
  Right = pBuffer_[3] + pBuffer_[2] - 1; /*0x56632e*/\
  this->MapCoordBounds.Right = Right; /*0x566332*/\
  this->MapCoordBounds.Bottom = Right; /*0x566338*/\
  if ( 2 * Right + 2 > 0 ) /*0x566344*/\
  {\
    n24 = 0; /*0x56634a*/\
    do /*0x566451*/\
    {\
      v50 = 0; /*0x566354*/\
      if ( this->MapCoordBounds.Right + 2 > 0 ) /*0x56635b*/\
      {\
        v142.Z = Z; /*0x566364*/\
        do /*0x56642c*/\
        {\
          LOWORD(this_pCoord.Z) = v50; /*0x56636c*/\
          HIWORD(this_pCoord.Z) = Z; /*0x566374*/\
          Width_6 = v50 + v142.Z; /*0x566379*/\
          Width_5 = this->MapRect.Width; /*0x56637c*/\
          if ( Width_6 > Width_5 /*0x5663ad*/\
            && v50 - v142.Z < Width_5\
            && v142.Z - v50 < Width_5\
            && Width_6 <= Width_5 + 2 * this->MapRect.Height )\
          {\
            v53 = n24 + v50; /*0x5663b9*/\
            v54 = *(&this->Cells.Items[n24] + v50); /*0x5663bc*/\
            if ( v54 ) /*0x5663c1*/\
            {\
              CellClass::CTOR(v54); /*0x5663fc*/\
              sub_485240(&this_pCoord.Z); /*0x566408*/\
            }\
            else\
            {\
              v55 = operator new(0x148u); /*0x5663c8*/\
              if ( v55 ) /*0x5663d2*/\
                v56 = CellClass::CTOR(v55); /*0x5663db*/\
              else\
                v56 = 0; /*0x5663df*/\
              sub_485240(&this_pCoord.Z); /*0x5663e8*/\
              this->Cells.Items[v53] = v56; /*0x5663f3*/\
              Z = Z_1.Z; /*0x5663f6*/\
            }\
            this->Cells.Items[v53]->Level = jj.X; /*0x56641a*/\
          }\
          ++v50; /*0x566426*/\
        }\
        while ( v50 < this->MapCoordBounds.Right + 2 ); /*0x56642c*/\
      }\
      Z_1.Z = ++Z; /*0x56643d*/\
      n24 += 512; /*0x566441*/\
    }\
    while ( Z < 2 * this->MapCoordBounds.Bottom + 2 ); /*0x566451*/\
  }\
  HIBYTE(v142.Y) = 0; /*0x566460*/\
  if ( a2 ) /*0x566467*/\
    goto LABEL_119; /*0x566467*/\
  Width_7 = this->MapRect.Width; /*0x56646d*/\
  this->CellIterator_NextX = 1; /*0x566473*/\
  this->CellIterator_NextY = Width_7; /*0x566479*/\
  this->CellIterator_CurrentY = Width_7 - 1; /*0x566482*/\
  this->CellIterator_NextCell = &this->Cells.Items[512 * Width_7 + 1]; /*0x566497*/\
  MapCoords_1 = MapClass::CellIteratorNext(this)->MapCoords; /*0x5664a2*/\
  v59 = pBuffer_[1]; /*0x5664b1*/\
  v60 = *pBuffer_; /*0x5664b4*/\
  v142.Z = MapCoords_1; /*0x5664b6*/\
  LOWORD(Z_1.Z) = MapCoords_1 - Width; /*0x5664bc*/\
  LOWORD(this_pCoord.Z) = v60 + v59; /*0x5664cc*/\
  HIWORD(this_pCoord.Z) = v59 - v60; /*0x5664d1*/\
  HIWORD(Z_1.Z) = HIWORD(MapCoords_1) - HIWORD(Width); /*0x5664da*/\
  LOWORD(n24_1) = MapCoords_1 - Width - (v60 + v59); /*0x5664e9*/\
  HIWORD(n24_1) = HIWORD(MapCoords_1) - HIWORD(Width) - (v59 - v60); /*0x5664f4*/\
  n24 = n24_1; /*0x566503*/\
  if ( Z_1.X > 0 ) /*0x566507*/\
  {\
    Z_1.Z = Z_1.X; /*0x566511*/\
    v61 = Y + 36; /*0x566515*/\
    do /*0x566ab1*/\
    {\
      Width = *v61; /*0x566523*/\
      n0x40000 = (Width + n24) + ((HIWORD(n24) + HIWORD(Width)) << 9); /*0x566545*/\
      if ( n0x40000 < 0x40000 && (p_MapClass::InvalidCell_1 = this->Cells.Items[n0x40000]) != 0 ) /*0x56655b*/\
      {\
        p_MapClass::InvalidCell = p_MapClass::InvalidCell_1; /*0x56655d*/\
      }\
      else\
      {\
        p_MapClass::InvalidCell = &MapClass::InvalidCell; /*0x566565*/\
        MapCoords_2.Y = HIWORD(n24) + HIWORD(Width); /*0x566534*/\
        MapCoords_2.X = Width + n24; /*0x56652f*/\
        MapClass::InvalidCell.MapCoords = MapCoords_2; /*0x56656a*/\
      }\
      Z_1.X = p_MapClass::InvalidCell->MapCoords; /*0x566574*/\
      if ( p_MapClass::InvalidCell ) /*0x566578*/\
      {\
        sub_588C10(v61 - 36); /*0x566581*/\
        MapCoords_3 = *v61; /*0x566586*/\
        Y = 24; /*0x566589*/\
        p_MapClass::InvalidCell->MapCoords = MapCoords_3; /*0x566591*/\
        p_MapClass::InvalidCell->FoggedObjects = *(v61 + 4); /*0x566597*/\
        p_MapClass::InvalidCell->BridgeOwnerCell = *(v61 + 8); /*0x56659d*/\
        p_MapClass::InvalidCell->unknown_30 = *(v61 + 12); /*0x5665a3*/\
        p_MapClass::InvalidCell->LightConvert = *(v61 + 16); /*0x5665a9*/\
        p_MapClass::InvalidCell->IsoTileTypeIndex = *(v61 + 20); /*0x5665af*/\
        p_MapClass::InvalidCell->AttachedTag = *(v61 + 24); /*0x5665b5*/\
        p_MapClass::InvalidCell->Rubble = *(v61 + 28); /*0x5665bb*/\
        p_MapClass::InvalidCell->OverlayTypeIndex = *(v61 + 32); /*0x5665c1*/\
        p_MapClass::InvalidCell->SmudgeTypeIndex = *(v61 + 36); /*0x5665c7*/\
        p_MapClass::InvalidCell->Passability = *(v61 + 40); /*0x5665cd*/\
        p_MapClass::InvalidCell->WallOwnerIndex = *(v61 + 44); /*0x5665d3*/\
        p_MapClass::InvalidCell->InfantryOwnerIndex = *(v61 + 48); /*0x5665d9*/\
        p_MapClass::InvalidCell->AltInfantryOwnerIndex = *(v61 + 52); /*0x5665df*/\
        p_MapClass::InvalidCell->unknown_5C = *(v61 + 56); /*0x5665e5*/\
        p_MapClass::InvalidCell->unknown_60 = *(v61 + 60); /*0x5665eb*/\
        p_MapClass::InvalidCell->RedrawFrame = *(v61 + 64); /*0x5665f4*/\
        p_MapClass::InvalidCell->InViewportRect.X = *(v61 + 68); /*0x5665fc*/\
        p_MapClass::InvalidCell->InViewportRect.Y = *(v61 + 72); /*0x566601*/\
        p_MapClass::InvalidCell->InViewportRect.Width = *(v61 + 76); /*0x566607*/\
        p_MapClass::InvalidCell->InViewportRect.Height = *(v61 + 80); /*0x56660d*/\
        p_MapClass::InvalidCell->CloakedByHouses = *(v61 + 84); /*0x566613*/\
        p_SensorsOfHouses = p_MapClass::InvalidCell->SensorsOfHouses; /*0x566618*/\
        v67 = v61 - 36 - p_MapClass::InvalidCell; /*0x56661b*/\
        do /*0x566630*/\
        {\
          *p_SensorsOfHouses = *(p_SensorsOfHouses + v67); /*0x566621*/\
          ++p_SensorsOfHouses; /*0x566628*/\
          --Y; /*0x56662c*/\
        }\
        while ( Y ); /*0x566630*/\
        p_DisguiseSensorsOfHouses = p_MapClass::InvalidCell->DisguiseSensorsOfHouses; /*0x566632*/\
        Y = 24; /*0x566638*/\
        do /*0x566653*/\
        {\
          *p_DisguiseSensorsOfHouses = *(p_DisguiseSensorsOfHouses + v67); /*0x566644*/\
          ++p_DisguiseSensorsOfHouses; /*0x56664b*/\
          --Y; /*0x56664f*/\
        }\
        while ( Y ); /*0x566653*/\
        p_MapClass::InvalidCell->BaseSpacerOfHouses = *(v61 + 184); /*0x56665b*/\
        p_MapClass::InvalidCell->Jumpjet = *(v61 + 188); /*0x566667*/\
        p_MapClass::InvalidCell->FirstObject = *(v61 + 192); /*0x566673*/\
        p_MapClass::InvalidCell->AltObject = *(v61 + 196); /*0x56667f*/\
        p_MapClass::InvalidCell->LandType = *(v61 + 200); /*0x56668b*/\
        LODWORD(p_MapClass::InvalidCell->RadLevel) = *(v61 + 204); /*0x566697*/\
        HIDWORD(p_MapClass::InvalidCell->RadLevel) = *(v61 + 208); /*0x5666a3*/\
        p_MapClass::InvalidCell->RadSite = *(v61 + 212); /*0x5666af*/\
        p_MapClass::InvalidCell->PixelFX = *(v61 + 216); /*0x5666bb*/\
        p_MapClass::InvalidCell->OccupyHeightsCoveringMe = *(v61 + 220); /*0x5666c7*/\
        p_MapClass::InvalidCell->Intensity = *(v61 + 224); /*0x5666d3*/\
        p_MapClass::InvalidCell->Ambient = *(v61 + 228); /*0x5666e0*/\
        p_MapClass::InvalidCell->Intensity_Normal = *(v61 + 230); /*0x5666ee*/\
        p_MapClass::InvalidCell->Intensity_Terrain = *(v61 + 232); /*0x5666fc*/\
        p_MapClass::InvalidCell->Color1_Blue = *(v61 + 234); /*0x56670a*/\
        p_MapClass::InvalidCell->Color2_Red = *(v61 + 236); /*0x566718*/\
        p_MapClass::InvalidCell->Color2_Green = *(v61 + 238); /*0x566726*/\
        p_MapClass::InvalidCell->Color2_Blue = *(v61 + 240); /*0x566734*/\
        p_MapClass::InvalidCell->TubeIndex = *(v61 + 242); /*0x566742*/\
        p_MapClass::InvalidCell->unknown_118 = *(v61 + 244); /*0x56674f*/\
        p_MapClass::InvalidCell->IsIceGrowthAllowed = *(v61 + 245); /*0x56675b*/\
        p_MapClass::InvalidCell->Height = *(v61 + 246); /*0x566767*/\
        p_MapClass::InvalidCell->Level = *(v61 + 247); /*0x566773*/\
        p_MapClass::InvalidCell->SlopeIndex = *(v61 + 248); /*0x56677f*/\
        p_MapClass::InvalidCell->unknown_11D = *(v61 + 249); /*0x56678b*/\
        p_MapClass::InvalidCell->OverlayData = *(v61 + 250); /*0x566797*/\
        p_MapClass::InvalidCell->SmudgeData = *(v61 + 251); /*0x5667a3*/\
        p_MapClass::InvalidCell->Visibility = *(v61 + 252); /*0x5667af*/\
        p_MapClass::InvalidCell->Foggedness = *(v61 + 253); /*0x5667bb*/\
        p_MapClass::InvalidCell->BlockedNeighbours = *(v61 + 254); /*0x5667c7*/\
        p_MapClass::InvalidCell->OccupationFlags = *(v61 + 256); /*0x5667d3*/\
        p_MapClass::InvalidCell->AltOccupationFlags = *(v61 + 260); /*0x5667df*/\
        AltFlags = p_MapClass::InvalidCell->AltFlags ^ (*(v61 + 264) ^ p_MapClass::InvalidCell->AltFlags) & 1; /*0x5667f8*/\
        p_MapClass::InvalidCell->AltFlags = AltFlags; /*0x5667fa*/\
        AltFlags_1 = AltFlags ^ (*(v61 + 264) ^ AltFlags) & 2; /*0x56680d*/\
        p_MapClass::InvalidCell->AltFlags = AltFlags_1; /*0x56680f*/\
        AltFlags_2 = AltFlags_1 ^ (*(v61 + 264) ^ AltFlags_1) & 4; /*0x566822*/\
        p_MapClass::InvalidCell->AltFlags = AltFlags_2; /*0x566824*/\
        AltFlags_3 = AltFlags_2 ^ (*(v61 + 264) ^ AltFlags_2) & 8; /*0x566837*/\
        p_MapClass::InvalidCell->AltFlags = AltFlags_3; /*0x566839*/\
        p_MapClass::InvalidCell->AltFlags = AltFlags_3 ^ (*(v61 + 264) ^ AltFlags_3) & 0x10; /*0x56684e*/\
        p_MapClass::InvalidCell->ShroudCounter = *(v61 + 268); /*0x56685a*/\
        p_MapClass::InvalidCell->GapsCoveringThisCell = *(v61 + 272); /*0x566866*/\
        Flags = p_MapClass::InvalidCell->Flags; /*0x566872*/\
        p_MapClass::InvalidCell->VisibilityChanged = *(v61 + 276); /*0x566878*/\
        p_MapClass::InvalidCell->unknown_13C = *(v61 + 280); /*0x566884*/\
        Flags_1 = Flags ^ (*(v61 + 284) ^ Flags) & 1; /*0x566897*/\
        p_MapClass::InvalidCell->Flags = Flags_1; /*0x566899*/\
        Flags_2 = Flags_1 ^ (*(v61 + 284) ^ Flags_1) & 2; /*0x5668ac*/\
        p_MapClass::InvalidCell->Flags = Flags_2; /*0x5668ae*/\
        Flags_3 = Flags_2 ^ (*(v61 + 284) ^ Flags_2) & 4; /*0x5668c1*/\
        p_MapClass::InvalidCell->Flags = Flags_3; /*0x5668c3*/\
        Flags_4 = Flags_3 ^ (*(v61 + 284) ^ Flags_3) & 8; /*0x5668d6*/\
        p_MapClass::InvalidCell->Flags = Flags_4; /*0x5668d8*/\
        Flags_5 = Flags_4 ^ (*(v61 + 284) ^ Flags_4) & 0x10; /*0x5668eb*/\
        p_MapClass::InvalidCell->Flags = Flags_5; /*0x5668ed*/\
        Flags_6 = Flags_5 ^ (*(v61 + 284) ^ Flags_5) & 0x20; /*0x566900*/\
        p_MapClass::InvalidCell->Flags = Flags_6; /*0x566902*/\
        Flags_7 = Flags_6 ^ (*(v61 + 284) ^ Flags_6) & 0x40; /*0x566915*/\
        p_MapClass::InvalidCell->Flags = Flags_7; /*0x566917*/\
        Flags_8 = Flags_7 ^ (*(v61 + 284) ^ Flags_7) & 0x80; /*0x56692d*/\
        p_MapClass::InvalidCell->Flags = Flags_8; /*0x56692f*/\
        Flags_9 = Flags_8 ^ (*(v61 + 284) ^ Flags_8) & 0x100; /*0x566944*/\
        p_MapClass::InvalidCell->Flags = Flags_9; /*0x566946*/\
        Flags_10 = Flags_9 ^ (*(v61 + 284) ^ Flags_9) & 0x200; /*0x56695c*/\
        p_MapClass::InvalidCell->Flags = Flags_10; /*0x56695e*/\
        Flags_11 = Flags_10 ^ (*(v61 + 284) ^ Flags_10) & 0x400; /*0x566973*/\
        p_MapClass::InvalidCell->Flags = Flags_11; /*0x566975*/\
        Flags_12 = Flags_11 ^ (*(v61 + 284) ^ Flags_11) & 0x800; /*0x56698b*/\
        p_MapClass::InvalidCell->Flags = Flags_12; /*0x56698d*/\
        Flags_13 = Flags_12 ^ (*(v61 + 284) ^ Flags_12) & 0x1000; /*0x5669a2*/\
        p_MapClass::InvalidCell->Flags = Flags_13; /*0x5669a4*/\
        Flags_14 = Flags_13 ^ (*(v61 + 284) ^ Flags_13) & 0x2000; /*0x5669ba*/\
        p_MapClass::InvalidCell->Flags = Flags_14; /*0x5669bc*/\
        Flags_15 = Flags_14 ^ (*(v61 + 284) ^ Flags_14) & 0x4000; /*0x5669d1*/\
        p_MapClass::InvalidCell->Flags = Flags_15; /*0x5669d3*/\
        Flags_16 = Flags_15 ^ (*(v61 + 284) ^ Flags_15) & 0x8000; /*0x5669e9*/\
        p_MapClass::InvalidCell->Flags = Flags_16; /*0x5669eb*/\
        Flags_17 = Flags_16 ^ (*(v61 + 284) ^ Flags_16) & 0x10000; /*0x566a00*/\
        p_MapClass::InvalidCell->Flags = Flags_17; /*0x566a02*/\
        Flags_18 = Flags_17 ^ (*(v61 + 284) ^ Flags_17) & 0x20000; /*0x566a18*/\
        p_MapClass::InvalidCell->Flags = Flags_18; /*0x566a1a*/\
        Flags_19 = Flags_18 ^ (*(v61 + 284) ^ Flags_18) & 0x40000; /*0x566a2f*/\
        p_MapClass::InvalidCell->Flags = Flags_19; /*0x566a31*/\
        Flags_20 = Flags_19 ^ (*(v61 + 284) ^ Flags_19) & 0x80000; /*0x566a47*/\
        p_MapClass::InvalidCell->Flags = Flags_20; /*0x566a49*/\
        Flags_21 = Flags_20 ^ (*(v61 + 284) ^ Flags_20) & 0x100000; /*0x566a5e*/\
        p_MapClass::InvalidCell->Flags = Flags_21; /*0x566a60*/\
        Flags_22 = Flags_21 ^ (*(v61 + 284) ^ Flags_21) & 0x200000; /*0x566a76*/\
        p_MapClass::InvalidCell->Flags = Flags_22; /*0x566a78*/\
        p_MapClass::InvalidCell->Flags = Flags_22 ^ (*(v61 + 284) ^ Flags_22) & 0x400000; /*0x566a94*/\
        sub_485240(&Z_1); /*0x566a9d*/\
      }\
      v61 += 328; /*0x566aa6*/\
      --Z_1.Z; /*0x566aad*/\
    }\
    while ( Z_1.Z ); /*0x566ab1*/\
  }\
  Width_8 = this->MapRect.Width; /*0x566ab7*/\
  this->CellIterator_NextX = 1; /*0x566abd*/\
  this->CellIterator_NextY = Width_8; /*0x566ac7*/\
  this->CellIterator_CurrentY = Width_8 - 1; /*0x566ad0*/\
  this->CellIterator_NextCell = &this->Cells.Items[512 * Width_8 + 1]; /*0x566ae5*/\
  for ( i = MapClass::CellIteratorNext(this); i; i = MapClass::CellIteratorNext(this) ) /*0x566af2*/\
  {\
    MapCoords_4 = i->MapCoords; /*0x566afc*/\
    Width_9 = this->MapRect.Width; /*0x566aff*/\
    X = MapCoords_4.X; /*0x566b05*/\
    v100 = pBuffer_[1]; /*0x566b09*/\
    Y = MapCoords_4; /*0x566b0c*/\
    if ( MapCoords_4.X + MapCoords_4.Y < Width_9 - 2 * v100 + 1 /*0x566b77*/\
      || MapCoords_4.Y - MapCoords_4.X > Width_9 + 2 * *pBuffer_ - 1\
      || MapCoords_4.X + MapCoords_4.Y > Width_9\
                                       + 2 * (v151 + this->MapRect.Height - v100 - MouseClass::Instance.MapRect.Height)\
      || MapCoords_4.X - MapCoords_4.Y > Width_9 + 2 * (Y_3 - *pBuffer_ - MouseClass::Instance.MapRect.Width) - 1 )\
    {\
      v101 = MapCoords_4.X + (MapCoords_4.Y << 9); /*0x566b86*/\
      v102 = this->Cells.Items[v101]; /*0x566b88*/\
      if ( v102 ) /*0x566b8d*/\
        (v102->~AbstractClass)(v102, 1); /*0x566b93*/\
      v103 = operator new(0x148u); /*0x566b9b*/\
      if ( v103 ) /*0x566ba5*/\
        v104 = CellClass::CTOR(v103); /*0x566ba9*/\
      else\
        v104 = 0; /*0x566bb0*/\
      this->Cells.Items[v101] = v104; /*0x566bbd*/\
      sub_485240(Z_2); /*0x566bc9*/\
      this->Cells.Items[v101]->IsoTileTypeIndex = 0xFFFF; /*0x566bd7*/\
      this->Cells.Items[v101]->Height = 0; /*0x566be7*/\
      this->Cells.Items[v101]->SlopeIndex = 0; /*0x566bf7*/\
      this->Cells.Items[v101]->OverlayTypeIndex = -1; /*0x566c07*/\
      this->Cells.Items[v101]->Level = X; /*0x566c1b*/\
    }\
  }\
  for ( n702 = 0; n702 < 702; ++n702 ) /*0x566c30*/\
  {\
    if ( sub_68BD80(ScenarioClass::Instance, n702) ) /*0x566c39*/\
    {\
      pFoundationData = ScenarioClass::GetWaypointCoords(ScenarioClass::Instance, &Cell_Zero_Zero_4, n702); /*0x566c58*/\
      FoundationMapCrd = CellStruct::GetFoundationMapCrd(pFoundationData, &pBuffer_, &pMapCrd); /*0x566c5f*/\
      (sub_68BF50)(n702, *FoundationMapCrd); /*0x566c72*/\
    }\
  }\
  for ( Count = 0; Count < TubeClass::Array.Count; ++Count ) /*0x566c89*/\
  {\
    sub_588C40(&pMapCrd); /*0x566c9c*/\
    sub_588C40(&pMapCrd); /*0x566ca9*/\
  }\
  CoordStruct::Set(&this_pCoord.Y, 128, 128, 0); /*0x566cc8*/\
  CoordStruct::Set(&Z_1.Y, (pMapCrd.X << 8) + 128, (pMapCrd.Y << 8) + 128, 0); /*0x566cf1*/\
  v109 = CoordStruct::Set(&v142.Y, Z_1.Y - this_pCoord.Y, Z_1.Z - this_pCoord.Z, Z_3 - v144); /*0x566d1b*/\
  X_1 = v109->X; /*0x566d20*/\
  pBuffer_ = 0; /*0x566d22*/\
  Y_1 = v109->Y; /*0x566d2a*/\
  Width = Y_1; /*0x566d2d*/\
  Cell_Zero_Zero = v109->Z; /*0x566d34*/\
  if ( ::Cell_Zero_Zero_2 > 0 ) /*0x566d3f*/\
  {\
    do /*0x566dc3*/\
    {\
      v112 = *(dword_A8E364 + pBuffer_); /*0x566d4f*/\
      if ( (*(*v112 + 44))(v112) != 4 ) /*0x566d5c*/\
      {\
        X_2 = X_1 + v112[39]; /*0x566d6a*/\
        this_pCoord.Z = v112[40]; /*0x566d6f*/\
        v114 = CoordStruct::Set(&v142.Y, X_2, this_pCoord.Z + Y_1, v112[41] + *&Cell_Zero_Zero); /*0x566d8a*/\
        Z_1.Y = v114->X; /*0x566d91*/\
        Z_1.Z = v114->Y; /*0x566d9a*/\
        v115 = *v112; /*0x566d9e*/\
        Z_3 = v114->Z; /*0x566da3*/\
        (*(v115 + 436))(v112, &Z_1.Y); /*0x566dac*/\
      }\
      ++Cell_Zero_Zero_4; /*0x566dbf*/\
    }\
    while ( Cell_Zero_Zero_4 < ::Cell_Zero_Zero_2 ); /*0x566dc3*/\
  }\
  for ( j = HouseClass::Array.Count - 1; j >= 0; --j ) /*0x566dd0*/\
    sub_50D250(v144); /*0x566ddf*/\
  Count_1 = 0; /*0x566ded*/\
  for ( Cell_Zero_Zero_4 = 0; Count_1 < AnimClass::Array.Count; Cell_Zero_Zero_4 = Count_1 ) /*0x566df5*/\
  {\
    v118 = AnimClass::Array.Items[Count_1]; /*0x566dfd*/\
    if ( !v118->OwnerObject ) /*0x566e00*/\
    {\
      Y_2 = v118->Location.Y; /*0x566e16*/\
      Z_1.X = X_1 + v118->Location.X; /*0x566e19*/\
      v120 = v118->ObjectClass::AbstractClass::IPersistStream::IPersist::IUnknown::__vftable; /*0x566e1d*/\
      Z_4 = v118->Location.Z; /*0x566e21*/\
      Z_1.Y = Y_1 + Y_2; /*0x566e28*/\
      Z_1.Z = Width + Z_4; /*0x566e33*/\
      v120->SetLocation(v118, &Z_1); /*0x566e37*/\
      Y_1 = Y_3; /*0x566e3d*/\
      Count_1 = Cell_Zero_Zero_4; /*0x566e41*/\
    }\
    ++Count_1; /*0x566e4b*/\
  }\
  Cell_Zero_Zero_1 = 0; /*0x566e60*/\
  ++Unsorted::IKnowWhatImDoing; /*0x566e64*/\
  Cell_Zero_Zero_4 = 0; /*0x566e6a*/\
  if ( ::Cell_Zero_Zero_2 > 0 ) /*0x566e6e*/\
  {\
    do /*0x566f54*/\
    {\
      if ( (*(**(dword_A8E364 + Cell_Zero_Zero_1) + 44))(*(dword_A8E364 + Cell_Zero_Zero_1)) != 24 /*0x566e9b*/\
        || *(*(*(dword_A8E364 + Cell_Zero_Zero_1) + 172) + 692) != 1 )\
      {\
        Cell_Zero_Zero = *(*(**(dword_A8E364 + Cell_Zero_Zero_1) + 440))(*(dword_A8E364 + Cell_Zero_Zero_1), &pBuffer_); /*0x566ebb*/\
        for ( k = (*(**(dword_A8E364 + Cell_Zero_Zero_1) + 264))(*(dword_A8E364 + Cell_Zero_Zero_1), 0); /*0x566ec4*/\
              *k != 0x7FFF || k[1] != 0x7FFF;\
              k += 2 )\
        {\
          v124 = (*k + Width); /*0x566ee9*/\
          Width_10 = this->MapRect.Width; /*0x566eec*/\
          v126 = (HIWORD(Width) + k[1]); /*0x566ef2*/\
          if ( v126 + v124 <= Width_10 ) /*0x566efa*/\
            goto LABEL_93; /*0x566efa*/\
          if ( v124 - v126 >= Width_10 || v126 - v124 >= Width_10 || v126 + v124 > Width_10 + 2 * this->MapRect.Height ) /*0x566f15*/\
          {\
            Cell_Zero_Zero_1 = Cell_Zero_Zero; /*0x566f20*/\
LABEL_93:\
            (*(**(dword_A8E364 + Cell_Zero_Zero_1) + 212))(*(dword_A8E364 + Cell_Zero_Zero_1)); /*0x566f24*/\
            v127 = *(dword_A8E364 + Cell_Zero_Zero_1); /*0x566f39*/\
            if ( v127 ) /*0x566f3e*/\
              (*(*v127 + 32))(v127, 1); /*0x566f44*/\
            --Cell_Zero_Zero_1; /*0x566f47*/\
            break; /*0x566f47*/\
          }\
          Cell_Zero_Zero_1 = Cell_Zero_Zero; /*0x566f17*/\
        }\
      }\
      Width = ++Cell_Zero_Zero_1; /*0x566f50*/\
    }\
    while ( Cell_Zero_Zero_1 < ::Cell_Zero_Zero_2 ); /*0x566f54*/\
  }\
  v128 = 0; /*0x566f60*/\
  --Unsorted::IKnowWhatImDoing; /*0x566f63*/\
  if ( this->Cells.Capacity > 0 ) /*0x566f71*/\
  {\
    do /*0x566f77*/\
    {\
      Items = this->Cells.Items; /*0x566f77*/\
      Width_11 = Items[v128]; /*0x566f7d*/\
      Y_3 = &Items[v128]; /*0x566f85*/\
      Width = Width_11; /*0x566f89*/\
      if ( Width_11 ) /*0x566f8d*/\
      {\
        v131 = v128 % 512; /*0x566fa0*/\
        Width_12 = this->MapRect.Width; /*0x566fac*/\
        v133 = (v128 / 512); /*0x566fb8*/\
        Width_13 = v131 + v133; /*0x566fbb*/\
        if ( Width_13 > Width_12 ) /*0x566fc0*/\
        {\
          if ( v131 - v133 < Width_12 && v133 - v131 < Width_12 && Width_13 <= Width_12 + 2 * this->MapRect.Height ) /*0x566fdb*/\
            continue; /*0x566fdb*/\
          Width_11 = Width; /*0x566fdd*/\
        }\
        *Y_3 = 0; /*0x566fe7*/\
        (Width_11->~AbstractClass)(Width_11, 1); /*0x566fef*/\
      }\
    }\
    while ( ++v128 < this->Cells.Capacity ); /*0x566f77*/\
  }\
  Width_14 = this->MapRect.Width; /*0x567001*/\
  this->CellIterator_NextX = 1; /*0x567007*/\
  this->CellIterator_NextY = Width_14; /*0x567011*/\
  this->CellIterator_CurrentY = Width_14 - 1; /*0x56701a*/\
  this->CellIterator_NextCell = &this->Cells.Items[512 * Width_14 + 1]; /*0x56702f*/\
  for ( m = MapClass::CellIteratorNext(this); m; m = MapClass::CellIteratorNext(this) ) /*0x56703c*/\
  {\
    Flags_23 = m->Flags; /*0x56703e*/\
    if ( (Flags_23 & 0x80u) != 0 && !m->BridgeOwnerCell ) /*0x567049*/\
    {\
      OverlayTypeIndex = m->OverlayTypeIndex; /*0x567050*/\
      v139 = 2 * ((~Flags_23 >> 11) & 1); /*0x56705b*/\
      if ( OverlayTypeIndex == 24 || OverlayTypeIndex == 25 ) /*0x567065*/\
        sub_47E040(v139, 1); /*0x567078*/\
      else\
        sub_47E470(v139, 1); /*0x56706c*/\
    }\
  }\
  if ( LOBYTE(Cell_Zero_Zero.X) ) /*0x56708e*/\
    sub_567110(this); /*0x567092*/\
  for ( Cell_Zero_Zero_2 = 0; Cell_Zero_Zero_2 < ::Cell_Zero_Zero_2; ++Cell_Zero_Zero_2 ) /*0x5670a5*/\
    (*(**(dword_A8E364 + Cell_Zero_Zero_2) + 292))(*(dword_A8E364 + Cell_Zero_Zero_2), 1); /*0x5670b4*/\
  GscreenClass::MarkNeedsRedraw(&MouseClass::Instance, 2); /*0x5670cb*/\
  if ( !v141 ) /*0x5670d6*/\
  {\
LABEL_119:\
    if ( Width ) /*0x5670de*/\
      sub_567110(this); /*0x5670e2*/\
  }\
  if ( &MapClass::InvalidCell ) /*0x5670ee*/\
    CellClass::CTOR(&MapClass::InvalidCell); /*0x5670f2*/\
  operator delete(this_pCoord.Y); /*0x5670fc*/\
}\",\"refs\":[{\"addr\":\"0xabd480\",\"name\":\"Cell_Zero_Zero_0\"},{\"addr\":\"0x87f7e8\",\"name\":\"MouseClass::Instance\"},{\"addr\":\"0xa8e364\",\"name\":\"dword_A8E364\"},{\"addr\":\"0xa8e370\",\"name\":\"Cell_Zero_Zero_2\"},{\"addr\":\"0x7c8e17\",\"name\":\"??2@YAPAXI@Z\"},{\"addr\":\"0x578290\",\"name\":\"MapClass::CellIteratorNext\"},{\"addr\":\"0x588c10\",\"name\":\"sub_588C10\"},{\"addr\":\"0x880c74\",\"name\":\"n2_0\"},{\"addr\":\"0xabed04\",\"name\":\"Width\"},{\"addr\":\"0xabed08\",\"name\":\"Width_1\"},{\"addr\":\"0x47bbf0\",\"name\":\"CellClass::CTOR\"},{\"addr\":\"0x485240\",\"name\":\"sub_485240\"},{\"addr\":\"0xabdc50\",\"name\":\"MapClass::InvalidCell\"},{\"addr\":\"0x68bcc0\",\"name\":\"ScenarioClass::GetWaypointCoords\"},{\"addr\":\"0xa8b230\",\"name\":\"ScenarioClass::Instance\"},{\"addr\":\"0x42d510\",\"name\":\"CellStruct::GetFoundationMapCrd\"},{\"addr\":\"0x68bf50\",\"name\":\"sub_68BF50\"},{\"addr\":\"0x68bd80\",\"name\":\"sub_68BD80\"},{\"addr\":\"0x588c40\",\"name\":\"sub_588C40\"},{\"addr\":\"0x8b4138\",\"name\":\"TubeClass::Array\"},{\"addr\":\"0x41c230\",\"name\":\"CoordStruct::Set\"},{\"addr\":\"0xa80228\",\"name\":\"HouseClass::Array\"},{\"addr\":\"0x50d250\",\"name\":\"sub_50D250\"},{\"addr\":\"0xa8e7ac\",\"name\":\"Unsorted::IKnowWhatImDoing\"},{\"addr\":\"0x47e040\",\"name\":\"sub_47E040\"},{\"addr\":\"0x47e470\",\"name\":\"sub_47E470\"},{\"addr\":\"0x567110\",\"name\":\"sub_567110\"},{\"addr\":\"0x4f42f0\",\"name\":\"GscreenClass::MarkNeedsRedraw\"},{\"addr\":\"0x7c8b3d\",\"name\":\"??3@YAXPAX@Z\"}]}"}]

