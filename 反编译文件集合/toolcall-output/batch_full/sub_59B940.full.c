double __stdcall sub_59B940(
        __int16 *pMapCoord,
        __int16 *pMapCoorda,
        _DWORD *a3,
        __int16 *p_MapCoords,
        float a5,
        float a6)
{
  int v7; // ebp
  int v8; // ebx
  int v9; // edi
  unsigned int v10; // ecx
  __int64 v11; // rax
  int p_MapCoordsa_1; // eax
  double v14; // st7
  signed int v15; // ecx
  __int64 v16; // rax
  double v17; // st7
  int v18; // eax
  int v19; // edx
  double v20; // [esp+10h] [ebp-8h]
  int v21; // [esp+1Ch] [ebp+4h]
  int pMapCoordb; // [esp+20h] [ebp+8h]
  int v23; // [esp+24h] [ebp+Ch]
  int p_MapCoordsa; // [esp+28h] [ebp+10h]

  if ( *a3 == dword_ABE2F0 && a3[1] == dword_ABE2F4 && a3[2] == dword_ABE2F8 && a3[3] == dword_ABE2FC )
  {
    v18 = *pMapCoord - *pMapCoorda;
    v19 = pMapCoord[1] - pMapCoorda[1];
    return YRMath::sqrt((v18 * v18 + v19 * v19));
  }
  else
  {
    v7 = p_MapCoords[1];
    v8 = *pMapCoorda;
    v9 = pMapCoorda[1];
    pMapCoordb = *p_MapCoords;
    v10 = abs32(((v8 - v9) >> 1) - ((pMapCoordb - v7) >> 1));
    v23 = v10;
    v11 = ((v8 + v9) >> 1) - ((v7 + pMapCoordb) >> 1);
    p_MapCoordsa_1 = (HIDWORD(v11) ^ v11) - HIDWORD(v11);
    p_MapCoordsa = p_MapCoordsa_1;
    if ( v10 || p_MapCoordsa_1 )
    {
      v14 = YRMath::sqrt((v10 * v10 + p_MapCoordsa_1 * p_MapCoordsa_1));
      v15 = abs32(pMapCoord[1] - pMapCoorda[1]);
      v16 = *pMapCoord - *pMapCoorda;
      v21 = (HIDWORD(v16) ^ v16) - HIDWORD(v16);
      v20 = v23 / v14;
      v17 = p_MapCoordsa / v14;
      if ( v21 <= v15 )
        v21 = v15;
      return (v17 * a6 + a5 * v20) * v21;
    }
    else
    {
      return 0.0;
    }
  }
}
