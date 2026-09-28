int __thiscall Randomizer::RandomRanged(_DWORD *this_pRandomizer, int min, int max)
{
  int min_1; // eax
  int nMax; // ecx
  int nMin; // ebx
  int nRange; // edi
  bool bHasRange; // zf
  int n31; // ecx
  int nRandomResult; // eax
  int i; // ebp
  int v12; // eax
  int n250; // eax
  int v14; // esi
  int n250_1; // ecx

  min_1 = min; /*0x65c7e0*/
  nMax = max; /*0x65c7e6*/
  nMin = min; /*0x65c7ed*/
  if ( min != max ) /*0x65c7ef*/
  {
    if ( min > max ) /*0x65c7f5*/
    {
      nMin = max; /*0x65c7f7*/
      nMax = min; /*0x65c7f9*/
    }
    nRange = nMax - nMin; /*0x65c7ff*/
    bHasRange = nMax - nMin >= 0; /*0x65c801*/
    n31 = 31; /*0x65c807*/
    if ( bHasRange ) /*0x65c80c*/
    {
      do /*0x65c81c*/
      {
        if ( n31 <= 0 ) /*0x65c810*/
          break; /*0x65c810*/
        --n31; /*0x65c812*/
      }
      while ( ((1 << n31) & nRange) == 0 ); /*0x65c81c*/
    }
    nRandomResult = nRange + 1; /*0x65c824*/
    for ( i = ~(-1 << (n31 + 1)); nRandomResult > nRange; nRandomResult = i & v12 ) /*0x65c82b*/
    {
      if ( *this_pRandomizer ) /*0x65c82e*/
      {
        v12 = 0; /*0x65c833*/
      }
      else
      {
        this_pRandomizer[this_pRandomizer[1] + 3] ^= this_pRandomizer[this_pRandomizer[2] + 3]; /*0x65c84b*/
        n250 = this_pRandomizer[1]; /*0x65c84d*/
        v14 = this_pRandomizer[n250++ + 3]; /*0x65c853*/
        n250_1 = this_pRandomizer[2] + 1; /*0x65c858*/
        this_pRandomizer[1] = n250; /*0x65c85e*/
        this_pRandomizer[2] = n250_1; /*0x65c861*/
        if ( n250 >= 250 ) /*0x65c864*/
          this_pRandomizer[1] = 0; /*0x65c866*/
        if ( n250_1 >= 250 ) /*0x65c873*/
          this_pRandomizer[2] = 0; /*0x65c875*/
        v12 = v14; /*0x65c87c*/
      }
    }
    return nMin + nRandomResult; /*0x65c886*/
  }
  return min_1; /*0x65c889*/
}
