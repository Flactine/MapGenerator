char __thiscall sub_598960(_DWORD *this, char a2, HWND hDlg)
{
  HWND hWnd; // eax
  int n3; // eax
  int v6; // ecx
  int v7; // eax
  int i; // esi
  void *v9; // ecx
  void *v10; // ecx
  int j; // edi
  int v12; // esi
  int n3_1; // eax
  bool v14; // al
  int n4; // eax
  CellClass *k; // eax
  int v17; // ecx
  int v18; // eax
  int m; // edi
  _DWORD *MapCoords_2; // esi
  int v21; // eax
  void *v22; // eax
  CellClass *n; // eax
  LRESULT (__stdcall *SendMessageA)(HWND, UINT, WPARAM, LPARAM); // esi
  CellClass *ii; // eax
  _DWORD *this_2; // edi
  CellClass *jj; // eax
  _DWORD *v28; // eax
  CellClass *kk; // eax
  int mm; // edi
  _DWORD *MapCoords_1; // esi
  int v32; // eax
  char result; // al
  HWND hWnd_1; // eax
  bool v35; // [esp+11h] [ebp-415h]
  _DWORD *MapCoords; // [esp+12h] [ebp-414h] BYREF
  _DWORD *this_1; // [esp+16h] [ebp-410h]
  _DWORD src_[6]; // [esp+1Ah] [ebp-40Ch] BYREF
  _DWORD v39[253]; // [esp+32h] [ebp-3F4h] BYREF

  this_1 = this; /*0x598973*/
  if ( psub_48D1D0 ) /*0x598977*/
    psub_48D1D0(); /*0x598979*/
  qmemcpy(&dst_, sub_65C6D0(v39, this[29]), 0x3F4u); /*0x59899b*/
  LOBYTE(src_[0]) = 0; /*0x5989ab*/
  src_[2] = 0; /*0x5989af*/
  src_[3] = 0; /*0x5989b7*/
  src_[4] = sub_598000; /*0x5989bf*/
  qmemcpy(&dst__0, src_, 0x18u); /*0x5989c9*/
  if ( psub_48D1D0 ) /*0x5989cb*/
    psub_48D1D0(); /*0x5989cd*/
  v35 = LOBYTE(ScenarioClass::Instance->unknown_3598) == 0; /*0x5989e7*/
  if ( !LOBYTE(ScenarioClass::Instance->unknown_3598) ) /*0x5989dc*/
  {
    sub_642A60(&dword_AC4F58, 0, 1079574528, 1, hDlg); /*0x5989fb*/
    sub_642C20(aProgbar2Shp, 0, 0); // "PROGBAR2.SHP" /*0x598a0c*/
    sub_642C80(-1, -1, 0, 0, 1); /*0x598a22*/
    sub_643AE0(NAN); /*0x598a34*/
    hWnd = GetDlgItem(hDlg, 1592); /*0x598a3f*/
    if ( hWnd ) /*0x598a47*/
      ShowWindow(hWnd, 5); /*0x598a4c*/
  }
  if ( psub_48D1D0 ) /*0x598a59*/
    psub_48D1D0(); /*0x598a5b*/
  nullsub_1(); /*0x598a62*/
  sub_599650(this, a2); /*0x598a74*/
  if ( psub_48D1D0 ) /*0x598a80*/
    psub_48D1D0(); /*0x598a82*/
  ++Unsorted::IKnowWhatImDoing; /*0x598a9a*/
  if ( a2 ) /*0x598aa0*/
  {
    sub_641140(dword_ABE154); /*0x598aa8*/
    ::SendMessageA(hDlg, 0xFu, 0, 0); /*0x598ab2*/
    if ( SessionClass::Instance::GameMode == GameMode_Internet && n2 == 3 ) /*0x598ac4*/
      sub_5E7EB0(dword_ABE154); /*0x598acc*/
  }
  if ( psub_48D1D0 ) /*0x598ad8*/
    psub_48D1D0(); /*0x598ada*/
  sub_5981F0(this); /*0x598ade*/
  nullsub_1(); /*0x598ae8*/
  n3 = this[15]; /*0x598aed*/
  if ( n3 == 3 || n3 == 4 ) /*0x598afb*/
  {
    if ( this[19] ) /*0x598b06*/
      sub_59C580(this); /*0x598b0d*/
  }
  else
  {
    sub_59A6C0(this); /*0x598aff*/
  }
  sub_59C630(this); /*0x598b14*/
  if ( LOBYTE(ScenarioClass::Instance->unknown_3598) ) /*0x598b1e*/
    sub_69AE90(154); /*0x598b30*/
  else
    sub_643C50(0, 55.0, NAN); /*0x598b4b*/
  if ( psub_48D1D0 ) /*0x598b57*/
    psub_48D1D0(); /*0x598b59*/
  if ( a2 ) /*0x598b62*/
  {
    sub_641140(dword_ABE154); /*0x598b6a*/
    ::SendMessageA(hDlg, 0xFu, 0, 0); /*0x598b74*/
    if ( SessionClass::Instance::GameMode == GameMode_Internet && n2 == 3 ) /*0x598b86*/
      sub_5E7EB0(dword_ABE154); /*0x598b8e*/
  }
  if ( psub_48D1D0 ) /*0x598b9a*/
    psub_48D1D0(); /*0x598b9c*/
  if ( LOBYTE(ScenarioClass::Instance->unknown_3598) ) /*0x598ba4*/
    sub_69AE90(159); /*0x598bb6*/
  else
    sub_643C50(0, 60.0, NAN); /*0x598bd1*/
  if ( psub_48D1D0 ) /*0x598bdd*/
    psub_48D1D0(); /*0x598bdf*/
  if ( a2 ) /*0x598be8*/
  {
    sub_641140(dword_ABE154); /*0x598bf0*/
    ::SendMessageA(hDlg, 0xFu, 0, 0); /*0x598bfa*/
    if ( SessionClass::Instance::GameMode == GameMode_Internet && n2 == 3 ) /*0x598c0c*/
      sub_5E7EB0(dword_ABE154); /*0x598c14*/
  }
  if ( psub_48D1D0 ) /*0x598c20*/
    psub_48D1D0(); /*0x598c22*/
  nullsub_1(); /*0x598c29*/
  if ( dword_ABED10 ) /*0x598c38*/
  {
    v6 = dword_89C2DC * dword_89C2DC; /*0x598c40*/
    if ( dword_89C2DC * dword_89C2DC > 0 ) /*0x598c45*/
    {
      v7 = 0; /*0x598c47*/
      do /*0x598c64*/
      {
        *(dword_ABED10 + v7 + 56) = -1; /*0x598c52*/
        *(dword_ABED10 + v7 + 60) = -1; /*0x598c5c*/
        v7 += 80; /*0x598c60*/
        --v6; /*0x598c63*/
      }
      while ( v6 ); /*0x598c64*/
    }
  }
  for ( i = dword_ABDFA0 - 1; i >= 0; --i ) /*0x598c71*/
  {
    v9 = *(dword_ABDF94 + i); /*0x598c78*/
    if ( v9 ) /*0x598c7d*/
      sub_5AC290(v9, 1); /*0x598c81*/
  }
  dword_ABED14 = 0; /*0x598c89*/
  sub_58CF90(); /*0x598c8f*/
  for ( j = 0; j < dword_ABDFA0; ++j ) /*0x598c9d*/
  {
    v10 = dword_ABDF94; /*0x598ca4*/
    v12 = *(dword_ABDF94 + j); /*0x598caa*/
    if ( *(v12 + 20) ) /*0x598cad*/
    {
      n3_1 = this_1[15]; /*0x598cb6*/
      v14 = n3_1 == 3 || n3_1 == 4; /*0x598cc7*/
      sub_58E740((*(v12 + 12) > 8000) + !v14 + 4); /*0x598ce4*/
      sub_58E9B0(v12); /*0x598ceb*/
    }
  }
  LOBYTE(v10) = 0; /*0x598cfa*/
  sub_58D010(v10); /*0x598cfc*/
  if ( LOBYTE(ScenarioClass::Instance->unknown_3598) ) /*0x598d07*/
    sub_69AE90(164); /*0x598d19*/
  else
    sub_643C50(0, 65.0, NAN); /*0x598d34*/
  if ( psub_48D1D0 ) /*0x598d40*/
    psub_48D1D0(); /*0x598d42*/
  nullsub_1(); /*0x598d49*/
  n4 = this_1[15]; /*0x598d55*/
  if ( n4 == 4 || n4 == 3 ) /*0x598d60*/
  {
    sub_58EBC0(); /*0x598d62*/
    sub_58EF10(); /*0x598d67*/
    sub_5A19E0(this_1); /*0x598d6e*/
    sub_578E60(0, -1); /*0x598d7b*/
    sub_5A17F0(this_1); /*0x598d82*/
  }
  if ( LOBYTE(ScenarioClass::Instance->unknown_3598) ) /*0x598d8d*/
    sub_69AE90(169); /*0x598d9f*/
  else
    sub_643C50(0, 70.0, NAN); /*0x598dba*/
  if ( psub_48D1D0 ) /*0x598dc6*/
    psub_48D1D0(); /*0x598dc8*/
  if ( a2 ) /*0x598dd1*/
  {
    sub_641140(dword_ABE154); /*0x598dd9*/
    ::SendMessageA(hDlg, 0xFu, 0, 0); /*0x598dea*/
    if ( SessionClass::Instance::GameMode == GameMode_Internet && n2 == 3 ) /*0x598e00*/
      sub_5E7EB0(dword_ABE154); /*0x598e08*/
  }
  if ( psub_48D1D0 ) /*0x598e14*/
    psub_48D1D0(); /*0x598e16*/
  sub_59B740(this_1); /*0x598e1a*/
  nullsub_1(); /*0x598e24*/
  sub_578350(&MouseClass::Instance); /*0x598e31*/
  for ( k = MapClass::CellIteratorNext(&MouseClass::Instance); k; k = MapClass::CellIteratorNext(&MouseClass::Instance) ) /*0x598e42*/
    sub_47D2B0(k, -1); /*0x598e48*/
  if ( psub_48D1D0 ) /*0x598e62*/
    psub_48D1D0(); /*0x598e64*/
  if ( LOBYTE(ScenarioClass::Instance->unknown_3598) ) /*0x598e6c*/
    sub_69AE90(174); /*0x598e7e*/
  else
    sub_643C50(0, 75.0, NAN); /*0x598e99*/
  nullsub_1(); /*0x598ea3*/
  do /*0x598ebd*/
  {
    while ( !sub_594B50() ) /*0x598eb2*/
      ; /*0x598eab*/
  }
  while ( !sub_5A1FB0(this_1) ); /*0x598ebd*/
  nullsub_1(); /*0x598ec4*/
  if ( this_1[15] ) /*0x598ec9*/
    sub_5A95B0(this_1); /*0x598ed5*/
  if ( psub_48D1D0 ) /*0x598ee1*/
    psub_48D1D0(); /*0x598ee3*/
  nullsub_1(); /*0x598eea*/
  sub_5A23A0(this_1); /*0x598ef4*/
  if ( psub_48D1D0 ) /*0x598f00*/
    psub_48D1D0(); /*0x598f02*/
  if ( dword_ABED10 ) /*0x598f0a*/
  {
    v17 = dword_89C2DC * dword_89C2DC; /*0x598f12*/
    if ( dword_89C2DC * dword_89C2DC > 0 ) /*0x598f17*/
    {
      v18 = 0; /*0x598f19*/
      do /*0x598f36*/
      {
        *(dword_ABED10 + v18 + 56) = -1; /*0x598f24*/
        *(dword_ABED10 + v18 + 60) = -1; /*0x598f2e*/
        v18 += 80; /*0x598f32*/
        --v17; /*0x598f35*/
      }
      while ( v17 ); /*0x598f36*/
    }
  }
  for ( m = dword_ABDFA0 - 1; m >= 0; --m ) /*0x598f48*/
  {
    MapCoords_2 = *(dword_ABDF94 + m); /*0x598f4f*/
    if ( MapCoords_2 ) /*0x598f54*/
    {
      if ( *MapCoords_2 ) /*0x598f56*/
      {
        (***MapCoords_2)(*MapCoords_2, 1); /*0x598f60*/
        *MapCoords_2 = 0; /*0x598f62*/
      }
      MapCoords = MapCoords_2; /*0x598f74*/
      v21 = (*(dword_ABDF90 + 16))(&dword_ABDF90, &MapCoords); /*0x598f78*/
      if ( v21 != -1 ) /*0x598f7e*/
        sub_5AD790(&dword_ABDF90, v21); /*0x598f86*/
      v22 = MapCoords_2[11]; /*0x598f8b*/
      MapCoords_2[10] = &VectorClass<Cell>::`vftable'; /*0x598f8e*/
      if ( v22 && *(MapCoords_2 + 53) ) /*0x598f95*/
      {
        operator delete(v22); /*0x598f9b*/
        MapCoords_2[11] = 0; /*0x598fa3*/
      }
      *(MapCoords_2 + 53) = 0; /*0x598fa7*/
      MapCoords_2[12] = 0; /*0x598faa*/
      operator delete(MapCoords_2); /*0x598fad*/
    }
  }
  dword_ABED14 = 0; /*0x598fbd*/
  nullsub_1(); /*0x598fc3*/
  sub_578350(&MouseClass::Instance); /*0x598fd0*/
  for ( n = MapClass::CellIteratorNext(&MouseClass::Instance); n; n = MapClass::CellIteratorNext(&MouseClass::Instance) ) /*0x598fe1*/
    sub_47D2B0(n, -1); /*0x598fe7*/
  if ( LOBYTE(ScenarioClass::Instance->unknown_3598) ) /*0x598fff*/
    sub_69AE90(179); /*0x599011*/
  else
    sub_643C50(0, 80.0, NAN); /*0x59902c*/
  if ( psub_48D1D0 ) /*0x599038*/
    psub_48D1D0(); /*0x59903a*/
  if ( a2 ) /*0x599043*/
  {
    sub_641140(dword_ABE154); /*0x59904b*/
    SendMessageA = ::SendMessageA; /*0x599057*/
    ::SendMessageA(hDlg, 0xFu, 0, 0); /*0x599062*/
    if ( SessionClass::Instance::GameMode == GameMode_Internet && n2 == 3 ) /*0x599079*/
      sub_5E7EB0(dword_ABE154); /*0x599081*/
  }
  else
  {
    SendMessageA = ::SendMessageA; /*0x599088*/
  }
  if ( psub_48D1D0 ) /*0x59909a*/
    psub_48D1D0(); /*0x59909c*/
  if ( LOBYTE(ScenarioClass::Instance->unknown_3598) ) /*0x5990a4*/
    sub_69AE90(184); /*0x5990b6*/
  else
    sub_643C50(0, 85.0, NAN); /*0x5990d1*/
  if ( psub_48D1D0 ) /*0x5990dd*/
    psub_48D1D0(); /*0x5990df*/
  if ( a2 ) /*0x5990e8*/
  {
    sub_641140(dword_ABE154); /*0x5990f0*/
    SendMessageA(hDlg, 0xFu, 0, 0); /*0x599101*/
    if ( SessionClass::Instance::GameMode == GameMode_Internet && n2 == 3 ) /*0x599112*/
      sub_5E7EB0(dword_ABE154); /*0x59911a*/
  }
  if ( psub_48D1D0 ) /*0x599126*/
    psub_48D1D0(); /*0x599128*/
  nullsub_1(); /*0x59912f*/
  sub_578350(&MouseClass::Instance); /*0x59913c*/
  for ( ii = MapClass::CellIteratorNext(&MouseClass::Instance); ii; ii = MapClass::CellIteratorNext(&MouseClass::Instance) ) /*0x59914d*/
    sub_47D2B0(ii, -1); /*0x599153*/
  if ( psub_48D1D0 ) /*0x59916d*/
    psub_48D1D0(); /*0x59916f*/
  nullsub_1(); /*0x599176*/
  this_2 = this_1; /*0x59917b*/
  sub_5A35F0(this_1); /*0x599184*/
  if ( LOBYTE(ScenarioClass::Instance->unknown_3598) ) /*0x59918f*/
    sub_69AE90(189); /*0x5991a1*/
  else
    sub_643C50(0, 90.0, NAN); /*0x5991bc*/
  if ( psub_48D1D0 ) /*0x5991c8*/
    psub_48D1D0(); /*0x5991ca*/
  if ( a2 ) /*0x5991d3*/
  {
    sub_641140(dword_ABE154); /*0x5991db*/
    SendMessageA(hDlg, 0xFu, 0, 0); /*0x5991ec*/
    if ( SessionClass::Instance::GameMode == GameMode_Internet && n2 == 3 ) /*0x5991fd*/
      sub_5E7EB0(dword_ABE154); /*0x599205*/
  }
  if ( psub_48D1D0 ) /*0x599211*/
    psub_48D1D0(); /*0x599213*/
  nullsub_1(); /*0x59921a*/
  if ( this_2[14] ) /*0x59921f*/
  {
    sub_578350(&MouseClass::Instance); /*0x59923e*/
    for ( jj = MapClass::CellIteratorNext(&MouseClass::Instance); jj; jj = MapClass::CellIteratorNext(&MouseClass::Instance) ) /*0x59924f*/
    {
      MapCoords = jj->MapCoords; /*0x59925a*/
      v28 = dword_ABED10 + 80 * MapCoords + 80 * dword_89C2DC * SHIWORD(MapCoords); /*0x59927b*/
      v28[10] = 1202590843; /*0x599283*/
      v28[11] = 1064598241; /*0x599286*/
      v28[8] = -755914244; /*0x599295*/
      v28[9] = 1062232653; /*0x599298*/
    }
    sub_5A4280(this_2); /*0x5992ab*/
  }
  else
  {
    sub_5A38C0(this_2); /*0x59922b*/
    sub_5A3AE0(this_2); /*0x599232*/
  }
  if ( psub_48D1D0 ) /*0x5992b7*/
    psub_48D1D0(); /*0x5992b9*/
  if ( LOBYTE(ScenarioClass::Instance->unknown_3598) ) /*0x5992c1*/
    sub_69AE90(194); /*0x5992d3*/
  else
    sub_643C50(0, 95.0, NAN); /*0x5992ee*/
  if ( psub_48D1D0 ) /*0x5992fa*/
    psub_48D1D0(); /*0x5992fc*/
  if ( a2 ) /*0x599305*/
  {
    sub_641140(dword_ABE154); /*0x59930d*/
    SendMessageA(hDlg, 0xFu, 0, 0); /*0x59931e*/
    if ( SessionClass::Instance::GameMode == GameMode_Internet && n2 == 3 ) /*0x59932f*/
      sub_5E7EB0(dword_ABE154); /*0x599337*/
  }
  --Unsorted::IKnowWhatImDoing; /*0x59934a*/
  if ( psub_48D1D0 ) /*0x599350*/
    psub_48D1D0(); /*0x599352*/
  nullsub_1(); /*0x599359*/
  sub_578350(&MouseClass::Instance); /*0x599366*/
  for ( kk = MapClass::CellIteratorNext(&MouseClass::Instance); kk; kk = MapClass::CellIteratorNext(&MouseClass::Instance) ) /*0x599377*/
    sub_47D2B0(kk, -1); /*0x59937d*/
  if ( psub_48D1D0 ) /*0x599397*/
    psub_48D1D0(); /*0x599399*/
  sub_722D00(); /*0x59939b*/
  sub_722240(); /*0x5993a0*/
  nullsub_1(); /*0x5993aa*/
  this_2[193] = 0; /*0x5993af*/
  this_2[194] = 0; /*0x5993b5*/
  if ( dword_ABED10 ) /*0x5993c5*/
  {
    operator delete(dword_ABED10); /*0x5993c8*/
    dword_ABED10 = 0; /*0x5993d0*/
  }
  for ( mm = dword_ABDFA0 - 1; mm >= 0; --mm ) /*0x5993e1*/
  {
    MapCoords_1 = *(dword_ABDF94 + mm); /*0x5993e9*/
    if ( MapCoords_1 ) /*0x5993ee*/
    {
      if ( *MapCoords_1 ) /*0x5993f0*/
      {
        (***MapCoords_1)(*MapCoords_1, 1); /*0x5993fa*/
        *MapCoords_1 = 0; /*0x5993fc*/
      }
      MapCoords = MapCoords_1; /*0x59940e*/
      v32 = (*(dword_ABDF90 + 16))(&dword_ABDF90, &MapCoords); /*0x599412*/
      if ( v32 != -1 ) /*0x599418*/
        sub_5AD790(&dword_ABDF90, v32); /*0x599420*/
      MapCoords_1[10] = &VectorClass<Cell>::`vftable'; /*0x599428*/
      sub_42F7C0((MapCoords_1 + 10)); /*0x59942e*/
      operator delete(MapCoords_1); /*0x599434*/
    }
  }
  dword_ABED14 = 0; /*0x599446*/
  sub_568BB0(&MouseClass::Instance, 1); /*0x59944c*/
  nullsub_1(); /*0x599456*/
  sub_654490(&MouseClass::Instance, &MouseClass::Instance.VisibleRect); /*0x599468*/
  MouseClass::Reinit(&MouseClass::Instance); /*0x599472*/
  if ( LOBYTE(ScenarioClass::Instance->unknown_3598) ) /*0x59947e*/
    sub_69AE90(199); /*0x599490*/
  else
    sub_643C50(0, 100.0, NAN); /*0x5994ab*/
  nullsub_1(); /*0x5994b5*/
  result = v35; /*0x5994ba*/
  if ( v35 ) /*0x5994c3*/
  {
    hWnd_1 = GetDlgItem(hDlg, 1592); /*0x5994d2*/
    if ( hWnd_1 ) /*0x5994da*/
      ShowWindow(hWnd_1, 0); /*0x5994de*/
    if ( LOBYTE(ScenarioClass::Instance->unknown_3598) ) /*0x5994ea*/
      sub_69AE90(99); /*0x5994f9*/
    else
      sub_643C50(0, 0.0, NAN); /*0x599510*/
    return sub_643E70(&dword_AC4F58); /*0x59951a*/
  }
  return result; /*0x59951f*/
}
