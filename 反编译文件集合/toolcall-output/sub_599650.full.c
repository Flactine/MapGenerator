
The MCP server responded with: [{"type":"text","text":"{\"addr\":\"sub_599650\",\"code\":\"char *__thiscall sub_599650(_DWORD *this, char a2)\
{\
  int n3; // eax\
  double v4; // st7\
  double number; // st7\
  int v6; // eax\
  int v7; // eax\
  int v8; // ecx\
  double v9; // rdi\
  double v10; // st7\
  _DWORD *WaypointCoords; // eax\
  CellStruct *pMapCoord; // eax\
  CellClass *CellAt_MapCrd; // eax\
  int v14; // eax\
  _DWORD *this_2; // esi\
  void *v16; // eax\
  int v17; // eax\
  _DWORD *v18; // eax\
  Theater *Theater_2; // ecx\
  Theater *Theater; // edi\
  void (*psub_48D1D0)(void); // eax\
  int v22; // esi\
  int v23; // eax\
  int Count; // edi\
  int v25; // eax\
  IsometricTileTypeClass *v26; // esi\
  int v27; // eax\
  TacticalClass *v28; // eax\
  TacticalClass *TacticalClass::Instance; // eax\
  int i; // eax\
  int v31; // ecx\
  int Count_1; // eax\
  InfantryClass *v33; // ecx\
  int Count_2; // eax\
  BuildingClass *v35; // ecx\
  int j; // eax\
  int v37; // ecx\
  CellClass *k; // eax\
  _DWORD *v39; // eax\
  CellStruct *pMapCoord_1; // eax\
  CellClass *v41; // eax\
  int v42; // eax\
  Theater *Theater_3; // esi\
  _DWORD *this_3; // edi\
  void (*psub_48D1D0_1)(void); // eax\
  int Count_3; // esi\
  HouseClass *v47; // eax\
  HouseClass *v48; // eax\
  Theater *Theater_4; // ecx\
  _DWORD *this_4; // edi\
  int v51; // esi\
  char *v52; // eax\
  int v53; // esi\
  char *v54; // ecx\
  int v55; // edx\
  CellClass *m; // eax\
  _DWORD *v57; // esi\
  int v58; // eax\
  void *v59; // eax\
  int AmbientOriginal; // eax\
  int Red; // eax\
  int Green; // eax\
  int Blue; // eax\
  wchar_t *Source; // eax\
  bool v66; // [esp+27h] [ebp-A1h]\
  float number_1; // [esp+28h] [ebp-A0h]\
  int v68; // [esp+28h] [ebp-A0h]\
  Theater *Theater_1; // [esp+28h] [ebp-A0h]\
  int n; // [esp+28h] [ebp-A0h]\
  float v71; // [esp+2Ch] [ebp-9Ch] BYREF\
  double v72[2]; // [esp+30h] [ebp-98h] BYREF\
  _DWORD *this_1; // [esp+40h] [ebp-88h]\
  int v74[2]; // [esp+44h] [ebp-84h] BYREF\
  int v75; // [esp+4Ch] [ebp-7Ch]\
  int v76; // [esp+50h] [ebp-78h]\
  int v77[4]; // [esp+54h] [ebp-74h] BYREF\
  CCINIClass pINI; // [esp+64h] [ebp-64h] BYREF\
  char v79[12]; // [esp+BCh] [ebp-Ch] BYREF\
\
  this_1 = this; /*0x599661*/\
  v71 = this[25] * 0.33333334; /*0x599674*/\
  number_1 = this[26] * 0.33333334; /*0x599681*/\
  sub_5981F0(this); /*0x599685*/\
  n3 = this[15]; /*0x59968a*/\
  if ( n3 == 3 || n3 == 4 ) /*0x599695*/\
  {\
    number = number_1; /*0x5996d7*/\
  }\
  else\
  {\
    if ( v71 >= 1.2 ) /*0x5996a6*/\
      v4 = 1.2; /*0x5996ae*/\
    else\
      v4 = v71; /*0x5996a8*/\
    v71 = v4; /*0x5996b4*/\
    if ( number_1 >= 1.2 ) /*0x5996c7*/\
      number = 1.2; /*0x5996cf*/\
    else\
      number = number_1; /*0x5996c9*/\
  }\
  this[96] = Game::F2I64(number); /*0x599700*/\
  v6 = Game::F2I64(number); /*0x599722*/\
  v75 = this[96]; /*0x59972f*/\
  v77[2] = v75 + 4; /*0x59973f*/\
  this[97] = v6; /*0x599748*/\
  v77[0] = 0; /*0x59974e*/\
  v77[1] = 0; /*0x599752*/\
  v77[3] = v6 + 12; /*0x599756*/\
  v74[0] = 2; /*0x59975a*/\
  v74[1] = 5; /*0x599762*/\
  v76 = v6; /*0x59976a*/\
  this[195] = 4; /*0x59976e*/\
  pINI.CurrentSectionName = 0; /*0x599774*/\
  pINI.CurrentSection = 0; /*0x599778*/\
  sub_49E8E0(&pINI.INIClass_Sections); /*0x59977c*/\
  sub_49EA10(&pINI.IndexClass_SectionIndex); /*0x599785*/\
  pINI.LineComments = 0; /*0x599790*/\
  *(&pINI + 64) = 0; /*0x599797*/\
  pINI.__vftable = &CCINIClass_vtbl1_; /*0x59979e*/\
  sub_5257C0(0, 0); /*0x5997a6*/\
  v7 = this[14]; /*0x5997ab*/\
  this[195] = 4; /*0x5997ae*/\
  sub_528660(&off_81FFF0, p_Theater, &Theater::Array[112 * v7]);// \\\"Theater\\\" /*0x5997d5*/\
  sub_527C10(&off_81FFF0, aSize, v77); // \\\"Size\\\" /*0x5997ed*/\
  sub_527C10(&off_81FFF0, aLocalsize, v74); // \\\"LocalSize\\\" /*0x599805*/\
  sub_5275C0(&off_81FFF0, aLevel, this[195], 0);// \\\"Level\\\" /*0x599820*/\
  sub_528660((*HouseTypeClass::Array.Items)->ID, aTechlevel, a0);// \\\"0\\\" /*0x59983f*/\
  sub_528660(aBasic, aPlayer, (*HouseTypeClass::Array.Items)->ID);// \\\"Player\\\" /*0x59985e*/\
  if ( this[14] ) /*0x599863*/\
    v8 = this[113]; /*0x599875*/\
  else\
    v8 = this[106]; /*0x59986d*/\
  v72[0] = *(v8 + 4 * this[18]) * 0.01; /*0x599890*/\
  v9 = v72[0]; /*0x599898*/\
  sub_5285B0(aLighting, aAmbient, v72[0]); // \\\"Ambient\\\" /*0x5998a8*/\
  sub_5285B0(aLighting, aRedtint, 1.0); // \\\"RedTint\\\" /*0x5998c1*/\
  sub_5285B0(aLighting, aGreentint, 1.0); // \\\"GreenTint\\\" /*0x5998da*/\
  sub_5285B0(aLighting, aBluetint, 1.0); // \\\"BlueTint\\\" /*0x5998f3*/\
  sub_5285B0(aLighting, aGround, 0.0); // \\\"Ground\\\" /*0x599908*/\
  LODWORD(v72[0]) = *(this_1[99] + 4 * this_1[18]) / 100; /*0x599935*/\
  v10 = SLODWORD(v72[0]); /*0x599939*/\
  sub_5285B0(aLighting, aLevel, v10); // \\\"Level\\\" /*0x59994a*/\
  sub_5285B0(aLighting, aIonambient, v9); // \\\"IonAmbient\\\" /*0x59995f*/\
  sub_5285B0(aLighting, aIonred, 0.3); // \\\"IonRed\\\" /*0x59997c*/\
  sub_5285B0(aLighting, aIongreen, 0.4); // \\\"IonGreen\\\" /*0x599999*/\
  sub_5285B0(aLighting, aIonblue, 0.75); // \\\"IonBlue\\\" /*0x5999b2*/\
  sub_5285B0(aLighting, aIonground, 0.0); // \\\"IonGround\\\" /*0x5999c7*/\
  sub_5285B0(aLighting, aIonlevel, 0.0); // \\\"IonLevel\\\" /*0x5999dc*/\
  if ( !LOBYTE(ScenarioClass::Instance->unknown_3598) ) /*0x5999e7*/\
    sub_643C50(0, 1.0, NAN); /*0x599a03*/\
  if ( ::psub_48D1D0 ) /*0x599a0f*/\
    ::psub_48D1D0(); /*0x599a11*/\
  sub_722390(); /*0x599a13*/\
  sub_722E50(); /*0x599a18*/\
  if ( !a2 ) /*0x599a20*/\
  {\
    ++Unsorted::IKnowWhatImDoing; /*0x599a38*/\
    sub_686700(&TagClass::DefaultTagStr); /*0x599a3e*/\
    if ( Unsorted::ArmageddonMode ) /*0x599a49*/\
      sub_6851F0(); /*0x599a4b*/\
    INIClass::ReadScenario(&pINI, 1, v10); /*0x599a56*/\
    sub_684C30(); /*0x599a5b*/\
    HIWORD(v68) = MouseClass::Instance.MapRect.Height / 2 + MouseClass::Instance.MapRect.Width / 2; /*0x599a7e*/\
    LOWORD(v68) = HIWORD(v68) + 1; /*0x599a86*/\
    sub_68BF50(700, v68); /*0x599a95*/\
    WaypointCoords = ScenarioClass::GetWaypointCoords(ScenarioClass::Instance, v72, 700); /*0x599aaa*/\
    sub_68BF50(ScenarioClass::Instance->HomeCell, *WaypointCoords); /*0x599abf*/\
    pMapCoord = ScenarioClass::GetWaypointCoords(ScenarioClass::Instance, v72, ScenarioClass::Instance->HomeCell); /*0x599ad6*/\
    CellAt_MapCrd = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, pMapCoord); /*0x599ae1*/\
    CellAt_MapCrd->Flags |= 4u; /*0x599af4*/\
    v14 = sub_68BD00(v72, ScenarioClass::Instance->HomeCell); /*0x599b08*/\
    sub_653F70(v14); /*0x599b13*/\
    goto LABEL_153; /*0x599b18*/\
  }\
  ScenarioClass::Constructor(ScenarioClass::Instance); /*0x599b23*/\
  this_2 = this_1; /*0x599b28*/\
  if ( !this_1[95] ) /*0x599b2c*/\
  {\
    v16 = operator new(4u); /*0x599b36*/\
    if ( v16 ) /*0x599b40*/\
      v17 = unknown_libname_27(v16); /*0x599b44*/\
    else\
      v17 = 0; /*0x599b4b*/\
    this_1[95] = v17; /*0x599b4d*/\
  }\
  if ( LOBYTE(ScenarioClass::Instance->unknown_3598) ) /*0x599b59*/\
    sub_69AE90(101); /*0x599b68*/\
  else\
    sub_643C50(0, 2.0, NAN); /*0x599b83*/\
  v18 = this_2[94]; /*0x599b8e*/\
  Theater_2 = this_2[14]; /*0x599b94*/\
  Theater = ScenarioClass::Instance->Theater; /*0x599b99*/\
  LODWORD(v72[0]) = Theater_2; /*0x599b9f*/\
  v66 = 1; /*0x599ba3*/\
  Theater_1 = Theater; /*0x599ba8*/\
  if ( v18 ) /*0x599bac*/\
  {\
    Theater = v18[14]; /*0x599bb1*/\
    Theater_1 = Theater; /*0x599bb7*/\
    if ( v18[25] == this_2[25] && v18[26] == this_2[26] && Theater == Theater_2 ) /*0x599bc7*/\
      v66 = v18[20] != this_2[20]; /*0x599bd3*/\
  }\
  psub_48D1D0 = ::psub_48D1D0; /*0x599bd7*/\
  if ( ::psub_48D1D0 ) /*0x599bde*/\
  {\
    ::psub_48D1D0(); /*0x599be0*/\
    psub_48D1D0 = ::psub_48D1D0; /*0x599be2*/\
    Theater_2 = LODWORD(v72[0]); /*0x599be7*/\
  }\
  if ( !this_2[94] || Theater_2 != Theater || v66 ) /*0x599bfb*/\
  {\
    v22 = dword_A8E978 - 1; /*0x599c07*/\
    if ( dword_A8E978 - 1 >= 0 ) /*0x599c0c*/\
    {\
      do /*0x599c55*/\
      {\
        if ( (*(*(*(dword_A8E96C + v22) + 4) + 12))(*(dword_A8E96C + v22) + 4) == 18 && v22 < dword_A8E978 ) /*0x599c2d*/\
        {\
          v23 = v22; /*0x599c30*/\
          if ( v22 < --dword_A8E978 ) /*0x599c3a*/\
          {\
            do /*0x599c52*/\
            {\
              ++v23; /*0x599c42*/\
              *(dword_A8E96C + v23 - 1) = *(dword_A8E96C + v23); /*0x599c46*/\
            }\
            while ( v23 < dword_A8E978 ); /*0x599c52*/\
          }\
        }\
        --v22; /*0x599c54*/\
      }\
      while ( v22 >= 0 ); /*0x599c55*/\
      psub_48D1D0 = ::psub_48D1D0; /*0x599c57*/\
    }\
    if ( psub_48D1D0 ) /*0x599c5e*/\
      psub_48D1D0(); /*0x599c60*/\
    sub_534450(); /*0x599c62*/\
    if ( ::psub_48D1D0 ) /*0x599c6e*/\
      ::psub_48D1D0(); /*0x599c70*/\
    Count = 0; /*0x599c77*/\
    if ( IsometricTileTypeClass::Array.Count > 0 ) /*0x599c7b*/\
    {\
      v25 = dword_A8E970; /*0x599c7d*/\
      do /*0x599c88*/\
      {\
        v26 = IsometricTileTypeClass::Array.Items[Count]; /*0x599c88*/\
        if ( dword_A8E978 < v25 ) /*0x599c93*/\
          goto LABEL_57; /*0x599c93*/\
        if ( !byte_A8E975 && v25 || dword_A8E97C <= 0 ) /*0x599ca9*/\
          goto LABEL_59; /*0x599ca9*/\
        if ( (*(dword_A8E968 + 8))(&dword_A8E968, dword_A8E97C + v25, 0) ) /*0x599cba*/\
        {\
LABEL_57:\
          v27 = dword_A8E978++; /*0x599cc7*/\
          *(dword_A8E96C + v27) = v26; /*0x599cd6*/\
        }\
        v25 = dword_A8E970; /*0x599cd9*/\
LABEL_59:\
        ++Count; /*0x599cde*/\
      }\
      while ( Count < IsometricTileTypeClass::Array.Count ); /*0x599c88*/\
    }\
  }\
  if ( LOBYTE(ScenarioClass::Instance->unknown_3598) ) /*0x599cef*/\
    sub_69AE90(104); /*0x599cfe*/\
  else\
    sub_643C50(0, 5.0, NAN); /*0x599d19*/\
  if ( ::psub_48D1D0 ) /*0x599d25*/\
    ::psub_48D1D0(); /*0x599d27*/\
  if ( v66 ) /*0x599d2d*/\
  {\
    sub_5BDF50(&MouseClass::Instance); /*0x599d34*/\
    sub_653F50(v77, 1, 0, 1); /*0x599d48*/\
    sub_654490(&MouseClass::Instance, v74); /*0x599d57*/\
    if ( ::TacticalClass::Instance ) /*0x599d64*/\
      (::TacticalClass::Instance->~AbstractClass)(::TacticalClass::Instance, 1); /*0x599d6a*/\
    v28 = operator new(0xE18u); /*0x599d72*/\
    if ( v28 ) /*0x599d7c*/\
      TacticalClass::Instance = sub_6D1C20(v28); /*0x599d80*/\
    else\
      TacticalClass::Instance = 0; /*0x599d87*/\
    ::TacticalClass::Instance = TacticalClass::Instance; /*0x599d8b*/\
    sub_6DA980(TacticalClass::Instance); /*0x599d90*/\
  }\
  if ( LOBYTE(ScenarioClass::Instance->unknown_3598) ) /*0x599d9a*/\
    sub_69AE90(109); /*0x599da9*/\
  else\
    sub_643C50(0, 10.0, NAN); /*0x599dc4*/\
  for ( i = dword_8B4118; dword_8B4118 > 0; i = dword_8B4118 ) /*0x599dd0*/\
  {\
    v31 = *(dword_8B410C + i - 1); /*0x599dd8*/\
    if ( v31 ) /*0x599dde*/\
      (*(*v31 + 32))(v31, 1); /*0x599de4*/\
  }\
  for ( Count_1 = InfantryClass::Array.Count; InfantryClass::Array.Count > 0; Count_1 = InfantryClass::Array.Count ) /*0x599df7*/\
  {\
    v33 = InfantryClass::Array.Items[Count_1 - 1]; /*0x599dff*/\
    if ( v33 ) /*0x599e05*/\
      (v33->~AbstractClass)(v33, 1); /*0x599e0b*/\
  }\
  for ( Count_2 = BuildingClass::Array.Count; BuildingClass::Array.Count > 0; Count_2 = BuildingClass::Array.Count ) /*0x599e1e*/\
  {\
    v35 = BuildingClass::Array.Items[Count_2 - 1]; /*0x599e26*/\
    if ( v35 ) /*0x599e2c*/\
      (v35->~AbstractClass)(v35, 1); /*0x599e32*/\
  }\
  for ( j = dword_A8E998; dword_A8E998 > 0; j = dword_A8E998 ) /*0x599e45*/\
  {\
    v37 = *(dword_A8E98C + j - 1); /*0x599e4d*/\
    if ( v37 ) /*0x599e53*/\
      (*(*v37 + 32))(v37, 1); /*0x599e59*/\
  }\
  if ( ::psub_48D1D0 ) /*0x599e6c*/\
    ::psub_48D1D0(); /*0x599e6e*/\
  sub_578350(&MouseClass::Instance); /*0x599e75*/\
  for ( k = MapClass::CellIteratorNext(&MouseClass::Instance); k; k = MapClass::CellIteratorNext(&MouseClass::Instance) ) /*0x599e86*/\
  {\
    k->SlopeIndex = 0; /*0x599e8d*/\
    k->Level = 4; /*0x599e93*/\
    k->IsoTileTypeIndex = 0; /*0x599e9a*/\
    k->Height = 0; /*0x599e9d*/\
    k->OverlayTypeIndex = -1; /*0x599ea3*/\
    k->OverlayData = 0; /*0x599eaa*/\
  }\
  if ( ::psub_48D1D0 ) /*0x599ec0*/\
    ::psub_48D1D0(); /*0x599ec2*/\
  if ( LOBYTE(ScenarioClass::Instance->unknown_3598) ) /*0x599ec9*/\
    sub_69AE90(114); /*0x599ed8*/\
  else\
    sub_643C50(0, 15.0, NAN); /*0x599ef3*/\
  sub_56D6E0(&MouseClass::Instance); /*0x599efd*/\
  sub_56C510(&MouseClass::Instance); /*0x599f07*/\
  sub_581F50(&MouseClass::Instance); /*0x599f11*/\
  if ( LOBYTE(ScenarioClass::Instance->unknown_3598) ) /*0x599f1c*/\
    sub_69AE90(119); /*0x599f2b*/\
  else\
    sub_643C50(0, 20.0, NAN); /*0x599f46*/\
  if ( ::psub_48D1D0 ) /*0x599f52*/\
    ::psub_48D1D0(); /*0x599f54*/\
  sub_68BD60(ScenarioClass::Instance); /*0x599f5c*/\
  HIWORD(v71) = MouseClass::Instance.MapRect.Height / 2 + MouseClass::Instance.MapRect.Width / 2; /*0x599f7f*/\
  LOWORD(v71) = HIWORD(v71) + 1; /*0x599f87*/\
  sub_68BF50(700, LODWORD(v71)); /*0x599f96*/\
  v39 = ScenarioClass::GetWaypointCoords(ScenarioClass::Instance, &v71, 700); /*0x599fab*/\
  sub_68BF50(699, *v39); /*0x599fbe*/\
  pMapCoord_1 = ScenarioClass::GetWaypointCoords(ScenarioClass::Instance, &v71, 699); /*0x599fd3*/\
  v41 = MapClass::GetCellAt_MapCrd(&MouseClass::Instance, pMapCoord_1); /*0x599fde*/\
  v41->Flags |= 4u; /*0x599ffd*/\
  v42 = sub_68BD00(v79, 699); /*0x59a006*/\
  sub_653F70(v42); /*0x59a011*/\
  if ( LOBYTE(ScenarioClass::Instance->unknown_3598) ) /*0x59a01c*/\
    sub_69AE90(124); /*0x59a02b*/\
  else\
    sub_643C50(0, 25.0, NAN); /*0x59a046*/\
  if ( ::psub_48D1D0 ) /*0x59a052*/\
    ::psub_48D1D0(); /*0x59a054*/\
  Theater_3 = LODWORD(v72[0]); /*0x59a061*/\
  ++Unsorted::IKnowWhatImDoing; /*0x59a066*/\
  if ( LODWORD(v72[0]) != ScenarioClass::Instance->Theater ) /*0x59a074*/\
  {\
    sub_5349C0(LODWORD(v72[0])); /*0x59a078*/\
    ScenarioClass::Instance->Theater = Theater_3; /*0x59a083*/\
  }\
  if ( LOBYTE(ScenarioClass::Instance->unknown_3598) ) /*0x59a08f*/\
    sub_69AE90(129); /*0x59a0a1*/\
  else\
    sub_643C50(0, 30.0, NAN); /*0x59a0bc*/\
  if ( ::psub_48D1D0 ) /*0x59a0c8*/\
    ::psub_48D1D0(); /*0x59a0ca*/\
  this_3 = this_1; /*0x59a0cc*/\
  if ( !this_1[94] || Theater_3 != Theater_1 || v66 ) /*0x59a0e2*/\
  {\
    sub_6686C0(RulesClass::Instance, INI_Rules); /*0x59a0f0*/\
    sub_689880(ScenarioClass::Instance, INI_Rules); /*0x59a102*/\
  }\
  if ( LOBYTE(ScenarioClass::Instance->unknown_3598) ) /*0x59a10d*/\
    sub_69AE90(134); /*0x59a11f*/\
  else\
    sub_643C50(0, 35.0, NAN); /*0x59a13a*/\
  psub_48D1D0_1 = ::psub_48D1D0; /*0x59a13f*/\
  if ( ::psub_48D1D0 ) /*0x59a146*/\
  {\
    ::psub_48D1D0(); /*0x59a148*/\
    psub_48D1D0_1 = ::psub_48D1D0; /*0x59a14a*/\
  }\
  if ( !this_3[94] || Theater_3 != Theater_1 || v66 ) /*0x59a161*/\
  {\
    if ( !HouseClass::Array.Count ) /*0x59a16d*/\
    {\
      Count_3 = 0; /*0x59a175*/\
      if ( HouseTypeClass::Array.Count > 0 ) /*0x59a179*/\
      {\
        do /*0x59a1b5*/\
        {\
          v47 = operator new(0x160B8u); /*0x59a180*/\
          if ( v47 ) /*0x59a18a*/\
            v48 = HouseClass::CTOR(v47, HouseTypeClass::Array.Items[Count_3]); /*0x59a198*/\
          else\
            v48 = 0; /*0x59a19f*/\
          sub_500B40(v48, &pINI); /*0x59a1a8*/\
          ++Count_3; /*0x59a1b2*/\
        }\
        while ( Count_3 < HouseTypeClass::Array.Count ); /*0x59a1b5*/\
        psub_48D1D0_1 = ::psub_48D1D0; /*0x59a1b7*/\
      }\
    }\
    if ( psub_48D1D0_1 ) /*0x59a1be*/\
      psub_48D1D0_1(); /*0x59a1c0*/\
    sub_71DCA0(ScenarioClass::Instance->Theater); /*0x59a1ce*/\
    Theater_4 = ScenarioClass::Instance->Theater; /*0x59a1d8*/\
    if ( Theater_4 == ::Theater ) /*0x59a1e5*/\
      sub_547110(); /*0x59a1f0*/\
    else\
      IsometricTileTypeClass::ReadINI(Theater_4, 1); /*0x59a1e9*/\
    sub_5FE620(ScenarioClass::Instance->Theater); /*0x59a201*/\
    if ( ::psub_48D1D0 ) /*0x59a20d*/\
    {\
      ::psub_48D1D0(); /*0x59a20f*/\
      if ( ::psub_48D1D0 ) /*0x59a218*/\
      {\
        ::psub_48D1D0(); /*0x59a21a*/\
        if ( ::psub_48D1D0 ) /*0x59a223*/\
          ::psub_48D1D0(); /*0x59a225*/\
      }\
    }\
    sub_45E970(ScenarioClass::Instance->Theater); /*0x59a233*/\
    if ( ::psub_48D1D0 ) /*0x59a23f*/\
      ::psub_48D1D0(); /*0x59a241*/\
    sub_427940(ScenarioClass::Instance->Theater); /*0x59a24e*/\
    if ( ::psub_48D1D0 ) /*0x59a25a*/\
      ::psub_48D1D0(); /*0x59a25c*/\
    sub_6B5490(ScenarioClass::Instance->Theater); /*0x59a26a*/\
    if ( ::psub_48D1D0 ) /*0x59a276*/\
      ::psub_48D1D0(); /*0x59a278*/\
    sub_546DA0(0, 1); /*0x59a27e*/\
  }\
  ::Theater = ScenarioClass::Instance->Theater; /*0x59a28f*/\
LABEL_153:\
  this_4 = this_1; /*0x59a294*/\
  --Unsorted::IKnowWhatImDoing; /*0x59a2a4*/\
  if ( LOBYTE(ScenarioClass::Instance->unknown_3598) ) /*0x59a2a9*/\
    sub_69AE90(139); /*0x59a2bd*/\
  else\
    sub_643C50(0, 40.0, NAN); /*0x59a2d8*/\
  if ( ::psub_48D1D0 ) /*0x59a2e4*/\
    ::psub_48D1D0(); /*0x59a2e6*/\
  if ( dword_ABED10 ) /*0x59a2ef*/\
    operator delete(dword_ABED10); /*0x59a2f2*/\
  v51 = dword_89C2DC * dword_89C2DC; /*0x59a300*/\
  v52 = operator new(80 * dword_89C2DC * dword_89C2DC); /*0x59a30a*/\
  if ( v52 ) /*0x59a314*/\
  {\
    v53 = v51 - 1; /*0x59a316*/\
    if ( v53 >= 0 ) /*0x59a319*/\
    {\
      v54 = v52 + 8; /*0x59a31b*/\
      v55 = v53 + 1; /*0x59a31e*/\
      do /*0x59a376*/\
      {\
        *(v54 - 4) = 0; /*0x59a321*/\
        *(v54 - 3) = 0; /*0x59a325*/\
        *v54 = 0; /*0x59a329*/\
        *(v54 + 2) = 0; /*0x59a32b*/\
        *(v54 + 4) = 0; /*0x59a32e*/\
        *(v54 + 6) = 0; /*0x59a331*/\
        *(v54 + 8) = 0; /*0x59a334*/\
        *(v54 + 10) = 0; /*0x59a337*/\
        *(v54 + 1) = 0; /*0x59a33a*/\
        *(v54 + 3) = 0; /*0x59a33d*/\
        *(v54 + 5) = 0; /*0x59a340*/\
        *(v54 + 7) = 0; /*0x59a343*/\
        *(v54 + 9) = 0; /*0x59a346*/\
        *(v54 + 11) = 0; /*0x59a349*/\
        *(v54 + 12) = 0; /*0x59a34c*/\
        *(v54 + 13) = 0; /*0x59a34f*/\
        *(v54 + 14) = -1; /*0x59a352*/\
        v54[60] = 0; /*0x59a359*/\
        v54[61] = 0; /*0x59a35c*/\
        v54[62] = 0; /*0x59a35f*/\
        v54[63] = 0; /*0x59a362*/\
        v54[64] = 0; /*0x59a365*/\
        v54[65] = 0; /*0x59a368*/\
        v54[66] = 1; /*0x59a36b*/\
        v54[67] = 0; /*0x59a36f*/\
        v54 += 80; /*0x59a372*/\
        --v55; /*0x59a375*/\
      }\
      while ( v55 ); /*0x59a376*/\
    }\
    dword_ABED10 = v52; /*0x59a378*/\
  }\
  else\
  {\
    dword_ABED10 = 0; /*0x59a37f*/\
  }\
  sub_578350(&MouseClass::Instance); /*0x59a38a*/\
  for ( m = MapClass::CellIteratorNext(&MouseClass::Instance); m; m = MapClass::CellIteratorNext(&MouseClass::Instance) ) /*0x59a39b*/\
  {\
    LODWORD(v72[0]) = m->MapCoords; /*0x59a3a0*/\
    *(dword_ABED10 + 20 * SLOWORD(v72[0]) + 20 * dword_89C2DC * SWORD1(v72[0])) = LODWORD(v72[0]); /*0x59a3c1*/\
    m->Level = *(this_4 + 780); /*0x59a3cf*/\
  }\
  if ( LOBYTE(ScenarioClass::Instance->unknown_3598) ) /*0x59a3e3*/\
    sub_69AE90(144); /*0x59a3f5*/\
  else\
    sub_643C50(0, 45.0, NAN); /*0x59a410*/\
  if ( ::psub_48D1D0 ) /*0x59a41c*/\
    ::psub_48D1D0(); /*0x59a41e*/\
  dword_ABED14 = 0; /*0x59a426*/\
  for ( n = dword_ABDFA0 - 1; n >= 0; --n ) /*0x59a435*/\
  {\
    v57 = *(dword_ABDF94 + n); /*0x59a441*/\
    if ( v57 ) /*0x59a446*/\
    {\
      if ( *v57 ) /*0x59a448*/\
      {\
        (***v57)(*v57, 1); /*0x59a452*/\
        *v57 = 0; /*0x59a454*/\
      }\
      LODWORD(v72[0]) = v57; /*0x59a466*/\
      v58 = (*(dword_ABDF90 + 16))(&dword_ABDF90, v72); /*0x59a46a*/\
      if ( v58 != -1 ) /*0x59a470*/\
        sub_5AD790(&dword_ABDF90, v58); /*0x59a478*/\
      v59 = v57[11]; /*0x59a47d*/\
      v57[10] = &VectorClass<Cell>::`vftable'; /*0x59a480*/\
      if ( v59 && *(v57 + 53) ) /*0x59a48b*/\
      {\
        operator delete(v59); /*0x59a491*/\
        v57[11] = 0; /*0x59a499*/\
      }\
      *(v57 + 53) = 0; /*0x59a49d*/\
      v57[12] = 0; /*0x59a4a0*/\
      operator delete(v57); /*0x59a4a3*/\
    }\
  }\
  this_4[193] = 0; /*0x59a4bb*/\
  this_4[194] = 0; /*0x59a4c1*/\
  *&v72[0] = Randomizer::Random(&dword_ABE890); /*0x59a4cc*/\
  *(this_4 + 784) = *&v72[0] * 2.328306437080797e-10 < 0.25; /*0x59a4fb*/\
  MouseClass::Uninit(&MouseClass::Instance); /*0x59a501*/\
  sub_654490(&MouseClass::Instance, v74); /*0x59a510*/\
  sub_6558D0(&MouseClass::Instance); /*0x59a51a*/\
  MouseClass::Reinit(&MouseClass::Instance); /*0x59a524*/\
  if ( this_4[14] ) /*0x59a529*/\
    AmbientOriginal = *(this_4[113] + 4 * this_4[18]); /*0x59a545*/\
  else\
    AmbientOriginal = *(this_4[106] + 4 * this_4[18]); /*0x59a537*/\
  ScenarioClass::Instance->AmbientOriginal = AmbientOriginal; /*0x59a54e*/\
  ScenarioClass::Instance->NormalLighting.Level = *(this_4[99] + 4 * this_4[18]); /*0x59a565*/\
  if ( this_4[14] ) /*0x59a56b*/\
    Red = *(this_4[141] + 4 * this_4[18]); /*0x59a589*/\
  else\
    Red = *(this_4[120] + 4 * this_4[18]); /*0x59a57b*/\
  ScenarioClass::Instance->NormalLighting.Tint.Red = Red; /*0x59a592*/\
  if ( this_4[14] ) /*0x59a598*/\
    Green = *(this_4[148] + 4 * this_4[18]); /*0x59a5b6*/\
  else\
    Green = *(this_4[127] + 4 * this_4[18]); /*0x59a5a8*/\
  ScenarioClass::Instance->NormalLighting.Tint.Green = Green; /*0x59a5bf*/\
  if ( this_4[14] ) /*0x59a5c5*/\
    Blue = *(this_4[155] + 4 * this_4[18]); /*0x59a5e3*/\
  else\
    Blue = *(this_4[134] + 4 * this_4[18]); /*0x59a5d5*/\
  ScenarioClass::Instance->NormalLighting.Tint.Blue = Blue; /*0x59a5ec*/\
  if ( LOBYTE(ScenarioClass::Instance->unknown_3598) ) /*0x59a5f8*/\
    sub_69AE90(149); /*0x59a60a*/\
  else\
    sub_643C50(0, 50.0, NAN); /*0x59a625*/\
  if ( !wcslen(this_4 + 60) ) /*0x59a62e*/\
  {\
    Source = StringTable::LoadString(aTxtRandomMapDe, 0, aDRa2mdpostMapg, 6746);// \\\"D:\\\\\\\\ra2mdpost\\\\\\\\MapGen.cpp\\\" /*0x59a64b*/\
    wcscpy(this_4 + 60, Source); /*0x59a652*/\
  }\
  return sub_5256F0(&pINI.__vftable); /*0x59a663*/\
}\",\"refs\":[{\"addr\":\"0x5981f0\",\"name\":\"sub_5981F0\"},{\"addr\":\"0x7c5f00\",\"name\":\"Game::F2I64\"},{\"addr\":\"0x49e8e0\",\"name\":\"sub_49E8E0\"},{\"addr\":\"0x49ea10\",\"name\":\"sub_49EA10\"},{\"addr\":\"0x7e1af4\",\"name\":\"CCINIClass_vtbl1_\"},{\"addr\":\"0x5257c0\",\"name\":\"sub_5257C0\"},{\"addr\":\"0x528660\",\"name\":\"sub_528660\"},{\"addr\":\"0x81fff0\",\"name\":\"pSection_\"},{\"addr\":\"0x818658\",\"name\":\"p_Theater\",\"string\":\"Theater\"},{\"addr\":\"0x7e1b78\",\"name\":\"Theater::Array\",\"string\":\"TEMPERATE\"},{\"addr\":\"0x527c10\",\"name\":\"sub_527C10\"},{\"addr\":\"0x820178\",\"name\":\"aSize\",\"string\":\"Size\"},{\"addr\":\"0x820164\",\"name\":\"aLocalsize\",\"string\":\"LocalSize\"},{\"addr\":\"0x5275c0\",\"name\":\"sub_5275C0\"},{\"addr\":\"0x81b0d4\",\"name\":\"aLevel\",\"string\":\"Level\"},{\"addr\":\"0xa83c98\",\"name\":\"HouseTypeClass::Array\"},{\"addr\":\"0x824e40\",\"name\":\"aTechlevel\",\"string\":\"TechLevel\"},{\"addr\":\"0x82bfac\",\"name\":\"a0\",\"string\":\"0\"},{\"addr\":\"0x82bf9c\",\"name\":\"aBasic\",\"string\":\"Basic\"},{\"addr\":\"0x82bfa4\",\"name\":\"aPlayer\",\"string\":\"Player\"},{\"addr\":\"0x5285b0\",\"name\":\"sub_5285B0\"},{\"addr\":\"0x82bf88\",\"name\":\"aLighting\",\"string\":\"Lighting\"},{\"addr\":\"0x82bf94\",\"name\":\"aAmbient\",\"string\":\"Ambient\"},{\"addr\":\"0x82bf80\",\"name\":\"aRedtint\",\"string\":\"RedTint\"},{\"addr\":\"0x82bf74\",\"name\":\"aGreentint\",\"string\":\"GreenTint\"},{\"addr\":\"0x82bf68\",\"name\":\"aBluetint\",\"string\":\"BlueTint\"},{\"addr\":\"0x81db84\",\"name\":\"aGround\",\"string\":\"Ground\"},{\"addr\":\"0x82bf5c\",\"name\":\"aIonambient\",\"string\":\"IonAmbient\"},{\"addr\":\"0x82bf54\",\"name\":\"aIonred\",\"string\":\"IonRed\"},{\"addr\":\"0x82bf48\",\"name\":\"aIongreen\",\"string\":\"IonGreen\"},{\"addr\":\"0x82bf40\",\"name\":\"aIonblue\",\"string\":\"IonBlue\"},{\"addr\":\"0x82bf34\",\"name\":\"aIonground\",\"string\":\"IonGround\"},{\"addr\":\"0x82bf28\",\"name\":\"aIonlevel\",\"string\":\"IonLevel\"},{\"addr\":\"0x643c50\",\"name\":\"sub_643C50\"},{\"addr\":\"0xa8b230\",\"name\":\"ScenarioClass::Instance\"},{\"addr\":\"0x82af14\",\"name\":\"psub_48D1D0\"},{\"addr\":\"0x722390\",\"name\":\"sub_722390\"},{\"addr\":\"0x722e50\",\"name\":\"sub_722E50\"},{\"addr\":\"0xa8e7ac\",\"name\":\"Unsorted::IKnowWhatImDoing\"},{\"addr\":\"0x686700\",\"name\":\"sub_686700\"},{\"addr\":\"0x889f64\",\"name\":\"TagClass::DefaultTagStr\"},{\"addr\":\"0x6851f0\",\"name\":\"sub_6851F0\"},{\"addr\":\"0x686b20\",\"name\":\"INIClass::ReadScenario\"},{\"addr\":\"0x684c30\",\"name\":\"sub_684C30\"},{\"addr\":\"0x87f7e8\",\"name\":\"MouseClass::Instance\"},{\"addr\":\"0x68bf50\",\"name\":\"sub_68BF50\"},{\"addr\":\"0x68bcc0\",\"name\":\"ScenarioClass::GetWaypointCoords\"},{\"addr\":\"0x5657a0\",\"name\":\"MapClass::GetCellAt_MapCrd\"},{\"addr\":\"0x68bd00\",\"name\":\"sub_68BD00\"},{\"addr\":\"0x653f70\",\"name\":\"sub_653F70\"},{\"addr\":\"0x683610\",\"name\":\"ScenarioClass::Constructor\"},{\"addr\":\"0x7c8e17\",\"name\":\"??2@YAPAXI@Z\"},{\"addr\":\"0x6406e0\",\"name\":\"unknown_libname_27\"},{\"addr\":\"0x69ae90\",\"name\":\"sub_69AE90\"},{\"addr\":\"0x534450\",\"name\":\"sub_534450\"},{\"addr\":\"0x5bdf50\",\"name\":\"sub_5BDF50\"},{\"addr\":\"0x653f50\",\"name\":\"sub_653F50\"},{\"addr\":\"0x654490\",\"name\":\"sub_654490\"},{\"addr\":\"0x887324\",\"name\":\"TacticalClass::Instance\"},{\"addr\":\"0x6d1c20\",\"name\":\"sub_6D1C20\"},{\"addr\":\"0x6da980\",\"name\":\"sub_6DA980\"},{\"addr\":\"0x8b4118\",\"name\":\"dword_8B4118\"},{\"addr\":\"0x8b410c\",\"name\":\"dword_8B410C\"},{\"addr\":\"0xa83de8\",\"name\":\"InfantryClass::Array\"},{\"addr\":\"0x578350\",\"name\":\"sub_578350\"},{\"addr\":\"0x578290\",\"name\":\"MapClass::CellIteratorNext\"},{\"addr\":\"0x56d6e0\",\"name\":\"sub_56D6E0\"},{\"addr\":\"0x56c510\",\"name\":\"sub_56C510\"},{\"addr\":\"0x581f50\",\"name\":\"sub_581F50\"},{\"addr\":\"0x68bd60\",\"name\":\"sub_68BD60\"},{\"addr\":\"0x5349c0\",\"name\":\"sub_5349C0\"},{\"addr\":\"0x6686c0\",\"name\":\"sub_6686C0\"},{\"addr\":\"0x8871e0\",\"name\":\"RulesClass::Instance\"},{\"addr\":\"0x887048\",\"name\":\"INI_Rules\"},{\"addr\":\"0x689880\",\"name\":\"sub_689880\"},{\"addr\":\"0x4f54a0\",\"name\":\"HouseClass::CTOR\"},{\"addr\":\"0x500b40\",\"name\":\"sub_500B40\"},{\"addr\":\"0xa80228\",\"name\":\"HouseClass::Array\"},{\"addr\":\"0x71dca0\",\"name\":\"sub_71DCA0\"},{\"addr\":\"0x547110\",\"name\":\"sub_547110\"},{\"addr\":\"0x545150\",\"name\":\"IsometricTileTypeClass::ReadINI\"},{\"addr\":\"0x822cf8\",\"name\":\"Theater\"},{\"addr\":\"0x5fe620\",\"name\":\"sub_5FE620\"},{\"addr\":\"0x45e970\",\"name\":\"sub_45E970\"},{\"addr\":\"0x427940\",\"name\":\"sub_427940\"},{\"addr\":\"0x6b5490\",\"name\":\"sub_6B5490\"},{\"addr\":\"0x546da0\",\"name\":\"sub_546DA0\"},{\"addr\":\"0x7c8b3d\",\"name\":\"??3@YAXPAX@Z\"},{\"addr\":\"0xabed10\",\"name\":\"dword_ABED10\"},{\"addr\":\"0x89c2dc\",\"name\":\"dword_89C2DC\"},{\"addr\":\"0xabed14\",\"name\":\"dword_ABED14\"},{\"addr\":\"0xabdfa0\",\"name\":\"dword_ABDFA0\"},{\"addr\":\"0xabdf94\",\"name\":\"dword_ABDF94\"},{\"addr\":\"0xabdf90\",\"name\":\"dword_ABDF90\"},{\"addr\":\"0x5ad790\",\"name\":\"sub_5AD790\"},{\"addr\":\"0x7e38d0\",\"name\":\"??_7?$VectorClass@VCell@@@@6B@\"},{\"addr\":\"0x65c780\",\"name\":\"Randomizer::Random\"},{\"addr\":\"0xabe890\",\"name\":\"dst_\"},{\"addr\":\"0x655a90\",\"name\":\"MouseClass::Uninit\"},{\"addr\":\"0x6558d0\",\"name\":\"sub_6558D0\"},{\"addr\":\"0x654650\",\"name\":\"MouseClass::Reinit\"},{\"addr\":\"0x734e60\",\"name\":\"StringTable::LoadString\"},{\"addr\":\"0x82ba2c\",\"name\":\"aTxtRandomMapDe\",\"string\":\"TXT_RANDOM_MAP_DESCRIPTION\"},{\"addr\":\"0x82ba48\",\"name\":\"aDRa2mdpostMapg\",\"string\":\"D:\\\\ra2mdpost\\\\MapGen.cpp\"},{\"addr\":\"0x7ca489\",\"name\":\"_wcscpy\"},{\"addr\":\"0x7ca405\",\"name\":\"_wcslen\"},{\"addr\":\"0x5256f0\",\"name\":\"sub_5256F0\"}]}"}]

