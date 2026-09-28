double __thiscall sub_5980C0(double *this)
{
  double v3; // st7
  double v4; // st7
  long double v5; // st7
  long double v6; // st6
  double v7; // st7
  double v8; // [esp+10h] [ebp-10h]
  double v9; // [esp+18h] [ebp-8h]

  if ( *this ) /*0x5980cc*/
  {
    *this = 0; /*0x5980d1*/
    return this[1]; /*0x5980d4*/
  }
  else
  {
    do /*0x598122*/
    {
      do /*0x598115*/
      {
        v3 = (*(this + 4))(); /*0x5980de*/
        v8 = v3 + v3 - 1.0; /*0x5980e9*/
        v4 = (*(this + 4))(); /*0x5980ed*/
        v9 = v4 + v4 - 1.0; /*0x5980f8*/
        v5 = v9 * v9 + v8 * v8; /*0x598108*/
      }
      while ( v5 >= 1.0 ); /*0x598115*/
    }
    while ( v5 == 0.0 ); /*0x598122*/
    v6 = __FYL2X__(v5, 0.6931471805599453094); /*0x59812d*/
    v7 = YRMath::sqrt((-v6 - v6) / v5); /*0x59813e*/
    *this = 1; /*0x59814c*/
    this[1] = v7 * v9; /*0x59814f*/
    return v7 * v8; /*0x598153*/
  }
}
