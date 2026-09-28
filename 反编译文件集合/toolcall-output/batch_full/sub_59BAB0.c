char __stdcall sub_59BAB0(__int16 *pMapCoord, int *a2, char a3, double a4, double a5)
{
  int v5; // esi
  int v7; // edx
  double v8; // st7
  double v9; // st6
  int v10; // eax
  int v11; // edx
  int v12; // eax

  v5 = *a2; /*0x59babb*/
  if ( *a2 == dword_ABE2F0 && a2[1] == dword_ABE2F4 && a2[2] == dword_ABE2F8 && a2[3] == dword_ABE2FC ) /*0x59bae5*/
    return 1; /*0x59baeb*/
  if ( a3 ) /*0x59baf4*/
  {
    v7 = pMapCoord[1]; /*0x59bb00*/
    v8 = (*pMapCoord - 2 * v5 - v7 + MouseClass::Instance.MapRect.Width - 1) * 0.5 - a2[2] * 0.5; /*0x59bb3f*/
    v9 = (*pMapCoord - 2 * a2[1] - MouseClass::Instance.MapRect.Width + v7 - 1) * 0.5 - a2[3] * 0.5; /*0x59bb54*/
    if ( v9 * v9 * a5 + v8 * v8 * a4 < 1.0 ) /*0x59bb77*/
      return 1; /*0x59bb80*/
  }
  else
  {
    v10 = *pMapCoord; /*0x59bb87*/
    v11 = pMapCoord[1]; /*0x59bb8a*/
    if ( v10 >= v5 && v10 < v5 + a2[2] ) /*0x59bb99*/
    {
      v12 = a2[1]; /*0x59bb9b*/
      if ( v11 >= v12 && v11 < v12 + a2[3] ) /*0x59bba9*/
        return 1; /*0x59bbb2*/
    }
  }
  return 0; /*0x59bae7*/
}