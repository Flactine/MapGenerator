char __stdcall sub_57A0C0(int a1, int a2)
{
  int v2; // esi
  void *v3; // eax
  void *v4; // ebx
  int v5; // esi
  _DWORD *v6; // edi
  int v7; // esi
  int v8; // esi
  int i; // edi
  int v10; // eax
  CellClass *v11; // eax
  char j; // bl
  CellClass *k; // eax
  CellClass *m; // eax
  CellClass *n; // eax
  char v17; // [esp+13h] [ebp-1h]

  sub_4A8BF0(&MouseClass::Instance, 0); /*0x57a0ce*/
  v17 = 0; /*0x57a0d8*/
  if ( !dword_ABED10 ) /*0x57a0df*/
  {
    v2 = dword_89C2DC * dword_89C2DC; /*0x57a0e7*/
    v3 = operator new(80 * dword_89C2DC * dword_89C2DC); /*0x57a0f1*/
    v4 = v3; /*0x57a0f6*/
    if ( v3 ) /*0x57a0fd*/
    {
      v5 = v2 - 1; /*0x57a0ff*/
      v6 = v3; /*0x57a100*/
      if ( v5 >= 0 ) /*0x57a104*/
      {
        v7 = v5 + 1; /*0x57a106*/
        do /*0x57a112*/
        {
          sub_58BDC0(v6); /*0x57a109*/
          v6 += 20; /*0x57a10e*/
          --v7; /*0x57a111*/
        }
        while ( v7 ); /*0x57a112*/
      }
      dword_ABED10 = v4; /*0x... [4892 chars total]