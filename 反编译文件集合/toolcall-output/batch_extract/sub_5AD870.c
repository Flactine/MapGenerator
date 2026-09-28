void __thiscall sub_5AD870(int *this, int a2)
{
  int v2; // esi
  int v3; // edx
  int v4; // edi
  int v5; // eax
  int v6; // ebp
  int v7; // edi

  v2 = a2; /*0x5ad875*/
  v3 = 2 * a2; /*0x5ad87a*/
  v4 = 2 * a2 + 1; /*0x5ad87d*/
  if ( 2 * a2 > *this || *(*(this[2] + 4 * a2) + 4) <= *(*(this[2] + 8 * a2) + 4) ) /*0x5ad89b*/
    v3 = a2; /*0x5ad89d*/
  if ( v4 <= *this && *(*(this[2] + 4 * v3) + 4) > *(*(this[2] + 4 * v4) + 4) ) /*0x5ad8b9*/
    v3 = 2 * a2 + 1; /*0x5ad8bb*/
  if ( v3 != a2 ) /*0x5ad8bf*/
  {
    do /*0x5ad91f*/
    {
      v5 = this[2]; /*0x5ad8c1*/
      v6 = 2 * v3 + 1; /*0x5ad8c4*/
      v7 = *(v5 + 4 * v2); /*0x5ad8cb*/
      *(v5 + 4 * v2) = *(v5 + 4 * v3); /*0x5ad8ce*/
      v2 = v3; /*0x5ad8d4*/
      *(this[2] + 4 * v3) = v7; /*0x5ad8d6*/
      if ( 2 * v3 <= *this && *(*(this[2] + 4 * v3) + 4) > *(*(this[2] + 8 * v3) + 4) ) /*0x5ad8fb*/
        v3 *= 2; /*0x5ad8fd*/
      if ( v6 <= *this && *(*(this[2] + 4 * v3) + 4) > *(*(this[2] + 4 * v6) + 4) ) /*0x5... [1086 chars total]