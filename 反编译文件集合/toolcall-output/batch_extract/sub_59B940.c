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

  if ( *a3 == dword_ABE2F0 && a3[1] == dword_ABE2F4 && a3[2] == dword_ABE2F8 && a3[3] == dword_ABE2FC ) /*0x59b979*/
  {
    v18 = *pMapCoord - *pMapCoorda; /*0x59ba7b*/
    v19 = pMapCoord[1] - pMapCoorda[1]; /*0x59ba7d*/
    return YRMath::sqrt((v18 * v18 + v19 * v19)); /*0x59ba94*/
  }
  else
  {
    v7 = p_MapCoords[1]; /*0x59b989*/
    v8 = *pMapCoorda; /*0x59b990*/
    v9 = pMa... [1940 chars total]