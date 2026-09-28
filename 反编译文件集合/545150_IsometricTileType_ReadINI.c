// IsometricTileTypeClass::ReadINI @ 0x545150 (full body, IDA MCP)

char *__fastcall IsometricTileTypeClass::ReadINI(int Theater, char a2)
{
  IsometricTileTypeClass *pTileType; // ebp
  size_t Size; // eax
  signed int nSize; // eax
  int i; // esi
  int v7; // eax
  void **p_pDest; // esi
  int v9; // esi
  size_t Size_1; // eax
  signed int nSize_1; // eax
  size_t Size_2; // eax
  signed int nSize_2; // eax
  size_t Size_3; // eax
  signed int nSize_3; // eax
  size_t Size_4; // eax
  signed int nSize_4; // eax
  _BYTE *pDest; // eax
  int n768; // ecx
  int *v20; // edi
  int IsoTileTypeIndex; // ebx
  int *v22; // eax
  int n4; // ecx
  signed int n4_3; // eax
  int v25; // eax
  int *v26; // eax
  int *v27; // ebx
  IsometricTileTypeClass *pTileType_6; // eax
  IRTTITypeInfo_vtbl *v29; // edx
  int v30; // eax
  int *MarbleMadnessTile_3; // eax
  char ShadowCaster_1; // al
  int v33; // ecx
  INIClass_INISection *Section; // eax
  int v35; // ebx
  IsometricTileTypeClass *v36; // eax
  int v37; // edx
  int *NonMarbleMadnessTile; // ecx
  int *ToSnowTheater; // ecx
  int *ToTemperateTheater; // edx
  DynamicVectorClass_Color16Struct_PTR_vtbl *p2A4; // edx
  int v42; // eax
  int v43; // esi
  void *pTileFile; // ebx
  IsometricTileTypeClass *v45; // eax
  int *MarbleMadnessTile_1; // edx
  IsometricTileTypeClass *pTileType_4; // ecx
  int v48; // edx
  unsigned int *v49; // ecx
  unsigned int pTileFile_1; // eax
  IsometricTileTypeClass *pTileType_5; // eax
  int unk_2F0; // ecx
  int v53; // edx
  int Count; // edi
  IsometricTileTypeClass *pTileType_1; // eax
  unsigned int v56; // ecx
  int MarbleMadnessTile_2; // edx
  int NonMarbleMadnessTile_2; // edx
  char v60; // [esp+11h] [ebp-9FFh]
  char v62; // [esp+13h] [ebp-9FDh]
  char ShadowCaster; // [esp+14h] [ebp-9FCh]
  char AllowToPlace; // [esp+15h] [ebp-9FBh]
  char RequiredByRMG; // [esp+16h] [ebp-9FAh]
  char v66; // [esp+17h] [ebp-9F9h]
  int unk_2F0_1; // [esp+18h] [ebp-9F8h]
  char Morphable; // [esp+1Ch] [ebp-9F4h]
  bool v69; // [esp+1Dh] [ebp-9F3h]
  __int16 src_; // [esp+1Eh] [ebp-9F2h] BYREF
  int n4_2; // [esp+20h] [ebp-9F0h]
  int IsoTileTypeIndex_1; // [esp+24h] [ebp-9ECh]
  int *v73; // [esp+28h] [ebp-9E8h]
  int *MarbleMadnessTile_4; // [esp+2Ch] [ebp-9E4h]
  int *MarbleMadnessTile; // [esp+30h] [ebp-9E0h]
  IsometricTileTypeClass *pTileType_2; // [esp+34h] [ebp-9DCh]
  CCINIClass v77; // [esp+38h] [ebp-9D8h] BYREF
  DWORD v78; // [esp+90h] [ebp-980h]
  int v79; // [esp+94h] [ebp-97Ch]
  int n4_1; // [esp+98h] [ebp-978h]
  IsometricTileTypeClass *pTileType_3; // [esp+9Ch] [ebp-974h]
  int *NonMarbleMadnessTile_1; // [esp+A0h] [ebp-970h]
  int v83; // [esp+A4h] [ebp-96Ch]
  int *v84; // [esp+A8h] [ebp-968h]
  int v85; // [esp+ACh] [ebp-964h]
  int *v86; // [esp+B0h] [ebp-960h]
  Theater *Theater_1; // [esp+B4h] [ebp-95Ch]
  int *v88; // [esp+B8h] [ebp-958h]
  int *v89; // [esp+BCh] [ebp-954h]
  int *v90; // [esp+C0h] [ebp-950h]
  int *v91; // [esp+C4h] [ebp-94Ch]
  int *v92; // [esp+C8h] [ebp-948h]
  int *v93; // [esp+CCh] [ebp-944h]
  int *v94; // [esp+D0h] [ebp-940h]
  int *v95; // [esp+D4h] [ebp-93Ch]
  int *v96; // [esp+D8h] [ebp-938h]
  int *v97; // [esp+DCh] [ebp-934h]
  int *v98; // [esp+E0h] [ebp-930h]
  int *v99; // [esp+E4h] [ebp-92Ch]
  int *v100; // [esp+E8h] [ebp-928h]
  int *v101; // [esp+ECh] [ebp-924h]
  int *v102; // [esp+F0h] [ebp-920h]
  int *v103; // [esp+F4h] [ebp-91Ch]
  int *v104; // [esp+F8h] [ebp-918h]
  int *ToSnowTheater_1; // [esp+FCh] [ebp-914h]
  int *v106; // [esp+100h] [ebp-910h]
  int *ToTemperateTheater_1; // [esp+104h] [ebp-90Ch]
  int *v108; // [esp+108h] [ebp-908h]
  int v109; // [esp+10Ch] [ebp-904h]
  int *v110; // [esp+110h] [ebp-900h]
  int *v111; // [esp+114h] [ebp-8FCh]
  int *v112; // [esp+118h] [ebp-8F8h]
  int *v113; // [esp+11Ch] [ebp-8F4h]
  int *v114; // [esp+120h] [ebp-8F0h]
  int *v115; // [esp+124h] [ebp-8ECh]
  int *v116; // [esp+128h] [ebp-8E8h]
  int *v117; // [esp+12Ch] [ebp-8E4h]
  int *v118; // [esp+130h] [ebp-8E0h]
  int *v119; // [esp+134h] [ebp-8DCh]
  int *v120; // [esp+138h] [ebp-8D8h]
  int *v121; // [esp+13Ch] [ebp-8D4h]
  int *v122; // [esp+140h] [ebp-8D0h]
  int *v123; // [esp+144h] [ebp-8CCh]
  int *v124; // [esp+148h] [ebp-8C8h]
  int *v125; // [esp+14Ch] [ebp-8C4h]
  int *v126; // [esp+150h] [ebp-8C0h]
  int *v127; // [esp+154h] [ebp-8BCh]
  int *v128; // [esp+158h] [ebp-8B8h]
  int *v129; // [esp+15Ch] [ebp-8B4h]
  int *v130; // [esp+160h] [ebp-8B0h]
  int *v131; // [esp+164h] [ebp-8ACh]
  int *v132; // [esp+168h] [ebp-8A8h]
  int *v133; // [esp+16Ch] [ebp-8A4h]
  int *v134; // [esp+170h] [ebp-8A0h]
  int *v135; // [esp+174h] [ebp-89Ch]
  DWORD v136; // [esp+178h] [ebp-898h]
  int v137; // [esp+17Ch] [ebp-894h]
  int n4_4; // [esp+180h] [ebp-890h]
  int *v139; // [esp+184h] [ebp-88Ch]
  char Buffer__4[32]; // [esp+188h] [ebp-888h] BYREF
  char Buffer__3[12]; // [esp+1A8h] [ebp-868h] BYREF
  char Buffer__2[64]; // [esp+1B4h] [ebp-85Ch] BYREF
  char Buffer[5]; // [esp+1F4h] [ebp-81Ch] BYREF
  char n50; // [esp+1F9h] [ebp-817h]
  CCFileClass v145; // [esp+214h] [ebp-7FCh] BYREF
  char pBuffer_[64]; // [esp+280h] [ebp-790h] BYREF
  char Destination[48]; // [esp+2C0h] [ebp-750h] BYREF
  char v148; // [esp+2F0h] [ebp-720h]
  char Destination_[48]; // [esp+2F4h] [ebp-71Ch] BYREF
  char v150; // [esp+324h] [ebp-6ECh]
  char Buffer__1[20]; // [esp+328h] [ebp-6E8h] BYREF
  CCFileClass v152; // [esp+33Ch] [ebp-6D4h] BYREF
  CCFileClass v153; // [esp+3A8h] [ebp-668h] BYREF
  char Filename[128]; // [esp+414h] [ebp-5FCh] BYREF
  CCFileClass v155; // [esp+494h] [ebp-57Ch] BYREF
  CCFileClass pFile_; // [esp+500h] [ebp-510h] BYREF
  CCFileClass pFile; // [esp+56Ch] [ebp-4A4h] BYREF
  CCFileClass v158; // [esp+5D8h] [ebp-438h] BYREF
  CCFileClass v159; // [esp+644h] [ebp-3CCh] BYREF
  char Buffer_[32]; // [esp+6B0h] [ebp-360h] BYREF
  char Source[128]; // [esp+6D0h] [ebp-340h] BYREF
  char pFileName[512]; // [esp+750h] [ebp-2C0h] BYREF
  char pBuffer__1[64]; // [esp+950h] [ebp-C0h] BYREF
  char Source_[128]; // [esp+990h] [ebp-80h] BYREF

  pTileType = 0;
  Theater_1 = Theater;
  v77.CurrentSectionName = 0;
  v77.CurrentSection = 0;
  sub_40E320(&v77.INIClass_Sections.__Sections[4]);
  sub_40E320(&v77.INIClass_Sections.__Sections[16]);
  sub_40E340(&v77.INIClass_Sections.__Sections[16]);
  v77.INIClass_Sections.Sections.INIClass::__vftable = &List_TL_INIClass_INISection_PTR_TR__vtbl1_;
  memset(&v77.IndexClass_SectionIndex, 0, 13);
  memset(&v77.IndexClass_SectionIndex.__SectionIndex[16], 0, 9);
  v77.__vftable = &CCINIClass_vtbl1_;
  v78 = sub_6C8C40();
  dword_AA102C[0] = 0;
  dword_AA1030 = 0;
  n4_1 = 0;
  dword_AA1034 = 0;
  v85 = 0;
  dword_AA1038 = 0;
  dword_AA103C = 0;
  sub_4739F0(&v152, aCShadowShp); // "C_SHADOW.SHP"
  if ( lpBuffer )
  {
    operator delete(lpBuffer);
    lpBuffer = 0;
  }
  Size = sub_473C00(&v152);
  lpBuffer = operator new(Size);
  nSize = sub_473C00(&v152);
  CCFileClass::LoadFile(&v152, lpBuffer, nSize);
  if ( dword_AA1088 )
  {
    for ( i = dword_AA1088 - 1; i >= 0; --i )
    {
      operator delete(*(dword_AA107C + i));
      if ( i < dword_AA1088 )
      {
        v7 = i;
        if ( i < --dword_AA1088 )
        {
          do
          {
            ++v7;
            *(dword_AA107C + v7 - 1) = *(dword_AA107C + v7);
          }
          while ( v7 < dword_AA1088 );
        }
      }
    }
  }
  p_pDest = &::pDest;
  do
  {
    if ( *p_pDest )
    {
      operator delete(*p_pDest);
      *p_pDest = 0;
    }
    ++p_pDest;
  }
  while ( p_pDest < &dbl_AA1070 );
  v9 = 112 * Theater;
  v109 = 112 * Theater;
  sprintf(Buffer, "SLOP01Z.%s", &off_7E1BC6 + 112 * Theater);
  sub_4739F0(&v145, Buffer);
  Size_1 = sub_473C00(&v145);
  ::pDest = operator new(Size_1);
  nSize_1 = sub_473C00(&v145);
  CCFileClass::LoadFile(&v145, ::pDest, nSize_1);
  n50 = 50;
  sub_473FC0(Buffer);
  Size_2 = sub_473C00(&v145);
  pDest_0 = operator new(Size_2);
  nSize_2 = sub_473C00(&v145);
  CCFileClass::LoadFile(&v145, pDest_0, nSize_2);
  n50 = 51;
  sub_473FC0(Buffer);
  Size_3 = sub_473C00(&v145);
  pDest_1 = operator new(Size_3);
  nSize_3 = sub_473C00(&v145);
  CCFileClass::LoadFile(&v145, pDest_1, nSize_3);
  n50 = 52;
  sub_473FC0(Buffer);
  Size_4 = sub_473C00(&v145);
  pDest_2 = operator new(Size_4);
  nSize_4 = sub_473C00(&v145);
  CCFileClass::LoadFile(&v145, pDest_2, nSize_4);
  while ( IsometricTileTypeClass::Array.Count )
  {
    if ( *IsometricTileTypeClass::Array.Items )
      (*(**IsometricTileTypeClass::Array.Items + 32))(*IsometricTileTypeClass::Array.Items, 1);
  }
  sprintf(Buffer_, "ISO%s.PAL", &off_7E1BC6 + v9);
  sub_4739F0(&v153, Buffer_);
  if ( sub_473C50(&v153, 0) )
  {
    CCFileClass::LoadFile(&v153, &pDest_, 768);
    pDest = &pDest_;
    n768 = 768;
    do
    {
      *pDest++ *= 4;
      --n768;
    }
    while ( n768 );
  }
  sub_545000();
  sprintf(Buffer__1, "%sMD.INI", &aTemperat[v9]);
  sub_4739F0(&pFile_, Buffer__1);
  sub_4741F0(&v77, &pFile_, 0, 0);
  v20 = 0;
  IsoTileTypeIndex = 0;
  v86 = 0;
  IsoTileTypeIndex_1 = 0;
  MarbleMadnessTile_4 = 0;
  v130 = INIClass::ReadInteger(&v77, aGeneral, aRampbase, 0xFFFFFFFF);// "RampBase"
  v134 = INIClass::ReadInteger(&v77, aGeneral, aRampsmooth, 0xFFFFFFFF);// "RampSmooth"
  v125 = INIClass::ReadInteger(&v77, aGeneral, aMmrampbase, 0xFFFFFFFF);// "MMRampBase"
  v90 = INIClass::ReadInteger(&v77, aGeneral, aCleartile, 0xFFFFFFFF);// "ClearTile"
  v111 = INIClass::ReadInteger(&v77, aGeneral, aRoughtile, 0xFFFFFFFF);// "RoughTile"
  v92 = INIClass::ReadInteger(&v77, aGeneral, aSandtile, 0xFFFFFFFF);// "SandTile"
  v112 = INIClass::ReadInteger(&v77, aGeneral, aGreentile, 0xFFFFFFFF);// "GreenTile"
  v94 = INIClass::ReadInteger(&v77, aGeneral, aPavetile, 0xFFFFFFFF);// "PaveTile"
  v114 = INIClass::ReadInteger(&v77, aGeneral, aMiscpavetile, 0xFFFFFFFF);// "MiscPaveTile"
  v96 = INIClass::ReadInteger(&v77, aGeneral, aCleartoroughla, 0xFFFFFFFF);// "ClearToRoughLat"
  v116 = INIClass::ReadInteger(&v77, aGeneral, aCleartosandlat, 0xFFFFFFFF);// "ClearToSandLat"
  v98 = INIClass::ReadInteger(&v77, aGeneral, aCleartogreenla, 0xFFFFFFFF);// "ClearToGreenLat"
  v118 = INIClass::ReadInteger(&v77, aGeneral, aCleartopavelat, 0xFFFFFFFF);// "ClearToPaveLat"
  v100 = INIClass::ReadInteger(&v77, aGeneral, aHeightbase, 0xFFFFFFFF);// "HeightBase"
  v120 = INIClass::ReadInteger(&v77, aGeneral, aBlacktile, 0xFFFFFFFF);// "BlackTile"
  v102 = INIClass::ReadInteger(&v77, aGeneral, aBridgeset, 0xFFFFFFFF);// "BridgeSet"
  v122 = INIClass::ReadInteger(&v77, aGeneral, aWoodbridgeset, 0xFFFFFFFF);// "WoodBridgeSet"
  v104 = INIClass::ReadInteger(&v77, aGeneral, aCliffset, 0xFFFFFFFF);// "CliffSet"
  v124 = INIClass::ReadInteger(&v77, aGeneral, aShorepieces, 0xFFFFFFFF);// "ShorePieces"
  v106 = INIClass::ReadInteger(&v77, aGeneral, aWaterset, 0xFFFFFFFF);// "WaterSet"
  v126 = INIClass::ReadInteger(&v77, aGeneral, aSlopesetpieces, 0xFFFFFFFF);// "SlopeSetPieces"
  v108 = INIClass::ReadInteger(&v77, aGeneral, aSlopesetpieces_0, 0xFFFFFFFF);// "SlopeSetPieces2"
  v128 = INIClass::ReadInteger(&v77, aGeneral, aMonorailslopes, 0xFFFFFFFF);// "MonorailSlopes"
  v132 = INIClass::ReadInteger(&v77, aGeneral, aTunnels, 0xFFFFFFFF);// "Tunnels"
  v113 = INIClass::ReadInteger(&v77, aGeneral, aTracktunnels, 0xFFFFFFFF);// "TrackTunnels"
  v110 = INIClass::ReadInteger(&v77, aGeneral, aDirttunnels, 0xFFFFFFFF);// "DirtTunnels"
  v88 = INIClass::ReadInteger(&v77, aGeneral, aDirttracktunne, 0xFFFFFFFF);// "DirtTrackTunnels"
  v135 = INIClass::ReadInteger(&v77, aGeneral, aWaterfalleast, 0xFFFFFFFF);// "WaterfallEast"
  v115 = INIClass::ReadInteger(&v77, aGeneral, aWaterfallwest, 0xFFFFFFFF);// "WaterfallWest"
  v127 = INIClass::ReadInteger(&v77, aGeneral, aWaterfallnorth, 0xFFFFFFFF);// "WaterfallNorth"
  v117 = INIClass::ReadInteger(&v77, aGeneral, aWaterfallsouth, 0xFFFFFFFF);// "WaterfallSouth"
  v133 = INIClass::ReadInteger(&v77, aGeneral, aClifframps, 0xFFFFFFFF);// "CliffRamps"
  v119 = INIClass::ReadInteger(&v77, aGeneral, aPavedroads, 0xFFFFFFFF);// "PavedRoads"
  v129 = INIClass::ReadInteger(&v77, aGeneral, aPavedroadends, 0xFFFFFFFF);// "PavedRoadEnds"
  v121 = INIClass::ReadInteger(&v77, aGeneral, aMedians, 0xFFFFFFFF);// "Medians"
  v139 = INIClass::ReadInteger(&v77, aGeneral, aRoughground, 0xFFFFFFFF);// "RoughGround"
  v123 = INIClass::ReadInteger(&v77, aGeneral, aDirtroadjuncti, 0xFFFFFFFF);// "DirtRoadJunction"
  v131 = INIClass::ReadInteger(&v77, aGeneral, aDirtroadcurve, 0xFFFFFFFF);// "DirtRoadCurve"
  v89 = INIClass::ReadInteger(&v77, aGeneral, aDirtroadstraig, 0xFFFFFFFF);// "DirtRoadStraight"
  v91 = INIClass::ReadInteger(&v77, aGeneral, aDestroyablecli, 0xFFFFFFFE);// "DestroyableCliffs"
  v95 = INIClass::ReadInteger(&v77, aGeneral, aWatercaves, 0xFFFFFFFF);// "WaterCaves"
  v93 = INIClass::ReadInteger(&v77, aGeneral, aWatercliffs, 0xFFFFFFFF);// "WaterCliffs"
  v97 = INIClass::ReadInteger(&v77, aGeneral, aPavedroadslope, 0xFFFFFFFF);// "PavedRoadSlopes"
  v99 = INIClass::ReadInteger(&v77, aGeneral, aDirtroadslopes, 0xFFFFFFFF);// "DirtRoadSlopes"
  v101 = INIClass::ReadInteger(&v77, aGeneral, aRocks, 0xFFFFFFFF);// "Rocks"
  v22 = INIClass::ReadInteger(&v77, aGeneral, aWaterbridge, 0xFFFFFFFF);// "WaterBridge"
  IsoTileTypeIndex_23 = -1;
  IsoTileTypeIndex_24 = -1;
  v103 = v22;
  IsoTileTypeIndex_25 = -1;
  IsoTileTypeIndex_26 = -1;
  IsoTileTypeIndex_27 = -1;
  IsoTileTypeIndex_28 = -1;
  IsoTileTypeIndex_29 = -1;
  IsoTileTypeIndex_30 = -1;
  IsoTileTypeIndex_31 = -1;
  IsoTileTypeIndex_32 = -1;
  IsoTileTypeIndex_33 = -1;
  IsoTileTypeIndex_34 = -1;
  IsoTileTypeIndex_35 = -1;
  IsoTileTypeIndex_36 = -1;
  IsoTileTypeIndex_37 = -1;
  IsoTileTypeIndex_38 = -1;
  ::IsoTileTypeIndex = -1;
  IsoTileTypeIndex_0 = -1;
  nIdx_4 = -1;
  nIdx = -1;
  ::IsoTileTypeIndex_1 = -1;
  IsoTileTypeIndex_2 = -1;
  IsoTileTypeIndex_3 = -1;
  IsoTileTypeIndex_6 = -1;
  IsoTileTypeIndex_7 = -1;
  IsoTileTypeIndex_4 = -1;
  IsoTileTypeIndex_5 = -1;
  nIdx_0 = -1;
  nIdx_1 = -1;
  nIdx_3 = -1;
  nIdx_2 = -1;
  IsoTileTypeIndex_8 = -1;
  IsoTileTypeIndex_9 = -1;
  IsoTileTypeIndex_10 = -1;
  IsoTileTypeIndex_11 = -1;
  IsoTileTypeIndex_12 = -1;
  IsoTileTypeIndex_13 = -1;
  IsoTileTypeIndex_14 = -1;
  IsoTileTypeIndex_15 = -1;
  IsoTileTypeIndex_16 = -2;
  IsoTileTypeIndex_18 = -1;
  IsoTileTypeIndex_17 = -1;
  IsoTileTypeIndex_19 = -1;
  IsoTileTypeIndex_20 = -1;
  IsoTileTypeIndex_21 = -1;
  IsoTileTypeIndex_22 = -1;
  dword_ABC2B4 = INIClass::ReadInteger(&v77, aGeneral, aBridgetopleft1, 0xFFFFFFFF);// "BridgeTopLeft1"
  dword_AA1130 = INIClass::ReadInteger(&v77, aGeneral, aBridgetopleft2, 0xFFFFFFFF);// "BridgeTopLeft2"
  dword_ABC1E8 = INIClass::ReadInteger(&v77, aGeneral, aBridgebottomri, 0xFFFFFFFF);// "BridgeBottomRight1"
  dword_AA0E38 = INIClass::ReadInteger(&v77, aGeneral, aBridgebottomri_0, 0xFFFFFFFF);// "BridgeBottomRight2"
  dword_AA1548 = INIClass::ReadInteger(&v77, aGeneral, aBridgetopright, 0xFFFFFFFF);// "BridgeTopRight1"
  dword_AA0740 = INIClass::ReadInteger(&v77, aGeneral, aBridgetopright_0, 0xFFFFFFFF);// "BridgeTopRight2"
  dword_ABC1D0 = INIClass::ReadInteger(&v77, aGeneral, aBridgebottomle, 0xFFFFFFFF);// "BridgeBottomLeft1"
  dword_AA1540 = INIClass::ReadInteger(&v77, aGeneral, aBridgebottomle_0, 0xFFFFFFFF);// "BridgeBottomLeft2"
  pBuffer_0 = INIClass::ReadInteger(&v77, aGeneral, aBridgemiddle1, 0xFFFFFFFF);// "BridgeMiddle1"
  pBuffer = INIClass::ReadInteger(&v77, aGeneral, aBridgemiddle2, 0xFFFFFFFF);// "BridgeMiddle2"
  dword_ABC558 = 0;
  v78 = sub_6C8C40();
  n4 = 4;
  v79 = v137;
  n4_1 = 4;
  while ( 1 )
  {
    n4_2 = n4;
    if ( v78 == -1 )
      goto LABEL_24;
    n4_3 = sub_6C8C40() - v78;
    if ( n4_3 < n4_2 )
    {
      n4 = n4_2 - n4_3;
LABEL_24:
      if ( n4 )
        goto LABEL_26;
    }
    sub_48D080();
    v136 = sub_6C8C40();
    n4_4 = 4;
    v78 = v136;
    v79 = v137;
    n4_1 = 4;
LABEL_26:
    v25 = dword_ABC558;
    dword_AA1140[dword_ABC558] = IsoTileTypeIndex;
    dword_ABC558 = v25 + 1;
    if ( v20 == v130 )
      IsoTileTypeIndex_23 = IsoTileTypeIndex;
    if ( v20 == v134 )
      IsoTileTypeIndex_24 = IsoTileTypeIndex;
    if ( v20 == v125 )
      IsoTileTypeIndex_25 = IsoTileTypeIndex;
    if ( v20 == v90 )
      IsoTileTypeIndex_26 = IsoTileTypeIndex;
    if ( v20 == v111 )
      IsoTileTypeIndex_27 = IsoTileTypeIndex;
    if ( v20 == v92 )
      IsoTileTypeIndex_28 = IsoTileTypeIndex;
    if ( v20 == v112 )
      IsoTileTypeIndex_29 = IsoTileTypeIndex;
    if ( v20 == v94 )
      IsoTileTypeIndex_30 = IsoTileTypeIndex;
    if ( v20 == v114 )
      IsoTileTypeIndex_31 = IsoTileTypeIndex;
    if ( v20 == v96 )
      IsoTileTypeIndex_32 = IsoTileTypeIndex;
    if ( v20 == v116 )
      IsoTileTypeIndex_33 = IsoTileTypeIndex;
    if ( v20 == v98 )
      IsoTileTypeIndex_34 = IsoTileTypeIndex;
    if ( v20 == v118 )
      IsoTileTypeIndex_35 = IsoTileTypeIndex;
    if ( v20 == v100 )
      IsoTileTypeIndex_36 = IsoTileTypeIndex;
    if ( v20 == v120 )
      IsoTileTypeIndex_37 = IsoTileTypeIndex;
    if ( v20 == v102 )
      IsoTileTypeIndex_38 = IsoTileTypeIndex;
    if ( v20 == v122 )
      ::IsoTileTypeIndex = IsoTileTypeIndex;
    if ( v20 == v104 )
      IsoTileTypeIndex_0 = IsoTileTypeIndex;
    if ( v20 == v124 )
      nIdx_4 = IsoTileTypeIndex;
    if ( v20 == v106 )
      nIdx = IsoTileTypeIndex;
    if ( v20 == v126 )
      ::IsoTileTypeIndex_1 = IsoTileTypeIndex;
    if ( v20 == v108 )
      IsoTileTypeIndex_2 = IsoTileTypeIndex;
    if ( v20 == v128 )
      IsoTileTypeIndex_3 = IsoTileTypeIndex;
    if ( v20 == v110 )
      IsoTileTypeIndex_4 = IsoTileTypeIndex;
    if ( v20 == v88 )
      IsoTileTypeIndex_5 = IsoTileTypeIndex;
    if ( v20 == v132 )
      IsoTileTypeIndex_6 = IsoTileTypeIndex;
    if ( v20 == v113 )
      IsoTileTypeIndex_7 = IsoTileTypeIndex;
    if ( v20 == v135 )
      nIdx_0 = IsoTileTypeIndex;
    if ( v20 == v115 )
      nIdx_1 = IsoTileTypeIndex;
    if ( v20 == v127 )
      nIdx_3 = IsoTileTypeIndex;
    if ( v20 == v117 )
      nIdx_2 = IsoTileTypeIndex;
    if ( v20 == v133 )
      IsoTileTypeIndex_8 = IsoTileTypeIndex;
    if ( v20 == v119 )
      IsoTileTypeIndex_9 = IsoTileTypeIndex;
    if ( v20 == v129 )
      IsoTileTypeIndex_10 = IsoTileTypeIndex;
    if ( v20 == v121 )
      IsoTileTypeIndex_11 = IsoTileTypeIndex;
    if ( v20 == v139 )
      IsoTileTypeIndex_12 = IsoTileTypeIndex;
    if ( v20 == v123 )
      IsoTileTypeIndex_13 = IsoTileTypeIndex;
    if ( v20 == v131 )
      IsoTileTypeIndex_14 = IsoTileTypeIndex;
    if ( v20 == v89 )
      IsoTileTypeIndex_15 = IsoTileTypeIndex;
    if ( v20 == v91 )
      IsoTileTypeIndex_16 = IsoTileTypeIndex;
    if ( v20 == v93 )
      IsoTileTypeIndex_17 = IsoTileTypeIndex;
    if ( v20 == v95 )
      IsoTileTypeIndex_18 = IsoTileTypeIndex;
    if ( v20 == v97 )
      IsoTileTypeIndex_19 = IsoTileTypeIndex;
    if ( v20 == v99 )
      IsoTileTypeIndex_20 = IsoTileTypeIndex;
    if ( v20 == v101 )
      IsoTileTypeIndex_21 = IsoTileTypeIndex;
    if ( v20 == v103 )
      IsoTileTypeIndex_22 = IsoTileTypeIndex;
    sprintf(Buffer__2, "TileSet%04d", v20);
    CCINIClass::Init(&v77);
    v73 = INIClass::ReadInteger(&v77, Buffer__2, aTilesinset, 0xFFFFFFFF);// "TilesInSet"
    if ( v73 == -1 )
      break;
    v26 = INIClass::ReadInteger(&v77, Buffer__2, aLasttilesinset, 0xFFFFFFFF);// "LastTilesInSet"
    v27 = v26;
    if ( v26 == -1 || v26 == v73 )
    {
      MarbleMadnessTile_3 = (MarbleMadnessTile_4 + v73);
    }
    else
    {
      pTileType_6 = operator new(8u);
      v29 = (v73 - v27);
      pTileType_2 = pTileType_6;
      MarbleMadnessTile = (MarbleMadnessTile_4 + v27);
      pTileType_6->ObjectTypeClass::AbstractTypeClass::AbstractClass::IPersistStream::IPersist::IUnknown::__vftable = (MarbleMadnessTile_4 + v27);
      pTileType_6->ObjectTypeClass::AbstractTypeClass::AbstractClass::IRTTITypeInfo::IUnknown::__vftable = v29;
      if ( dword_AA1088 < dword_AA1080
        || (byte_AA1085 || !dword_AA1080)
        && dword_AA108C > 0
        && (*(dword_AA1078 + 8))(&dword_AA1078, dword_AA108C + dword_AA1080, 0) )
      {
        v30 = dword_AA1088++;
        *(dword_AA107C + v30) = pTileType_2;
      }
      MarbleMadnessTile_3 = MarbleMadnessTile;
    }
    MarbleMadnessTile_4 = MarbleMadnessTile_3;
    INIClass::ReadString(&v77, Buffer__2, aSetname, aNoName, pBuffer_, 64);// "No Name"
    INIClass::ReadString(&v77, Buffer__2, aFilename, aTile, pBuffer__1, 64);// "TILE"
    MarbleMadnessTile = INIClass::ReadInteger(&v77, Buffer__2, aMarblemadness, 0xFFFF);// "MarbleMadness"
    NonMarbleMadnessTile_1 = INIClass::ReadInteger(&v77, Buffer__2, aNonmarblemadne, 0xFFFF);// "NonMarbleMadness"
    Morphable = CCINIClass::ReadBool(&v77, Buffer__2, aMorphable, 0);// "Morphable"
    AllowToPlace = CCINIClass::ReadBool(&v77, Buffer__2, aAllowtoplace, 1);// "AllowToPlace"
    v66 = CCINIClass::ReadBool(&v77, Buffer__2, aAllowburrowing, 1);// "AllowBurrowing"
    v62 = CCINIClass::ReadBool(&v77, Buffer__2, aAllowtiberium, 0);// "AllowTiberium"
    RequiredByRMG = CCINIClass::ReadBool(&v77, Buffer__2, aRequiredforrmg, 0);// "RequiredForRMG"
    ToSnowTheater_1 = INIClass::ReadInteger(&v77, Buffer__2, aTosnowtheater, 0xFFFFFFFF);// "ToSnowTheater"
    ToTemperateTheater_1 = INIClass::ReadInteger(&v77, Buffer__2, aTotemperatethe, 0xFFFFFFFF);// "ToTemperateTheater"
    ShadowCaster_1 = CCINIClass::ReadBool(&v77, Buffer__2, aShadowcaster, 0);// "ShadowCaster"
    ShadowCaster = ShadowCaster_1;
    if ( ShadowCaster_1 )
    {
      v33 = v85;
      dword_AA102C[v85] = IsoTileTypeIndex_1;
      v85 = v33 + 1;
    }
    v84 = 0;
    if ( ShadowCaster_1 )
      v84 = INIClass::ReadInteger(&v77, Buffer__2, aShadowtiles, 0);// "ShadowTiles"
    Section = INIClass::GetSection(&v77, pBuffer_);
    n4_2 = 0;
    v69 = Section != 0;
    if ( v73 > 0 )
    {
      while ( 1 )
      {
        unk_2F0_1 = 0;
        pTileType_2 = 0;
        pTileType_3 = 0;
        v83 = IsoTileTypeIndex_1 - 1;
        do
        {
          if ( unk_2F0_1 )
            src_ = (unk_2F0_1 + 96);
          else
            LOBYTE(src_) = 0;
          v35 = n4_2 + 1;
          sprintf(Buffer__3, "%02d", n4_2 + 1);
          strcat(Buffer__3, &src_);
          strcpy(Filename, pBuffer__1);
          strcat(Filename, Buffer__3);
          sprintf(Source, "%.28s %02d", pBuffer_, v35);
          if ( !unk_2F0_1 )
          {
            v36 = operator new(0x30Cu);
            if ( v36 )
            {
              v37 = IsoTileTypeIndex_1++;
              ++v83;
              pTileType = IsometricTileTypeClass::CTOR(v36, v37, 0xBFu, 0, Filename, 0);
            }
            else
            {
              pTileType = 0;
            }
            if ( Source )
            {
              strncpy(Destination, Source, 0x30u);
              v148 = 0;
            }
            else
            {
              Destination[0] = Source;
            }
            if ( Destination != pTileType->Name )
            {
              qmemcpy(pTileType->Name, Destination, 0x30u);
              pTileType->Name[48] = v148;
            }
            NonMarbleMadnessTile = NonMarbleMadnessTile_1;
            pTileType->MarbleMadnessTile = MarbleMadnessTile;
            pTileType->NonMarbleMadnessTile = NonMarbleMadnessTile;
            pTileType->AllowToPlace = AllowToPlace;
            pTileType->Morphable = Morphable;
            pTileType->RequiredByRMG = RequiredByRMG;
            *(&pTileType->AllowTiberium + 1) = v66;
            ToSnowTheater = ToSnowTheater_1;
            *(&pTileType->AllowTiberium + 2) = v62;
            ToTemperateTheater = ToTemperateTheater_1;
            pTileType->Image = 0;
            pTileType->ImageAllocated = 0;
            pTileType->ToSnowTheater = ToSnowTheater;
            pTileType->ToTemperateTheater = ToTemperateTheater;
            if ( ShadowCaster && v84 )
              pTileType->ShadowCaster = ShadowCaster;
            if ( a2 )
              pTileType->unk_2F4 = 1;
            p2A4 = pTileType->unk_2A4.__vftable;
            pTileType->unk_2A0 = dword_AA113C[dword_ABC558];
            p2A4->Clear(&pTileType->unk_2A4);
            if ( v69 )
            {
              sprintf(Buffer__4, "Tile%02dAnim", v35);
              if ( INIClass::ReadString(&v77, pBuffer_, Buffer__4, &TagClass::DefaultTagStr, Source_, 128) )
              {
                v42 = sub_428B80(Source_);
                if ( v42 )
                {
                  pTileType->TileAnimIndex = (*(*v42 + 64))(v42);
                  sprintf(Buffer__4, "Tile%02dXOffset", v35);
                  pTileType->TileXOffset = INIClass::ReadInteger(&v77, pBuffer_, Buffer__4, pTileType->TileXOffset);
                  sprintf(Buffer__4, "Tile%02dYOffset", v35);
                  pTileType->TileYOffset = INIClass::ReadInteger(&v77, pBuffer_, Buffer__4, pTileType->TileYOffset);
                  sprintf(Buffer__4, "Tile%02dAttachesTo", v35);
                  pTileType->TileAttachesTo = INIClass::ReadInteger(
                                                &v77,
                                                pBuffer_,
                                                Buffer__4,
                                                pTileType->TileAttachesTo);
                  sprintf(Buffer__4, "Tile%02dZAdjust", v35);
                  pTileType->TileZAdjust = INIClass::ReadInteger(&v77, pBuffer_, Buffer__4, pTileType->TileZAdjust);
                }
              }
            }
            pTileType_2 = pTileType;
            pTileType_3 = pTileType;
          }
          v43 = v109;
          _makepath(pFileName, 0, 0, Filename, &off_7E1BC6 + v109);
          pTileFile = 0;
          v60 = 0;
          if ( a2 )
          {
            sub_4739F0(&pFile, pFileName);
            v60 = sub_473C50(&pFile, 0);
            if ( v60 && !unk_2F0_1 )
              strncpy(pTileType->FileName, pFileName, 0xEu);
            pFile.__vftable = &CCFileClass_vtbl1_;
            pFile.Position = 0;
            MemoryBuffer::Reset(&pFile.Buffer);
            pFile.__vftable = &CCFileClass_vtbl2_;
            sub_431B80(&pFile);
            if ( v60 )
              goto LABEL_190;
          }
          else
          {
            pTileFile = FileSystem::LoadFile(pFileName, 0);
            if ( pTileFile )
              goto LABEL_189;
          }
          if ( !NonMarbleMadnessTile_1 )
            goto LABEL_190;
          if ( Theater_1 == -1 )
            _makepath(pFileName, 0, 0, Filename, aMmt);// ".MMT"
          else
            _makepath(pFileName, 0, 0, Filename, &off_7E1BCA + v43);
          if ( a2 )
          {
            sub_4739F0(&v158, pFileName);
            v60 = sub_473C50(&v158, 0);
            if ( v60 && !unk_2F0_1 )
              strncpy(pTileType->FileName, pFileName, 0xEu);
            v158.__vftable = &CCFileClass_vtbl1_;
            v158.Position = 0;
            MemoryBuffer::Reset(&v158.Buffer);
            v158.__vftable = &CCFileClass_vtbl2_;
            sub_431B80(&v158);
            if ( v60 )
              goto LABEL_190;
          }
          else
          {
            pTileFile = FileSystem::LoadFile(pFileName, 0);
            if ( pTileFile )
              goto LABEL_189;
          }
          _makepath(pFileName, 0, 0, Filename, aTem);// ".TEM"
          if ( a2 )
          {
            sub_4739F0(&v155, pFileName);
            v60 = sub_473C50(&v155, 0);
            if ( v60 && !unk_2F0_1 )
              strncpy(pTileType->FileName, pFileName, 0xEu);
            v155.__vftable = &CCFileClass_vtbl1_;
            v155.Position = 0;
            MemoryBuffer::Reset(&v155.Buffer);
            v155.__vftable = &CCFileClass_vtbl2_;
            sub_431B80(&v155);
            if ( v60 )
              goto LABEL_190;
          }
          else
          {
            pTileFile = FileSystem::LoadFile(pFileName, 0);
            if ( pTileFile )
              goto LABEL_189;
          }
          _makepath(pFileName, 0, 0, Filename, aUrb);// ".URB"
          if ( !a2 )
          {
            pTileFile = FileSystem::LoadFile(pFileName, 0);
            if ( !pTileFile )
              goto LABEL_190;
LABEL_189:
            v60 = 1;
            goto LABEL_190;
          }
          sub_4739F0(&v159, pFileName);
          v60 = sub_473C50(&v159, 0);
          if ( v60 && !unk_2F0_1 )
            strncpy(pTileType->FileName, pFileName, 0xEu);
          v159.__vftable = &CCFileClass_vtbl1_;
          v159.Position = 0;
          MemoryBuffer::Reset(&v159.Buffer);
          v159.__vftable = &CCFileClass_vtbl2_;
          sub_431B80(&v159);
LABEL_190:
          if ( !unk_2F0_1 )
            goto LABEL_207;
          if ( !pTileFile && !v60 )
            break;
          v45 = operator new(0x30Cu);
          if ( v45 )
            pTileType = IsometricTileTypeClass::CTOR(v45, v83, 0xBFu, 0, Filename, 1);
          else
            pTileType = 0;
          if ( Source )
          {
            strncpy(Destination_, Source, 0x30u);
            v150 = 0;
          }
          else
          {
            Destination_[0] = Source;
          }
          if ( Destination_ != pTileType->Name )
          {
            qmemcpy(pTileType->Name, Destination_, 0x30u);
            pTileType->Name[48] = v150;
          }
          MarbleMadnessTile_1 = MarbleMadnessTile;
          pTileType->NonMarbleMadnessTile = NonMarbleMadnessTile_1;
          pTileType->MarbleMadnessTile = MarbleMadnessTile_1;
          *(&pTileType->AllowTiberium + 1) = v66;
          pTileType->Morphable = Morphable;
          pTileType->AllowToPlace = AllowToPlace;
          *(&pTileType->AllowTiberium + 2) = v62;
          pTileType->RequiredByRMG = RequiredByRMG;
          if ( a2 )
          {
            pTileType->unk_2F4 = 1;
            strncpy(pTileType->FileName, pFileName, 0xEu);
          }
          if ( ShadowCaster && v84 )
            pTileType->ShadowCaster = ShadowCaster;
          pTileType_4 = pTileType_3;
          pTileType->unk_2A0 = dword_AA113C[dword_ABC558];
          pTileType_4->unk_2BC = pTileType;
          pTileType->unk_2A4.Clear(&pTileType->unk_2A4);
          pTileType_3 = pTileType;
          if ( !pTileFile )
          {
LABEL_215:
            if ( !unk_2F0_1 )
            {
              pTileType->CellsInX = 0;
              pTileType->CellsInY = 0;
            }
            goto LABEL_217;
          }
LABEL_207:
          pTileType->Image = pTileFile;
          if ( !pTileFile )
            goto LABEL_215;
          v48 = 0;
          pTileType->CellsInX = *pTileFile;
          pTileType->CellsInY = *(pTileFile + 4);
          if ( *(pTileFile + 1) * *pTileFile > 0 )
          {
            v49 = (pTileFile + 16);
            do
            {
              pTileFile_1 = *v49;
              if ( *v49 && pTileFile_1 < pTileFile )
                *v49 = pTileFile + pTileFile_1;
              ++v48;
              ++v49;
            }
            while ( v48 < *(pTileFile + 1) * *pTileFile );
          }
          IsometricTileTypeClass::ReadRadarColor_(pTileType);
LABEL_217:
          ++unk_2F0_1;
        }
        while ( pTileFile || v60 );
        if ( unk_2F0_1 > 1 )
        {
          pTileType_5 = pTileType_2;
          if ( unk_2F0_1 > 1 )
          {
            unk_2F0 = unk_2F0_1;
            v53 = unk_2F0_1 - 1;
            do
            {
              pTileType_5->unk_2F0 = unk_2F0;
              pTileType_5 = pTileType_5->unk_2BC;
              --unk_2F0;
              --v53;
            }
            while ( v53 );
          }
        }
        if ( ++n4_2 >= v73 )
        {
          v20 = v86;
          break;
        }
      }
    }
    n4 = n4_1;
    IsoTileTypeIndex = IsoTileTypeIndex_1;
    v20 = (v20 + 1);
    v86 = v20;
  }
  for ( Count = 0; Count < IsometricTileTypeClass::Array.Count; ++Count )
  {
    pTileType_1 = IsometricTileTypeClass::Array.Items[Count];
    v56 = pTileType_1->ArrayIndex - pTileType_1->unk_2A0;
    MarbleMadnessTile_2 = pTileType_1->MarbleMadnessTile;
    if ( MarbleMadnessTile_2 != 0xFFFF )
      pTileType_1->MarbleMadnessTile = v56 + dword_AA1140[MarbleMadnessTile_2];
    NonMarbleMadnessTile_2 = pTileType_1->NonMarbleMadnessTile;
    if ( NonMarbleMadnessTile_2 != 0xFFFF )
      pTileType_1->NonMarbleMadnessTile = v56 + dword_AA1140[NonMarbleMadnessTile_2];
  }
  if ( Theater_1 == 5 )
  {
    nIdx_4 = -1;
    nIdx = -1;
    IsoTileTypeIndex_0 = -1;
    IsoTileTypeIndex_17 = -1;
    IsoTileTypeIndex_22 = -1;
    IsoTileTypeIndex_38 = -1;
    ::IsoTileTypeIndex = -1;
  }
  pFile_.__vftable = &CCFileClass_vtbl1_;
  pFile_.Position = 0;
  MemoryBuffer::Reset(&pFile_.Buffer);
  pFile_.__vftable = &CCFileClass_vtbl2_;
  sub_431B80(&pFile_);
  v153.__vftable = &CCFileClass_vtbl1_;
  v153.Position = 0;
  MemoryBuffer::Reset(&v153.Buffer);
  v153.__vftable = &CCFileClass_vtbl2_;
  sub_431B80(&v153);
  v145.__vftable = &CCFileClass_vtbl1_;
  v145.Position = 0;
  MemoryBuffer::Reset(&v145.Buffer);
  v145.__vftable = &CCFileClass_vtbl2_;
  sub_431B80(&v145);
  v152.__vftable = &CCFileClass_vtbl1_;
  v152.Position = 0;
  MemoryBuffer::Reset(&v152.Buffer);
  v152.__vftable = &CCFileClass_vtbl2_;
  sub_431B80(&v152);
  return sub_5256F0(&v77.__vftable);
}