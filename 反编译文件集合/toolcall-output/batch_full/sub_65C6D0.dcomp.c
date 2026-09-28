_DWORD *__thiscall sub_65C6D0(_DWORD *this, int a2)
{
  int v2; // eax
  int v3; // ebp
  int v4; // esi
  int n4; // ebx
  int v6; // eax
  int v7; // edx
  int v8; // ecx
  _DWORD *this_1; // eax
  int *v10; // [esp+10h] [ebp-14h]
  int n250; // [esp+14h] [ebp-10h]
  int v13; // [esp+20h] [ebp-4h]

  v2 = 0; /*0x65c6d3*/
  this[1] = 0; /*0x65c6da*/
  this[2] = 103; /*0x65c6dd*/
  v10 = this + 3; /*0x65c6ea*/
  n250 = 250; /*0x65c6ee*/
  while ( 1 ) /*0x65c6fc*/
  {
    v3 = a2; /*0x65c6fc*/
    v4 = v2; /*0x65c700*/
    n4 = 0; /*0x65c703*/
    v13 = v2 + 1; /*0x65c705*/
    do /*0x65c74f*/
    {
      v6 = v4; /*0x65c70f*/
      v7 = v4 ^ dword_839644[n4++]; /*0x65c711*/
      v8 = v3 /*0x65c746*/
         ^ (v7 * (v7 >> 16)
          + (dword_839690[n4]
           ^ (((v7 * v7 + ~((v7 >> 16) * (v7 >> 16))) << 16) | ((v7 * v7 + ~((v7 >> 16) * (v7 >> 16))) >> 16))));
      v4 = v8; /*0x65c74b*/
      v3 = v6; /*0x65c74d*/
    }
    while ( n4 < 4 ); /*0x65c74f*/
    *v10++ = v8; /*0x65c755*/
    if ( !--n250 ) /*0x65c767*/
      break; /*0x65c767*/
    v2 = v13; /*0x65c6f8*/
  }
  this_1 = this; /*0x65c769*/
  *this = 0; /*0x65c770*/
  return this_1; /*0x65c76d*/
}
